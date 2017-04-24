//My includes
#include "student.h"
#include "course.h"

using namespace std;

//My namespace
namespace BrooklynPoly
{
  //Necessary Forward Decs
  class Course;

  //Constructor
  Student::Student(const string& name) : name(name) {}

  const string& Student::getName() const
    { return name; }

  //True if it worked, false if something went wrong
  bool Student::addCourse(Course* course)
  {
    //Make sure they're not already in the course, then add them
    if (isInCourse(course->getName()))
      return false;
    else
    {
      courses.push_back(course);
      //Double check (and call the course info)
      return isInCourse(course->getName());
    }
  }

  bool Student::removedFromCourse(Course* cp)
  { //The opposite of addCourse
    //Make sure they're in the course, then remove them
    if (!isInCourse(cp->getName()))
      return false;
    else
    {
      for (size_t i = 0; i<courses.size(); ++i)
        if (courses[i] == cp)
        {
          courses[i] = courses[courses.size()-1];
          courses.pop_back();
        }

      return !(isInCourse(cp->getName()));
    }
  }
  void Student::changeName(const string& name)
    { this->name = name; }

  void Student::dropCourses()
  {
    //Inform Each Course
    for (Course* course : courses)
      course->removeStudent(this);
    //Clear student schedule
    courses.clear();
  }

  bool Student::isInCourse(const string& courseName) const
  {
    for (Course* course : courses)
      if (course->getName() == courseName)
        return true;
    return false;
  }

  ostream& operator<<(ostream& os, const Student& rhs)
  {
    os << rhs.name;
    return os;
  }
}
