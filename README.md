# Exercise_sorting

This repository stands for sorting out teams of students. This is an exercise to deal with C++ and datastructures.
It works on both Windows and macOS.

## Features

The program is meant to sort out students in teams.

When you launch the program, there's the main menu.

```md
        This is ALGOSUP teams management! 

You can manage the school's teams here.

Choose an option:
1: See the teams
2: See the students
3: Sort students in teams
4: Reset teams
0: Quit
```

You just have to press the appropriate number on your keyboard to execute actions.

Pressing `0` quits the program.

### See the teams

Pressing `1` displays the teams. There are 8 of them.

At the beginning, no students are sort out in the teams yet.
Once the user sorts the students out, they are assigned among the teams and to a role.

### See the students

Pressing `2` displays the students. They are just listed by year of enrolment.

### Sort the students in teams

Pressing `3` sorts out randomly the students in the 8 teams. Each student is unique and a role cannot be assigned twice in a team.

### Reset teams

Pressing `4` resets the teams, so they no longer have students assigned.

## How does it work?

You just have to run the appropriate file to run the program, depending on your platform:

On macOS:

`./start.sh`

On Windows:

`start.cmd`

It will compile and then execute the compiled program.
