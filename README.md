# Snake Game

Консольная версия классической игры "Змейка" на C++. Проект создан в обучающих целях. Возможны ошибки и лишние строчки.

## Установка

```sh
git clone https://github.com/your-repo/snake-game.git
cd snake-game
```

## Сборка

**Linux:**

```sh
mkdir build && cd build
cmake ..
make
./Snake
```

**Windows (MinGW):**

```sh
mkdir build && cd build
cmake -G "MinGW Makefiles" ..
mingw32-make
Snake.exe
```

## Управление
- **w** – вверх
- **s** – вниз
- **a** – влево
- **d** – вправо

## Зависимости

- **Linux:** `g++`, `CMake`
- **Windows:** `MinGW`

## TODO
- Улучшить отображение
