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
    GetXY(position.Y, position.X);

    Map::map[position.Y][position.X] = 'a';
}

void Snake::spawn() {
    GetXY(headPosition.Y, headPosition.X);

    Map::map[headPosition.Y][headPosition.X] = 'S';
}

void Snake::move(int &&x, int &&y) {

    if (BodyX.size() > 0) {
        Map::map[BodyY[0]][BodyX[0]] = ' ';

        BodyX[0] = this->headPosition.X;
        BodyY[0] = this->headPosition.Y;

        for (int i = BodyX.size() - 1; i > 0; --i) {
            Map::map[BodyY[i]][BodyX[i]] = ' ';

            BodyX[i] = BodyX[i - 1];
            BodyY[i] = BodyY[i - 1];
        }
    }
    this->headPosition.X += x;
    this->headPosition.Y += y;

    if (Map::map[headPosition.Y][headPosition.X] == '#') Game::state = false;
}

bool Snake::eat() {
    return Map::map[headPosition.Y][headPosition.X] == 'a';
}

void Snake::draw() {
    Map::map[headPosition.Y][headPosition.X] = 'S';

    for (int i = 0; i < BodyX.size(); ++i) {
        Map::map[BodyY[i]][BodyX[i]] = '*';
    }

}

void Snake::grow(int &&x, int &&y) {
    BodyX.push_back(x);
    BodyY.push_back(y);
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

    int x = snake.GetPosition().X;
    int y = snake.GetPosition().Y;

    map[y][x] = ' ';

    switch (Snake::dir) {
        case Direction::UP:
            snake.move(0,-1);
            break;
        case Direction::DOWN:
            snake.move(0,1);
            break;
        case Direction::LEFT:
            snake.move(-1,0);
            break;
        case Direction::RIGHT:
            snake.move(1,0);
            break;
        case Direction::STAY:
            map[y][x] = 'S';
            break;
    }

    if (snake.eat()) {
        snake.grow(std::move(x), std::move(y));
        Game::count += 1;
        apples.spawn();
    }

    snake.draw();

    std::cout << "Points: " << Game::count << std::endl;
    show();
}
