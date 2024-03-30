    // Библиотеки C++
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

    // Библиотеки C
#include <stdlib.h>
#include <time.h>

    // Пространства имен
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

    // Генерируем случайные координаты
static int genRandCords(int window_side, int size) {
    return rand() % (window_side - size);
}

int main() {
    // Подкючаем генератор случайных чисел из C
    srand(time(NULL));

    int width = 900;
    int height = 600;

    int width_rand = genRandCords(width, 40);
    int height_rand = genRandCords(height, 40);

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

    snake.push_back(snakeShape);
    snake[1].setPosition(snake[0].getPosition().x, snake[0].getPosition().y + 40);
    snake[1].setFillColor(Color::Red);

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
            width_rand = genRandCords(width, 40);
            height_rand = genRandCords(height, 40);
            apple.setPosition(width_rand, height_rand);
        }

        // Движение по стрелочкам
        if (dir.choice == "Up") {
            snake[0].move(0, -5);
            snake[1].move(0, -5);
        } else if (dir.choice == "Down") {
            snake[0].move(0, 5);
            snake[1].move(0, 5);
        } else if (dir.choice == "Left") {
            snake[0].move(-5, 0);
            snake[1].move(-5, 0);
        } else if (dir.choice == "Right") {
            snake[0].move(5, 0);
            snake[1].move(5, 0);
        }

        window.clear();
        window.draw(apple);
        window.draw(watermelon);
        window.draw(snake_part);

        for (const auto& i : snake) {
            window.draw(i);
            //window.draw(snake_head);
        }
        window.display();
    }

    return 0;
}