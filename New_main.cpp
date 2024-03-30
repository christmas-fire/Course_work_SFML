// Библиотеки C++
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

    // Библиотеки C
#include <stdlib.h>
#include <time.h>

using namespace std;
using namespace sf;

    // Создаем окно
static void initWindow(RenderWindow& window, int width, int height) {
    window.create(VideoMode(width, height), L"Курсовая работа: Змейка");
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);
}

int main() {
    // Подкючаем генератор случайных чисел из C
    srand(time(NULL));

    int width = 900;
    int height = 600;

    RenderWindow window;
    initWindow(window, width, height);

    // Game loop
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear();
        window.display();
    }

    return 0;
}