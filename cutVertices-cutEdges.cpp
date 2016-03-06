#include <iostream>
#include <vector>
#include <map>
#include <list>
using namespace std;

bool *visited;
int *start;
int *parent;
int *low;
bool *cutv;
list<int> *adj;
vector<vector<int> > cutedges;

void addEdges (int ori, int des) {
    adj[ori].push_back(des);
    adj[des].push_back(ori);
}

int num_cutedges;
int tim = 1;
void cut (int u) {
    
    visited[u] = true;
    start[u] = tim;
    low[u] = tim;
    tim++;
    int child = 0;
    list<int>::iterator it;
    for (it = adj[u].begin(); it != adj[u].end(); it++) {
        int temp = *it;
        if (visited[temp] == false) {
            child++;
            parent[temp] = u;
            cut(temp);
            
            low[u] = min(low[u], low[temp]);
            if ((parent[u] == 0) && (child >= 2)) {
                cutv[u] = true;
            }
            if ((parent[u] != 0) && low[temp] >= start[u]) {
                cutv[u] = true;
            }
            if (low[temp] > start[u]) {
                cutedges[u].push_back(temp);
                num_cutedges++;
            }
        } else if (temp != parent[u]) {
            low[u] = min(low[u], start[temp]);
        }
    }
}

int main() {
    int num_v, num_e, ori, des;
    cin >> num_v;
    cin >> num_e;
    
    visited = new bool[num_v+1];
    start = new int[num_v+1];
    parent = new int[num_v+1];
    low = new int[num_v+1];
    cutv = new bool[num_v+1];
    adj = new list<int>[num_v+1];
    cutedges = vector<vector<int> >(num_v+1);
    
    for (int i = 1; i < num_v+1; i++) {
        visited[i] = false;
        start[i] = 0;
        parent[i] = 0;
        cutv[i] = false;
    }
    
    while (!cin.fail()) {
        cin >> ori;
        cin >> des;
        addEdges(ori, des);
    }
    cut(1);
    
    int num_cutvertices = 0;
    for (int i = 1; i < num_v+1; i++) {
        if (cutv[i] == true) {
            num_cutvertices++;
        }
    }
    cout << num_cutvertices << " ";
    for (int i = 1; i < num_v+1; i++) {
        if (cutv[i] == true) {
            cout << i << " ";
        }
    }
    cout << endl;
    cout << num_cutedges << " ";
    
    for(int i = 0; i < num_v+1; i++){
        for(int j = 0; j < cutedges[i].size(); j++){
            cout << "(" << i << "," << cutedges[i][j] << ")" << " ";
        }
    }
    cout << endl;
}



