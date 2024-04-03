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
    window.setFramerateLimit(15);
}

// Задаем шрифт
void setFont(Font& font) {
    if (!font.loadFromFile("Fonts/Roboto-Medium.ttf")) {
        cerr << "Не загрузился шрифт!" << endl;
    }
}

// Задаем отображение счетчика
void setCounter(Font& font, Text& fruit_count_text, RectangleShape& box) {
    box.setFillColor(Color::Transparent);
    box.setOutlineColor(sf::Color::Black);
    box.setOutlineThickness(2);
    box.setPosition(2, 2);

    fruit_count_text.setFont(font);
    fruit_count_text.setCharacterSize(30);
    fruit_count_text.setFillColor(Color::White);
    fruit_count_text.setPosition(270, 805);
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