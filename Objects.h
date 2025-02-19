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
    Apple () {
        spawn();
    }
    void spawn();
};

class Snake {
    std::vector<int> BodyX;
    std::vector<int> BodyY;
    Position headPosition;

public:
    Snake () {
        spawn();
    }
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


    Map (Apple &apples, Snake& snake) : apples(apples), snake(snake) {}

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
            boost::this_thread::sleep_for( boost::chrono::milliseconds(500));
            map.update();

        }
        std::cout << "[ Game lose ]" << std::endl;
        std::cout << "Press key ..." << std::endl;

    }
};


#endif //SNAKE_OBJECTS_H
