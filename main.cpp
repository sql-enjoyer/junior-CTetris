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
        cout<<ch<<endl;



        if(ch == 27) break;
        if(ch == 97){ // a
            root.moveRight();
        }  
        if(ch == 100);{ // d
            root.moveLeft();
        }
        if(ch == 32); // space

        
        root.fall();
        root.print_block();
        root.print_scene();
    }
}