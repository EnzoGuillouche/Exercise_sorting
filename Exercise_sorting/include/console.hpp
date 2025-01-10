#include "jsonManagement.hpp"
#include <stdlib.h>
#ifdef _WIN32
#include <conio.h> // Windows-specific header for _getch()
#else
#include <termios.h>
#include <unistd.h>

char getch() {
    struct termios oldt, newt;
    char ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;                             
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}
#endif

void clearScreen(){
    #if defined _WIN32
        system("cls");
    #elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
        system("clear");
    #elif defined (__APPLE__)
        system("clear");
    #endif
}

using namespace std;

void printStudents(std::vector<Member> students){
    if (!students.empty()){
        cout << endl << "Students:" << endl;
        int i = 1;
        for (Member student : students) {
            string s = student.getRole() == "Not defined" ? "" : ": " + student.getRole();
            cout << i << ". " << student.getName() << s << endl;
            i++;
        }
        cout << endl;
    }
}

void printTeams(){
    cout << endl;
    for (Team team : teams) {
        cout << "Team " << team.getTeamNumber() << endl;
        printStudents(team.getMembers());
    }
    cout << endl;
}

void setMemberRole(Member* m, Team t){
    m->setRole();
    for (Member& member : t.getMembers()) {
        if (member.getRole() == m->getRole()) {
            setMemberRole(m, t);
        }
    }
}

void setMember(Member* m, Team t){
    m->setName(members);
    for (Member& member : t.getMembers()) {
        if (member.getName() == m->getName()) {
            setMember(m, t);
        }
    }
    setMemberRole(m, t);
}

void randomStudentAllocation(){
    for (Team& team : teams){
        team.reset();
        while (team.getMembersNumber() < 6){
            Member m("");
            setMember(&m, team);
            team.addMember(m);
            team.increaseMemberNb();
        }
    }
    printTeams();
}

void output(bool* quitProgram){
    char ch;
    #ifdef _WIN32
        ch = _getch(); // Use _getch() on Windows
    #else
        ch = getch();  // Use custom getch() function on macOS
    #endif

    switch (ch){
        case '1':
            clearScreen();
            printTeams();
            break;
        case '2':
            clearScreen();
            printStudents(members);
            break;
        case '3':
            clearScreen();
            randomStudentAllocation();
            break;
        case '0':
            clearScreen();
            *quitProgram = true;
            break;
        default:
            cout << endl << "Invalid input, try again." << endl << endl;
            break;
    }
}

void init(){
    string filePath = "students.json";

    for (int i = 0; i < NUMBER_OF_TEAMS; i++) {
        Team t(i+1);
        teams.push_back(t);
    }
    
    members = setupJSON(filePath);
    
    cout << "\tThis is ALGOSUP teams management! \n\nYou can manage the school's teams here." << endl << endl;
}


void mainMenu(){
    cout << "Choose an option:" << endl;
    cout << "1: See the teams" << endl;
    cout << "2: See the students" << endl;
    cout << "3: Add student to a team" << endl;
    cout << "0: Quit" << endl;
}