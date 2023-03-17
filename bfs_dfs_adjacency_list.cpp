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
void addEdge(struct Graph &g, int s, int e){
    g.adj[s].push_back(e);
}

void bfs(struct Graph g, int s){
    vector<bool> visited;
    vector<int> phi;

    int n = g.vertices;
    vector<vector<int>> list = g.adj;

    queue<int> q;
    for (int i=0; i<n; i++){
        phi.push_back(-2);
        visited.push_back(false);
    }

    q.push(s);
    phi[s]= -1;
    visited[s]= true;

    while (!q.empty()){
        int u= q.front();
        //cout<<u<<" ";
        q.pop();
        for (int v=0; v<list[u].size(); v++){
            //printVector(list[u]);
            if (visited[list[u][v]]==false){
                q.push(list[u][v]);
                phi[list[u][v]]= u;
                visited[list[u][v]]= true;
        }
    }

}
    cout<<endl;

    cout<<"Phi- "<<endl;
    printVector(phi);
}

void dfs(struct Graph g, int s){
    vector<bool> visited;
    vector<int> phi;
    //vector<int> d,f;

    int n = g.vertices;
    vector<vector<int>> list = g.adj;

    for (int i=0; i<n; i++){
        phi.push_back(-2);
        //d.push_back(0);
        visited.push_back(false);
        //f.push_back(0);
    }

    stack<int> st;

    int count = 1;
    phi[s]=-1; 
    st.push(s); 
    //visited[s]=true;

    while(!st.empty()){
        int u = st.top();
        //cout<<u<<" ";
        st.pop();
        if (visited[u] == false){
            visited[u] = true;
            st.push(u);
            cout<<u<<" ";
            //d[u]= count++;

            for (int v=0; v<list[u].size(); v++){
                if (visited[list[u][v]] == false){
                    st.push(list[u][v]); phi[list[u][v]] = u; 
                }
            }
        } 
        /*
        else if (f[u]==0 ) f[u] = count++;
        */
    }
    cout<<endl;

    cout<<"Phi- "<<endl;
    printVector(phi);

}

int main(){
    Graph g = Graph(4);
    addEdge(g,0,1);
    addEdge(g,0,2);
    addEdge(g,1,2);
    addEdge(g,2,0);
    addEdge(g,2,3);

    //bfs(g,2);
    cout<<endl;
    dfs(g,2);
}