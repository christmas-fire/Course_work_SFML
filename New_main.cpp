// Библиотеки C++
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

    // Библиотеки C
#include <stdlib.h>
#include <time.h>

using namespace std;
using namespace sf;

    // Создаем окно
static void initWindow(RenderWindow& window, int width, int height) {
    window.create(VideoMode(width, height), L"Курсовая работа: Змейка");
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);
}

    // Задаем иконку
static void setIcon(Image& icon, RenderWindow& window) {
    if (!icon.loadFromFile("Icons/icon.png")) {
        cerr << "Не загрузились иконки!" << endl;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

    // Задаем текстуры
static void setTextures(Texture& texture_apple,
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

int main() {
    // Подкючаем генератор случайных чисел из C
    srand(time(NULL));

    int width = 900;
    int height = 600;

    RenderWindow window;
    initWindow(window, width, height);

    Image icon;
    setIcon(icon, window);

    Texture texture_apple, texture_watermelon, texture_snake_head, texture_snake_part;
    setTextures(texture_apple, texture_watermelon, texture_snake_head, texture_snake_part);

    Sprite apple(texture_apple), watermelon(texture_watermelon), snake_head(texture_snake_head), snake_part(texture_snake_part);

    apple.setPosition(450, 100);
    watermelon.setPosition(450, 200);
    //snake_head.setPosition(450, 300);
    snake_part.setPosition(450, 400);

    RectangleShape snakeShape(Vector2f(40, 40));
    snakeShape.setFillColor(Color::Cyan);

    vector <RectangleShape> snake;
    snake.push_back(snakeShape);
    snake[0].setPosition(width / 2, height / 2);
    snake_head.setPosition(width / 2, height / 2);

    // Game loop
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(apple);
        window.draw(watermelon);
        window.draw(snake_part);

        for (const auto& i : snake) {
            window.draw(i);
            window.draw(snake_head);
        }
        window.display();
    }

    return 0;
}