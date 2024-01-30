#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <random>
#include <algorithm>
#include "Edge.cpp"
using namespace std;

class VisGraph {
private:
    vector<Node> nodes;
    vector<Edge> edges;
    mt19937 rng;
    static const int minDistance = 200; // Minimum distance between nodes

public:
    VisGraph() {
        rng = mt19937(rand());
    }

    void addNode(float x, float y, const sf::Font& font, vector<pair<bool, loc>> &store) {
        int id = nodes.size();
        nodes.emplace_back(x, y, id, font, store);
    }

    void addEdge(int nodeId1, int nodeId2) {
        edges.emplace_back(nodes[nodeId1], nodes[nodeId2]);

    }

    Edge* getEdge(int node1, int node2) {
        for (Edge& edge : edges) {
            if ((edge.nodeId1 == node1 && edge.nodeId2 == node2) ||
                (edge.nodeId1 == node2 && edge.nodeId2 == node1)) {
                return &edge;
            }
        }
        return nullptr;
    }


    bool edgeExists(int nodeId1, int nodeId2) {
        Edge tempEdge = Edge(nodes[nodeId1], nodes[nodeId2]);
        return find(edges.begin(), edges.end(), tempEdge) != edges.end();
    }

    void randomizeEdges(int edgeCount, Graph graph) {
        uniform_int_distribution<int> dist(0, nodes.size() - 1);
        int weight;

        while (edges.size() < edgeCount) {
            int nodeId1 = dist(rng);
            int nodeId2 = dist(rng);

            // Avoid self-loops and duplicate edges
            if (nodeId1 != nodeId2 && !edgeExists(nodeId1, nodeId2)) {
                weight = ((stoi(nodes[nodeId1].location.density)+stoi(nodes[nodeId2].location.density))/2)
                         *sqrt((nodes[nodeId1].shape.getPosition().x-nodes[nodeId2].shape.getPosition().x)*
                               (nodes[nodeId1].shape.getPosition().x-nodes[nodeId2].shape.getPosition().x)+
                               (nodes[nodeId1].shape.getPosition().y-nodes[nodeId2].shape.getPosition().y)*
                               (nodes[nodeId1].shape.getPosition().y-nodes[nodeId2].shape.getPosition().y));
                cout <<"Node 1: " << nodeId1 << "and Node 2: " << nodeId2 << "and weight is " << weight << endl;
                addEdge(nodeId1, nodeId2);
                graph.addEdge(nodeId1, nodeId2, weight);
            }
        }
    }

    bool isFarEnough(float x, float y) {
        for (const auto& node : nodes) {
            float dx = node.shape.getPosition().x - x;
            float dy = node.shape.getPosition().y - y;
            if (sqrt(dx * dx + dy * dy) < minDistance) {
                return false;
            }
        }
        return true;
    }

    void addNodeSafely(const sf::Font& font, vector<pair<bool,loc>> &store) {
        uniform_real_distribution<float> distX(50, 700);
        uniform_real_distribution<float> distY(50, 700);

        float x, y;
        do {
            x = distX(rng);
            y = distY(rng);
        } while (!isFarEnough(x, y));

        addNode(x, y, font,store);
    }

    void draw(sf::RenderWindow& window, bool check) {
        //If SPT is checked or not
        if(check) {
            for (auto &edge: edges) {
                if (edge.spt == true) {
                    window.draw(edge.shape);
                }
            }
            for (auto &node: nodes) {
                window.draw(node.shadowShape);
                window.draw(node.shape);
                window.draw(node.highlightShape);
                window.draw(node.num);
            }
        }else{
            for (auto &edge: edges) {
                    window.draw(edge.shape);
            }
            for (auto &node: nodes) {
                window.draw(node.shadowShape);
                window.draw(node.shape);
                window.draw(node.highlightShape);
                window.draw(node.num);
            }
        }

    }

    pair<bool, int> getNodeIndexAtPosition(sf::Vector2f position) {
        for (size_t i = 0; i < nodes.size(); ++i) {
            sf::Vector2f nodePos = nodes[i].shape.getPosition();
            float dx = nodePos.x - position.x;
            float dy = nodePos.y - position.y;
            if (sqrt(dx * dx + dy * dy) < Node::radius) {
                return make_pair(true, i);
            }
        }
        return make_pair(false, -1);
    }

    string getCountry(int ID) {
        return nodes[ID].location.country;
    }
    string getCapital(int ID) {
        return nodes[ID].location.capital;
    }
    int getPopulation(int ID) {
        return nodes[ID].location.population;
    }
    int getSize(int ID) {
        return nodes[ID].location.size;
    }
    string getDensity(int ID) {
        return nodes[ID].location.density;
    }

    void edgeHighlight(int id1, int id2){
        getEdge(id1, id2)->highlight();
    }

    void edgeDraw(int id1, int id2){
        getEdge(id1, id2)->spt = true;
    }


    vector<Edge>& edgeVec(){
        return edges;
    }



};
