//
// Created by rukati on 18.02.2025.
//
#include "Objects.h"

#ifdef __linux__
#include <termios.h>
#include <unistd.h>

void getKeyPress() {
    struct termios oldt, newt;
    char ch;
    while (Game::state) {
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
#elif _WIN32
#include <windows.h>
void getKeyPress()
{
    while (Game::state) {
        if (GetAsyncKeyState('w') & 0x8000)
            if (Snake::dir != Direction::DOWN)
                    Snake::dir = Direction::UP;
        if (GetAsyncKeyState('s') & 0x8000)
            if (Snake::dir != Direction::UP)
                    Snake::dir = Direction::DOWN;
        if (GetAsyncKeyState('a') & 0x8000)
            if (Snake::dir != Direction::RIGHT)
                    Snake::dir = Direction::LEFT;
        if (GetAsyncKeyState('d') & 0x8000)
            if (Snake::dir != Direction::LEFT)
                    Snake::dir = Direction::RIGHT;
    }
}
#endif



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
    if (!tailPosition.empty()) {
        Map::map[tailPosition[0].Y][tailPosition[0].X] = ' ';

        for (int i = tailPosition.size() - 1; i > 0; --i) {
            Map::map[tailPosition[i].Y][tailPosition[i].X] = ' ';

            tailPosition[i].X = tailPosition[i - 1].X;
            tailPosition[i].Y = tailPosition[i - 1].Y;
        }

        tailPosition[0].X = this->headPosition.X;
        tailPosition[0].Y = this->headPosition.Y;
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

    for (int i = 0; i < tailPosition.size(); ++i) {
        Map::map[tailPosition[i].Y][tailPosition[i].X] = '*';
    }

}

void Snake::grow(int &&x , int &&y) {
    tailPosition.push_back(Position(std::move(x), std::move(y)));
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
#ifdef __linux__
    system("clear");
#elif _WIN32
    system("cls");
#endif
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

    if (Map::map[snake.GetPosition().Y][snake.GetPosition().X] == '*') Game::state = false;

    std::cout << "Points: " << Game::count << std::endl;
    show();
}
