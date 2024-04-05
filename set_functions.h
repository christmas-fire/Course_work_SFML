#pragma once

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

void setWindow(RenderWindow& window, int& width, int& height);

void setIcon(Image& icon, RenderWindow& window);

void setBorder(RectangleShape& border);

void setTextures(Texture& texture_apple,
                 Texture& texture_strawberry,
                 Texture& texture_snake_head,
                 Texture& texture_snake_part,
                 Texture& texture_background);

void setFont(Font& font);

void setSound(SoundBuffer& buffer);

void setMenu(RectangleShape& menu_box,
             Text& menu_text_title,
             Text& menu_text_pressToStart,
             Font& font);

void setFailScreen(RectangleShape& fail_screen_box,
                   Text& fail_screen_text,
                   Text& fail_screen_pressToExit,
                   Text& fail_screen_pressToStats,
                   Text& fail_screen_pressToRestart,
                   Font& font,
                   int& fruit_count);

void setStats(RectangleShape& stats_box,
              Text& stats_text,
              Font& font,
              int& fruit_count);

void setCounter(Font& font, Text& fruit_count_text);

void refreshCounter(Text& fruit_count_text, int& fruit_count);


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
    bool& gameIsFailed);