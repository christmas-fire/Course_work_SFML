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

// Заголовочные файлы
#include <set_functions.h>    

    // Генерируем случайные координаты
int genRandCords() {
    return rand() % 20 * 40;
}

int main() {
    // Подкючаем RNG из C
    srand(time(NULL));

    int width = 800;
    int height = 840;

    int game_width = 800;
    int game_height = 800;

    int game_width_rand = genRandCords();
    int game_height_rand = genRandCords();

    int fruit_count = 0;

    // "Булевы" переменные, которые отслеживают начало/конец игры
    bool gameIsRunning = false;
    bool isMenu = true;
    bool isEnterPressed = false;
    bool gameIsFailed = false;
    bool isEscPressed = false;

    RenderWindow window;
    setWindow(window, width, height);

    Image icon;
    setIcon(icon, window);

    RectangleShape border(Vector2f(800 - 4, 800 - 2));
    setBorder(border);

    Texture texture_apple, texture_strawberry, texture_snake_head, texture_snake_part, texture_background;
    setTextures(texture_apple, texture_strawberry, texture_snake_head, texture_snake_part, texture_background);

    Sprite apple(texture_apple), strawberry(texture_strawberry), snake_head(texture_snake_head), snake_part(texture_snake_part), background(texture_background);

    strawberry.setPosition(game_width_rand, game_height_rand);

    Font font;
    Text fruit_count_text;

    setFont(font);
    setCounter(font, fruit_count_text);

    Sound sound;
    SoundBuffer buffer;

    setSound(buffer);
    sound.setBuffer(buffer);

    // Задаем объекты для меню
    RectangleShape menu_box(Vector2f(16*40, 8*40));
    Text menu_text_title;
    Text menu_text_pressToStart;

    setMenu(menu_box, menu_text_title, menu_text_pressToStart, font);

    // Задаем объекты для экрана конца игры
    RectangleShape fail_screen_box(Vector2f(16 * 40, 8 * 40));
    Text fail_screen_text;
    Text fail_screen_pressToExit;

    setFailScreen(fail_screen_box, fail_screen_text, fail_screen_pressToExit, font, fruit_count);

    // Задаем "форму" всем частям змейки
    RectangleShape snakeShape(Vector2f(40, 40));
    snakeShape.setFillColor(Color::Magenta);

    // Создаем змейку
    vector <RectangleShape> snake;
    vector <Sprite> snake_sprite;

    // Создаем голову
    snake.push_back(snakeShape);
    snake_sprite.push_back(snake_head);
    snake[0].setPosition(game_width / 2, game_height / 2);
    snake_sprite[0].setPosition(game_width / 2, game_height / 2);
    
    // Создаем хвост
    snake.push_back(snakeShape);
    snake_sprite.push_back(snake_part);
    snake[1].setPosition((game_width / 2) - 40, game_height / 2);
    snake_sprite[1].setPosition((game_width / 2) - 40, game_height / 2);

    // Создаем направления
    struct Direction {
        string choice;
    };

    Direction dir;
    dir.choice = "None";

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
 
    // Game loop
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }
        window.clear();
        window.draw(background);
        window.draw(border);

        if (isMenu) {
            window.draw(menu_box);
            window.draw(menu_text_title);
            window.draw(menu_text_pressToStart);
        }

        // Выходим из меню после нажатия на Enter
        if (Keyboard::isKeyPressed(Keyboard::Enter)) {
            isMenu = false;
            isEnterPressed = true;
        }

        if (isEnterPressed) {
            // Начинаем движение
            if (!gameIsRunning) {
                if (Keyboard::isKeyPressed(Keyboard::Right)) {
                    gameIsRunning = true;
                    dir.choice = "Right";
                }
                else if (Keyboard::isKeyPressed(Keyboard::Up)) {
                    gameIsRunning = true;
                    dir.choice = "Up";
                }
                else if (Keyboard::isKeyPressed(Keyboard::Down)) {
                    gameIsRunning = true;
                    dir.choice = "Down";
                }
            }
            else {
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
                sound.play();
                fruit_count++;
                game_width_rand = genRandCords();
                game_height_rand = genRandCords();
                strawberry.setPosition(game_width_rand, game_height_rand);

                // Создаем новую часть змейки с условием от ее направления в момент съедения фрукта
                if (dir.choice == "Up") {
                    snake.push_back(snakeShape);
                    snake.back().setPosition(snake[snake.size() - 2].getPosition().x, snake[snake.size() - 2].getPosition().y + 40);
                    snake_sprite.push_back(snake_part);
                    snake_sprite.back().setPosition(snake_sprite[snake_sprite.size() - 2].getPosition().x, snake_sprite[snake_sprite.size() - 2].getPosition().y + 40);
                }
                else if (dir.choice == "Down") {
                    snake.push_back(snakeShape);
                    snake.back().setPosition(snake[snake.size() - 2].getPosition().x, snake[snake.size() - 2].getPosition().y - 40);
                    snake_sprite.push_back(snake_part);
                    snake_sprite.back().setPosition(snake_sprite[snake_sprite.size() - 2].getPosition().x, snake_sprite[snake_sprite.size() - 2].getPosition().y - 40);

                }
                else if (dir.choice == "Left") {
                    snake.push_back(snakeShape);
                    snake.back().setPosition(snake[snake.size() - 2].getPosition().x + 40, snake[snake.size() - 2].getPosition().y);
                    snake_sprite.push_back(snake_part);
                    snake_sprite.back().setPosition(snake_sprite[snake_sprite.size() - 2].getPosition().x + 40, snake_sprite[snake_sprite.size() - 2].getPosition().y);
                }
                else if (dir.choice == "Right") {
                    snake.push_back(snakeShape);
                    snake.back().setPosition(snake[snake.size() - 2].getPosition().x - 40, snake[snake.size() - 2].getPosition().y);
                    snake_sprite.push_back(snake_part);
                    snake_sprite.back().setPosition(snake_sprite[snake_sprite.size() - 2].getPosition().x - 40, snake_sprite[snake_sprite.size() - 2].getPosition().y);
                }
            }
            refreshCounter(fruit_count_text, fruit_count);

            // Движение частей змейки друг за другом
            if (dir.choice != "None")
                for (int i = snake.size() - 1; i > 0; i--) {
                    snake[i].setPosition(snake[i - 1].getPosition().x, snake[i - 1].getPosition().y);
                    snake_sprite[i].setPosition(snake_sprite[i - 1].getPosition().x, snake_sprite[i - 1].getPosition().y);
                }

            // Движение по стрелочкам
            if (dir.choice == "Up") {
                snake[0].move(0, -40);
                snake_sprite[0].move(0, -40);
            }
            else if (dir.choice == "Down") {
                snake[0].move(0, 40);
                snake_sprite[0].move(0, 40);
            }
            else if (dir.choice == "Left") {
                snake[0].move(-40, 0);
                snake_sprite[0].move(-40, 0);
            }
            else if (dir.choice == "Right") {
                snake[0].move(40, 0);
                snake_sprite[0].move(40, 0);
            }

            // Закрываем окно при столкновении с границами окна
            if (snake[0].getPosition().x < 0 || snake[0].getPosition().y < 0 ||
                snake[0].getPosition().x >(game_width - 40) || snake[0].getPosition().y >(game_height - 40)) {
                //window.close();
                gameIsFailed = true;
            }

            // Закрываем окно при столкновении с самой собой
            for (int i = 0; i < snake.size(); i++) {
                for (int j = 0; j < snake.size(); j++) {
                    if (i == 0 && i != j) {
                        if (snake[0].getGlobalBounds().intersects(snake[j].getGlobalBounds())) {
                            window.close();
                        }

                    }
                }
            }

            // Экран конца игры
            if (gameIsFailed) {
                window.draw(fail_screen_box);
                window.draw(fail_screen_text);
                window.draw(fail_screen_pressToExit);
                if (Keyboard::isKeyPressed(Keyboard::Escape)) {
                    isEscPressed = true;
                }
            }

            if (!gameIsFailed) {
                // Отрисовываем объекты
                window.draw(strawberry);
                window.draw(fruit_count_text);

                // Отрисовываем части змейки
                for (auto i : snake) {
                    window.draw(i);
                }

                // Отрисовываем спрайты змейки
                for (auto i : snake_sprite) {
                    window.draw(i);
                }
            }

            if (isEscPressed) {
                window.close();
            }
        }
        window.display();
    }
    return 0;
}