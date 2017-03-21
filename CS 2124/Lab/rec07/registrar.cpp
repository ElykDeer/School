//My includes
#include "registrar.h"
#include "student.h"
#include "course.h"

using namespace std;

//My namespace
namespace BrooklynPoly
{
  //Necessary Forward Decs
  class Course;
  class Student;

  Registrar::~Registrar()
  {
    //Only stuff that's on the heap.
      //Will leave dangling pointers
    for (Course* course : courses)
      { delete course; }
    for (Student* student : students)
      { delete student; }
  }

  //To print the registrar
  ostream& operator<<(ostream& os, const Registrar& rhs)
  {
    //Check if there are courses and studnets
    if ((!rhs.students.size()) && (!rhs.courses.size()))
      return os << "No students or courses in the registrar.\n\n";

    bool thereAreStudents, thereAreCourses;
    if (!(thereAreStudents = rhs.students.size()))
      os << "No students in the registrar.\n";
    if (!(thereAreCourses = rhs.courses.size()))
      os << "No courses in the registrar.\n";

    //Print Students
    if (thereAreStudents)
    {
      os << "All Students:";
      for (Student* student : rhs.students)
        { os << " " << *student; }
      os << endl;
    }

    //Print Courses
    if (thereAreCourses)
    {
      os << "Courses And Enrolled Students:\n";
      for (Course* course : rhs.courses)
        { os << *course; }
    }

    os << endl;

    //Return to allow for chaining
    return os;
  }

  //Alternative Print Meathod
  void Registrar::printReport(ostream& os) const
    { cout << *this; }

  //Add A Course of Course
  bool Registrar::addCourse(const string& newCourseName)
  {
    //Check to see if the course already exsits
    if (findCourse(newCourseName))
      return false;

    //Add Courses
    courses.push_back(new Course(newCourseName));
    return true;
  }

  //Add a student
  bool Registrar::addStudent(const string& newStudentName)
  {
    if (findStudent(newStudentName))
      return false;

    //Add the Student
    students.push_back(new Student(newStudentName));
    return true;
  }

  bool Registrar::enrollStudentInCourse(const string& studentName,
                                        const string& courseName)
  {
    //Find Course and Student
    Student* student;
    Course* course;
    if (!(student = findStudent(studentName)))
      return false;
    if (!(course = findCourse(courseName)))
      return false;

    //Do the work
    return (student->addCourse(course) && course->addStudent(student));
  }

  bool Registrar::cancelCourse(const string& courseName)
  {
    //Find Course
    Course* course = nullptr;
    size_t indexOfCourse;
    for (size_t i = 0; i<courses.size(); ++i)
      if (courses[i]->getName() == courseName)
      {
        course = courses[i];
        indexOfCourse = i;
      }
    if (!course) //Make sure we found a course
      return false;

    //Notify all students
    if (!course->cancel())
      return false;
    delete course; //Delete the actual course object

    //Remove the course from records
    courses[indexOfCourse] = courses[courses.size()-1];
    courses.pop_back();
    return true;
  }

  bool Registrar::changeStudentName(const string& oldName, const string& newName)
  {
    //Find Student
    Student* student;
    if (!(student = findStudent(oldName)))
      return false;
    student->changeName(newName);
    return true;
  }

  bool Registrar::dropStudentFromCourse(const string& studentName,
                                        const string& courseName)
  {
    //Find Course and Student
    Student* student;
    Course* course;
    if (!(student = findStudent(studentName)))
      return false;
    if (!(course = findCourse(courseName)))
      return false;

    //Notify student
    return course->removeStudent(student);
  }

  bool Registrar::removeStudent(const string& studentName)
  {
    //Find Course
    Student* student = nullptr;
    size_t indexOfStudent;
    for (size_t i = 0; i<students.size(); ++i)
      if (students[i]->getName() == studentName)
      {
        student = students[i];
        indexOfStudent = i;
      }
    if (!student) //Make sure we found a course
      return false;

    //Drop them out of all classes
    student->dropCourses();

    //Remove them from the registrar
    students[indexOfStudent] = students[students.size()-1];
    students.pop_back();
    return true;
  }

  void Registrar::purge()
  {
    for (Course* inspectCourse : courses)
      cancelCourse(inspectCourse->getName());

    for (Student* student : students)
      { delete student; }
    students.clear();
  }

  Course* Registrar::findCourse(const string& courseName) const
  {
    //Find the course
    Course* course = nullptr;
    for (Course* inspectCourse : courses)
      if (inspectCourse->getName() == courseName)
        course = inspectCourse;
    return course;
  }

  Student* Registrar::findStudent(const string& studentName) const
  {
    //Find the student
    Student* student = nullptr;
    for (Student* inspectStudent : students)
      if (inspectStudent->getName() == studentName)
        student = inspectStudent;
    return student;
  }

  void Registrar::readCommandFile()
  {
    ifstream transactionFile("transactions");
    if (!transactionFile)
    {
        cerr<<"The file failed to open.  Closing program/n";
        exit(1);
    }

    string command;
    while (transactionFile >> command)
    {
      string argumentString; //get the rest of the line
      getline(transactionFile, argumentString);
      istringstream argumentStream(argumentString);

      //Format.  Define argument strings,
        //define "checkArguments" to check for too many argumentsws,
        //check stringstream, make sure there are the expected number of args
      if (command == "PrintReport")
      {
        string checkArguments;
        if (argumentStream >> checkArguments)
        {
          cerr << "PrintReport Has Too Many Arguments.  Expected: None.\n";
          continue;
        }
        cout << *this;
      }

      else if (command == "AddCourse")
      {
        string courseName;
        string checkArguments = "";
        argumentStream >> courseName >> checkArguments;
        if (!(courseName.size()) || (checkArguments.size())) //Error check
        {
          cerr << "AddCourse Has Too Many Or Few Arguments.  Expected: One.\n";
          continue;
        }
        if (!addCourse(courseName))
          cerr << "AddCourse failed. Course already exists.";
      }

      else if (command == "AddStudent")
      {
        string studentName;
        string checkArguments = "";
        argumentStream >> studentName >> checkArguments;
        if (!(studentName.size()) || (checkArguments.size())) //Error check
        {
          cerr << "AddStudent Has Too Many Or Few Arguments.  Expected: One.\n";
          continue;
        }
        if (!addStudent(studentName))
          cerr << "AddStudent failed.  Student Already Exists.";
      }

      else if (command == "EnrollStudentInCourse")
      {
        string studentName, courseName;
        string checkArguments = "";
        argumentStream >> studentName >> courseName >> checkArguments;
        if (!(studentName.size()) || !(courseName.size()) || (checkArguments.size())) //Error check
        {
          cerr << "EnrollStudentInCourse Has Too Many Or Few Arguments.  Expected: Two.\n";
          continue;
        }

        if (!enrollStudentInCourse(studentName, courseName))
          cerr << "EnrollStudentInCourse failed.  Student or course does not"
                  " exist, or the student is already in the course.\n";
      }

      else if (command == "CancelCourse")
      {
        string courseName;
        string checkArguments = "";
        argumentStream >> courseName >> checkArguments;
        if (!(courseName.size()) || (checkArguments.size())) //Error check
        {
          cerr << "CancelCourse Has Too Many Or Few Arguments.  Expected: One.\n";
          continue;
        }

        if (!cancelCourse(courseName))
          cerr << "CancelCourse failed.  Course does not exist.\n";
      }

      else if (command == "DropStudentFromCourse")
      {
        string studentName, courseName;
        string checkArguments = "";
        argumentStream >> studentName >> courseName >> checkArguments;
        if (!(studentName.size()) || !(courseName.size()) || (checkArguments.size())) //Error check
        {
          cerr << "DropStudentFromCourse Has Too Many Or Few Arguments.  Expected: Two.\n";
          continue;
        }

        if (!dropStudentFromCourse(studentName, courseName))
          cerr << "DropStudentFromCourse failed.  Student or course does not"
                  " exist, or the student is not in that course.\n";
      }

      else if (command == "RemoveStudent")
      {
        string studentName;
        string checkArguments = "";
        argumentStream >> studentName >> checkArguments;
        if (!(studentName.size()) || (checkArguments.size())) //Error check
        {
          cerr << "RemoveStudent Has Too Many Or Few Arguments.  Expected: One.\n";
          continue;
        }
        if (!removeStudent(studentName))
          cerr << "RemoveStudent failed.  Student Does Not Exists.";
      }

      else if (command == "ChangeStudentName")
      {
        string studentName, newStudentName;
        string checkArguments = "";
        argumentStream >> studentName >> newStudentName >> checkArguments;
        if (!(studentName.size()) || !(newStudentName.size()) || (checkArguments.size())) //Error check
        {
          cerr << "ChangeStudentName Has Too Many Or Few Arguments.  Expected: Two.\n";
          continue;
        }

        if (!changeStudentName(studentName, newStudentName))
          cerr << "ChangeStudentName Failed.  Student Does Not Exist.\n";
      }

      else if (command == "Purge")
      {
        string checkArguments;
        if (argumentStream >> checkArguments)
        {
          cerr << "Purge Has Too Many Arguments.  Expected: None.\n";
          continue;
        }
        purge();
      }
      else
        cerr << "Unknown command: " << command << endl;
    }
  }
}
