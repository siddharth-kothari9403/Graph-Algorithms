#include <bits/stdc++.h>
using namespace std;

//using edge list here
struct Graph{
    int vertices;
    vector<pair<pair<int, int>, int>> edgeList;
    Graph(int n){
        vertices = n;
        edgeList = {};
    }
};

void printVector(vector<int> arr){
    for (int i=0; i<arr.size(); i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}

void addEdge(struct Graph &g, int s, int e, int weight){
    pair<int,int> temp = make_pair(s,e);
    g.edgeList.push_back(make_pair(temp, weight));
    //g.adj[e].push_back(s);
}

vector<int> bellman_ford(struct Graph g, int s){
    vector<pair<pair<int, int>, int>> edges = g.edgeList;
    int n = g.vertices;

    vector<int> distances(n);
    for (int i=0; i<n; i++){
        distances[i]=INT_MAX;
    }

    int m = edges.size();

    distances[s]=0; 
    for (int i=0; i<n; i++){
        pair<pair<int, int>,int> temp = edges[0];
        int count = 0;
        while (count != m){
            if (distances[temp.first.second]> distances[temp.first.first] + temp.second){
                distances[temp.first.second] = distances[temp.first.first] + temp.second;
            }
            count++;
            temp = edges[count];
        }
    }

    return distances;
}

int main(){
    Graph g = Graph(5);
    addEdge(g, 0, 1, 10);
    addEdge(g, 0, 2, 1);
    addEdge(g, 1, 2, 4);
    addEdge(g, 2, 4, 3);
    addEdge(g, 4, 1, 5);
    addEdge(g, 1, 3, 8);
    addEdge(g, 4, 3, 2);

    vector<int> results = bellman_ford(g, 0);
    printVector(results);
}

