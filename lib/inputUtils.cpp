#include "inputUtils.h"
#include <unistd.h>
#include <termios.h>
#include <iostream>

void restore_terminal(termios& oldt){
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}

void sigint(termios& oldt){
    restore_terminal(oldt);
    exit(0);
}



char linux_getch() {
    char ch = 0;

    struct termios oldt, newt;

    if(tcgetattr(STDIN_FILENO, &oldt) == -1){
        return 0;
    }

    newt = oldt;

    newt.c_lflag &= ~(ICANON | ECHO);

    if (tcsetattr(STDIN_FILENO, TCSANOW, &newt) == -1) {
        return 0; 
    }

    restore_terminal(oldt);

    return ch;
}
