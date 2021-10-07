// हर हर महादेव
/*
EE 677 - Logic simulator
Name - Shivang Tiwari
Roll number - 190040112

Netlist format - 
----------------------------------------------------------------------------------------------
<output_node_1><space><gate_type><space><input_node_1><space><intput_node_2>...
<output_node_2><space><gate_type><space><input_node_1><space><intput_node_2>...
.
.
.
end
<circuit_input_1><space><value>
<circuit_input_2><space><value>
.
.
.
----------------------------------------------------------------------------------------------
*/


#include <stdio.h>
using namespace std;
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

int deduce(string s){
	if(s == "AND")return 0;
	if(s == "OR")return 1;
	if(s == "NOT")return 2;
	cerr << "Invalid gate type" << endl;
	exit(0);
	return -1;
}
//This detects cycle in a ***directed graph***
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


int main(){
	int node_count = 0;
	vector<pair<int,vector<int>>> all;
	map<int,int> ots; // Gate type of the node
	map<int,int> type; // 0 for input, 2 for output and 1 for intermediate
	while(true){
		string s;
		getline(cin,s);
		if(s == "end")break;
		vector<string> line = split(s);
		int ot_node = stoi(line[0]);
		node_count = max(node_count,ot_node);
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
	vector<vector<int>> graph(node_count+1);
	for(auto &x : all){
		for(int y : x.second){
			graph[x.first].push_back(y); // Connecting each node to its dependencies
		}
	}
	if(isCyclic(graph)){ // Cycle can't be present in the graph
		cerr << "The netlist is not valid" << endl;
		exit(0);
	}
	vector<int> inps,outs; // inps = input nodes, outs = output nodes
	for(auto x : type){
		if(x.second == 0)inps.push_back(x.first);
		if(x.second == 2)outs.push_back(x.first);
	}
	vector<int> value(node_count+1,-1);
	for(int i = 0; i < (int)inps.size(); i++){
		int x,val;
		cin >> x >> val;
		assert(val != -1);
		if(type.find(x) == type.end() || type[x] == 0){
			cerr << x << " is not a valid input node" << endl;
			exit(0);
		}
		if(value[x] != -1){
			cerr << "Value of " << x << " has already been assigned" << endl;
			exit(0);
		}
		value[x] = val;
	}
	for(int x : inps){
		if(value[x] == -1){// All inputs must be provided
			cerr << "Value of input node " << x << " is not provided" << endl;
			exit(0);
		}
	}
	function<void(int)> dfs = [&](int i){
		if(value[i] != -1)return; // Return if already calculated
		assert(ots.find(i) != ots.end()); // Must be output or intermediate node
		for(int x : graph[i]){
			dfs(x); // Calculating all dependencies
		}
		bool ans; // Calculating the value at this node
		switch(ots[i]){
			case 0: // AND gate
				ans = 1;
				assert((int)graph[i].size() >= 2);
				for(auto y : graph[i])ans &= value[y];
				break;
			case 1: // OR gate
				ans = 0;
				assert((int)graph[i].size() >= 2);
				for(auto y: graph[i])ans |= value[y];
				break;
			case 2: // NOT gate
				assert((int)graph[i].size() == 1);
				ans = !(value[graph[i][0]]);
				break;
			default:
				assert(false);
		}
		value[i] = ans;
	};
	for(int ot : outs){
		dfs(ot); // Running the depth first search on all outputs
	}
	cout << "The inputs are : " << endl;
	for(int x : inps){
		cout << x << " -> " << value[x] << endl;
	}
	cout << "For these inputs, the outputs are : " << endl;
	for(int x : outs){
		cout << x << " -> " << value[x] << '\n';
	}
	return 0;
}
/*
5 NOT 3
4 OR 0 2
3 AND 0 1
6 AND 4 5
end
0 1
1 1
2 0
*/
