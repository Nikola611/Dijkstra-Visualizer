#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <chrono>
using namespace std;

class DropdownMenu {
private:
    sf::Font font;
    sf::RectangleShape mainButton;
    sf::Text mainButtonText;
    vector<sf::RectangleShape> items;
    vector<sf::Text> itemTexts;
    bool isOpen;
    float itemHeight;
    int selectedItemIndex;
    chrono::steady_clock::time_point lastToggleTime;
    const chrono::milliseconds toggleDelay = chrono::milliseconds(200);

public:
    DropdownMenu(const sf::Vector2f &position, const sf::Vector2f &size, const sf::Font &font,
                 const vector<int> &options)
            : font(font), isOpen(false), itemHeight(size.y), selectedItemIndex(0) {
        mainButton.setSize(size);
        mainButton.setPosition(position);
        mainButton.setFillColor(sf::Color::White);

        mainButtonText.setFont(font);
        mainButtonText.setCharacterSize(20);
        mainButtonText.setFillColor(sf::Color::Black);
        mainButtonText.setString("0");
        mainButtonText.setPosition(position.x + 18, position.y+10);

        for (const auto &option: options) {
            sf::RectangleShape item(size);
            item.setFillColor(sf::Color::White);
            items.push_back(item);

            sf::Text text(to_string(option), font, 20);
            text.setFillColor(sf::Color::Black);
            itemTexts.push_back(text);
        }

        updateItems();
    }

    void updateItems() {
        for (size_t i = 0; i < items.size(); ++i) {
            items[i].setPosition(mainButton.getPosition().x, mainButton.getPosition().y + itemHeight * (i + 1));
            itemTexts[i].setPosition(mainButton.getPosition().x + 18,
                                     mainButton.getPosition().y + itemHeight * (i + 1)+10);
        }
    }

    void draw(sf::RenderWindow &window) {
        window.draw(mainButton);
        window.draw(mainButtonText);

        if (isOpen) {
            for (size_t i = 0; i < items.size(); ++i) {
                window.draw(items[i]);
                window.draw(itemTexts[i]);
            }
        }
    }

    int getSelectedItemIndex(){
        return selectedItemIndex;
    }

    void handleEvent(const sf::Event& event, sf::RenderWindow& window) {
        auto now = chrono::steady_clock::now();
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));

                if (mainButton.getGlobalBounds().contains(mousePos) && now - lastToggleTime > toggleDelay) {
                    isOpen = !isOpen;
                    lastToggleTime = now;
                    updateItems();
                } else if (isOpen) {
                    for (size_t i = 0; i < items.size(); ++i) {
                        if (items[i].getGlobalBounds().contains(mousePos)) {
                            selectedItemIndex = i;
                            mainButtonText.setString(itemTexts[i].getString());
                            isOpen = false;
                            lastToggleTime = now;
                            break;
                        }
                    }
                }
            }
        }
    }
};
