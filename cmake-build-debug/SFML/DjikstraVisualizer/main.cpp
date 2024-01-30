#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Graph.cpp"
#include "dropDownMenu.cpp"
#include "Checkbox.cpp"
using namespace std;

int main() {
    ifstream inFile;

    string country;
    string capital;
    string population;
    string size;
    string density;

    vector<pair<bool, loc>> store;

    int count = 0;
    int edgeCount = 15;

    inFile.open("citylist.csv");
    if (inFile.is_open()) {
        cout << "File has been opened" << endl;
    } else {
        cout << "File has not been opened" << endl;
    }
    while (inFile.is_open() && count < 100) {
        getline(inFile, country, ',');
        getline(inFile, capital, ',');
        getline(inFile, population, ',');
        getline(inFile, size, ',');
        inFile >> density;
        loc temp = loc(country, capital, stoi(population), stoi(size), density);
        store.push_back(make_pair(false, temp));
        count++;
    }
    inFile.close();

    Graph g(edgeCount);

    sf::RenderWindow window(sf::VideoMode(1024, 768), "Djikstra Visualizer");
    sf::Font font;
    if (!font.loadFromFile("BRLNSB.TTF")) {
        cout << "Font not available to display text!" << endl;
    }

    sf::RectangleShape infoBox;
    infoBox.setFillColor(sf::Color(200, 200, 200, 200));
    infoBox.setSize(sf::Vector2f(200, 200));

    sf::Text infoText;
    infoText.setFont(font); // Use the same font as nodes
    infoText.setCharacterSize(20);
    infoText.setFillColor(sf::Color::Black);

    sf::RectangleShape menuBck;
    menuBck.setFillColor(sf::Color(200, 200, 255));
    menuBck.setSize(sf::Vector2f(300, 768));
    menuBck.setPosition(724, 0);

    sf::Text ToText;
    ToText.setFont(font);
    ToText.setString("to");
    ToText.setCharacterSize(30);
    ToText.setFillColor(sf::Color::Black);
    ToText.setPosition(858, 105);

    sf::Text shortPath;
    shortPath.setFont(font);
    shortPath.setString("Shortest Path\n        From");
    shortPath.setCharacterSize(30);
    shortPath.setFillColor(sf::Color::Black);
    shortPath.setPosition(775, 20);

    VisGraph visualGraph;

    for (int i = 0; i < 10; ++i) {
        visualGraph.addNodeSafely(font, store);
    }

    visualGraph.randomizeEdges(edgeCount, g);

    vector<int> options;
    for (int i = 0; i < 10; i++) {
        options.push_back(i);
    }
    DropdownMenu menu1(sf::Vector2f(800, 100), sf::Vector2f(50, 50), font, options);
    DropdownMenu menu2(sf::Vector2f(895, 100), sf::Vector2f(50, 50), font, options);

    sf::RectangleShape enterButton(sf::Vector2f(100, 50));
    enterButton.setPosition(915, 710);
    enterButton.setFillColor(sf::Color::Green);

    sf::Text enterButtonText;
    enterButtonText.setFont(font);
    enterButtonText.setString("Enter");
    enterButtonText.setCharacterSize(20);
    enterButtonText.setFillColor(sf::Color::White);
    enterButtonText.setPosition(enterButton.getPosition().x + 25, enterButton.getPosition().y + 10);

    Checkbox check(sf::Vector2f(750, 720), 20, font);

    //Shortest Path Tree
    sf::Text SPT;
    SPT.setFont(font);
    SPT.setString("SPT");
    SPT.setCharacterSize(20);
    SPT.setFillColor(sf::Color::Black);
    SPT.setPosition(780, 717);

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    //Gets the position of the mouse at all times, makes the clicking more accurate
                    sf::Vector2f mousePos(static_cast<float>(event.mouseButton.x),
                                          static_cast<float>(event.mouseButton.y));
                    if (enterButton.getGlobalBounds().contains(mousePos)) {
                        //shortest path vector
                        vector<int> sp;
                        g.shortestPath(sp, menu1.getSelectedItemIndex(), menu2.getSelectedItemIndex());
                        for (auto &i: visualGraph.edgeVec()) {
                            i.resetColor();
                        }
                        if (sp[0] != sp[1]) {
                            cout << sp.size();
                            for (int i = sp.size() - 1; i > 0; --i) {
                                visualGraph.edgeHighlight(sp[i], sp[i - 1]);
                                cout << sp[i] << endl;
                            }
                        }
                    }
                    if (check.contains(mousePos)) {
                        check.toggle();
                        if(check.checked()) {
                            for (int x = 0; x < 10; x++) {
                                vector<int> sp;
                                g.shortestPath(sp, menu1.getSelectedItemIndex(), x);
                                if (sp[0] != sp[1]) {
                                    cout << sp.size();
                                    for (int i = sp.size() - 1; i > 0; --i) {
                                        visualGraph.edgeDraw(sp[i], sp[i - 1]);
                                        cout << sp[i] << endl;
                                    }
                                }
                            }
                        }else{
                            for (auto &i: visualGraph.edgeVec()) {
                                i.spt=false;
                            }
                        }
                    }
                }
            }
        }
        sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
        auto [isHovering, nodeId] = visualGraph.getNodeIndexAtPosition(mousePos);
        bool showInfoBox = isHovering;

        if (showInfoBox && nodeId != -1) {
            infoText.setString("Country: " + visualGraph.getCountry(nodeId) +
                               "\nCapital: " + visualGraph.getCapital(nodeId) +
                               "\nPopulation: " + to_string(visualGraph.getPopulation(nodeId)) +
                               "\nSize(mi^2): " + to_string(visualGraph.getSize(nodeId)) +
                               "\nDensity(ppl/mi^2): " + visualGraph.getDensity(nodeId));
            sf::FloatRect textBounds = infoText.getLocalBounds();
            infoBox.setSize(sf::Vector2f(textBounds.width + 20, textBounds.height + 20));
            infoBox.setPosition(mousePos.x, mousePos.y);

            // Keep the box within window bounds
            if (infoBox.getPosition().x + infoBox.getSize().x > window.getSize().x) {
                infoBox.setPosition(window.getSize().x - infoBox.getSize().x, infoBox.getPosition().y);
            }
            if (infoBox.getPosition().y + infoBox.getSize().y > window.getSize().y) {
                infoBox.setPosition(infoBox.getPosition().x, window.getSize().y - infoBox.getSize().y);
            }

            infoText.setPosition(infoBox.getPosition().x + 10, infoBox.getPosition().y + 5);

            window.draw(infoBox);
            window.draw(infoText);
        }

        window.clear(sf::Color(250, 157, 105));
        visualGraph.draw(window, check.checked());
        window.draw(menuBck);
        menu1.handleEvent(event, window);
        menu1.draw(window);
        menu2.handleEvent(event, window);
        menu2.draw(window);
        window.draw(ToText);
        window.draw(shortPath);
        window.draw(SPT);
        check.draw(window);
        window.draw(enterButton);
        window.draw(enterButtonText);
        window.display();
    }
        return 0;
    }