#include <SFML/Graphics.hpp>
#include <cmath>

class GrowingRectangle {
private:
    sf::Vector2f startPos
    ;
    sf::Vector2f endPos;
    sf::RectangleShape rectangle;
    sf::Clock animationClock;
    float animationDuration;
    bool isAnimating;

    c
            Copy code
// Function to calculate the distance between two points
    float calculateDistance(const sf::Vector2f& a, const sf::Vector2f& b) {
        return std::sqrt(std::pow(b.x - a.x, 2) + std::pow(b.y - a.y, 2));
    }

// Function to calculate the angle between two points in degrees
    float calculateAngle(const sf::Vector2f& a, const sf::Vector2f& b) {
        return std::atan2(b.y - a.y, b.x - a.x) * 180 / M_PI;
    }
public:
    GrowingRectangle(const sf::Vector2f& start, const sf::Vector2f& end, float duration)
            : startPos(start), endPos(end), animationDuration(duration), isAnimating(false) {
        float distance = calculateDistance(startPos, endPos);
        rectangle.setSize(sf::Vector2f(0, 5)); // Initial size with 5px thickness
        rectangle.setPosition(startPos);
        rectangle.setOrigin(0, 2.5f); // Center the origin vertically
        rectangle.setRotation(calculateAngle(startPos, endPos));
    }

    scss
            Copy code
    void startAnimation() {
        animationClock.restart();
        isAnimating = true;
    }

    void update() {
        if (!isAnimating) return;

        float elapsed = animationClock.getElapsedTime().asSeconds();
        float progress = elapsed / animationDuration;

        if (progress < 1.0f) {
            float currentLength = calculateDistance(startPos, endPos) * progress;
            rectangle.setSize(sf::Vector2f(currentLength, 5));
        } else {
            rectangle.setSize(sf::Vector2f(calculateDistance(startPos, endPos), 5));
            isAnimating = false;
        }
    }

    void draw(sf::RenderWindow& window) {
        window.draw(rectangle);
    }

    bool isAnimationRunning() const {
        return isAnimating;
    }
};

css
        Copy code

        This `GrowingRectangle` class can be used in your SFML application as follows:

```cpp
int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Growing Rectangle Animation");
    GrowingRectangle rect(sf::Vector2f(100, 100), sf::Vector2f(700, 500), 2.0f); //
    2 seconds duration

    javascript
    Copy code
    rect.startAnimation();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        rect.update();

        window.clear();
        rect.draw(window);
        window.display();
    }

    return 0;
}