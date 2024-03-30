// Библиотеки C++
#include <SFML/Graphics.hpp>
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
    window.setFramerateLimit(60);
}

// Задаем шрифт
void setFont(Font& font) {
    if (!font.loadFromFile("Fonts/Roboto-Medium.ttf")) {
        cerr << "Не загрузился шрифт!" << endl;
    }
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
    Texture& texture_snake_part
)
{
    if (!texture_apple.loadFromFile("Sprites/apple.png") ||
        !texture_strawberry.loadFromFile("Sprites/strawberry.png") ||
        !texture_snake_head.loadFromFile("Sprites/snake_head.png") ||
        !texture_snake_part.loadFromFile("Sprites/snake_part.png"))
    {
        cerr << "Не загрузились текстуры!" << endl;
    }
}