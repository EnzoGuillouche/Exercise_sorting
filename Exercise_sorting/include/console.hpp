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

void mainMenu(){
    cout << "Choose an option:" << endl;
    cout << "1: See the teams" << endl;
    cout << "2: See the students" << endl;
    cout << "3: Sort students in teams" << endl;
    cout << "4: Reset teams" << endl;
    cout << "0: Quit" << endl;
}

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

bool canAskRetrieval = false;

void printStudents(std::vector<Member> students){
    if (!students.empty()){
        canAskRetrieval = true;
        int i = 1;
        for (Member student : students) {
            string s = student.getRole() == "Not defined" ? "" : ": " + student.getRole();
            cout << i << ". " << student.getName() << s << endl;
            i++;
        }
        cout << endl;
    } else {
        canAskRetrieval = false;
    }
    
}

void printTeams(){
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
        }
    }
    printTeams();
}

void resetTeams(){
    for (Team& team: teams){
        team.reset();
    }
    
}

void findStudent(Team t){
    bool found = false;
    while (!found){
        string ch;
        cin >> ch;
        
        for (Member member : t.getMembers()){
            if (member.getName() == ch){
                cout << endl << member.getName() << " is present." << endl;
                found = true;
                break;
            }
        }

        if (!found){
            cout << endl << ch << " is not present, try again: ";
            findStudent(t);
        }
    }

    cout << endl;
}

void askRetrieval(){
    char ch;
    while (canAskRetrieval){
        cout << "Do you want to find a specific student in a team?" << endl;
        cout << "[Yes]: Type the team's number" << endl;
        cout << "[No]: Type 0" << endl;

        #ifdef _WIN32
            ch = _getch(); // Use _getch() on Windows
        #else
            ch = getch();  // Use custom getch() function on macOS
        #endif
        switch (ch){
            case '0':
                canAskRetrieval = false;
                clearScreen();
                break;
            default:
                int c = ch - '0';
                if (c > 0 && c < 9){
                    for (Team team : teams){
                        if (team.getTeamNumber() == c){
                            cout << endl << "Find a student by writing its name or role:" << endl;
                            findStudent(team);
                            canAskRetrieval = false;
                        }
                    }
                } else {
                    cout << endl << "Invalid input, try again." << endl << endl;
                }
                
                break;
        }
    }
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
            askRetrieval();
            break;
        case '2':
            clearScreen();
            cout << "Students:" << endl;
            printStudents(members);
            break;
        case '3':
            clearScreen();
            randomStudentAllocation();
            break;
        case '4':
            clearScreen();
            resetTeams();
            cout << "Teams have been reset." << endl << endl;
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
