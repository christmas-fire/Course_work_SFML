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

// Заголовочные файлы
#include <set_functions.h>    

    // Генерируем случайные координаты
int genRandCords(int window_side, int size) {
    return rand() % (window_side - size);
}

int main() {
    // Подкючаем генератор случайных чисел из C
    srand(time(NULL));

    int width = 800;
    int height = 800;

    int width_rand = genRandCords(width, 40);
    int height_rand = genRandCords(height, 40);

    int fruit_count = 0;

    RenderWindow window;
    setWindow(window, width, height);

    Image icon;
    setIcon(icon, window);

    Texture texture_apple, texture_strawberry, texture_snake_head, texture_snake_part, texture_background_grey;
    setTextures(texture_apple, texture_strawberry, texture_snake_head, texture_snake_part, texture_background_grey);

    Sprite apple(texture_apple), strawberry(texture_strawberry), snake_head(texture_snake_head), snake_part(texture_snake_part), background_grey(texture_background_grey);

    strawberry.setPosition(width_rand, height_rand);

    Font font;
    Text fruit_count_text;
    RectangleShape box(Vector2f(80, 40));

    setFont(font);
    setCounter(font, fruit_count_text, box);

    // Задаем форму всем частям змейки
    RectangleShape snakeShape(Vector2f(40, 40));
    snakeShape.setFillColor(Color::Magenta);

    // Создаем змейку
    vector <RectangleShape> snake;
    snake.push_back(snakeShape);
    snake[0].setPosition(width / 2, height / 2);
    snake.push_back(snakeShape);
    snake[1].setPosition((width / 2) - 40, height / 2);
    snake_head.setPosition(width / 2, height / 2);

    // Создаем направления
    struct Direction {
        string choice;
    };

    Direction dir;
    dir.choice = "None";

    int gameIsRunning = 0;

    // Game loop
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }
        window.clear();

        // Начинаем наше движение
        if (!gameIsRunning) {
            if (Keyboard::isKeyPressed(Keyboard::Right)) {
                gameIsRunning = 1;
                dir.choice = "Right";
            }
            else if (Keyboard::isKeyPressed(Keyboard::Up)) {
                gameIsRunning = 1;
                dir.choice = "Up";
            }
            else if (Keyboard::isKeyPressed(Keyboard::Down)) {
                gameIsRunning = 1;
                dir.choice = "Down";
            }
        } else {
            if (Keyboard::isKeyPressed(Keyboard::Up) && dir.choice != "Down") {
                dir.choice = "Up";
            }
            else if (Keyboard::isKeyPressed(Keyboard::Down) && dir.choice != "Up") {
                dir.choice = "Down";
            }
            else if (Keyboard::isKeyPressed(Keyboard::Left) && dir.choice != "Right") {
                dir.choice = "Left";
            }
            else if (Keyboard::isKeyPressed(Keyboard::Right) && dir.choice != "Left") {
                dir.choice = "Right";
            }
        }

        // Если мы съедим фрукт
        if (snake[0].getGlobalBounds().intersects(strawberry.getGlobalBounds())) {
            fruit_count++;
            width_rand = genRandCords(width, 40);
            height_rand = genRandCords(height, 40);
            strawberry.setPosition(width_rand, height_rand);

            if (dir.choice == "Up") {
                snake.push_back(snakeShape);
                snake.back().setPosition(snake[snake.size()-2].getPosition().x, snake[snake.size() - 2].getPosition().y + 40);
            }
            else if (dir.choice == "Down") {
                snake.push_back(snakeShape);
                snake.back().setPosition(snake[snake.size() - 2].getPosition().x, snake[snake.size() - 2].getPosition().y - 40);
            }
            else if (dir.choice == "Left") {
                snake.push_back(snakeShape);
                snake.back().setPosition(snake[snake.size() - 2].getPosition().x+40, snake[snake.size() - 2].getPosition().y);
            }
            else if (dir.choice == "Right") {
                snake.push_back(snakeShape);
                snake.back().setPosition(snake[snake.size() - 2].getPosition().x-40, snake[snake.size() - 2].getPosition().y);
            }
        }

        refreshCounter(fruit_count_text, fruit_count);

        // Движение частей змейки друг за другом
        if (dir.choice != "None")
            for (int i = snake.size() - 1; i > 0; i--) {
                snake[i].setPosition(snake[i - 1].getPosition().x, snake[i - 1].getPosition().y);
            }

        // Движение по стрелочкам
        if (dir.choice == "Up") {
            snake[0].move(0, -40);
        }
        else if (dir.choice == "Down") {
            snake[0].move(0, 40);
        }
        else if (dir.choice == "Left") {
            snake[0].move(-40, 0);
        }
        else if (dir.choice == "Right") {
            snake[0].move(40, 0);
        }

        // Закрываем окно при столкновении с границами окна
        if (snake[0].getPosition().x < 0 || snake[0].getPosition().y < 0 ||
            snake[0].getPosition().x >(width - 40) || snake[0].getPosition().y >(height - 40)) {
            window.close();
        }

        // Отрисовываем объекты
        window.draw(strawberry);
        window.draw(box);
        window.draw(fruit_count_text);

        for (auto i : snake) {
            window.draw(i);
        }

        window.display();
    }

    return 0;
}