//
// Created by rukati on 18.02.2025.
//
#include <termios.h>
#include <unistd.h>
#include "Objects.h"


void getKeyPress() {
    while (Game::state) {
        struct termios oldt, newt;
        char ch;

        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);

        ch = getchar();

        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

        switch (ch) {
            case 'w':
                if (Snake::dir != Direction::DOWN)
                    Snake::dir = Direction::UP;
                break;
            case 's':
                if (Snake::dir != Direction::UP)
                    Snake::dir = Direction::DOWN;
                break;
            case 'a':
                if (Snake::dir != Direction::RIGHT)
                    Snake::dir = Direction::LEFT;
                break;
            case 'd':
                if (Snake::dir != Direction::LEFT)
                    Snake::dir = Direction::RIGHT;
                break;
        }
    }
}

void GetXY (int & x, int & y)
{
    static std::random_device rnd;
    static std::mt19937 mt(rnd());
    static std::uniform_int_distribution<int> distribution (1, Map::map.size() - 2) ;
    do {
        x = distribution(mt);
        y = distribution(mt);
    }while (Map::map[y][x] != ' ');
}

void Apple::spawn() {
    GetXY(y, x);

    Map::map[y][x] = 'a';
}

void Snake::spawn() {
    GetXY(y, x);

    Map::map[y][x] = 'S';
}

void Map::show() {
    for (int i = 0; i < map.size(); ++i) {
        for (int j = 0; j < map[i].size(); ++j) {
            std::cout << map[i][j];
        }
        std::cout << std::endl;
    }
}

void Map::update() {
    system("clear");

    int x = snake.GetPositionX();
    int y = snake.GetPositionY();
    map[y][x] = ' ';

    switch (Snake::dir) {
        case Direction::UP:
            snake.move(0,-1);
            if (map[y - 1][x] == '#')
                Game::state = false;
            else
                map[y - 1][x] = 'S';
            break;
        case Direction::DOWN:
            snake.move(0,1);
            if (map[y + 1][x] == '#')
                Game::state = false;
            else
                map[y + 1][x] = 'S';
            break;
        case Direction::LEFT:
            snake.move(-1,0);
            if (map[y][x - 1] == '#')
                Game::state = false;
            else
                map[y][x - 1] = 'S';
            break;
        case Direction::RIGHT:
            snake.move(1,0);
            if (map[y][x + 1] == '#')
                Game::state = false;
            else
                map[y][x + 1] = 'S';
            break;
    }


    show();
}
