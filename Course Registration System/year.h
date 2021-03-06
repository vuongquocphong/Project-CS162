#pragma once
#include <iostream>
#include <string.h>
#include <string>
#include "linkedList.h"
#include "class.h"
#include "semester.h"

using namespace std;

struct Year {
	int yearStart;
	LinkedList<Semester> ListSemester;
	LinkedList<Class> Listclass;
};

void CreateYear(LinkedList<Year>& yearList);
void inputStudentCSV(LinkedList<Year> &ListYear, string &className);
Year inputYear();
void displayYear(LinkedList<Year> yearList);
void viewListCoursethisSemester(LinkedList<Year> listYear);
void outputScoreBoardOfClassMenu(LinkedList<Course>& ListCourse);
void viewScoreBoardOfClass(LinkedList <Class>& ListClass, LinkedList<Course>& ListCourse);
void EndofSemester(LinkedList<Year> ListYear);
Semester inputSemester(Year y1);
void semester(LinkedList<Year> &ListYear, Regis &reg);
void student(int id, LinkedList<Year>& ListYear, Date &today, Regis &reg);
