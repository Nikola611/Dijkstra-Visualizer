#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "DjikstraAlg.cpp"
using namespace std;

class Node {
public:
    sf::CircleShape shape;
    sf::CircleShape highlightShape;
    sf::CircleShape shadowShape;
    sf::Text num;
    static const int radius = 15;
    int id;
    loc location;

    Node(float x, float y, int id, const sf::Font& font, vector<pair<bool, loc>> store) : id(id) {
        shape.setPosition(x, y);
        shape.setRadius(radius);
        shape.setFillColor(sf::Color(168,150,230,255));
        shape.setOrigin(radius, radius);

        highlightShape.setPosition(x - 2, y - 2);
        highlightShape.setRadius(radius);
        highlightShape.setFillColor(sf::Color(170, 170, 230, 100)); // Lighter, semi-transparent
        highlightShape.setOrigin(radius, radius);

        shadowShape.setPosition(x + 3, y + 3);
        shadowShape.setRadius(radius);
        shadowShape.setFillColor(sf::Color(100, 100, 230, 230)); // Darker, semi-transparent
        shadowShape.setOrigin(radius, radius);


        num.setFont(font);
        num.setCharacterSize(25);
        num.setPosition(x-8, y-15);
        num.setString(to_string(id));
        num.setFillColor(sf::Color::Black);

        int rngLoc = rand()%99;
        while(store[rngLoc].first){
            rngLoc = rand()%99;
        }
        store[rngLoc].first = true;
        location = store[rngLoc].second;

    }
};
