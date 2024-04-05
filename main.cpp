// Библиотеки C++
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

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
    return (rand() % 20) * 40;
}

int main() {
    // Подкючаем RNG из C
    srand(time(NULL));

    // Локальные переменные
    int width = 800;
    int height = 840;

    int game_width = 800;
    int game_height = 800;

    int game_width_rand = genRandCords();
    int game_height_rand = genRandCords();

    int fruit_count = 0;

    bool isFirstMove = false;
    bool isMenu = true;
    bool gameIsStarted = false;
    bool gameIsFailed = false;
    bool isEscPressed = false;
    bool isRPressed = false;
    bool isSPressed = false;

    // Иннициализируем объекты для окна -> задаем окно
    RenderWindow window;
    setWindow(window, width, height);

    // Иннициализируем объекты для иконки -> задаем иконку
    Image icon;
    setIcon(icon, window);

    // Иннициализируем объекты для границ игрового поля -> задаем границы игрового поля
    RectangleShape border(Vector2f(800 - 4, 800 - 2));
    setBorder(border);

    // Иннициализируем объекты для текстур -> задаем текстуры
    Texture texture_apple, texture_strawberry, texture_snake_head, texture_snake_part, texture_background;
    setTextures(texture_apple, texture_strawberry, texture_snake_head, texture_snake_part, texture_background);

    // Задаем спрайты
    Sprite apple(texture_apple), strawberry(texture_strawberry), snake_head(texture_snake_head), snake_part(texture_snake_part), background(texture_background);
    strawberry.setPosition(game_width_rand, game_height_rand);

    // Иннициализируем объекты для шрифта -> задаем шрифт
    Font font;
    setFont(font);

    // Иннициализируем объекты для счетчика фруктов -> задаем счетчик фруктов
    Text fruit_count_text;
    setCounter(font, fruit_count_text);

    // Иннициализируем объекты для звуков -> задаем звуки
    Sound sound;
    SoundBuffer buffer;
    setSound(buffer);
    sound.setBuffer(buffer);

    // Иннициализируем объекты для меню -> задаем меню
    RectangleShape menu_box(Vector2f(16 * 40, 8 * 40));
    Text menu_text_title;
    Text menu_text_pressToStart;
    setMenu(menu_box, menu_text_title, menu_text_pressToStart, font);

    // Иннициализируем объекты для экрана конца игры -> задаем экран конца игры
    RectangleShape fail_screen_box(Vector2f(16 * 40, 8 * 40));
    Text fail_screen_text;
    Text fail_screen_pressToExit;
    Text fail_screen_pressToStats;
    Text fail_screen_pressToRestart;
    setFailScreen(fail_screen_box, fail_screen_text, fail_screen_pressToExit, fail_screen_pressToStats, fail_screen_pressToRestart, font, fruit_count);

    // Иннициализируем объекты для окна статистики
    RectangleShape stats_box(Vector2f(6 * 40, 3 * 40));
    Text stats_text;

    // Задаем "форму" всем частям змейки
    RectangleShape snakeShape(Vector2f(40, 40));
    snakeShape.setFillColor(Color::Magenta);

    // Иннициализируем векторы, в которых будут храниться части змейки/спрайты к ним
    vector <RectangleShape> snake;
    vector <Sprite> snake_sprite;

    // Задаем голову змейки
    snake.push_back(snakeShape);
    snake_sprite.push_back(snake_head);
    snake[0].setPosition(game_width / 2, game_height / 2);
    snake_sprite[0].setPosition(game_width / 2, game_height / 2);

    // Задаем хвост змейки
    snake.push_back(snakeShape);
    snake_sprite.push_back(snake_part);
    snake[1].setPosition((game_width / 2) - 40, game_height / 2);
    snake_sprite[1].setPosition((game_width / 2) - 40, game_height / 2);

    // Задаем направления
    struct Direction {
        string choice;
    };

    Direction dir;
    dir.choice = "None";

    // Игровой цикл
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }
        window.clear();

        // Отрисовка элементов меню
        if (isMenu) {
            window.draw(background);
            window.draw(border);
            window.draw(menu_box);
            window.draw(menu_text_title);
            window.draw(menu_text_pressToStart);
        }

        // Выходим из меню -> начинаем игру после нажатия на Enter
        if (Keyboard::isKeyPressed(Keyboard::Enter)) {
            isMenu = false;
            gameIsStarted = true;
        }

        if (gameIsStarted) {
            if (!isFirstMove) {
                if (Keyboard::isKeyPressed(Keyboard::Right) ||
                    Keyboard::isKeyPressed(Keyboard::D)) 
                {
                    isFirstMove = true;
                    dir.choice = "Right";
                }
                else if (Keyboard::isKeyPressed(Keyboard::Up) ||
                            Keyboard::isKeyPressed(Keyboard::W)) 
                {
                    isFirstMove = true;
                    dir.choice = "Up";
                }
                else if (Keyboard::isKeyPressed(Keyboard::Down) ||
                            Keyboard::isKeyPressed(Keyboard::S)) 
                {
                    isFirstMove = true;
                    dir.choice = "Down";
                }
            }
            else {
                if (Keyboard::isKeyPressed(Keyboard::Up) && dir.choice != "Down" ||
                    Keyboard::isKeyPressed(Keyboard::W) && dir.choice != "Down")
                {
                    dir.choice = "Up";
                }
                else if (Keyboard::isKeyPressed(Keyboard::Down) && dir.choice != "Up" ||
                    Keyboard::isKeyPressed(Keyboard::S) && dir.choice != "Up")
                {
                    dir.choice = "Down";
                }
                else if (Keyboard::isKeyPressed(Keyboard::Left) && dir.choice != "Right" ||
                    Keyboard::isKeyPressed(Keyboard::A) && dir.choice != "Right")
                {
                    dir.choice = "Left";
                }
                else if (Keyboard::isKeyPressed(Keyboard::Right) && dir.choice != "Left" ||
                    Keyboard::isKeyPressed(Keyboard::D) && dir.choice != "Left")
                {
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

            // Логика движения
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

            // Завершаем игру при столкновении с границами окна
            if (snake[0].getPosition().x < 0 || snake[0].getPosition().y < 0 ||
                snake[0].getPosition().x >(game_width - 40) || snake[0].getPosition().y >(game_height - 40)) {
                gameIsFailed = true;
            }

            // Завершаем игру при столкновении головы змейки с телом
            for (int i = 0; i < snake.size(); i++) {
                for (int j = 0; j < snake.size(); j++) {
                    if (i == 0 && i != j) {
                        if (snake[0].getGlobalBounds().intersects(snake[j].getGlobalBounds())) {
                            gameIsFailed = true;
                        }
                    }
                }
            }

            // Экран конца игры
            if (gameIsFailed) {
                window.draw(background);
                window.draw(border);
                window.draw(fail_screen_box);
                window.draw(fail_screen_text);
                window.draw(fail_screen_pressToExit);
                window.draw(fail_screen_pressToStats);
                window.draw(fail_screen_pressToRestart);

                if (Keyboard::isKeyPressed(Keyboard::Escape)) {
                    isEscPressed = true;
                }
                else if (Keyboard::isKeyPressed(Keyboard::R)) {
                    isRPressed = true;
                }
                else if (Keyboard::isKeyPressed(Keyboard::S)) {
                    isSPressed = true;
                }
            }

            if (!gameIsFailed) {
                window.draw(background);
                window.draw(border);
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

            if (isSPressed) {
                setStats(stats_box, stats_text, font, fruit_count);
                window.draw(stats_box);
                window.draw(stats_text);
            }

            if (isRPressed) {
                resetGame(fruit_count, game_width, game_height, snake, snake_sprite, snake_head, snake_part, isMenu, isFirstMove, gameIsStarted, gameIsFailed);
                dir.choice = "None";
                isRPressed = false;
                isSPressed = false;
            }
        }
        window.display();
    }
    return 0;
}