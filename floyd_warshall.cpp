#include <bits/stdc++.h>
using namespace std;

//the graph in this question is an adjacency matrix with the number of nodes
struct Graph{
    int vertices;
    vector<vector<int>> adjacency_matrix;
    Graph(int n){
        //initialisations
        vertices = n;
        vector<int> temp1= {};
        temp1.resize(n, INT_MAX);

        adjacency_matrix = {};
        adjacency_matrix.resize(n, temp1);

        for (int i=0; i<n; i++){
            adjacency_matrix[i][i]= 0;
        }
    }
};

//helper function to print the answer in the end
void printVector(vector<vector<int>> arr){
    for (int i=0; i<arr.size(); i++){
        for (int j=0; j<arr[0].size(); j++){
            if (arr[i][j]==INT_MAX){
                cout<<"I ";
            }else{
                cout<<arr[i][j]<<" ";
            }
        }
        cout<<endl;
    }
    cout<<endl;
}

//helper function to add edge
void addEdge(struct Graph &g, int s, int e, int weight){
    g.adjacency_matrix[s][e]= weight;
}

vector<vector<int>> floyd_warshall(struct Graph g){
    int n = g.vertices;
    vector<vector<int>> matrix = g.adjacency_matrix;

    vector<int> temp1={};
    temp1.resize(n, 0);
    vector<vector<int>> results;
    results.resize(n, temp1);

    //initially the matrix is just the adjacency matrix
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            results[i][j]= matrix[i][j];
        }
    }

    //this is a dp algorithm 
    //for a given i,j we see the shortest length of path considering intermediate nodes only from {1,2,...,k}
    //if a new shortest path is discovered through vertex k, then we update the value of results[i][j], else we don't change it
    for (int k=0; k<n; k++){
        for (int i=0; i<n; i++){
            for (int j=0; j<n; j++){
                if (results[i][j]> results[i][k] + results[k][j] && results[i][k]!= INT_MAX && results[k][j]!= INT_MAX){
                    results[i][j]= results[i][k] + results[k][j];
                }
            }
        }
    }

    return results;
}

int main(){
    Graph g = Graph(4);
    addEdge(g, 0,1,5);
    addEdge(g, 1,2,3);
    addEdge(g, 2,3,1);
    addEdge(g, 0,3,10);

    printVector(floyd_warshall(g));
}