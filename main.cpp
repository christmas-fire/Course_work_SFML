    // Библиотеки C++
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

    // Библиотеки C
#include <stdlib.h>
#include <time.h>

using namespace std;
using namespace sf;

int main() {
    // Подкючаем генератор рандомных чисел из C
    srand(time(NULL));

    // Размеры окна
    int width = 900;
    int height = 600;

    // Координаты центра
    int width_center = width / 2;
    int height_center = height / 2;

    // Рандомные координаты
    int width_random = rand() % (width - 40);
    int height_random = rand() % (height - 40);

    // Размеры элементов змейки
    int width_snake = 40;
    int height_snake = 40;

    // Количество фруктов
    int fruit_count = 0;
    //int fruit_choice = rand() % 2;

    // Создаем окно
    RenderWindow window(VideoMode(width, height), L"Курсовая работа: Змейка");

    // Задаем вертикалку + лок в 60 фпс
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    // Загружаем иконку окна
    Image icon;
    if (!icon.loadFromFile("icon.png")) {
        cerr << "Failed to load icon!" << endl;
        return 1;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // Задаем объекты класса текстур и загружаем спрайты
    Texture texture_snake_head;
    if (!texture_snake_head.loadFromFile("snake_head.png")) {
        cerr << "Failed to load texture!" << endl;
        return -1;
    }
    Sprite snake_head(texture_snake_head);
    snake_head.setPosition(width_center, height_center);

    Texture texture_snake_part;
    if (!texture_snake_part.loadFromFile("snake_part.png")) {
        cerr << "Failed to load texture!" << endl;
        return -1;
    }
    Sprite snake_part(texture_snake_part);

    Texture texture_apple;
    if (!texture_apple.loadFromFile("strawberry.png")) {
        cerr << "Failed to load texture!" << endl;
        return -1;
    }
    Sprite apple(texture_apple);
    apple.setPosition(width_random, height_random);
 /*   bool isApple = true;*/

    Texture texture_watermelon;
    if (!texture_watermelon.loadFromFile("watermelon.png")) {
        cerr << "Failed to load texture!" << endl;
        return -1;
    }
    Sprite watermelon(texture_watermelon);
  
    // Создаем змейку
    vector <RectangleShape> snake;
    snake.push_back(RectangleShape(Vector2f(width_snake, height_snake)));
    snake[0].setFillColor(Color::Green);
    snake[0].setPosition(width_center, height_center);

    // Создаем класс направлений
    enum class Direction { None, Up, Down, Left, Right };
    Direction dir = Direction::Right;

    // "Game loop"
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
            else if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Up && dir != Direction::Down)
                    dir = Direction::Up;
                else if (event.key.code == Keyboard::Down && dir != Direction::Up)
                    dir = Direction::Down;
                else if (event.key.code == Keyboard::Left && dir != Direction::Right)
                    dir = Direction::Left;
                else if (event.key.code == Keyboard::Right && dir != Direction::Left)
                    dir = Direction::Right;
            }
        }

        // Координаты головы змейки
        Vector2f headPos = snake[0].getPosition();

        // Создаем часть змейки
        RectangleShape newPart(Vector2f(width_snake, height_snake));
        newPart.setFillColor(Color::Black);

        // Проверяем столкновение с фруктом
        if (snake.size() > 0 && snake[0].getGlobalBounds().intersects(apple.getGlobalBounds())
            /*|| snake.size() > 0 && snake[0].getGlobalBounds().intersects(watermelon.getGlobalBounds())*/) {

            for (int i = 0; i < 2; i++) {
                newPart.setPosition(snake.back().getPosition().x + 20, snake.back().getPosition().y + 20);
                snake_part.setPosition(snake.back().getPosition().x+20, snake.back().getPosition().y+20);
                newPart.setFillColor(Color::Cyan);
                snake.push_back(newPart);
                
            }

            // Обновляем число собранных фруктов
            fruit_count += 1;

            // Обновляем рандомные числа
            width_random = rand() % (width - width_snake);
            height_random = rand() % (height - height_snake);

            // Обновляем позицию яблока
            apple.setPosition(width_random, height_random);
            //fruit_choice = rand() % 2;

            // В зависимости от рандомного числа (от 1 до 3) рисуем соответствующий фрукт
            //if (isApple) {
            //    apple.setPosition(width_random, height_random);
            //}
            //else {
            //    watermelon.setPosition(width_random, height_random);
            //}
            //isApple = !isApple;


        //    if (snake.size() > 1) {
        //        newPart.setPosition(snake.back().getPosition().x+20, snake.back().getPosition().y+20);
        //        snake_part.setPosition(snake.back().getPosition().x, snake.back().getPosition().y);
        //    } else {
        //        newPart.setPosition(snake[0].getPosition().x, snake[0].getPosition().y);
        //    }
        //    snake.push_back(newPart);

        }

        // Закрываем окно если змейка врежется в границы окна
        if (headPos.x < 0 || headPos.x + snake[0].getSize().x > window.getSize().x ||
            headPos.y < 0 || headPos.y + snake[0].getSize().y > window.getSize().y) {
            window.close();
        }

        // Задаем позицию новым частям змейки
        for (int i = snake.size() - 1; i > 0; --i) {
            snake[i].setPosition(snake[i - 1].getPosition().x, snake[i - 1].getPosition().y);
        }

        // Как вариант, с каждой съеденой штучкой прибавлять по 0.1 к шагу
        if (dir == Direction::Up) {
            snake[0].move(0, -5);
            snake_head.move(0, -5);
        } else if (dir == Direction::Down) {
            snake[0].move(0, 5);
            snake_head.move(0, 5);
        } else if (dir == Direction::Left){
            snake[0].move(-5, 0);
            snake_head.move(-5, 0);
        } else if (dir == Direction::Right) {
            snake[0].move(5, 0);
            snake_head.move(5, 0);
        }
            
        window.clear();
        window.draw(apple);
        //if (isApple) {
        //    window.draw(apple);
        //}
        //else {
        //    window.draw(watermelon);
        //}
        for (const auto& i : snake) {
            window.draw(i);
            window.draw(snake_head);
        }
        window.display();
    }

    return 0;
}
