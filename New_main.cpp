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
static int genRandCords(int window_side, int size) {
    return rand() % (window_side - size);
}

int main() {
    // Подкючаем генератор случайных чисел из C
    srand(time(NULL));

    int width = 800;
    int height = 600;

    int width_rand = genRandCords(width, 40);
    int height_rand = genRandCords(height, 40);

    int fruit_count = 0;

    RenderWindow window;
    setWindow(window, width, height);

    Image icon;
    setIcon(icon, window);

    Texture texture_apple, texture_strawberry, texture_snake_head, texture_snake_part;
    setTextures(texture_apple, texture_strawberry, texture_snake_head, texture_snake_part);

    Sprite apple(texture_apple), strawberry(texture_strawberry), snake_head(texture_snake_head), snake_part(texture_snake_part);

    apple.setPosition(450, 100);
    strawberry.setPosition(450, 200);
    snake_part.setPosition(450, 400);

    RectangleShape box(Vector2f(80, 40));
    box.setFillColor(Color::Black);
    box.setOutlineColor(sf::Color::White);
    box.setOutlineThickness(2);
    box.setPosition(0, 0);

    Font font;
    setFont(font);

    Text fruit_count_text;
    fruit_count_text.setFont(font);
    fruit_count_text.setCharacterSize(30);
    fruit_count_text.setFillColor(Color::White);
    fruit_count_text.setPosition(10, 0);

    RectangleShape snakeShape(Vector2f(40, 40));
    snakeShape.setFillColor(Color::Cyan);

    vector <RectangleShape> snake;
    snake.push_back(snakeShape);
    snake[0].setPosition(width / 2, height / 2);
    snake_head.setPosition(width / 2, height / 2);

    struct Direction {
        string choice;
    };
    
    Direction dir;
    dir.choice = "None";

    // Game loop
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            else if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Up && dir.choice != "Down") {
                    dir.choice = "Up";
                }
                else if (event.key.code == Keyboard::Down && dir.choice != "Up") {
                    dir.choice = "Down";
                }
                else if (event.key.code == Keyboard::Left && dir.choice != "Right") {
                    dir.choice = "Left";
                }
                else if (event.key.code == Keyboard::Right && dir.choice != "Left") {
                    dir.choice = "Right";
                }
            }
        }

         // Если мы съедим фрукт
        if (snake[0].getGlobalBounds().intersects(apple.getGlobalBounds())) {
            fruit_count++;
            width_rand = genRandCords(width, 40);
            height_rand = genRandCords(height, 40);
            apple.setPosition(width_rand, height_rand);

            //if (dir.choice == "Up") {
            //    snake.push_back(snakeShape);
            //    snake.back().setPosition(snake[0].getPosition().x, snake[0].getPosition().y + 40);
            //    window.draw(snake.back());
            //}
            //else if (dir.choice == "Down") {
            //    snake.push_back(snakeShape);
            //    snake.back().setPosition(snake[0].getPosition().x, snake[0].getPosition().y - 40);
            //    window.draw(snake.back());
            //}
            //else if (dir.choice == "Left") {
            //    snake.push_back(snakeShape);
            //    snake.back().setPosition(snake[0].getPosition().x+40, snake[0].getPosition().y);
            //    window.draw(snake.back());
            //}
            //else if (dir.choice == "Right") {
            //    snake.push_back(snakeShape);
            //    snake.back().setPosition(snake[0].getPosition().x-40, snake[0].getPosition().y);
            //    window.draw(snake.back());
            //}
        }

        wstringstream ss;
        ss << fruit_count;
        fruit_count_text.setString(ss.str());

        // Движение по стрелочкам
        if (dir.choice == "Up") {
            snake[0].move(0, -5);
            snake_head.move(0, -5);
        }
        else if (dir.choice == "Down") {
            snake[0].move(0, 5);
            snake_head.move(0, 5);
        }
        else if (dir.choice == "Left") {
            snake[0].move(-5, 0);
            snake_head.move(-5, 0);
        }
        else if (dir.choice == "Right") {
            snake[0].move(5, 0);
            snake_head.move(5, 0);
        }

        if (snake[0].getPosition().x < 0 || snake[0].getPosition().y < 0 ||
            snake[0].getPosition().x > (width-40) || snake[0].getPosition().y > (height-40)) {
            window.close();
        }
        
        window.clear();
        window.draw(apple);
        window.draw(strawberry);
        window.draw(snake_part);

        window.draw(box);
        window.draw(fruit_count_text);

        for (auto& i : snake) {
            window.draw(i);
            window.draw(snake_head);
        }
        window.display();
    }

    return 0;
}