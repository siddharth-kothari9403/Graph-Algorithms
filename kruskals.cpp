#include <bits/stdc++.h>
using namespace std;

//struct graph which consists of the number of vertices and the adjacency list as a vector of vectors
struct Graph{
    int vertices; 
    vector<vector<pair<int, int>>> adj;

    Graph(int n){
        vertices = n;
        vector<pair<int,int>> temp= {};
        adj.resize(n, temp);
    }
};

//to make the set of connected components, initially the root of a node is the node itself, indicating n separate connected components
vector<vector<int>> makeSet(int n){
    vector<int> root(n);
    vector<int> number(n);
    
    for (int i=0; i<n; i++){
        root[i]=i;
        number[i]=1;
    }
    vector<vector<int>> ans = {root, number};
    return ans; 
    //initially all nodes have parent value as itself
}

int findParent(int i, vector<int> &root){
    if (root[i]==i){
        return i; //find the element having root[i]=i, that will be the root of the tree
    }else{
        return root[i]= findParent(root[i], root); //path compression
    }
}

//to find whether two nodes are currently part of the same connected component or not
//thety are, if they have the same parent
bool disjoint(int i, int j, vector<int> &root){
    if (findParent(i, root)== findParent(j, root)){
        return false;
    }
    return true;
}

//to merge two connected components, i.e. take disjoint union of the two 
void disjointUnion(vector<int> &root, vector<int> &number, int n1, int n2){
    int i = findParent(n1, root);
    int j = findParent(n2, root);

    if (i!=j){
        //merging the set with smaller no of elements to the one with larger number of elements 
        if (number[i]> number[j]){
            root[j]= i; number[i]+=number[j];
        }else{
            root[i]= j; number[j]+=number[i];
        }
    }
}


//helper function to add edge to adjacency list
void addEdge(Graph &g, int s, int e, int weight){
    g.adj[s].push_back(make_pair(e, weight));
}

pair<vector<pair<pair<int, int>, int>>, int> kruskals(Graph g){
    vector<vector<pair<int, int>>> list = g.adj;
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>> > edges;
    //weight, src, dest so that they are sorted based on first value, i.e. weight

    //the priority queue maintains the order based on weight
    for (int i=0; i<list.size(); i++){
        for (int j=0; j<list[i].size(); j++){
            pair<int, int> temp = make_pair(i, list[i][j].first);
            //source and destination
            edges.push(make_pair(list[i][j].second, temp));
        }
    }
    //pushins the edges into the priority queue

    //making the connected components
    vector<vector<int>> data = makeSet(g.vertices);

    //the edges to be added to the MST
    vector<pair<pair<int, int>, int>> pairs;
    int weightTree=0;

    while (!edges.empty()){
        pair<int, pair<int, int>> edge = edges.top();
        edges.pop();
        if (disjoint(edge.second.first, edge.second.second, data[0])){
            
            disjointUnion(data[0], data[1], edge.second.first, edge.second.second);
            pair<int, int> temp = make_pair(edge.second.first, edge.second.second);
            pairs.push_back(make_pair(temp, edge.first));
            weightTree+=edge.first;
        }
    }

    return make_pair(pairs, weightTree);

    //structure of the o/t is as follows 
    //the pairs to be added to mst as weight, {start, end} and the weight of the mst
}

int main(){
    Graph g = Graph(5);
    addEdge(g,1,3,-4);
    addEdge(g,2,4,-3);
    addEdge(g,1,2,-2);
    addEdge(g,1,4,-1);
    addEdge(g,3,4,1);
    addEdge(g,0,2,1);
    addEdge(g,0,4,3);
    addEdge(g,0,1,4);
    addEdge(g,2,3,5);
    addEdge(g,0,3,6);

    pair<vector<pair<pair<int, int>, int>>, int> res = kruskals(g);
    //printVector(res.first);
    cout<<res.second<<endl;
}