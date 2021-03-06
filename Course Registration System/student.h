#pragma once
#include "linkedList.h"
#include "fstream"
#include <string.h>
#include <sstream>
using namespace std;

struct Session {
	string day;
	string period;
};

struct Date {
	int day;
	int month;
	int year;
};

struct CourseData {
	string ID;
	string CourseName;
	string TeacherName;
	Session s1;
	Session s2;
};

struct Student {
	int No;
	int StudentID;
	string FirstName;
	string LastName;
	int Gender; //1 is Male, 2 is Female
	Date dob;
	int SocialID;
	LinkedList<CourseData> ListCourseData;
	int numCourse = 0;
};

bool compareDate(Date a, Date b);
Student AddStudent();
void inputStudentFile(Student& s1, string line);
void outputStudent(Student s1);
void displayStudentMenu();
void outputAllStudent(LinkedList<Student> ListStudent);
void outputStudentFile(Student s1, ofstream& foutList);
Node<Student> *findStudent(LinkedList<Student> ListStudent, int StudentID, bool &check);
