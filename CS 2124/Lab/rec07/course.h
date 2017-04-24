#ifndef BROOKLYN_POLLY_COURSE
#define BROOKLYN_POLLY_COURSE 1

#include <iostream>
#include <string.h>
#include <vector>

namespace BrooklynPoly
{
  //Necessary Forward Dec
  class Student;

  class Course
  {
    friend std::ostream& operator<<(std::ostream&, const Course&);
  public:
    Course(const std::string& courseName);
    void printReport(std::ostream& = std::cout) const;
    const std::string& getName() const;
    bool addStudent(Student*); //Changed from intstructor's to bool
    bool removeStudent(Student*);
    bool cancel();
  private:
    bool hasStudent(const std::string&) const; //Added to class
    std::string name;
    std::vector<Student*> students;
  };

  std::ostream& operator<<(std::ostream&, const Course&);
}
#endif
