/*
EE 677 - Heuristic based logic minimizer
Language - C++17
Input format - 
----------------------------------------------------------------------------------------------
<On-set term 1>
<On-set term 2>
<On-set term 3>
.
.
.
end
<Off-set term 1>
<Off-set term 2>
<Off-set term 3>
.
.
.
end
<DC-set term 1>
<DC-set term 2>
<DC-set term 3>
.
.
.
end
*/

#include <bits/stdc++.h>
using namespace std;
//------------------------------Primary class--------------------------------------------------//
class logic_cover{
	public:
	int lit; // Number of literals
	vector<vector<int>> on,off,dc; // ON, OFF and DC set
	logic_cover(vector<string> Set,vector<string> Unset,vector<string> DontCare){
		lit = Set[0].size();
		auto fill = [&](vector<string> &inp,vector<vector<int>> &out){ // Converting from literal to cube notation
			if(inp.empty())return;
			for(string s : inp){
				vector<int> row;
				for(int i = 0; i < lit; i++){
					if(s[i] == '1'){
						row.push_back(0);
						row.push_back(1);
					}
					else{
						row.push_back(1);
						row.push_back(0);
						
					}
				}
				out.push_back(row);
			}
		};
		fill(Set,on);
		fill(Unset,off);
		fill(DontCare,dc);
	}
//------------------------------Helper functions--------------------------------------------------//
	pair<int,int> computeCost(){ // Computes the cost of the cover. Priority to number of minterms then number of literals
		pair<int,int> ans;
		ans.first = on.size();
		int n = on.size(),m = on[0].size();
		int cnt = 0;
		for(int j = 0; j < m; j+=2){
			for(int i = 0; i < n; i++){
				if(on[i][j] != 1 || on[i][j+1] != 1){
					cnt++;
					break;
				}
			}
		}
		ans.second = cnt;
		return ans;
	}
	
	bool checkIntersection(vector<int> &impl1,vector<int> &impl2){ // Returns true if impl1 intesects with impl2
		int n = impl1.size();
		vector<int> res(n);
		for(int i = 0; i < n; i++){
			res[i] = impl1[i] & impl2[i];
		}
		for(int i = 0; i < n; i+=2){
			if(res[i] == 0 && res[i+1] == 0)return false;
		}
		return true;
	}
	
	bool checkIntersection(vector<int> &impl,vector<vector<int>> &col){ // Returns true if impl intesects with col(cover of implicants)
		for(vector<int> &v : col){
			if(checkIntersection(impl,v))return true;
		}
		return false;
	}
	bool checkContainment(vector<int> &subset, vector<int> &superset){ // Checks if subset is contained by superset
		int n = subset.size();
		vector<int> intersect(n);
		for(int i = 0; i < n; i++){
			intersect[i] = subset[i] | superset[i];
		}
		return intersect == superset;
	}
	vector<string> getMinterms(vector<int> impl){ // Finds minterms of an implicant
		int n = impl.size();
		string s;
		vector<string> res;
		function<void(int)> dfs = [&](int i){ // Recursive function to get minterm list
			if(i >= n){
				res.push_back(s);
				return;
			}
			int here = impl[i]*2 + impl[i+1];
			assert(here != 0);
			if(here & 1){
				s += '1';
				dfs(i+2);
				s.pop_back();
			}
			if(here & 2){
				s += '0';
				dfs(i+2);
				s.pop_back();
			}
		}; dfs(0);
		return res;
	}
	
	bool canCover(vector<int> &impl,string &minterm){ // Returns true if impl covers minterm
		int n = minterm.size();
		for(int i = 0; i < n; i++){
			int val = impl[2*i]*2 + impl[2*i+1];
			if(val == 3)continue;
			int state = minterm[i] - '0';
			if(state == 1 && val != 1)return false;
			if(state == 0 && val != 2)return false;
		}
		return true;
	}
	
	void sortOnSet(){ // Sorts the ON set by computing weights and taking dot product
		int n = on.size(),m = on[0].size();
		vector<int> col(m,0),wt(n,0),order(n);
		iota(order.begin(),order.end(),0);
		for(int j = 0; j < m; j++){
			for(int i = 0; i < n; i++){
				col[j] += on[i][j]; // col[j] stores the sum of the column
			}
		}
		for(int i = 0; i < n; i++){
			for(int j = 0; j < m; j++){
				wt[i] += on[i][j] * col[j]; // Taking dot product with the set itself
			}
		}
		sort(order.begin(),order.end(),[&](const auto &v1,const auto &v2){
			return wt[v1] < wt[v2]; // (v1 < v2) : if true then v1 is before v2
		});
		vector<vector<int>> new_vec;
		for(int i = 0; i < n; i++){
			new_vec.push_back(on[order[i]]);
		}
		on = new_vec;
	}
//------------------------------Espresso functions--------------------------------------------------//
	void expand(){ // Expand operator of Espresso
		while(true){
			sortOnSet();
			auto old_set = on;
			int n = on.size(),m = on[0].size();
			for(int i = 0; i < n; i++){
				vector<int> impl = on[i]; // Implicant which we are going to expand
				bool expanded = false; // Indicator variable
				for(int j = 0; j < m; j++){
					if(impl[j] == 1)continue; // Already one, Can't expand
					impl[j] = 1;
					if(checkIntersection(impl,off)){ // If it intersects with OFF set then cannot expand
						impl[j] = 0;
					}
					else{
						expanded = true;
					}
				}
				if(!expanded)continue;
				vector<vector<int>> new_vec = {impl};
				for(vector<int> &v : on){
					if(!checkContainment(v,impl)){
						new_vec.push_back(v);
					}
				}
				on = new_vec;
				break;
			}
			sort(on.begin(),on.end());
			sort(old_set.begin(),old_set.end());
			if(on == old_set)return; // No expansion happened
		}
	}
	
	void irredundant(){
		vector<vector<int>> new_vec;
		int n = on.size();
		for(int i = 0; i < n; i++){
			bool essential = false;
			vector<string> mint = getMinterms(on[i]);
			for(string &s : mint){ // For every minterm, checking if it is covered by other implicants
				bool covered = false;
				for(int j = 0; j < n; j++){
					if(i == j)continue;
					if(canCover(on[j],s)){
						covered = true;
						break;
					}
				}
				if(!covered){ // If this minterm is uncovered, then the implicant is essential so can't remove it
					essential = true;
					break;
				}
			}
			if(essential){ // Keeping all essential implicants
				new_vec.push_back(on[i]);
			}
		}
		on = new_vec;
	}
	
	void reduce(){ // Reduce function used by espresso
		sortOnSet();
		int n = on.size(),m = on[0].size();
		for(int i = n-1; i >= 0; i--){
			for(int k = 0; k < m; k+=2){
				if(on[i][k] == 0 || on[i][k+1] == 0)continue; // Can only reduce 11
				{ // Checking if the dropped implicant has all of its minterms covered or not
					vector<int> rem = on[i];
					rem[k] = 0;
					bool essential = false;
					vector<string> mint = getMinterms(rem);
					for(string &s : mint){
						bool covered = false;
						for(int j = 0; j < n; j++){
							if(i == j)continue;
							if(canCover(on[j],s)){
								covered = true;
								break;
							}
						}
						if(!covered){
							essential = true;
							break;
						}
					}
					if(!essential){
						on[i][k+1] = 0;
						continue; // Reduction successful
					}
				}
				{
					vector<int> rem = on[i];
					rem[k+1] = 0;
					bool essential = false;
					vector<string> mint = getMinterms(rem);
					for(string &s : mint){
						bool covered = false;
						for(int j = 0; j < n; j++){
							if(i == j)continue;
							if(canCover(on[j],s)){
								covered = true;
								break;
							}
						}
						if(!covered){
							essential = true;
							break;
						}
					}
					if(!essential){
						on[i][k] = 0;
						continue; // Reduction successful
					}
				}
			}
		}
	}
	
	void espresso(){ // Main espresso function
		expand();
		irredundant();
		while(true){
			pair<int,int> old_cost = computeCost();
			auto old_set = on;
			reduce();
			expand();
			irredundant();
			pair<int,int> new_cost = computeCost();
			if(new_cost >= old_cost){
				on = old_set;
				return;
			}
		}
	}
//------------------------------Output--------------------------------------------------//
	void showResult(){ // Function which prints the result
		cout << "Minimal function cover generated by the espresso algorithm in cube notation is as follows" << endl;
		cout << "-------------------------------------------------------" << endl;
		for(auto p : on){
			int m = p.size();
			for(int i = 0; i < m; i+=2){
				cout << p[i] << p[i+1] << " ";
			}
			cout << endl;
		}
		cout << "-------------------------------------------------------" << endl;
	}
};

//------------------------------Main Program--------------------------------------------------//
vector<string> on,off,dc;

void take_input(vector<string> &col){
	while(true){
		string s;
		cin >> s;
		if(s == "end")return;
		col.push_back(s);
	}
}

void take_input(){
	take_input(on);
	take_input(off);
	take_input(dc);
}

int main(){
	take_input();
	logic_cover my(on,off,dc);
	my.espresso();
	my.showResult();
	return 0;
}
/*
Sample input - 
--------------------------------------------------------------------------------
000
100
010
001
end
101
111
011
end
110
end
--------------------------------------------------------------------------------
*/
