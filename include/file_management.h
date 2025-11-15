#pragma once

struct Student
{
    int id;
    char name[100];
    double paidAmount;

};


// ---- Student Functions ----
void initStudents();
int  addStudent(const char name[]);
void displayAllStudents();
int  findStudentByID(int id);
void resizeStudentArray();
