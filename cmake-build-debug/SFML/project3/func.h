/*#pragma once
sf::RenderWindow gameWindow(sf::VideoMode(1, 1), "Game Window");
while(gameWindow.isOpen()  && progress == 1)
{
sf::Event event;
welcomeWindow.clear(sf::Color(192, 192, 192, 255));
while (welcomeWindow.pollEvent(event)) {
if (event.type == sf::Event::Closed) {
gameWindow.close();
}
if (cursor.loadFromSystem(sf::Cursor::Arrow)) {
welcomeWindow.setMouseCursor(cursor);
}
}
gameWindow.display();
}
*/