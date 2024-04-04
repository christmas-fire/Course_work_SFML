#pragma once

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

void setWindow(RenderWindow& window, int width, int height);

void setFont(Font& font);

void setBorder(RectangleShape& border);

void setCounter(Font& font, Text& fruit_count_text);

void refreshCounter(Text& fruit_count_text, int fruit_count);

void setIcon(Image& icon, RenderWindow& window);

void setTextures(Texture& texture_apple,
                        Texture& texture_strawberry,
                        Texture& texture_snake_head,
                        Texture& texture_snake_part,
                        Texture& texture_background
                        );

void setSound(SoundBuffer& buffer);

void setMenu(RectangleShape& menu_box, Text& menu_text_title, Text& menu_text_pressToStart, Font& font);

