#include <bits/stdc++.h>
using namespace std;

struct Graph{
    int vertices;
    vector<vector<pair<int, int>>> adj;
    Graph(int n){
        vertices = n;
        vector<pair<int, int>> temp = {};
        adj.resize(n, temp);
    }
};

//pair in edges represents end point, weight

void printVector(vector<int> arr){
    for (int i=0; i<arr.size(); i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}

void addEdge(struct Graph &g, int s, int e, int weight){
    g.adj[s].push_back(make_pair(e, weight));
}

vector<int> dijkstra(struct Graph g, int s){
    int n = g.vertices;
    vector<vector<pair<int, int>>> list = g.adj;

    vector<int> phi(n), distance(n);
    vector<bool> visited(n);

    //phi is the parent, distance contains the shortest distance from node s
    for (int i=0; i<n; i++){
        phi[i]=-2;
        visited[i]=false;
        distance[i]=INT_MAX;
    }

    distance[s]= 0; phi[s]=-1;

    //initialising the priority queue with pair<int, int>
    priority_queue<pair<int,int> , vector<pair<int, int>>, greater<pair<int, int>>> pq;

    //priority queue will contain a pair of the distance and the index.
    //priority is taken as the first value of the pair, and hence the distances act as the priority
    pq.push(make_pair(distance[s],s));

    while (!pq.empty()){
        //extracting index from pair
        int u = pq.top().second;
        pq.pop();

        visited[u]=true;
        for (int v=0; v<list[u].size(); v++){
            if (visited[list[u][v].first]==false && distance[list[u][v].first]> distance[u]+ list[u][v].second){
                distance[list[u][v].first] = distance[u]+ list[u][v].second;
                pq.push(make_pair(distance[u]+ list[u][v].second, list[u][v].first));
                // we need to push the updated distance into the queue as well, duplicates will be there but the algorithm will take care of that
                // duplicate won't cause problem as we are setting visited = true as soon as first time acces is done
                phi[list[u][v].first] = u;
            }
        }
    }
    cout<<"Phi- "<<endl;
    printVector(phi);

    return distance;

    /*cout<<endl;
    cout<<"Distance- "<<endl;
    printVector(distance); */
}

vector<int> minPrims(struct Graph g, int s){
    int n = g.vertices;
    vector<vector<pair<int, int>>> list = g.adj;

    vector<int> phi(n), distance(n);
    vector<bool> visited(n);

    //phi is the parent, distance contains the shortest distance from node s
    for (int i=0; i<n; i++){
        phi[i]=-2;
        visited[i]=false;
        distance[i]=INT_MAX;
    }

    distance[s]= 0; phi[s]=-1;

    //initialising the priority queue with pair<int, int>
    priority_queue<pair<int,int> , vector<pair<int, int>>, greater<pair<int, int>>> pq;

    //priority queue will contain a pair of the distance and the index.
    //priority is taken as the first value of the pair, and hence the distances act as the priority

    pq.push(make_pair(distance[s],s));

    while (!pq.empty()){
        //extracting index from pair
        int u = pq.top().second;
        pq.pop();

        visited[u]=true;
        for (int v=0; v<list[u].size(); v++){
            if (visited[list[u][v].first]==false && distance[list[u][v].first]> list[u][v].second){
                distance[list[u][v].first] = list[u][v].second;
                pq.push(make_pair(list[u][v].second, list[u][v].first));
                // we need to push the updated distance into the queue as well, duplicates will be there but the algorithm will take care of that
                // duplicate won't cause problem as we are setting visited = true as soon as first time acces is done
                phi[list[u][v].first] = u;
            }
        }
    }
    cout<<"Phi- "<<endl;
    printVector(phi);

    return distance;

    /*cout<<endl;
    cout<<"Distance- "<<endl;
    printVector(distance); */
}

vector<int> maxPrims(struct Graph g, int s){
    int n = g.vertices;
    vector<vector<pair<int, int>>> list = g.adj;

    vector<int> phi(n), distance(n);
    vector<bool> visited(n);

    //phi is the parent, distance contains the shortest distance from node s
    for (int i=0; i<n; i++){
        phi[i]=-2;
        visited[i]=false;
        distance[i]=INT_MIN;
    }

    distance[s]= 0; phi[s]=-1;

    //initialising the priority queue with pair<int, int>
    priority_queue<pair<int,int>> pq;

    //priority queue will contain a pair of the distance and the index.
    //priority is taken as the first value of the pair, and hence the distances act as the priority

    pq.push(make_pair(distance[s],s));

    while (!pq.empty()){
        //extracting index from pair
        int u = pq.top().second;
        pq.pop();

        visited[u]=true;
        for (int v=0; v<list[u].size(); v++){
            if (visited[list[u][v].first]==false && distance[list[u][v].first] < list[u][v].second){
                distance[list[u][v].first] = list[u][v].second;
                pq.push(make_pair(list[u][v].second, list[u][v].first));
                // we need to push the updated distance into the queue as well, duplicates will be there but the algorithm will take care of that
                // duplicate won't cause problem as we are setting visited = true as soon as first time acces is done
                phi[list[u][v].first] = u;
            }
        }
    }
    cout<<"Phi- "<<endl;
    printVector(phi);

    return distance;

    /*cout<<endl;
    cout<<"Distance- "<<endl;
    printVector(distance); */
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

    vector<int> results = dijkstra(g, 0);
    printVector(results);

    vector<int> results1 = minPrims(g, 0);
    printVector(results1);

    vector<int> results2 = maxPrims(g, 0);
    printVector(results2);

    return 0;
}