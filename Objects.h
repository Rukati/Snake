//
// Created by rukati on 18.02.2025.
//

#ifndef SNAKE_OBJECTS_H
#define SNAKE_OBJECTS_H

#include <iostream>
#include <vector>
#include <random>
#include <future>


void getKeyPress();

enum class Direction {
    STAY = 0, UP = 'w', DOWN = 's', LEFT = 'a', RIGHT = 'd'
};

struct Position {
    int X, Y;
};

class Apple{
    Position position;
public:
    void spawn();
};

class Snake {
    std::vector<Position> tailPosition;
    Position headPosition;
public:
    inline static Direction dir {Direction::STAY};

    void draw();
    bool eat();
    void spawn();
    void grow(int && x, int && y);
    void move(int && x, int && y);

    Position& GetPosition () { return headPosition; }
};

class Map{
    Apple apples;
    Snake snake;

    const int size = 30;
public:
    void show ();
    inline static std::vector<std::vector<char>> map;


    Map (Apple &apples, Snake& snake) : apples(apples), snake(snake) {
        for (int i = 0; i < size; ++i) {
            map.push_back(std::vector<char>(size));
            for (int j = 0; j < size; ++j) {
                if (i == 0 || i == size - 1 || j == 0 || j == size - 1 )
                    map[i][j] = '#';
                else
                    map[i][j] = ' ';
            }
        }

        this->apples.spawn();
        this->snake.spawn();
    }

    void update();
};


class Game {
public:
    inline static int count = 0;

    inline static bool state = true;
    void play()
    {
        Snake snake;
        Apple apple;

        Map map (apple, snake);

//        boost::thread keyBoard(getKeyPress);

        auto keyBoard = std::async(std::launch::async, getKeyPress);
//        keyBoard.detach();

        while (Game::state){
            std::this_thread::sleep_for( std::chrono::milliseconds(333));
            map.update();

        }
        std::cout << "[ Game lose ]" << std::endl;
        std::cout << "Press key ..." << std::endl;

    }
};


#endif //SNAKE_OBJECTS_H
