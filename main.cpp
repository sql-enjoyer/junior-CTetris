#include <termios.h>
#include <unistd.h>
#include "Game.h"

int main(int argc, char const *argv[]) {
    struct termios oldt, newt;
    int ch;

    Game root;
    root.scene();

    cout << "PRESS ANY KEY TO START" << endl;
    while(true){
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        // cout<<ch<<endl;

        switch(ch){
        case 100:
          root.moveRight();
          break;
        case 97:
          root.moveLeft();
          break;
        }

        root.fall();
        root.print_scene();
    }
}