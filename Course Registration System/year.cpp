#include "year.h"
#include<sstream>
using namespace std;

void CreateYear(LinkedList<Year>& yearList)
{
    Node<Year>* current = yearList.pHead;
    int temp;
    cout << "Type in Year Start: ";
    cin >> temp;
    if (yearList.pHead == nullptr)
    {
        yearList.pHead = new Node<Year>;
        yearList.pTail = yearList.pHead;
        current = yearList.pHead;
    }
    else
    {
        yearList.pTail->pNext = new Node<Year>;
        yearList.pTail = yearList.pTail->pNext;
        yearList.pTail->data.yearStart = temp;
    }
}

void inputStudentCSV(LinkedList<Year> &ListYear, string &className)
{
    // ListYear.pHead->data.Listclass.pHead->data.listOfStudents

    //  Node<Class> *current = ListYear.pHead->data.Listclass.pHead;
    LinkedList<Student> s;
    /* bool check = false;
     while (current != nullptr)
     {
         if (current->data.classname == className)
             {
                 s = current->data.listOfStudents;
                 check = true;
                 break;
             }
             current = current->pNext;
     }
     if (check == false)
     {
         cout << "Can not find this class, please try again!" << endl;
         return;
     }*/
    Node<Student> dummy;
    Node<Student>* temp = &dummy;
    ifstream fin;
    fin.open("Student.csv");
    string line;
    while (getline(fin, line))
    {
        temp->pNext = new Node<Student>;
        temp = temp->pNext;
        string sNo;
        string sID;
        string sGender;
        string sDay, sMonth, sYear;
        string sSocial;
        string dob;
        stringstream inputstream;
        inputstream.str(line);
        inputstream >> temp->data.No;
        inputstream >> temp->data.StudentID;
        cout << temp->data.No << ' ' << temp->data.StudentID<<endl;
        system("pause");
        getline(inputstream, temp->data.FirstName, ',');
        getline(inputstream, temp->data.LastName, ',');
        inputstream >> temp->data.Gender;
        getline(inputstream, dob, ',');
        stringstream dobstream;
        dobstream.str(dob);
        dobstream >> temp->data.dob.day;
        dobstream >> temp->data.dob.month;
        dobstream >> temp->data.dob.year;
        inputstream >> temp->data.SocialID;
    }
    s.pHead = dummy.pNext;
    s.pTail = temp;
    outputAllStudent(s);
    //cout << endl;
    /*	current = ListYear.pHead->data.Listclass.pHead;
    	while (current != nullptr)
        {
            if (current->data.classname == className)
                {
                    current->data.listOfStudents = s;
                    break;
                }
                current = current->pNext;
        }
       // outputAllStudent()
    */
}
//Format for Adding students to class function
//LinkedList StudentList;
//addList(Class.listOfStudents, &AddStudent);
Year inputYear()
{
    Year res{ 0, nullptr };
    cout << "input year start: ";
    cin >> res.yearStart;
    return res;
}
void displayYear(LinkedList<Year>yearList)
{
    Node<Year>* temp = yearList.pHead;
    if (yearList.pHead == nullptr) return;
    cout << "All years shown below: " << endl;
    while (temp)
    {
        cout << temp->data.yearStart << endl;
        temp = temp->pNext;
    }
}
void viewListCoursethisSemester(LinkedList<Year> listYear)
{
    displayYear(listYear);
    cout << "Input Year: ";
    int year;
    cin >> year;
    Node<Year>* cur = listYear.pHead;
    while (cur)
    {
        if (cur->data.yearStart == year) break;
        cur = cur->pNext;
    }
    cout << "Input semester (from 1 to 3) in " << year << " you want to view list courses: ";
    int n;
    cin >> n;
    while (n <= 0 || n >= 4)
    {
        cout << "Please choose semester again: ";
        cin >> n;
    }
    if (n >= 1 && n <= 3)
    {
        cout << "All courses in semester " << n << " of year " << cur->data.yearStart << " shown as below: " << endl;
        Node <Semester>* temp = cur->data.ListSemester.pHead;
        int count = n - 1;
        int count2 = 0;
        while (count2 < count)
        {
            temp = temp->pNext;
            count2++;
        }
        outputAllCourse(temp->data.ListCourse);
    }
}

void outputScoreBoardOfClassMenu(LinkedList<Course>& ListCourse)
{
    cout << "\n";

    cout << "No"
         << "\t" << "StudentID"
         << "\t" << "Student Name\t";
    Node <Course>* NodeCourse = ListCourse.pHead;
    for (; NodeCourse != nullptr; NodeCourse = NodeCourse->pNext)
    {
        cout << "\t" << NodeCourse->data.ID;
    }
    cout << "\t" << "Semester GPA";
    cout << "\t" << "Overall GPA\n";
    cout << "\n";
}

void viewScoreBoardOfClass(LinkedList <Class>& ListClass, LinkedList<Course>& ListCourse)
{
    string clName;
    cout << "\nPlease enter the class's name:";
    getline(cin >> ws, clName);
    Node <Class>* NodeClass = ListClass.pHead;
    for (; NodeClass != nullptr; NodeClass = NodeClass->pNext)
    {
        if (NodeClass->data.classname == clName) break;
    }
    if (NodeClass == nullptr)
    {
        cout << "\nThere is no class with this name, please try again!";
        return;
    }

    Node<Student>* NodeStudent = NodeClass->data.listOfStudents.pHead;
    cout << "---------------------------------- Score Board of class " << clName << " ----------------------------------------\n";
    outputScoreBoardOfClassMenu(ListCourse);
    int noOfStudent = 0;
    for (; NodeStudent != nullptr; NodeStudent = NodeStudent->pNext)
    {
        cout << ++noOfStudent << "\t" << NodeStudent->data.StudentID << "\t" << NodeStudent->data.FirstName << ' ' << NodeStudent->data.LastName;
        int countCourse = 0;
        float sumGPA = 0;
        Node<Course>* NodeCourse = ListCourse.pHead;
        for (; NodeCourse != nullptr; NodeCourse = NodeCourse->pNext)
        {

            Node<Score>* NodeSore = NodeCourse->data.scoreBoard.pHead;
            for (; NodeSore != nullptr; NodeSore = NodeSore->pNext)
            {
                if (NodeSore->data.ID == NodeStudent->data.StudentID)
                {
                    cout << "        " << NodeSore->data.totalMark;
                    countCourse++;
                    sumGPA += NodeSore->data.totalMark;
                    break;
                }
            }
            if (NodeSore == nullptr) cout << "        " << "X";
        }
        float GPAThisSemester = sumGPA / ((float)countCourse);
        cout << "        " << fixed << setprecision(1) << GPAThisSemester;
        float overallGPA;
        ifstream GPAfile;
        string classnameGPA = clName;
        classnameGPA += "GPA.txt";
        GPAfile.open(classnameGPA);
        if (GPAfile)
        {
            int NumOfStudentInClass;
            GPAfile >> NumOfStudentInClass;
            int STID;
            int allCourse;
            float GPA;
            for (int i = 1; i <= NumOfStudentInClass; i++)
            {
                GPAfile >> STID >> allCourse >> GPA;
                if (STID == NodeStudent->data.StudentID)
                {
                    overallGPA = (GPA * ((float)allCourse) + GPAThisSemester) / ((float)(allCourse + 1));
                    break;
                }
            }
        }
        else cout << "file " << classnameGPA << " cannot open !\n";
        cout << "        " << fixed << setprecision(1) << overallGPA << '\n';
    }
}
void EndofSemester(LinkedList<Year> ListYear)
{
    int tmp;
    cout << "21. Export a list of students in a course to a CSV file" << endl;
    cout << "22. Import the scoreboard of a course." << endl;
    cout << "23. View the scoreboard of a course." << endl;
    cout << "24. Update a student result." << endl;
    cout << "25. View the scoreboard of a class" << endl;
    cout << "26. Back" << endl;
    cin >> tmp;
    if (tmp == 26)
    {
        return;
    }
    if(tmp == 21)
    {
        cout << "Please choose the course you want (from 1) :\n";
        outputAllCourse(ListYear.pHead->data.ListSemester.pHead->data.ListCourse);
        int num;
        cin >> num;
        Course a;
        findIndex(ListYear.pHead->data.ListSemester.pHead->data.ListCourse, num, a);
        ofstream fout;
        string coursename = a.CourseName + ".CSV";
        fout.open(coursename);
        outputListFile(a.EnrollStudentList,fout,outputStudentFile);
        fout.close();
    }
    if (tmp == 22)
    {
        importScoreboard(ListYear.pHead->data.ListSemester.pHead->data.ListCourse);
    }
    if (tmp == 23)
    {
        viewScoreBoardOfCourse(ListYear.pHead->data.ListSemester.pHead->data.ListCourse);
    }
    if (tmp == 24)
    {
        updateAStudent(ListYear.pHead->data.ListSemester.pHead->data.ListCourse);
    }
    if (tmp == 25)
    {
        viewScoreBoardOfClass(ListYear.pHead->data.Listclass,ListYear.pHead->data.ListSemester.pHead->data.ListCourse);
    }

}

/*
2
2
1
1
2

1
2021
2
2
1
21CTT1
1
21CTT2
2
2
4
21CTT1
2
5
21
*/
