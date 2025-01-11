#include "jsonManagement.hpp"
#include <stdlib.h>
#include <algorithm>

// depending on the architecture, some code will differ
// this prevents from including unecessary files
#ifdef _WIN32
#include <conio.h> // Windows-specific header for _getch()
#else
#include <termios.h>
#include <unistd.h>

// macOS function to get character from input 
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
    // displays the main menu
    cout << "Choose an option:" << endl;
    cout << "1: See the teams" << endl;
    cout << "2: See the students" << endl;
    cout << "3: Sort students in teams" << endl;
    cout << "4: Reset teams" << endl;
    cout << "0: Quit" << endl;
}

void clearScreen(){
    // clears the console depending on your architecture
    #if defined _WIN32
        system("cls");
    #elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__) || defined (__APPLE__)
        system("clear");
    #endif
}

using namespace std;

bool canAskRetrieval = false;

// Function to display students by role priority
vector<Member> sortByRole(vector<Member> members) {
    vector<Member> sortedMembers;

    // Add members with roles in the priority order
    for (string& role : roles) {
        for (Member& member : members) {
            if (member.getRole() == role) {
                sortedMembers.push_back(member);
            }
        }
    }

    // Add members with roles not in the priority list
    for (Member& member : members) {
        if (find(roles.begin(), roles.end(), member.getRole()) == roles.end()) {
            sortedMembers.push_back(member);
        }
    }

    return sortedMembers;
}

void printStudents(vector<Member> members) {
    if (!members.empty()) {
        vector<Member> sortedMembers = sortByRole(members);

        // Display sorted members
        for (Member& student : sortedMembers) {
            if (student.getRole() != "Not defined") {
                cout << student.getRole() << ": " << student.getName() << endl;
            } else {
                cout << student.getName() << endl;
            }
        }
        cout << endl;
    } else {
        cout << "";
    }
}

void printTeams(){
    // displays the entirety of the teams
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
            setMemberRole(m, t); // recursion if the student has the same role
        }
    }
}

vector<string> allocatedNames = {}; // contains names of students that have been assigned

void setMember(Member* m, Team t){
    m->setName(members);
    for (Member& member : t.getMembers()) {
        if (member.getName() == m->getName() && find(allocatedNames.begin(), allocatedNames.end(), m->getName()) != allocatedNames.end()) {
            setMember(m, t); // recursion if a student has the same name
        }
    }
    allocatedNames.push_back(m->getName());
    setMemberRole(m, t);
}

void randomStudentAllocation(){
    allocatedNames.clear();
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
    // reset all the teams
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
                int c = ch - '0'; // convertion from char to int
                if (c > 0 && c < 9){ // is it a valid team?
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
            cout << "There are " << NUMBER_OF_STUDENTS << " students." << endl << endl;
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
