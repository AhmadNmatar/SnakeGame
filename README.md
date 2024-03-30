# SnakeGame
This snake game is developed in C language and designed to run on the Uno32 microcontroller.

# Course
Computer hardware engineering  IS1200 spring 2024.

# Project

The project is a snake game developed in C language on Uno32 Chipkit board with a basic I/O shield. 

The game is developed by Gustav Landberg and Ahmad Matar.

## How to install the game?

To install the game on your chipkit board you need to have a MBC32 terminal installed on your computer to be able to run the code on your board, once you have mbc32 installed do the following:
1) Download the repository to your labtop
2) Open mbc32 terminal and navigate to folder containing the game file

3) connect your chipkit to your device
4) run `make` on mbc32 terminal to complie the code
5) run`make install TTYDEV=/dev/ttySX`,Replace the 'X' with the COM number of your device.

## How to play the game?

1) Press BTN 4 to start the game
2) use "BTN4" and "BTN3" to move the snake, BTN4 move the snake clockwise and BTN3 moves the snake counterclockwise.
