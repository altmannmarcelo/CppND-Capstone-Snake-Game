# CPPND: Capstone Snake Game Example

This is a starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

<img src="snake_game.gif"/>

The Capstone Project gives you a chance to integrate what you've learned throughout this program. This project will become an important part of your portfolio to share with current and future colleagues and employers.

In this project, you can build your own C++ application or extend this Snake game, following the principles you have learned throughout this Nanodegree Program. This project will demonstrate that you can independently create applications using a wide range of C++ features.

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  * Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.

## Added Functionality

1. Added a new Class to controll food objects
2. Added a Thread that apart from Normal food, randomly adds different types of food:
2.1. Yellow(Normal) - Add 1 point, Increase speed, Increase Body.
2.2. Green(Points Only) - Add 1 point.
2.3. Blue (Speed Reducer) - Reduces speed.
2.4. Brown(Double) - Add 2 points, Increase speed twice, Increase Body twice.
3. Modified Game Object to hold a vector of Food items.

## Code structure

| Class  | Description  |
| ------------ | ------------ |
| Controller  |  Responsible for handling snake direction and keyboard input. |
| Food  | Responsible for handling food objects around the game board. Also controlls the different types of food and how it affects  points,  speed / body of snake  |
| Game |  Responsible for handling the game, keeping controll of score, snake and invoking rendering actions |
| Render | Responsible for UI elements |
| Snake| Responsible for Snake and its attributes |

## Rubic points addressed

| Item  | File  | Comment
| ------------ | ------------ | ------------ |
|The project demonstrates an understanding of C++ functions and control structures.| `src/food.cpp` | Throughout `food.cpp`  a variaty of control structures are used to controll different aspects of Food and FoodItem objects |
|The project uses Object Oriented Programming techniques| N/A | The entire project is structured using objects |
|Classes use appropriate access specifiers for class members| `src/food.h:39` | Food Class has private and public attributes and members |
|Class constructors utilize member initialization lists| `src/food.cpp:4`| Class uses member initialization list for `_type` attribute|
|The project uses multithreading| `game.cpp:47` | Thread randomFood is used to controll placement and removal or special types of food.
|A mutex or lock is used in the project| `game.cpp:27` / `game.cpp:106` | A mutex is used to protect `_items` vector from Food object
