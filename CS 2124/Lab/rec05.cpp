/* Author: Kyle Martin
 * 
 * This code was written for the class CS 2124
 * 
 * The purpose of this code is to 
 * 
 * */


#include <iostream>
#include <string.h>
#include <vector>
#include <sstream>
using namespace std;

const int SEMESTER_LENGTH = 14;

class Section
{
public:
	Section(const string& sectionName, const string& day, const unsigned int time):
		classTime(day, time), sectionName(sectionName) {}

	Section(const Section& originalSection): classTime(originalSection.classTime), sectionName(originalSection.sectionName)
	{
		for (StudentRecord* const student : originalSection.GradeRecord)
			GradeRecord.push_back(new StudentRecord(*student));
	}

	void addStudent(const string& name)
		{ GradeRecord.push_back(new StudentRecord(name)); }

	void display() const
	{
		cout << "Section " << sectionName << " on ";
		classTime.get();
		cout << ".";
		
		if (GradeRecord.size() == 0)
			cout << " Students: None\n";
		else
			for (const StudentRecord* const student : GradeRecord)
			{
				cout << endl;
				student->print();
			}
		cout<<endl;
				
	}
	
	void addGrade(const string& studentName, const int grade, const int week)
	{
		//Find Student
		for (StudentRecord* const student : GradeRecord)
			if (student->getName() == studentName)
				student->addGrade(grade, week);
	}
	
	~Section()
	{
		cout << endl << "Section " << sectionName << " is being deleted." << endl;
		for (StudentRecord* const student : GradeRecord)
		{
			cout << "Deleting " << student->getName() << "." << endl;
			delete student;
		}
	}
	
	
private:
	//CLasses have times!
	class TimeSlot
	{
	public:
		TimeSlot(const string& day, const unsigned int hour): day(day), hour(hour) {}
		
		//Return a formatted string of day and time
		void get() const
		{
			cout << day << " at ";  
			if (hour < 12)
				cout << hour << "am";
			else if (hour > 12)
				cout << hour-12 << "pm";
			else
				cout << hour << "pm";
		}
			
	private:
		const string day;
		const unsigned int hour;
	};
	
	class StudentRecord
	{
	public:
		StudentRecord(const string& name): name(name), WeeklyGrades(SEMESTER_LENGTH, -1) {}
		
		string getName() const
			{ return name; }
		
		void print() const
		{
			cout << "Student: " << name << ", Grades: ";
			for (const int grade : WeeklyGrades)
				cout << " " << grade;
		}
		
		void addGrade(const int grade, const int week)
			{ WeeklyGrades[week-1] = grade; }
		
	private:
		string name;
		vector <int> WeeklyGrades;
	};
	
	vector <StudentRecord*> GradeRecord;
	TimeSlot classTime;
	string sectionName;
};


class LabWorker
{
public:
	LabWorker(string name): name(name)
	{
		//Check if they have a "good" name (more than one letter), and if they don't, don't let them be used.
		if (!(name.size() > 1))
		{
			cerr << "\nInvalid name!!\n\n";
			certified = false;
		} //Otherwise, good! They've been approved to work
	}
	
	void addSection (Section& newAssignment)
	{
		if (!isQualified())
			cout << name << " is not qualified to teach.\n";
		else
			lab = &newAssignment;
	}

	void display() const
	{
		if (!isQualified())
			cout << name << " is not qualified to teach.\n";
		else if (!lab)
			cout << name << " does not have a section.\n";
		else
		{
			cout << name << " has ";
			lab->display();
		}
	}
	
	void addGrade(const string& studentName, const int grade, const int week)
	{
		if (!isQualified())
			cout << name << " is not qualified to teach.\n";
		else
			lab->addGrade(studentName, grade, week);
	}
	
private:
	Section* lab = nullptr;
	
	bool isQualified() const
		{ return certified; }

	string name;
	bool certified = true;
	
};


// Test code
void doNothing(Section sec) { sec.display(); }

int main() {

	cout << "Test 1: Defining a section\n";
	Section secA2("A2", "Tuesday", 16);
	secA2.display();

	cout << "\nTest 2: Adding students to a section\n";
	secA2.addStudent("John");
	secA2.addStudent("George");
	secA2.addStudent("Paul");
	secA2.addStudent("Ringo");
	secA2.display();

	cout << "\nTest 3: Defining a lab worker.\n";
	LabWorker moe( "Moe" );
	moe.display();

	cout << "\nTest 4: Adding a section to a lab worker.\n";
	moe.addSection( secA2 );
	moe.display();

	cout << "\nTest 5: Adding a second section and lab worker.\n";
	LabWorker jane( "Jane" );
	Section secB3( "B3", "Thursday", 11 );
	secB3.addStudent("Thorin");
	secB3.addStudent("Dwalin");
	secB3.addStudent("Balin");
	secB3.addStudent("Kili");
	secB3.addStudent("Fili");
	secB3.addStudent("Dori");
	secB3.addStudent("Nori");
	secB3.addStudent("Ori");
	secB3.addStudent("Oin");
	secB3.addStudent("Gloin");
	secB3.addStudent("Bifur");
	secB3.addStudent("Bofur");
	secB3.addStudent("Bombur");
	jane.addSection( secB3 );
	jane.display();

	cout << "\nTest 6: Adding some grades for week one\n";
	moe.addGrade("John", 17, 1);  
	moe.addGrade("Paul", 19, 1);  
	moe.addGrade("George", 16, 1);  
	moe.addGrade("Ringo", 7, 1);  
	moe.display();

	cout << "\nTest 7: Adding some grades for week three (skipping week 2)\n";
	moe.addGrade("John", 15, 3);  
	moe.addGrade("Paul", 20, 3);  
	moe.addGrade("Ringo", 0, 3);  
	moe.addGrade("George", 16, 3);  
	moe.display();

	cout << "\nTest 8: We're done (almost)! \nWhat should happen to all those students (or rather their records?)\n";

	cout << "\nTest 9: Oh, IF you have covered copy constructors in lecture, then make sure the following call works\n";
	doNothing(secA2);
	cout << "Back from doNothing\n\n";

} // main
