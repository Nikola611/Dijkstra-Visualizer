//
// Created by nikol on 1/8/2024.
//
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <queue>
#define INF 0xffffff
using namespace std;

class loc{
public:
    string country;
    string capital;
    int population;
    int size;
    string density;

    loc(){};

    loc(string country, string capital, int population, int size, string density){
        this->country = country;
        this->capital = capital;
        this->population = population;
        this->size = size;
        this->density = density;
    }
};

class Graph {
    int numVert;
    list<pair<int, int> >* adj;
    map<int, loc> m;

public:
    Graph(int numVert)
    {
        this->numVert = numVert;
        adj = new list<pair<int, int>>[numVert];
    }

    void addEdge(int a, int b, int weight)
    {
        adj[a].push_back(make_pair(b, weight));
        adj[b].push_back(make_pair(a, weight));
    }

    int shortestPath(vector<int> &sp, int src, int end)
    {
        vector<int> pathID;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>>pq;
        vector<pair<int, int>> dist(numVert, make_pair(INF, INF));

        pq.push(make_pair(0, src));
        dist[src] = make_pair(0,src);

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            for (auto i = adj[u].begin(); i != adj[u].end(); ++i) {
                int vertexID = (*i).first;
                int weight = (*i).second;

                if (dist[vertexID].first > dist[u].first + weight) {
                    dist[vertexID].first = dist[u].first + weight;
                    dist[vertexID].second = u;
                    pq.push(make_pair(dist[vertexID].first, vertexID));
                }
            }

        }

        printf("Shortest Path from A to B\n");
        int temp = dist[end].second;
        int distance = dist[end].first;
        sp.push_back(end);
        sp.push_back(temp);
        while(true){
            if(temp == src){break;}
            temp = dist[temp].second;
            sp.push_back(temp);
        }
        return distance;
    }
};


