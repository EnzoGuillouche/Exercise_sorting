#include <iostream>
#include <list>
#include <string>

// list of existing roles
std::vector<std::string> roles = {
    "Project Manager", 
    "Program Manager",
    "Tech Lead",
    "Software Engineer",
    "Quality Assurance",
    "Technical Writer"
};

using namespace std;

const int NUMBER_OF_TEAMS = 6; 
int NUMBER_OF_STUDENTS;

class Member {
    private:
        // private encapsulated data
        string name;
        string role = "Not defined";
    public:
        // public methods to manipulate private data
        // constructor
        Member(string name){
            this->name = name;
        }

        string getName(){
            return this->name;
        }

        string getRole(){
            return this->role;
        }

        void setName(vector<Member> mbs){
            int i = rand() % NUMBER_OF_STUDENTS + 0;
            this->name = mbs[i].getName();
        }

        void setRole(){
            int i = rand() % 6 + 0;
            this->role = roles[i];
        }
};

class Team {
    private:
        // private encapsulated data
        int number;
        int membersNb;
        vector<Member> members;

    public:
        // public methods to manipulate private data
        // constructor
        Team(int nb){
            this->number = nb;
            this->membersNb = 0;
        }

        void reset(){
            this->members = {};
            this->membersNb = 0;
        }

        void addMember(Member memb){
            this->members.push_back(memb);
            this->membersNb++;
        }

        int getMembersNumber(){
            return this->membersNb;
        }

        vector<Member> getMembers(){
            return this->members;
        }

        int getTeamNumber(){
            return this->number;
        }
};
// lists of existing teams and students
std::list<Team> teams;
std::vector<Member> members;
