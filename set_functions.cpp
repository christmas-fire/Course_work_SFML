// Библиотеки C++
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <sstream>

    // Библиотеки C
#include <stdlib.h>
#include <time.h>

    // Пространства имен
using namespace std;
using namespace sf;

// Создаем окно
void setWindow(RenderWindow& window, int width, int height) {
    window.create(VideoMode(width, height), L"Курсовая работа: Змейка");
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(10);
}

// Задаем шрифт
void setFont(Font& font) {
    if (!font.loadFromFile("Fonts/Roboto-Medium.ttf")) {
        cerr << "Не загрузился шрифт!" << endl;
    }
}

void setBorder(RectangleShape& border) {
    border.setFillColor(Color::Transparent);
    border.setOutlineColor(sf::Color::White);
    border.setOutlineThickness(2);
    border.setPosition(2, 2);
}

// Задаем отображение счетчика
void setCounter(Font& font, Text& fruit_count_text) {
    fruit_count_text.setFont(font);
    fruit_count_text.setCharacterSize(28);
    fruit_count_text.setFillColor(Color::White);
    fruit_count_text.setPosition(270, 800);
}

// Обновляем счетчик на экране
void refreshCounter(Text& fruit_count_text, int fruit_count) {
    wstringstream ss;
    ss << L"Съедено фруктов: " << fruit_count;
    fruit_count_text.setString(ss.str());
}

// Задаем иконку
void setIcon(Image& icon, RenderWindow& window) {
    if (!icon.loadFromFile("Icons/icon.png")) {
        cerr << "Не загрузились иконки!" << endl;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

// Задаем текстуры
void setTextures(Texture& texture_apple,
    Texture& texture_strawberry,
    Texture& texture_snake_head,
    Texture& texture_snake_part,
    Texture& texture_background)                                    
{
    if (!texture_apple.loadFromFile("Sprites/apple.png") ||
        !texture_strawberry.loadFromFile("Sprites/strawberry.png") ||
        !texture_snake_head.loadFromFile("Sprites/snake_head.png") ||
        !texture_snake_part.loadFromFile("Sprites/snake_part.png") ||
        !texture_background.loadFromFile("Sprites/background.png"))
    {
        cerr << "Не загрузились текстуры!" << endl;
    }
}

void setSound(SoundBuffer& buffer) {
    if (!buffer.loadFromFile("Music/burping.ogg")) {
        cerr << "Не загрузились звуки!" << endl;
    }
}

void setMenu(RectangleShape& menu_box, Text& menu_text_title, Text& menu_text_pressToStart, Font& font) {
    menu_box.setPosition(6 * 40, 2 * 40);
    menu_box.setFillColor(Color::Black);
    menu_box.setOutlineColor(Color::White);
    menu_box.setOutlineThickness(2);

    menu_text_title.setFont(font);
    menu_text_title.setPosition((7 * 40) - 10, (3 * 40) - 10);
    menu_text_title.setCharacterSize(50);
    menu_text_title.setFillColor(Color::White);
    menu_text_title.setString("SnakeGame");

    menu_text_pressToStart.setFont(font);
    menu_text_pressToStart.setPosition((7 * 40) - 10, (4 * 40) + 15);
    menu_text_pressToStart.setCharacterSize(20);
    menu_text_pressToStart.setFillColor(Color::White);
    menu_text_pressToStart.setString("Press 'Enter' to start");


}