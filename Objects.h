//
// Created by rukati on 18.02.2025.
//

#ifndef SNAKE_OBJECTS_H
#define SNAKE_OBJECTS_H

#include <iostream>
#include <boost/thread.hpp>
#include <boost/chrono.hpp>
#include <vector>
#include <random>


void getKeyPress();

enum class Direction {
    STAY = 0, UP = 'w', DOWN = 's', LEFT = 'a', RIGHT = 'd'
};


class Apple{
    int x, y;
public:
    void spawn();
};

class Snake{
    int x, y;
public:
    inline static Direction dir {Direction::STAY};

    void spawn();
    void move(int x, int y)
    {
        this->x += x;
        this->y += y;
    }

    int GetPositionX () { return x; }
    int GetPositionY () { return y; }
};

class Map{
    Apple apples;
    Snake snake;
public:
    void show ();
    inline static std::vector<std::vector<char>> map = {
            {'#','#','#','#','#','#','#','#','#','#','#','#','#'},
            {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
            {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
            {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
            {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
            {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
            {'#','#','#','#','#','#','#','#','#','#','#','#','#'}
    };


    Map (Apple &apples, Snake& snake) : apples(apples), snake(snake)
    {
        this->apples.spawn();
        this->snake.spawn();
    }

    void update();
};


class Game {
public:
    inline static bool state = true;
    void play()
    {
        Snake snake;
        Apple apple;

        Map map (apple, snake);

        boost::thread keyBoard(getKeyPress);
        keyBoard.detach();

        while (Game::state){
            boost::this_thread::sleep_for( boost::chrono::milliseconds(500));
            map.update();

        }
        std::cout << "Game lose" << std::endl;

    }
};


#endif //SNAKE_OBJECTS_H
