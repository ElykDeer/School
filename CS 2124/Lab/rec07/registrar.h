#ifndef BROOKLYN_POLLY_REGISTRAR
#define BROOKLYN_POLLY_REGISTRAR 1

#include <iostream>
#include <string.h>
#include <vector>
#include <fstream>
#include <sstream>

namespace BrooklynPoly
{
  //Necessary Forward Decs
  class Course;
  class Student;

  class Registrar {
   friend std::ostream& operator<<(std::ostream&, const Registrar&);
  public:
    ~Registrar(); //Added
    void printReport(std::ostream& = std::cout) const;
    bool addCourse(const std::string&);
    bool addStudent(const std::string&);
    bool enrollStudentInCourse(const std::string&, const std::string&);
    bool cancelCourse(const std::string& courseName);
    bool changeStudentName(const std::string&, const std::string&);
    bool dropStudentFromCourse(const std::string&, const std::string&);
    bool removeStudent(const std::string&);
    void purge();
    void readCommandFile(); //Added
  private:
    Student* findStudent(const std::string& ) const; //Added
    Course* findCourse(const std::string& ) const; //Added
    std::vector<Course*> courses;
    std::vector<Student*> students;
  };

  std::ostream& operator<<(std::ostream& os, const Registrar&);
}
#endif
