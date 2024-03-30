// Библиотеки C++
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

    // Библиотеки C
#include <stdlib.h>
#include <time.h>

using namespace std;
using namespace sf;


// Создание окна
static void initWindow(RenderWindow& window, int width, int height) {
    RenderWindow window(VideoMode(width, height), L"Курсовая работа: Змейка");
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);
}

int main() {
    // Подкючаем генератор случайных чисел из C
    srand(time(NULL));

    int width = 900;
    int height = 600;

    RenderWindow window;
    initWindow()



    return 0;
}