#include "include/console.hpp"

bool quitProgram = false;

int main(){
    clearScreen();
    init();
    while (!quitProgram){
        mainMenu();
        output(&quitProgram);
    }
}