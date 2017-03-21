//My includes
#include "course.h"
#include "student.h"

using namespace std;

//My namespace
namespace BrooklynPoly
{
  //Necessary Forward Dec
  class Student;

  //Printing Overload
  ostream& operator<<(ostream& os, const Course& rhs)
  {
    os << " Course Name: ";
    os << rhs.name;
    os << "\n  Students:";

    //If there are students, print them all out on one lines
    bool thereAreStudents;
    if (!(thereAreStudents = rhs.students.size()))
      os << " None.";
    else
      for (Student* student : rhs.students)
        { os << " " << *student; }
    os << endl;
    return os; //For Cahining
  }

  //Courses are made with names
  Course::Course(const string& courseName) : name(courseName) {}

  void Course::printReport(ostream& os) const
    { cout << *this; }

  const string& Course::getName() const
    { return name; }

  //Will add a student if they're not in the class already.
    //Returns false if they can't be added, otherwise true
  bool Course::addStudent(Student* student)
  {
    //Make sure they're not already in the course, then add them
    if (hasStudent(student->getName()))
      return false;
    else
    {
      students.push_back(student);
      return hasStudent(student->getName()); //Double check
    }
  }

  //Added Function - checks if a student is in this course
  bool Course::hasStudent(const std::string& studentName) const
  {
    for (Student* student : students)
      if (student->getName() == studentName)
        return true;
    return false;
  }

  bool Course::cancel()
  {
    for (Student* student : students)
      if (!removeStudent(student)) //If everything goes smoothly
        return false;
    return true; //All good
  }

  bool Course::removeStudent(Student* student)
  {
    //Find the student and remove them
    for (size_t i = 0; i<students.size(); ++i)
      if (students[i] == student)
      {
        //Make sure they know not to attend
        students[i]->removedFromCourse(this);
        //Remove them:
        students[i] = students[students.size()-1];
        students.pop_back();
        return true;
      }
    return false;
  }
}
