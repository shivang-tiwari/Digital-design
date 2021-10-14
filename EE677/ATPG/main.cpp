// हर हर महादेव
/*
EE 677 - ATPG
Name - Shivang Tiwari
Language - C++17
Netlist format - 
----------------------------------------------------------------------------------------------
<output_node_1><space><gate_type><space><input_node_1><space><intput_node_2>...
<output_node_2><space><gate_type><space><input_node_1><space><intput_node_2>...
.
.
.
end
<fault_location><space><fault_type>
----------------------------------------------------------------------------------------------
Warning !!! Unwanted spaces will give memory and runtime errors

Logic encoding is performed as follows
0  ->  0
1  ->  1
X  -> -1
D  ->  2
D' ->  3

Gate decoding is done as follows
AND -> 0
OR  -> 1
NOT -> 2

This program detects stuck at faults using the PODEM algorithm
*/


#include <bits/stdc++.h>
using namespace std;
//------------------------------Global Variables--------------------------------------------------//
int node_count,fault_location,fault_type;
map<int,int> ots; // Gate type of output nodes
map<int,int> type; // 0 for input, 2 for output and 1 for intermediate
vector<vector<int>> graph; // Connection of node to its dependencies
vector<vector<pair<int,int>>> rgraph; // Connection of node to its forward gates
vector<int> value,fault;
vector<int> inps,outs,order,level;
vector<int> path;
//------------------------------Basic helper functions--------------------------------------------------//
vector<string> split(string str){ // Split a string by spaces
	string word = "";
	vector<string> ans;
	for (auto x : str){
		if (x == ' '){
			ans.push_back(word);
			word = "";
		}
		else{
			word = word + x;
		}
	}
	ans.push_back(word);
	return ans;
}
int deduce(string s){ // Decode gate into number
	if(s == "AND")return 0;
	if(s == "OR")return 1;
	if(s == "NOT")return 2;
	cerr << "Invalid gate type" << endl;
	exit(0);
	return -1;
}
//This detects cycle in a ***directed graph***
//Ref - https://www.geeksforgeeks.org/detect-cycle-in-a-graph/
bool isCyclic(vector<vector<int>> &adj){
	int V = adj.size();
	bool *visited = new bool[V];
	bool *recStack = new bool[V];
	for(int i = 0; i < V; i++){
		visited[i] = false;
		recStack[i] = false;
	}
	function<bool(int)> cycle = [&](int v){
			if(visited[v] == false){
				visited[v] = true;
				recStack[v] = true;
				for(int i : adj[v]){
					if (!visited[i] && cycle(i))return true;
					else if (recStack[i])return true;
				}
			}
			recStack[v] = false;
			return false;
	};
	for(int i = 0; i < V; i++){
		if(cycle(i))return true;
	}
	return false;
}
//------------------------------Initialising--------------------------------------------------//
void init(){ // Initialise the program
	node_count = 0;
	ots.clear();
	type.clear();
	graph.clear();
	rgraph.clear();
	value.clear();
	fault.clear();
	order.clear();
	level.clear();
}
//------------------------------Logic gates--------------------------------------------------//
int inverse(int x){ // NOT gate
	if(x == -1)return -1;
	return x^1;
}
int and_gate(vector<int> inp){ // AND gate
	for(int x : inp){
		if(x == 0)return 0;
	}
	for(int x : inp){
		if(x == -1)return -1;
	}
	for(int x : inp){
		if(x == 2)return 2;
	}
	for(int x : inp){
		if(x == 3)return 3;
	}
	return 1;
}
int or_gate(vector<int> inp){ // OR gate
	for(int x : inp){
		if(x == 1)return 1;
	}
	for(int x : inp){
		if(x == -1)return -1;
	}
	for(int x : inp){
		if(x == 3)return 3;
	}
	for(int x : inp){
		if(x == 2)return 2;
	}
	return 0;
}
//------------------------------Input processors--------------------------------------------------//
void input_netlist(){
	vector<pair<int,vector<int>>> all; // <Output,Inputs> pairs
	while(true){
		string s;
		getline(cin,s);
		if(s == "end")break; // Netlist has been provided
		vector<string> line = split(s);
		int ot_node = stoi(line[0]);
		node_count = max(node_count,1+ot_node);
		int gate_type = deduce(line[1]);
		if(ots.find(ot_node) != ots.end()){ // Only one definition of an output node is possible
			cerr << "Conflicting definitions of node " << ot_node << endl;
			exit(0);
		}
		ots[ot_node] = gate_type;
		vector<int> ids;
		for(string x : vector<string>(line.begin()+2,line.end())){
			int num = stoi(x);
			if(type.find(num) == type.end()){ // First time seeing this node, assigning it to be input node
				type[num] = 0;
			}
			else{
				if(type[num] == 2)type[num] = 1;// Already seen this input node as some output node so it is an intermediate node
			}
			node_count = max(node_count,num);
			ids.push_back(num);
		}
		if(type.find(ot_node) != type.end()){ // Already seen this output node as some input node so it is an intermediate node
			type[ot_node] = 1;
		}
		else{
			type[ot_node] = 2; // Otherwise output node
		}
		all.push_back({ot_node,ids});
	}
	graph.resize(node_count+1);
	rgraph.resize(node_count+1);
	value.resize(node_count+1,-1);
	for(auto &x : all){
		for(int y : x.second){
			graph[x.first].push_back(y); // Connecting each node to its dependencies
			rgraph[y].push_back({x.first,ots[x.first]});
		}
	}
	if(isCyclic(graph)){ // Cycle can't be present in the graph
		cerr << "The netlist is not valid" << endl;
		exit(0);
	}
	for(int i = 0; i < node_count; i++){
		if(rgraph[i].empty()){
			outs.push_back(i);
		}
		if(graph[i].empty()){
			inps.push_back(i);
		}
	}
}
void input_fault(){ // Format is <fault_location><space><fault_type>
	fault.resize(node_count+1,-1);
	cin >> fault_location >> fault_type;
	if(fault_type != 0 && fault_type != 1){
		cerr << "Invalid fault type " << fault_type << endl;
		exit(0);
	}
	fault[fault_location] = fault_type;
}
//------------------------------Circuit simulation--------------------------------------------------//
void levelize(){ // Levelises the circuit and stores the order in the 'order' vector
	level.resize(node_count);
	order.resize(node_count);
	function<void(int)> dfs = [&](int i){
		if(graph[i].empty()){
			level[i] = 0;
		}
		for(int x : graph[i]){
			dfs(x);
			level[i] = max(level[i],1+level[x]); // Level of parent = 1 + level of child
		}
	};
	for(int ot : outs){
		dfs(ot); // Running the depth first search on all outputs
	}
	iota(order.begin(),order.end(),0);
	sort(order.begin(),order.end(),[&](const auto &v1,const auto &v2){
		return level[v1] < level[v2]; // Sorting about the level
	});
	
}
void find_output(){ // Simulates the circuit in level order
	for(int i : order){
		if(graph[i].empty())continue;
		int ans;
		vector<int> inp;
		for(int y : graph[i])inp.push_back(value[y]);
		switch(ots[i]){
			case 0: // AND gate
				assert((int)inp.size() >= 2);
				ans = and_gate(inp);
				break;
			case 1: // OR gate
				assert((int)inp.size() >= 2);
				ans = or_gate(inp);
				break;
			case 2: // NOT gate
				assert((int)graph[i].size() == 1);
				ans = inverse(value[graph[i][0]]);
				break;
			default:
				assert(false);
		}
		// Checking if the node is faulty
		if(ans == 0 && fault[i] == 1){
			ans = 2;
		}
		if(ans == 1 && fault[i] == 0){
			ans = 3;
		}
		value[i] = ans;
	}
}
//------------------------------PODEM functions--------------------------------------------------//
void find_path(){ // Finds a path to primary inputs
	path.clear();
	for(int i = 0; i < node_count; i++){
		if(value[i] != -1)continue;
		for(int x : graph[i]){
			if(value[x] > 1){
				path.push_back(i);
				break;
			}
		}
	}
}
bool getObjective(int &node, int &val){ // Gets the objective as (node,value)
	if(value[fault_location] == -1){
		node = fault_location;
		val = (!fault_type)+2;
		return true;
	}
	if(value[fault_location] <= 1){
		return false;
	}
	find_path();
	if(path.empty())return false;
	int d = path[0];
	for(int x : graph[d]){
		if(value[x] == -1){
			node = x;
			break;
		}
	}
	if(ots[d] == 0) val = 1;
	else if(ots[d] == 1) val = 0;
	else val = -1;
	return true;
}
void backtrace(int node,int val,int &pi, int &pival){ // Backtracing to primary inputs
	pi = node;
	int gate_type = ots[pi];
	int inv = gate_type == 2;
	while(!graph[pi].empty()){
		for(int x : graph[pi]){
			if(value[x] == -1){
				pi = x;
				break;
			}
		}
		gate_type = ots[pi];
		inv += (gate_type == 2);
	}
	pival = val&1;
	if(inv&1)pival = !pival;
}
void set_value(int node, int val){ // Sets node to val after checking for faults
	if((fault[node] == 0) && (val == 1)){
		value[node] = 3;
	}
	else if ((fault[node] == 0) && (val == 2)) {
		value[node] = 0;
	}
	else if ((fault[node] == 1) && (val == 0)){
		value[node] = 2;
	}
	else if ((fault[node] == 1) && (val == 3)){
		value[node] = 1;
	}
	else{
		value[node] = val;
	}
}
bool PODEM(){
	for(int x : outs){
		if(value[x] > 1)return true; // If fault has propogated to output then return true
	}
	int node,val;
	if(!getObjective(node,val)){
		return false; // No test possible
	}
	int pi,pival;
	backtrace(node,val,pi,pival); // Backtracing to primary inputs and finding the required assignment in pival
	set_value(pi,pival); // Set primary input to desired value
	find_output(); // Simulate the circuit
	if(PODEM())return true; // Recursively check for fault detection at output
	set_value(pi,inverse(pival)); // Otherwise set primary input to opposite value
	find_output(); // Simulate the circuit
	if(PODEM())return true;// Recursively check for fault detection at output
	set_value(pi,-1); // Reset primary input to X
	return false;
}
//------------------------------Main--------------------------------------------------//
int main(){
	init();
	input_netlist();
	levelize();
	input_fault();
	if(PODEM()){
		cout << "The test vector to detect stuck at " << fault_type << " fault at node " << fault_location << " is" << endl;
		for(int x : inps){
			cout << x << " -> " << (value[x]&1) << '\n';
		}
	}
	else{
		cout << "The stuck at " << fault_type << " fault at node " << fault_location << " cannot be detected" << endl;
	}
	return 0;
}
//------------------------------Some examples--------------------------------------------------//
/*
2 AND 0 1
3 OR 1 2
end
2 1
--------------------------------------------------------------------------------
2 AND 0 1
3 OR 1 2
end
2 0
--------------------------------------------------------------------------------
*/
//------------------------------End--------------------------------------------------//
