#include <SFML/Graphics.hpp>
using namespace std;

class Checkbox {
private:
    sf::RectangleShape box;
    bool isChecked;

public:
    Checkbox(const sf::Vector2f& position, float size, sf::Font font) : isChecked(false) {
        box.setSize(sf::Vector2f(size, size));
        box.setPosition(position);
        box.setFillColor(sf::Color::White);
        box.setOutlineColor(sf::Color::Black);
        box.setOutlineThickness(1);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(box);
        if (isChecked) {
            sf::RectangleShape check(sf::Vector2f(box.getSize().x * 0.7f, box.getSize().y * 0.7f));
            check.setPosition(box.getPosition().x + box.getSize().x * 0.15f,
                              box.getPosition().y + box.getSize().y * 0.15f);
            check.setFillColor(sf::Color::Green);
            window.draw(check);
        }
    }

    void toggle() {
        isChecked = !isChecked;
    }

    bool contains(const sf::Vector2f& point) const {
        return box.getGlobalBounds().contains(point);
    }

    bool checked() const {
        return isChecked;
    }
};