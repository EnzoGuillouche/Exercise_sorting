#include "include/console.hpp"

bool quitProgram = false; // main loop condition

int main(){
    clearScreen();
    init();
    while (!quitProgram){
        mainMenu();
        output(&quitProgram);
    }
    return 0;
}