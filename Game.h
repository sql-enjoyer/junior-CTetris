#pragma once
#include <iostream>
#include <random>
using namespace std;

class Block{
public:
    void randomBlock(){
        int arr[6] = {0, 1, 2, 3, 4, 5};

        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, sizeof(arr)/sizeof(arr[0])-1);

        int randomEl = arr[dis(gen)];

        for(char i=0; i < 3; ++i)
            for(int j=0; j<3; ++j)
                obj[i][j] = blocks[randomEl][i][j];
    }

    Block(const int x_inp,const int y_inp):x(x_inp), y(y_inp){ randomBlock(); };

    int const getX(){ return x; }
    int const getY(){ return y; }
    char& getObj(const int& row, const int& col){ return obj[row][col]; }

    void setX(const int x_inp){ x = x_inp; }
    void setY(const int y_inp){ y = y_inp; }

    void flip() {
        for (int i = 0; i < 3; ++i) {
            for (int j = i; j < 3 - i - 1; ++j) {
                int temp = obj[i][j];
                obj[i][j] = obj[2 - j][i];
                obj[2 - j][i] = obj[2 - i][2 - j];
                obj[2 - i][2 - j] = obj[j][2 - i];
                obj[j][2 - i] = temp;
            }
        }
    }

private:
    int x;
    int y;
    char obj[3][3];
    char blocks[6][3][3]{
        {
        {' ', ' ', '@'},
        {'@', '@', '@'},
        {' ', ' ', ' '}
        },

        {
        {'@', ' ', ' '},
        {'@', '@', '@'},
        {' ', ' ', ' '}
        },

        {
        {' ', ' ', ' '},
        {'@', '@', '@'},
        {' ', ' ', ' '}
        },

        {
        {' ', ' ', ' '},
        {'@', '@', ' '},
        {' ', '@', '@'}
        },

        {
        {' ', ' ', ' '},
        {' ', '@', '@'},
        {'@', '@', ' '}
        },

        {
        {' ', ' ', ' '},
        {' ', '@', ' '},
        {'@', '@', '@'}
        }
    };
};

class Game {
public:
    Game();
    void scene();
    void clean();
    void print_scene();
    void print_block();

    void fall();
    void flip();
    void moveRight();
    void moveLeft();
    void startPos();

    void check_row();
    void check_floor();
    void check_walls_right();
    void check_walls_left();

private:
    static const int width = 120, height = 39;
    char screen[width * height];
    Block block;
};

Game::Game():block(60, 0){};

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

void Game::clean(){
    for(int i=0; i<3; i++)
        for(int j=0; j < 3; j++) 
            if(block.getObj(i, j)=='@') screen[block.getX()+j + (block.getY()+i) * width] = ' ';
}

void Game::print_scene(){
    for (char i : screen) cout << i;
    cout << endl;
}

void Game::print_block(){
    for(int i=0; i<3; i++)
        for(int j=0; j < 3; j++) 
            if(block.getObj(i, j)=='@') screen[block.getX()+j + (block.getY()+i) * width] = '@';
}




void Game::fall(){
    check_floor();
    clean();
    block.setY(block.getY()+1);
    print_block();
}

void Game::flip(){
    check_floor();
    clean();
    block.flip();
    print_block();
}

void Game::moveRight(){
    clean();
    check_walls_right();
    block.setX(block.getX()+1);
    print_block();
}

void Game::moveLeft(){
    clean();
    check_walls_left();
    block.setX(block.getX()-1);
    print_block();
}

void Game::startPos(){
    block.setY(0);
    block.setX(60);
    block.randomBlock();
    print_block();
    check_row();
}

void Game::check_row(){
    int border = width/4;
    bool flag = true; 
    for (int i = height-2; i > -1; --i) {
        for (int j = border+1 ; j < width-border-1; ++j) {
            if(screen[j + i * width] == ' '){
                flag = false;
                break;
            }
        }
        if(flag) 
            cout << "ROW" << endl;
        flag = true;
    }
}

void Game::check_walls_right(){
    for(int i=0; i < 3; i++) {
        if(block.getObj(i, 2)=='@' and screen[block.getX()+3 + (block.getY()+i) * width]!=' ') block.setX(block.getX()-1);
        else if(block.getObj(i, 2)==' ' and block.getObj(i, 1)=='@' and screen[block.getX()+2 + (block.getY()+i) * width]!=' ') block.setX(block.getX()-1);
    }
}

void Game::check_walls_left(){
    for(int i=0; i < 3; i++) {
        if(block.getObj(i, 0)=='@' and screen[block.getX()-1 + (block.getY()+i) * width]!=' ') block.setX(block.getX()+1);
        else if(block.getObj(i, 0)==' ' and block.getObj(i, 1)=='@' and screen[block.getX() + (block.getY()+i) * width]!=' ') block.setX(block.getX()+1);
    }
}

void Game::check_floor(){
    for(int i=0; i < 3; i++) {
        if(block.getObj(2, i)=='@' and screen[block.getX()+i + (block.getY()+3) * width]!=' ') startPos();
        else if(block.getObj(2, i)==' ' and block.getObj(1, i)=='@' and screen[block.getX()+i + (block.getY()+2) * width]!=' ') startPos();
    }
}
