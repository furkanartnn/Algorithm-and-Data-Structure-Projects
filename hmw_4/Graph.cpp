#include "Graph.h"
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

Graph::Graph(Edge* edges_array, int num_nodes, int num_edges): num_nodes(num_nodes), num_edges(num_edges){
	adjMatrix = new int*[num_nodes];
	for (int i=0; i<num_nodes; ++i){
		adjMatrix[i] = new int[num_nodes];
		fill(adjMatrix[i], adjMatrix[i]+ num_nodes,0);
	}
	initializeMatrix(edges_array);
}

Graph::~Graph(){
	for (int i=0; i< num_nodes; ++i){
		delete[] adjMatrix[i];
	}
	delete[] adjMatrix;
}

void Graph::initializeMatrix(Edge* edges_array) {
    for (int i = 0; i < num_edges; ++i) {
        int u = edges_array[i].node1;
        int v = edges_array[i].node2;
        int len = edges_array[i].length;
        adjMatrix[u][v] = len;
        adjMatrix[v][u] = len; // because the graph is undirected
    }
}

int* Graph::dijkstra(int source){
	int* distances = new int[num_nodes];
	fill(distances, distances + num_nodes, INT_MAX);
	distances[source] = 0;
	
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, source});
    
    while (!pq.empty()) {
    	int dist = pq.top().first;
    	int node = pq.top().second;
    	pq.pop();
    	
    	if (dist > distances[node]) continue;
    	
    	for (int i = 0; i< num_nodes; ++i){
    		if (adjMatrix[node][i] != 0){
    			int newDist = dist + adjMatrix[node][i];
                if (newDist < distances[i]) {
                    distances[i] = newDist;
                    pq.push({newDist, i});
    			
				}
			}
		}	
	}
	for (int i = 0; i < num_nodes; ++i) {
        if (distances[i] == INT_MAX) distances[i] = -1;
    }

    return distances;
}
vector<vector<int>> Graph::getConnectedComponents() {
    vector<vector<int>> components;
    vector<bool> visited(num_nodes, false);

    for (int i = 0; i < num_nodes; ++i) {
        if (!visited[i]) {
            vector<int> component;
            queue<int> q;
            q.push(i);
            visited[i] = true;

            while (!q.empty()) {
                int node = q.front();
                q.pop();
                component.push_back(node);

                for (int j = 0; j < num_nodes; ++j) {
                    if (adjMatrix[node][j] != 0 && !visited[j]) {
                        visited[j] = true;
                        q.push(j);
                    }
                }
            }
 			sort(component.begin(), component.end());
            components.push_back(component);
        }
    }

    return components;
}

int Graph::calculateCentroid(const vector<int>& component) {
	int minSumDist = INT_MAX;
    int centroid = -1;

    for (int node : component) {
        int sumDist = 0;
        int* distances = dijkstra(node);
        for (int other : component) {
            if (distances[other] != -1) {
                sumDist += distances[other];
            }
        }
        delete[] distances;

        if (sumDist < minSumDist) {
            minSumDist = sumDist;
            centroid = node;
        }
    }

    return centroid;
}
int* Graph::get_centroids(){
	vector<vector<int>> components = getConnectedComponents();
    vector<int> centroids;

    for (const vector<int>& component : components) {
        int centroid = calculateCentroid(component);
        centroids.push_back(centroid);
    }

    sort(centroids.begin(), centroids.end());

    int* result = new int[centroids.size()+ 1];
    result[0] = centroids.size();
    for (size_t i = 0; i < centroids.size(); ++i) {
        result[i+1] = centroids[i];
    }

    return result;
}

int Graph::get_centroid_of_connected_component_containing(int node){
	vector<vector<int>> components = getConnectedComponents();

    for (const vector<int>& component : components) {
        if (find(component.begin(), component.end(), node) != component.end()) {
            return calculateCentroid(component);
        }
    }

    return -1;
}
int* Graph::nodes_in_connected_component_with_centroid(int centroid_node){
	int* centroids = get_centroids();
    if (find(centroids + 1, centroids + 1 + centroids[0], centroid_node) == centroids + 1 + centroids[0]) {
        delete[] centroids;
        int* result = new int[1];
        result[0] = 0;
        return result;
    }
    delete[] centroids;

    vector<vector<int>> components = getConnectedComponents();

    for (const vector<int>& component : components) {
        if (calculateCentroid(component) == centroid_node) {
            int* result = new int[component.size() + 1];
            result[0] = component.size();
            for (size_t i = 0; i < component.size(); ++i) {
                result[i + 1] = component[i];
            }
            return result;
        }
    }

    int* result = new int[1];
    result[0] = 0;
    return result;
}
