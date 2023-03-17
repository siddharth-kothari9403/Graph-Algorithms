#include <bits/stdc++.h>
using namespace std;

struct Graph{
    int vertices; 
    vector<vector<pair<int, int>>> adj;

    Graph(int n){
        vertices = n;
        vector<pair<int,int>> temp= {};
        adj.resize(n, temp);
    }
};

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

bool disjoint(int i, int j, vector<int> &root){
    if (findParent(i, root)== findParent(j, root)){
        return false;
    }
    return true;
}

void disjointUnion(vector<int> &root, vector<int> &number, int n1, int n2){
    int i = findParent(n1, root);
    int j = findParent(n2, root);

    if (i!=j){
        if (number[i]> number[j]){
            root[j]= i; number[i]+=number[j];
        }else{
            root[i]= j; number[j]+=number[i];
        }
    }
}

void addEdge(Graph &g, int s, int e, int weight){
    g.adj[s].push_back(make_pair(e, weight));
}


void addEdge1(Graph &g, int s, int e, int weight){
    g.adj[s].push_back(make_pair(e, weight));
    g.adj[e].push_back(make_pair(s, weight));
}

void deleteEdge(Graph &g, int s, int e){
    for (int i=0; i<g.adj[s].size(); i++){
        if (g.adj[s][i].first==e){
            g.adj[s].erase(g.adj[s].begin() + i);
        }
    }
}

pair<vector<pair<pair<int, int>, int>>, int> kruskals(Graph g){
    vector<vector<pair<int, int>>> list = g.adj;
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>> > edges;
    //weight, src, dest so that they are sorted based o first value, i.e. weight
    for (int i=0; i<list.size(); i++){
        for (int j=0; j<list[i].size(); j++){
            pair<int, int> temp = make_pair(i, list[i][j].first);
            //source and destination
            edges.push(make_pair(list[i][j].second, temp));
        }
    }

    vector<vector<int>> data = makeSet(g.vertices);

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
}

vector<int> connectedComponents(struct Graph &g){
    int n = g.vertices;
    vector<vector<pair<int, int>>> list = g.adj;

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
                    if (connected[list[u][v].first]==0){
                        //cout<<"Hey "<<list[u][v]<<endl;
                        q.push(list[u][v].first);
                        connected[list[u][v].first]=count;
                    }
                }
                //cout<<"Yo"<<endl;
            }
        }
    }
    //cout<<count<<endl;

    return connected;
}

pair<vector<pair<pair<int, int>, int>>, int> deleted_edge_MST(Graph g, pair<pair<int, int>,int> deleted_edge){
    pair<vector<pair<pair<int, int>, int>>, int> initial = kruskals(g);
    vector<pair<pair<int, int>, int>> edges_in_MST = initial.first;
    int initial_weight = initial.second;

    deleteEdge(g, deleted_edge.first.first, deleted_edge.first.second);
    bool in_MST = false;
    for (int i=0; i<edges_in_MST.size(); i++){
        if (deleted_edge.first == edges_in_MST[i].first){
            in_MST=true;
            //cout<<in_MST<<endl;
            break;
        }
    }

    if (in_MST==false){
        cout<<"No change"<<endl;
        return initial;
    }


    for (int i=0; i<edges_in_MST.size(); i++){
        if (edges_in_MST[i].first == deleted_edge.first){
            edges_in_MST.erase(edges_in_MST.begin()+i);
            initial_weight-=deleted_edge.second;
            break;
        }
    }
    //cout<<"Yo"<<endl;

    struct Graph MST = Graph(g.vertices);
    for (int i=0; i<edges_in_MST.size(); i++){
        addEdge1(MST, edges_in_MST[i].first.first, edges_in_MST[i].first.second, edges_in_MST[i].second);
    }
    //cout<<"Hi"<<endl;

    vector<int> components =connectedComponents(MST);
    int minWeight = INT_MAX;
    int a,b;
    for (int i=0; i<g.adj.size(); i++){
        for (int j=0; j<g.adj[i].size(); j++){
            if (components[i]!=components[g.adj[i][j].first] && minWeight> g.adj[i][j].second){
                minWeight=g.adj[i][j].second; a=i; b= g.adj[i][j].first;
            }
        }
    }
    //printVector(components);
    //cout<<"Here"<<endl;

    pair<int, int> temp = make_pair(a,b);
    edges_in_MST.push_back(make_pair(temp, minWeight));
    initial_weight+=minWeight;

    return make_pair(edges_in_MST, initial_weight);
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

    pair<int, int> temp = {1,3};
    pair<pair<int, int>, int> edge = {temp, -4};
    pair<vector<pair<pair<int, int>, int>>, int> res1 = deleted_edge_MST(g, edge);

    cout<<res1.second<<endl;
}