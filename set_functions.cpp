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

// Задаем окно
void setWindow(RenderWindow& window, int& width, int& height) {
    window.create(VideoMode(width, height), "SnakeGame");
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(10);
}

// Задаем иконку
void setIcon(Image& icon, RenderWindow& window) {
    if (!icon.loadFromFile("Icons/icon.png")) {
        cerr << "Не загрузились иконки!" << endl;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

// Задаем границы игрового поля
void setBorder(RectangleShape& border) {
    border.setFillColor(Color::Transparent);
    border.setOutlineColor(sf::Color::White);
    border.setOutlineThickness(2);
    border.setPosition(2, 2);
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

// Задаем шрифт
void setFont(Font& font) {
    if (!font.loadFromFile("Fonts/Roboto-Medium.ttf")) {
        cerr << "Не загрузился шрифт!" << endl;
    }
}

// Задаем звуки
void setSound(SoundBuffer& buffer) {
    if (!buffer.loadFromFile("Music/burping.ogg")) {
        cerr << "Не загрузились звуки!" << endl;
    }
}

// Задаем меню
void setMenu(RectangleShape& menu_box,
             Text& menu_text_title,
             Text& menu_text_pressToStart,
             Font& font) 
{
    menu_box.setPosition(2 * 40, 6 * 40);
    menu_box.setFillColor(Color::Black);
    menu_box.setOutlineColor(Color::White);
    menu_box.setOutlineThickness(2);

    menu_text_title.setFont(font);
    menu_text_title.setPosition(3*40, 8*40);
    menu_text_title.setCharacterSize(100);
    menu_text_title.setFillColor(Color::White);
    menu_text_title.setString("SnakeGame");

    menu_text_pressToStart.setFont(font);
    menu_text_pressToStart.setPosition(3*40, 11*40);
    menu_text_pressToStart.setCharacterSize(30);
    menu_text_pressToStart.setFillColor(Color::White);
    menu_text_pressToStart.setString("Press 'Enter' to start");
}

// Задаем экран конца игры
void setFailScreen(RectangleShape& fail_screen_box,
                   Text& fail_screen_text,
                   Text& fail_screen_pressToExit,
                   Text& fail_screen_pressToStats,
                   Text& fail_screen_pressToRestart,
                   Font& font,
                   int& fruit_count) 
{
    fail_screen_box.setPosition(2 * 40, 6 * 40);
    fail_screen_box.setFillColor(Color::Black);
    fail_screen_box.setOutlineColor(Color::White);
    fail_screen_box.setOutlineThickness(2);

    fail_screen_text.setFont(font);
    fail_screen_text.setPosition(4 * 40, 7 * 40);
    fail_screen_text.setCharacterSize(100);
    fail_screen_text.setFillColor(Color::White);
    fail_screen_text.setString("You've lost");

    fail_screen_pressToExit.setFont(font);
    fail_screen_pressToExit.setPosition(4 * 40, 10 * 40);
    fail_screen_pressToExit.setCharacterSize(20);
    fail_screen_pressToExit.setFillColor(Color::White);
    fail_screen_pressToExit.setString("Press 'Esc' to exit");

    fail_screen_pressToStats.setFont(font);
    fail_screen_pressToStats.setPosition(4 * 40, 11 * 40);
    fail_screen_pressToStats.setCharacterSize(20);
    fail_screen_pressToStats.setFillColor(Color::White);
    fail_screen_pressToStats.setString("Press 'S' to see stats");

    fail_screen_pressToRestart.setFont(font);
    fail_screen_pressToRestart.setPosition(4 * 40, 12 * 40);
    fail_screen_pressToRestart.setCharacterSize(20);
    fail_screen_pressToRestart.setFillColor(Color::White);
    fail_screen_pressToRestart.setString("Press 'R' to resrart");
}

// Задаем отображение статистики 
void setStats(RectangleShape& stats_box,
              Text& stats_text,
              Font& font,
              int& fruit_count)
{
    stats_box.setPosition(7 * 40, 16 * 40);
    stats_box.setFillColor(Color::Black);
    stats_box.setOutlineColor(Color::White);
    stats_box.setOutlineThickness(2);

    stats_text.setFont(font);
    stats_text.setPosition((8 * 40)-10, 17 * 40);
    stats_text.setCharacterSize(30);
    stats_text.setFillColor(Color::White);
    
    string str = to_string(fruit_count);
    string res = "Your score: " + str;
    stats_text.setString(res);
}

// Задаем отображение счетчика
void setCounter(Font& font, Text& fruit_count_text) {
    fruit_count_text.setFont(font);
    fruit_count_text.setCharacterSize(28);
    fruit_count_text.setFillColor(Color::White);
    fruit_count_text.setPosition(390, 800);
}

// Обновляем счетчик на экране
void refreshCounter(Text& fruit_count_text, int& fruit_count) {
    wstringstream ss;
    ss << fruit_count;
    fruit_count_text.setString(ss.str());
}

// Перезапускаем игру
void resetGame(int& fruit_count,
               int& game_width,
               int& game_height,
               vector<RectangleShape>& snake,
               vector<Sprite>& snake_sprite,
               Sprite& snake_head,
               Sprite& snake_part,
               bool& isMenu,
               bool& isFirstMove,
               bool& gameIsStarted,
               bool& gameIsFailed) 
{
    fruit_count = 0;
    snake.clear();
    snake_sprite.clear();
    isMenu = true;
    isFirstMove = false;
    gameIsStarted = false;
    gameIsFailed = false;

    RectangleShape snakeShape(Vector2f(40, 40));
    snakeShape.setFillColor(Color::Magenta);
    snake.push_back(snakeShape);
    snake.push_back(snakeShape);
    snake[0].setPosition(game_width / 2, game_height / 2);
    snake[1].setPosition((game_width / 2) - 40, game_height / 2);

    snake_sprite.push_back(snake_head);
    snake_sprite.push_back(snake_part);
    snake_sprite[0].setPosition(game_width / 2, game_height / 2);
    snake_sprite[1].setPosition((game_width / 2) - 40, game_height / 2);
}

// Генерируем случайные координаты
int genRandCords() {
    return (rand() % 20) * 40;
}

// Задаем координаты в том случае если они не равны координатам какой-либо из частей змейки
void setStrawberry(vector<RectangleShape>& snake, Sprite& strawberry) {
    int x = genRandCords();
    int y = genRandCords();
    for (auto i : snake) {
        if (i.getGlobalBounds() == strawberry.getGlobalBounds()) {
            x = genRandCords();
            y = genRandCords();
        }
        strawberry.setPosition(x, y);
    }
}