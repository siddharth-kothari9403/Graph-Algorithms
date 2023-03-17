#include<bits/stdc++.h>
using namespace std;

struct Graph{
    int vertices;
    vector<vector<int>> adj;
    Graph(int n){
        vertices = n;
        vector<int> temp = {};
        adj.resize(n, temp);
    }
};

void printVector(vector<int> arr){
    for (int i=0; i<arr.size(); i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}

//for undirected graph
void addEdge(struct Graph &g, int s, int e){
    g.adj[s].push_back(e);
    g.adj[e].push_back(s);
}

vector<int> connectedComponents(struct Graph &g){
    int n = g.vertices;
    vector<vector<int>> list = g.adj;

    vector<int> connected(n);
    for (int i=0; i<n; i++){
        connected[i]= 0;
    }

    int count = 0;
    //printVector(connected);

    queue<int> q;
    for (int i=0; i<n; i++){
        if (connected[i]==0){
            int s = i;
            q.push(s);
            count++;
            connected[s]= count;
            //cout<<s<<" "<<connected[s]<<endl;

            while (!q.empty()){
                int u = q.front();
                //cout<<"u "<<u<<endl;
                q.pop();

                for (int v=0; v<list[u].size(); v++){
                    if (connected[list[u][v]]==0){
                        //cout<<"Hey "<<list[u][v]<<endl;
                        q.push(list[u][v]);
                        connected[list[u][v]]=count;
                    }
                }
                //cout<<"Yo"<<endl;
            }
        }
    }
    //cout<<count<<endl;

    return connected;
}

int main(){
    Graph g = Graph(8);
    addEdge(g, 0, 1);
    addEdge(g, 0, 2);
    addEdge(g, 1, 2);
    addEdge(g, 2, 4);
    addEdge(g, 4, 1);
    addEdge(g, 1, 3);
    addEdge(g, 4, 3);
    addEdge(g, 5, 6);

    vector<int> results = connectedComponents(g);
    printVector(results);
}