#ifndef BROOKLYN_POLLY_STUDENT
#define BROOKLYN_POLLY_STUDENT 1

//System Includes
#include <iostream>
#include <string.h>
#include <vector>

namespace BrooklynPoly
{
  //Necessary Forward Dec
  class Course;

  class Student
  {
   friend std::ostream& operator<<(std::ostream&, const Student&);
   public:
    Student(const std::string& name);
    void printReport(std::ostream& = std::cout) const;
    const std::string& getName() const;

    //Changed from instructor's default (returned void)
      bool addCourse(Course*);
    //Changed from instructor's default (returned void)
      bool removedFromCourse(Course*);

    void changeName(const std::string& name);
    void dropCourses();
   private:
    //Added in addition to instructor's recomended fuctions
      bool isInCourse(const std::string&) const;
    std::string name;
    std::vector<Course*> courses;
  };

  std::ostream& operator<<(std::ostream&, const Student&);
}
#endif
