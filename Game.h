#pragma once
#include <iostream>
using namespace std;

class Block{
public:
    Block(const int x_inp,const int y_inp):x(x_inp), y(y_inp){};

    int const getX(){ return x; }
    int const getY(){ return y; }
    char& getObj(int row, int col){ return obj[row][col]; } 

    void setX(const int x_inp){ x = x_inp; }
    void setY(const int y_inp){ y = y_inp; }

private:
    char obj[3][3]{
        {' ', ' ', ' '},
        {'@', '@', '@'},
        {'@', ' ', ' '}
    };
    int x;
    int y;
};

class Game {
public:
    Game();
    void scene();
    void clean();
    void print_scene();
    void print_block();

    void fall();
    void moveRight(){}
    void moveLeft(){}

    
    void check_floor();
    // void check_walls();

private:
    static const int width = 120, height = 39;
    char screen[width * height];
    Block block;
};

Game::Game():block(60, 0){};

void Game::print_block(){
    for(int i=0; i<3; i++)
        for(int j=0; j < 3; j++) 
            if(block.getObj(i, j)=='@') screen[block.getX()+j + (block.getY()+i) * width] = '@';
}

void Game::clean(){
    for(int i=0; i<3; i++)
        for(int j=0; j < 3; j++) 
            if(block.getObj(i, j)=='@') screen[block.getX()+j + (block.getY()+i) * width] = ' ';
}

void Game::fall(){
    check_floor();
    clean();
    block.setY(block.getY()+1);
}

void Game::check_floor(){
    for(int i=0; i < 3; i++) {
        if(screen[block.getX()+i + (block.getY()+3) * width]!=' ' and block.getObj(2, i)=='@') block.setY(0);
        else if(block.getObj(2, 0)==' ' and block.getObj(2, 1)==' ' and block.getObj(2, 2)==' ')
            if(screen[block.getX()+i + (block.getY()+2) * width]!=' ' and block.getObj(1, i)=='@') block.setY(0);
    }
}

void Game::scene(){
    int border = width/4;
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            if (i == border - 1 || i == width - border) screen[i + j * width] = '[';
            else if (i == border || i == width - border + 1) screen[i + j * width] = ']';
            else screen[i + j * width] = ' ';
            if (i >= border - 1 && i <= width - border + 1 && j == height - 1) screen[i + j * width] = '=';
        }
    }
}

void Game::print_scene(){
    for (char i : screen) cout << i;
    cout << endl;
}