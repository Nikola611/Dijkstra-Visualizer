#include <SFML/Graphics.hpp>
#include <cmath>
#include "node.cpp"
using namespace std;

class Edge {
public:
    sf::RectangleShape shape;
    static const int thickness = 2;
    int nodeId1, nodeId2;
    bool spt;

    Edge(const Node& a, const Node& b) : nodeId1(a.id), nodeId2(b.id), spt(false){
        sf::Vector2f positionA = a.shape.getPosition();
        sf::Vector2f positionB = b.shape.getPosition();

        sf::Vector2f direction = positionB - positionA;
        sf::Vector2f unitDirection = direction / sqrt(direction.x*direction.x + direction.y*direction.y);
        sf::Vector2f unitPerpendicular(-unitDirection.y, unitDirection.x);

        sf::Vector2f offset = (float)(thickness / 2) * unitPerpendicular;

        shape.setSize(sf::Vector2f(sqrt(direction.x*direction.x + direction.y*direction.y), thickness));
        shape.setPosition(positionA + offset);
        shape.setFillColor(sf::Color::White);

        float angle = atan2(direction.y, direction.x) * 180 / 3.14159265;
        shape.setRotation(angle);
    }

    bool operator==(const Edge& other) const {
        return (nodeId1 == other.nodeId1 && nodeId2 == other.nodeId2) ||
               (nodeId1 == other.nodeId2 && nodeId2 == other.nodeId1);
    }

    void highlight(){
        shape.setFillColor(sf::Color::Black);
    }

    void resetColor(){
        shape.setFillColor(sf::Color::White);
    }
};
