#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cstdlib>
using namespace std;

/*========== Class Prototypes ==========*/
	class Time;
    class Holding;
	class Course;
	class Student;
	class StudentCourse;
	class Teacher;
	class ClassRoom;
	class Position;
	
/*========== End Class Prototypes ==========*/

/*========== Class Time ==========*/
	class Time
	{
	public:
		Time();
		Time(int h,int m);
		int getHour();
		int getMinute();
		void printTime();
		bool operator <(Time rhs);
		bool operator <=(Time rhs);
	private:
		int hour,minute;

		/* data */
	};

/*====================*/
	Time::Time()
	{

	}

/*====================*/
	Time::Time(int h,int m)
	{
		hour = h;
		minute = m;
		if (h<0 || h>23 || m<0 || m>59)
		{
			hour = 0;
			minute = 0;
		}
	}

/*====================*/
	int Time::getHour()
	{
		return hour;
	}

/*====================*/
	int Time::getMinute()
	{
		return minute;
	}

/*====================*/
	void Time::printTime()
	{
		cout<<hour<<":"<<minute;
	}

/*====================*/
	bool Time::operator <(Time rhs)
	{
		if (hour< rhs.getHour())
		{
			return 1;
		}
		if (hour == rhs.getHour())
		{
			return (minute<rhs.getMinute());
		}
		return 0;
	}

/*====================*/
	bool Time::operator <=(Time rhs)
	{
		if (hour< rhs.getHour())
		{
			return 1;
		}
		if (hour == rhs.getHour())
		{
			return (minute<=rhs.getMinute());
		}
		return 0;
	}

/*========== End Class Time ==========*/

/*========== Class Position ==========*/
	class Position
	{
	public:
	    Position();
		Position(string fclty);
		void setPosition(string fclty);
		void printPosition();
		string getFaculty();
		bool operator ==(Position rhs);
	private:
		string faculty;
		/* data */
	};

/*====================*/
    Position::Position()
    {

    }

/*====================*/
	Position::Position(string fclty)
	{
		setPosition(fclty);
	}

/*====================*/
	void Position::setPosition(string fclty)
	{
		faculty = fclty;
	}

/*====================*/
	void Position::printPosition()
	{
		cout<<faculty;
	}
/*====================*/

	string Position::getFaculty()
	{
		return faculty;
	}

/*====================*/

	bool Position::operator ==(Position rhs)
	{
		return (faculty == rhs.getFaculty());
	}

/*========== End Class Position ==========*/

/*========== Class ClassRoom ==========*/
	class ClassRoom
	{
	public:
		ClassRoom(int rmCode,string rmName,Position pstn);
		void setRoomName(string rmName);
		void setRoomPosition(Position pstn);
		void printClassRoom();
		int getRoomCode();
		Position getPosition();
		bool operator ==(ClassRoom rhs);
		vector<Holding*> holdings;
		/* data */
	private:
		int roomCode;
		string roomName;
		Position position;
	};

/*====================*/
	ClassRoom::ClassRoom(int rmCode,string rmName,Position pstn)
	{
		roomCode = rmCode;
		setRoomName(rmName);
		position = pstn;
	}

/*====================*/
	void ClassRoom::setRoomName(string rmName)
	{
		roomName = rmName;
	}

/*====================*/
	void ClassRoom::setRoomPosition(Position pstn)
	{
		position = pstn;
	}

/*====================*/
	void ClassRoom::printClassRoom()
	{
		cout<<roomCode<<" "<<roomName<<" ";
		position.printPosition();
	}

/*====================*/
	int ClassRoom::getRoomCode()
	{
		return roomCode;
	}

/*====================*/
	Position ClassRoom::getPosition()
	{
		return position;
	}

/*====================*/
	bool ClassRoom::operator == (ClassRoom rhs)
	{
		if (position == rhs.getPosition())
		{
			return (roomCode == rhs.getRoomCode());
		}
		return 0;
	}

/*========== End Class ClassRoom ==========*/

/*========== Class Holding ==========*/
	class Holding
	{
	public:
		Holding(int d,Time sTime,Time eTime,ClassRoom &clsRoom);
		int getDay();
		Time getStartTime();
		Time getEndTime();
		ClassRoom* getClassRoom();
		void printDay();
		void printHolding();
		bool isNested(Holding hld);
		bool isNestedTime(Time sTime,Time eTime);
	private:
		int day;
		Time startTime,endTime;
		ClassRoom* classRoom;

		/* data */
	};

/*====================*/
	Holding::Holding(int d,Time sTime,Time eTime,ClassRoom &clsRoom)
	{
		day = d;
		classRoom = &clsRoom;
		startTime = sTime;
		endTime = eTime;
	}

/*====================*/
	int  Holding::getDay()
	{
		return day;
	}

/*====================*/
	Time  Holding::getStartTime()
	{
		return startTime;
	}

/*====================*/
	Time  Holding::getEndTime()
	{
		return endTime;
	}

/*====================*/
	ClassRoom* Holding::getClassRoom()
	{
		return classRoom;
	}

/*====================*/
	void Holding::printHolding()
	{

		classRoom->printClassRoom();
		cout<<" ";
		printDay();
		cout<<" ";
		startTime.printTime();
		cout<<" ";
		endTime.printTime();
	}

/*====================*/
	bool Holding::isNested(Holding hld){
		if (day == hld.getDay())
		{
			if (isNestedTime(hld.getStartTime(),hld.getEndTime()))
			{
				if (*classRoom == *(hld.getClassRoom()))
				{
					return 1;
				}
			}
		}
		return 0;
	}

/*====================*/
	bool Holding::isNestedTime(Time sTime,Time eTime)
	{
		if (sTime<=startTime)
		{
			return (startTime<eTime);
		}
		if (startTime<sTime)
		{
			return (sTime<endTime);
		}
	}

/*====================*/
	void Holding::printDay()
	{

		switch(day)
		{
            case 1:
                cout<<"Shanbe";
                break;
            case 2:
                cout<<"Yekshanbe";
                break;
            case 3:
                cout<<"Doshanbe";
                break;
            case 4:
                cout<<"Seshanbe";
                break;
            case 5:
                cout<<"Charshanbe";
                break;
            case 6:
                cout<<"Panjshanbe";
                break;
            case 7:
                cout<<"Jome";
                break;
            default:
                break;
		}
	}

/*========== End Class holding ==========*/

/*========== Class Course ==========*/
	class Course
	{
		public:
			Course(int cCode,string cName,int unt,int grp,int cpcty);
			Course(int cCode,int grp);
			void printCourse();
			bool isFull();
			void plusStdCount();
			void minesStdCount();
			long getCourseCode();
			string getCourseName();
			int getUnit();
			int getGroup();

			bool haveTeacher();
			void addHolding(Holding hld);
			void setTeacher(Teacher &tchr);
			void addPreReqCourse(Course &crs);
			Teacher* getTeacher();
			bool isNested(Holding hld);
			bool isNested(Course crs);
			bool operator==(Course crs);
			vector<Course*> preReqCourses;
			vector<Holding> holdings;
		private:
			int capacity,stdCount,group,unit;
			bool haveTchr;
			long courseCode;
			string courseName;
			Teacher *teacher;
			/* data */
	};

/*====================*/
	Course::Course(int cCode,string cName,int unt,int grp,int cpcty)
	{
		courseCode = cCode;
		courseName = cName;
		unit = unt;
		stdCount = 0;
		group = grp;
		capacity = cpcty;
		haveTchr = 0;
	}


	Course::Course(int cCode,int grp)
	{
		courseCode = cCode;
		group = grp;
	}
/*====================*/
	void Course::printCourse()
	{
		cout<<courseCode<<" "<<courseName<<" Group: "<<group<<" Capacity: "<<capacity<<" Filled: "<<stdCount;
	}

/*====================*/
	bool Course::isFull()
	{
		return (stdCount >= capacity);
	}

/*====================*/
	void Course::plusStdCount()
	{
		stdCount++;
	}

/*====================*/
	void Course::minesStdCount()
	{
		stdCount--;
	}

/*====================*/
	long Course::getCourseCode()
	{
		return courseCode;
	}

/*====================*/
	string Course::getCourseName()
	{
		return courseName;
	}

/*====================*/
	int Course::getUnit()
	{
		return unit;
	}

/*====================*/
	int Course::getGroup()
	{
		return group;
	}

/*====================*/
	bool Course::haveTeacher()
	{
		return haveTchr;
	}

/*====================*/
	void Course::addHolding(Holding hld)
	{
		holdings.push_back(hld);
	}

/*====================*/
	void Course::setTeacher(Teacher &tchr)
	{
		teacher = &tchr;
	}

/*====================*/
	void Course::addPreReqCourse(Course &crs)
	{
		preReqCourses.push_back(&crs);
	}
/*====================*/
	Teacher* Course::getTeacher()
	{
		return teacher;
	}

/*====================*/

	bool Course::isNested(Holding hld)
	{
		for (int i = 0; i < holdings.size(); ++i)
		{
			if (holdings.at(i).isNested(hld))
			{
				return 1;
			}
		}
		return 0;
	}

/*====================*/
	bool Course::isNested(Course crs)
	{
		for (int i = 0; i < crs.holdings.size(); ++i)
		{
			if (isNested(crs.holdings.at(i)))
			{
				return 1;
			}
		}
		return 0;
	}


	bool Course::operator==(Course crs)
	{
		return (courseCode == crs.getCourseCode() && group == crs.getGroup());
	}

/*========== End Class Course ==========*/

/*========== Class StudentCourse ==========*/
	class StudentCourse
	{
		public:
			StudentCourse(Course &crs);
			long getCourseCode();
			int getStatus();
			float getMark();
			int getUnit();
			void printCourse();
			void setMark(int mrk);
			bool isNested(Course crs);
			Course* course;
			/* data */
		private:
			int status;
			float mark;
	};

/*====================*/
	StudentCourse::StudentCourse(Course &crs)
	{
		course = &crs;
		mark = 0;
		status = 0;
	}

/*====================*/
	long StudentCourse::getCourseCode()
	{
		return course->getCourseCode();
	}
/*====================*/
	int StudentCourse::getStatus()
	{
		return status;
	}

/*====================*/
	float StudentCourse::getMark()
	{
		return mark;
	}

/*====================*/
	int StudentCourse::getUnit()
	{
		return course->getUnit();
	}

/*====================*/
	void StudentCourse::printCourse()
	{
		cout<<course->getCourseCode()<<" "<<course->getCourseName()<<"  Group: "<<course->getGroup()<<" Mark: "<<getMark();
	}

/*====================*/
	void StudentCourse::setMark(int mrk)
	{
		mark = mrk;
		if (mark<10)
		{
			status = -1;
		} else
		{
			status = 1;
		}
	}

/*====================*/
	bool StudentCourse::isNested(Course crs)
	{
		return course->isNested(crs);
	}

/*========== End Class StudentCourse ==========*/

/*========== Class Student ==========*/
	class Student
	{
		public:
			Student(long stdCode, string fName, string lName);
			void resetName(string fName,string lName);
			void printStudent();
			void addCourse(Course &course);
			long getStudentCode();
			int printCourses();
			bool isNested(Course course);
			StudentCourse* getCourse(int input);
			float getAverage();
			vector<StudentCourse> studentCourses;
		private:
			long studentCode;
			string firstName, lastName;
			/* data */
	};

/*====================*/
	Student::Student(long stdCode, string fName, string lName)
	{
		studentCode = stdCode;
		firstName = fName;
		lastName = lName;
	}

/*====================*/
	void Student::resetName(string fName,string lName)
	{
		firstName = fName;
		lastName = lName;
	}

/*====================*/
	void Student::printStudent()
	{
		cout<<firstName<<" "<<lastName<<" "<<studentCode;
	}

/*====================*/
	long Student::getStudentCode()
	{
		return studentCode;
	}

/*====================*/
	int Student::printCourses()
	{
		for (int i = 0; i < studentCourses.size(); ++i)
		{
			cout<<i+1<<". ";
			studentCourses.at(i).printCourse();
			cout<<endl;
		}
		return studentCourses.size();
	}

/*====================*/
	void Student::addCourse(Course &course)
	{
		system("CLS");
		if (course.isFull() == 1)
		{
			cout<<"This Course's Student Counts is Reached "<<endl;
			system("PAUSE");
			return;
		}
		if (isNested(course))
		{
			cout<<"This Course is Nested with other selected Courses"<<endl;
			system("PAUSE");
			return;
		}
		for (int j = 0; j < studentCourses.size(); ++j)
			{
			if (studentCourses.at(j).getCourseCode() == course.getCourseCode() && studentCourses.at(j).getStatus() == 1)
			{
				cout<<"You Passed This Course Before"<<endl;
				system("PAUSE");
				return;
			}
			if (studentCourses.at(j).getCourseCode() == course.getCourseCode() && studentCourses.at(j).getStatus() == 0)
			{
				cout<<"You Have Selected This Course For This Term"<<endl;
				system("PAUSE");
				return;
			}
		}

		if (course.preReqCourses.size() > 0 && studentCourses.size() == 0)
		{

			cout<<"You Did not Pass Pre Required Courses "<<endl;
			system("PAUSE");
			return;
		}
		for (int i = 0; i < course.preReqCourses.size(); ++i)
		{

			for (int j = 0; j < studentCourses.size(); ++j)
			{

				if (studentCourses.at(j).getCourseCode() == course.preReqCourses.at(i)->getCourseCode() && studentCourses.at(j).getStatus() == 1)
				{
					break;
				}
				if (j+1 == studentCourses.size())
				{
					cout<<"You Don't Passed Pre Required Courses "<<endl;
					system("PAUSE");
					return;
				}
			}
		}
		studentCourses.push_back(course);
		course.plusStdCount();
		cout<<"This Course Added Successfully "<<endl;
		system("PAUSE");
	}

/*====================*/
	bool Student::isNested(Course course)
	{
		for (int i = 0; i < studentCourses.size(); ++i)
		{
			if (studentCourses.at(i).isNested(course))
			{
				return 1;
			}
		}
		return 0;
	}

/*====================*/
	StudentCourse* Student::getCourse(int input)
	{
		return &(studentCourses.at(input));
	}

/*====================*/
	float Student::getAverage()
	{
		float markSum=0;
		int unitSum=0;
		for (int i = 0; i < studentCourses.size(); ++i)
		{
			if (studentCourses.at(i).getStatus() !=0)
			{
				markSum += studentCourses.at(i).getMark() * studentCourses.at(i).getUnit();
				unitSum += studentCourses.at(i).getUnit();
			}
		}
		return markSum/unitSum;
	}

/*========== End Class Student ==========*/

/*========== Class Teacher ==========*/
	class Teacher
	{
		public:
			Teacher(long tchrCode,string fName,string lName);
			void printTeacher();
			long getTeacherCode();
			void resetName(string fName,string lName);
			vector<Course*> courses;
		private:
			long teacherCode;
			string firstName, lastName;
		/* data */
	};

/*====================*/
    Teacher::Teacher(long tchrCode,string fName,string lName)
    {
        teacherCode = tchrCode;
        firstName = fName;
        lastName = lName;
    }

/*====================*/
	void Teacher::resetName(string fName,string lName)
	{
		firstName = fName;
		lastName = lName;
	}

/*====================*/
	long Teacher::getTeacherCode()
	{
		return teacherCode;
	}

/*====================*/
	void Teacher::printTeacher()
	{
		cout<<teacherCode<<" "<<firstName<<" "<<lastName;
	}

/*========== End Class Teacher ==========*/

/*========== Functions Prototypes ==========*/
	void studentsMainPage(vector<Student>& students,vector<Course>& courses);
	void studentSelectPage(vector<Student>& students,vector<Course>& courses);
	void studentPage(Student& student,vector<Course>& courses);
	void studentAddCoursePage(Student &student,vector<Course>& courses);
	void studentAddCourse(Student &student,Course &course);
	void studentRecordMarkMainPage(Student &student);
	void studentRecordMarkPage(StudentCourse *course);
	void studentRemoveCourseMainPage(Student &student);
	void studentGetAveragePage(Student student);
	void studentEditName(Student &student);
	void studentAddPage(vector<Student>& students);
	void studentRemove(vector<Student>& students);
	void teachersMainPage(vector<Teacher>& teachers);
	void teachersSelectPage(vector<Teacher>& teachers);
	void teacherPage(Teacher &teacher);
	void teacherSelectCourse(Teacher teacher);
	void teacherEditNamePage(Teacher &teacher);
	void teacherAddPAge(vector<Teacher> &teachers);
	void teacherRemovePage(vector<Teacher>& teachers);
	void coursesMainPage(vector<Course> &courses,vector<ClassRoom> &classRooms,vector<Teacher>& teachers);
	void courseSelectPage(vector<Course> &courses,vector<ClassRoom> &classRooms,vector<Teacher>& teachers);
	void coursePage(Course *course,vector<ClassRoom> &classRooms,vector<Teacher>& teachers,vector<Course> &courses);
	void courseAddHolding(Course &course,vector<ClassRoom> &classRooms);
	void courseRemoveHolding(Course &course);
	void courseShowHoldings(Course &course);
	void courseSetTeacher(Course &course,vector<Teacher>& teachers);
	void courseAddPrereqCourse(Course &course,vector<Course> &courses);
	void courseAddPage(vector<Course> &courses);
	void classRoomsMainPage(vector<ClassRoom>& classRooms);
	void classRoomSelect(vector<ClassRoom>& classRooms);
	void classRoomPage(ClassRoom &classRoom);
	void classRoomHoldings(ClassRoom classRoom);
	void classRoomEditNamePositionPage(ClassRoom &classRoom);
	void classRoomEditRoomName(ClassRoom &classRoom);
	void classRoomEditRoomPosition(ClassRoom &classRoom);
	void classRoomsAddPage(vector<ClassRoom>& classRooms);

/*========== End Functions Prototype ==========*/

/*========== Main ==========*/
	int main()
	{
		static vector<Student> students;
		static vector<Course> courses;
		static vector<Teacher> teachers;
		static vector<ClassRoom> classRooms;
		int input;
		do
		{
			system("CLS");
			cout
			<<"1. Students"<<endl
			<<"2. Teachers"<<endl
			<<"3. Courses"<<endl
			<<"4. Class Rooms"<<endl
			<<endl<<"0. Exit"<<endl;
			cin>>input;
			switch (input)
			{
				case 1:
					studentsMainPage(students,courses);
					break;
				case 2:
					teachersMainPage(teachers);
					break;
				case 3:
					coursesMainPage(courses,classRooms,teachers);
					break;
				case 4:
					classRoomsMainPage(classRooms);
					break;
				default:
					break;
			}
		} while (input > 0 && input <= 4);
	}

/*========== End Main ==========*/

/*====================*/
	void studentsMainPage(vector<Student>& students,vector<Course>& courses)
	{
		int input;
		do
		{
			system("CLS");
			cout
			<<"1. Select Student"<<endl
			<<"2. Add Student"<<endl
			<<"3. Remove Student"<<endl
			<<endl<<"0. Back"<<endl;
			cin>>input;
			switch(input)
			{
				case 1:
					studentSelectPage(students,courses);
					break;
				case 2:
					studentAddPage(students);
					break;
				case 3:
					studentRemove(students);
					break;
				default:
					break;
			}
		} while (input > 0 && input <=3);
	}

/*====================*/
	void studentSelectPage(vector<Student>& students,vector<Course>& courses)
	{
		int input;
		do
		{
			system("CLS");
			for (int i = 0; i < students.size(); ++i)
			{
				cout
				<<i+1<<". ";
				students.at(i).printStudent();
				cout<<endl;
			}
			cout
			<<endl<<"0. Back"<<endl;
			cin>>input;
			if (input > 0 && input <= students.size())
			{
				studentPage(students.at(input-1),courses);
			}
			if (input > students.size())
			{
				continue;
			}
		} while (input != 0);
	}

/*====================*/
	void studentPage(Student &student,vector<Course>& courses)
	{
		int input;
		do
		{
			system("CLS");
			cout
			<<"1. Add Course"<<endl
			<<"2. Record Mark"<<endl
			<<"3. Remove Course"<<endl
			<<"4. Get Average"<<endl
			<<"5. Edit Student Name"<<endl
			<<endl<<"0. Back"<<endl;
			cin>>input;
			switch(input)
			{
				case 1:
					studentAddCoursePage(student,courses);
					break;
				case 2:
					studentRecordMarkMainPage(student);
					break;
				case 3:
					studentRemoveCourseMainPage(student);
					break;
				case 4:
					studentGetAveragePage(student);
					break;
				case 5:
					studentEditName(student);
					break;
				default:
					break;
			}
		} while (input > 0 && input <=5);
	}

/*====================*/
	void studentAddCoursePage(Student &student,vector<Course>& courses)
	{
		int input;
		do
		{
			system("CLS");
			for (int i = 0; i < courses.size(); ++i)
			{
				cout
				<<i+1<<". ";
				courses.at(i).printCourse();
				cout<<endl;
			}
			cout
			<<endl<<"0. Back"<<endl;
			cin>>input;
			if (input > courses.size())
			{
				continue;
			}
			if (input > 0 && input <= courses.size())
			{
				studentAddCourse(student,courses.at(input-1));
			}
		} while (input != 0);
	}

/*====================*/
	void studentAddCourse(Student &student,Course &course)
	{
		student.addCourse(course);
	}

/*====================*/
	void studentRecordMarkMainPage(Student &student)
	{
		int input;
		do
		{
			system("CLS");
			int coursesCount = student.printCourses();
			cout<<endl<<"0. Back"<<endl;
			cin>>input;
			if (input > coursesCount)
			{
				continue;
			}
			if (input > 0 && input <= coursesCount)
			{
				studentRecordMarkPage(student.getCourse(input-1));
			}
		} while (input != 0);
	}

/*====================*/
	void studentRecordMarkPage(StudentCourse *course)
	{
		int input;
		system("CLS");
		cout<<"Enter Mark: ";
		cin>>input;
		course->setMark(input);
	}

/*====================*/
	void studentRemoveCourseMainPage(Student &student)
	{
		int input;
		do
		{
			system("CLS");
			int coursesCount = student.printCourses();
			cout<<endl<<"0. Back"<<endl;
			cin>>input;
			if (input > coursesCount)
			{
				continue;
			}
			if (input > 0 && input <= coursesCount)
			{
				student.studentCourses.at(input-1).course->minesStdCount();
				student.studentCourses.erase (student.studentCourses.begin() + input-1);
				cout<<"Course Removed Successfully "<<endl;
				system("PAUSE");
				return;
			}
		} while (input != 0);
	}


/*====================*/
	void studentGetAveragePage(Student student)
	{
		cout<<"Average: "<<student.getAverage()<<endl;
		system("PAUSE");
	}

/*====================*/
	void studentEditName(Student &student)
	{
		string fName,lName;
		system("CLS");
		cout<<"Enter New FirstName: ";
		cin>>fName;
		cout<<"Enter New LastName: ";
		cin>>lName;
		student.resetName(fName,lName);
		cout<<"Student Name Changed successfully"<<endl;
		system("PAUSE");
	}

/*====================*/
	void studentAddPage(vector<Student>& students)
	{
		long stdCode;
		string fName,lName;
		system("CLS");
		cout<<"Enter Student Code: ";
		cin>>stdCode;
		for (int i = 0; i < students.size(); ++i)
		{
			if (students.at(i).getStudentCode() == stdCode)
			{
				cout<<"Invalid Student Code"<<endl;
				system("PAUSE");
				return;
			}
		}
		cout<<"Enter First Name: ";
		cin>>fName;
		cout<<"Enter Last Name: ";
		cin>>lName;
		Student temp(stdCode,fName,lName);
		students.push_back(temp);
		cout<<"Student Added Successfully "<<endl;
		system("PAUSE");
		return;
	}

/*====================*/
	void studentRemove(vector<Student>& students)
	{
	    int input;
		do
		{
			system("CLS");
			for (int i = 0; i < students.size(); ++i)
			{
				cout<<i+1<<". ";
				students.at(i).printStudent();
				cout<<endl;
			}
			cout<<endl<<"0. Back"<<endl;
			cin>>input;
			if (input>0 && input <= students.size())
			{
				for (int j = 0; j < students.at(input-1).studentCourses.size(); ++j)
				{
					students.at(input-1).studentCourses.at(j).course->minesStdCount();
				}
				students.erase (students.begin() + input-1);
				cout<<"Student Removed Successfully "<<endl;
				system("PAUSE");
				return;
			}
		} while (input !=0);
	}

/*====================*/
	void teachersMainPage(vector<Teacher>& teachers)
	{
		int input;
		do
		{
			system("CLS");
			cout
			<<"1. Select Teacher"<<endl
			<<"2. Add Teacher"<<endl
			<<"3. Remove Teacher"<<endl
			<<endl<<"0. Back"<<endl;
			cin>>input;
			switch(input)
			{
				case 1:
					teachersSelectPage(teachers);
					break;
				case 2:
					teacherAddPAge(teachers);
					break;
				case 3:
					teacherRemovePage(teachers);
					break;
				default:
					break;
			}
		} while (input > 0 && input <=3);
	}

/*====================*/
	void teachersSelectPage(vector<Teacher>& teachers)
	{
		int input;
		do
		{
			system("CLS");
			for (int i = 0; i < teachers.size(); ++i)
			{
				cout
				<<i+1<<". ";
				teachers.at(i).printTeacher();
				cout<<endl;
			}
			cout
			<<endl<<"0. Back"<<endl;
			cin>>input;
			if (input > 0 && input <= teachers.size())
			{
				teacherPage(teachers.at(input-1));
			}
			if (input > teachers.size())
			{
				continue;
			}
		} while (input != 0);
	}

/*====================*/
	void teacherPage(Teacher &teacher)
	{
		int input;
		do
		{
			system("CLS");
			cout
			<<"1. Show Courses"<<endl
			<<"2. Edit Teacher Name"<<endl
			<<endl<<"0. Back"<<endl;
			cin>>input;
			switch(input)
			{
				case 1:
					teacherSelectCourse(teacher);
					break;
				case 2:
					teacherEditNamePage(teacher);
					break;
				default:
					break;
			}
		} while (input > 0 && input <=2);
	}

/*====================*/
	void teacherSelectCourse(Teacher teacher)
	{

		system("CLS");
		for (int i = 0; i < teacher.courses.size(); ++i)
		{
			cout
			<<i+1<<". ";
			teacher.courses.at(i)->printCourse();
			cout<<endl;
		}
		system("PAUSE");
	}

/*====================*/
	void teacherEditNamePage(Teacher &teacher)
	{
		string fName,lName;
		system("CLS");
		cout<<"Enter New FirstName: ";
		cin>>fName;
		cout<<"Enter New LastName: ";
		cin>>lName;
		teacher.resetName(fName,lName);
		cout<<"Teacher Name Changed successfully"<<endl;
		system("PAUSE");
	}

/*====================*/
	void teacherAddPAge(vector<Teacher> &teachers)
	{
		long tchrCode;
		string fName,lName;
		system("CLS");
		cout<<"Enter Teacher Code: ";
		cin>>tchrCode;
		for (int i = 0; i < teachers.size(); ++i)
		{
			if (teachers.at(i).getTeacherCode() == tchrCode)
			{
				cout<<"Invalid Teacher Code"<<endl;
				system("PAUSE");
				return;
			}
		}
		cout<<"Enter First Name: ";
		cin>>fName;
		cout<<"Enter Last Name: ";
		cin>>lName;
		Teacher temp(tchrCode,fName,lName);
		teachers.push_back(temp);
		cout<<"Teacher Added Successfully "<<endl;
		system("PAUSE");
		return;
	}

/*====================*/
	void teacherRemovePage(vector<Teacher>& teachers)
	{
		int input;
		do
		{
			system("CLS");
			for (int i = 0; i < teachers.size(); ++i)
			{
				cout<<i+1<<". ";
				teachers.at(i).printTeacher();
				cout<<endl;
			}
			cout<<endl<<"0. Back"<<endl;
			cin>>input;
			if (input>0 && input <= teachers.size())
			{
				teachers.erase (teachers.begin() + input-1);
				cout<<"Teacher Removed Successfully "<<endl;
				system("PAUSE");
				return;
			}
		} while (input !=0);
	}

/*====================*/
	void classRoomsMainPage(vector<ClassRoom>& classRooms)
	{
		int input;
		do
		{
			system("CLS");
			cout
			<<"1. Select Class Room"<<endl
			<<"2. Add Class Room"<<endl
			<<endl<<"0. Back"<<endl;
			cin>>input;
			switch(input)
			{
				case 1:
					classRoomSelect(classRooms);
					break;
				case 2:
					classRoomsAddPage(classRooms);
					break;
				default:
					break;
			}
		} while (input > 0 && input <=2);
	}

/*====================*/
	void classRoomSelect(vector<ClassRoom>& classRooms)
	{
		int input;
		do
		{
			system("CLS");
			for (int i = 0; i < classRooms.size(); ++i)
			{
				cout
				<<i+1<<". ";
				classRooms.at(i).printClassRoom();
				cout<<endl;
			}
			cout
			<<endl<<"0. Back"<<endl;
			cin>>input;
			if (input > 0 && input <= classRooms.size())
			{
				classRoomPage(classRooms.at(input-1));
			}
			if (input > classRooms.size())
			{
				continue;
			}
		} while (input != 0);
	}

/*====================*/
	void classRoomPage(ClassRoom &classRoom)
	{
		int input;
		do
		{
			system("CLS");
			cout
			<<"1. Show Class Room Program "<<endl
			<<"2. Edit Class Room Name And Position"<<endl
			<<endl<<"0. Back"<<endl;
			cin>>input;
			switch(input)
			{
				case 1:
					classRoomHoldings(classRoom);
					break;
				case 2:
					classRoomEditNamePositionPage(classRoom);
					break;
				default:
					break;
			}
		} while (input > 0 && input <=2);
	}

/*====================*/
	void classRoomHoldings(ClassRoom classRoom)
	{
		system("CLS");
		for (int i = 0; i < classRoom.holdings.size(); ++i)
		{
			cout<<i+1<<". ";
			classRoom.holdings.at(i)->printHolding();
			cout<<endl;
		}
		system("PAUSE");
	}

/*====================*/
	void classRoomEditNamePositionPage(ClassRoom &classRoom)
	{
		int input;
		do
		{
			system("CLS");
			cout
			<<"1. Edit Room Name "<<endl
			<<"2. Edit Room Position"<<endl
			<<endl<<"0. Back"<<endl;
			cin>>input;
			switch(input)
			{
				case 1:
					classRoomEditRoomName(classRoom);
					break;
				case 2:
					classRoomEditRoomPosition(classRoom);
					break;
				default:
					break;
			}
		} while (input > 0 && input <=2);
	}

/*====================*/
	void classRoomEditRoomName(ClassRoom &classRoom)
	{
		system("CLS");
		string rmName;
		cout<<"Enter Class Room's New Name: ";
		cin>>rmName;
		classRoom.setRoomName(rmName);
		cout<<"Room Name Changed successfully"<<endl;
		system("PAUSE");
	}

/*====================*/
	void classRoomEditRoomPosition(ClassRoom &classRoom)
	{
		system("CLS");
		string fclty;
		cout<<"Enter Class Room's New Position' Faculty: ";
		cin>>fclty;
		classRoom.setRoomPosition(fclty);
		cout<<"Position Changed successfully"<<endl;
		system("PAUSE");
	}

/*====================*/
	void classRoomsAddPage(vector<ClassRoom>& classRooms)
	{
		system("CLS");
		int rmCode;
		string rmName,fclty;
		cout<<"Enter ClassRoom Code: ";
		cin>>rmCode;
		cout<<"Enter Room Faculty:";
		cin>>fclty;
		Position p(fclty);
		for (int i = 0; i < classRooms.size(); ++i)
		{
			if (classRooms.at(i).getRoomCode() == rmCode && classRooms.at(i).getPosition() == p)
			{
				cout<<"Room With This Room Code And Position Exist Before"<<endl;
				system("PAUSE");
				return;
			}
		}
		cout<<"Enter Room Name: ";
		cin>>rmName;
		ClassRoom temp(rmCode,rmName,p);
		classRooms.push_back(temp);
		cout<<"Class Room Added Successfully"<<endl;
		system("PAUSE");
		return;
	}

/*====================*/
	void coursesMainPage(vector<Course> &courses,vector<ClassRoom> &classRooms,vector<Teacher>& teachers)
	{
		int input;
		do
		{
			system("CLS");
			cout
			<<"1. Select Course"<<endl
			<<"2. Add Course"<<endl
			<<endl<<"0. Back"<<endl;
			cin>>input;
			switch(input)
			{
				case 1:
					courseSelectPage(courses,classRooms,teachers);
					break;
				case 2:
					courseAddPage(courses);
					break;
				default:
					break;
			}
		} while (input > 0 && input <=2);
	}

/*====================*/
	void courseSelectPage(vector<Course> &courses,vector<ClassRoom> &classRooms,vector<Teacher>& teachers)
	{
		int input;
		do
		{
			system("CLS");
			for (int i = 0; i < courses.size(); ++i)
			{
				cout
				<<i+1<<". ";
				courses.at(i).printCourse();
				cout<<endl;
			}
			cout
			<<endl<<"0. Back"<<endl;
			cin>>input;
			if (input > 0 && input <= courses.size())
			{
				coursePage(&(courses.at(input-1)),classRooms,teachers,courses);
			}
			if (input > courses.size())
			{
				continue;
			}
		} while (input != 0);
	}

/*====================*/
	void coursePage(Course *course,vector<ClassRoom> &classRooms,vector<Teacher>& teachers,vector<Course> &courses)
	{
		int input;
		do
		{
			system("CLS");
			cout
			<<"1. Add Course Hold "<<endl
			<<"2. Remove Course Hold"<<endl
			<<"3. Show All Course Hold"<<endl
			<<"4. Set Teacher"<<endl
			<<"5. Add Pre Required Course"<<endl
			<<endl<<"0. Back"<<endl;
			cin>>input;
			switch(input)
			{
				case 1:
					courseAddHolding(*course,classRooms);
					break;
				case 2:
					courseRemoveHolding(*course);
					break;
				case 3:
					courseShowHoldings(*course);
					break;
				case 4:
					courseSetTeacher(*course,teachers);
					break;
				case 5:
					courseAddPrereqCourse(*course,courses);
					break;
				default:
					break;
			}
		} while (input > 0 && input <=5);
	}

/*====================*/
	void courseAddHolding(Course &course,vector<ClassRoom> &classRooms)
	{
		system("CLS");
		int input,d,h,m;
		cout<<"Choose Class Room"<<endl;
		for (int i = 0; i < classRooms.size(); ++i)
		{
			cout<<i+1<<". ";
			classRooms.at(i).printClassRoom();
			cout<<endl;
		}
		cin>>input;
		do
		{
			system("CLS");
			cout<<"Choose day:"<<endl;
			cout
			<<"1. Shanbe"<<endl
			<<"2. Yekshanbe"<<endl
			<<"3. Doshanbe"<<endl
			<<"4. Seshanbe"<<endl
			<<"5. Charshanbe"<<endl
			<<"6. Panjshanbe"<<endl
			<<"7. Jome"<<endl;
			cin>>d;
		} while (d<1 || d>7);

		cout<<"Enter Course Start Time:(e: 10 45) ";
		cin>>h>>m;
		Time sTime(h,m);
		cout<<"Enter Course End Time:(e: 10 45) ";
		cin>>h>>m;
		Time eTime(h,m);
		Holding hldTmp(d,sTime,eTime,classRooms.at(input-1));
		if (course.isNested(hldTmp))
		{
			cout<<"This Class Room is Filled This Time"<<endl;
			system("PAUSE");
			return;
		} else
		{
			if (course.haveTeacher())
			{
				for (int i = 0; i < course.getTeacher()->courses.size(); ++i)
				{
					if (course.getTeacher()->courses.at(i)->isNested(hldTmp))
					{
						cout<<"Teacher's is Engaged This Time"<<endl;
						system("PAUSE");
						return;
					}
				}
			}
			course.addHolding(hldTmp);
		}
	}

/*====================*/
	void courseRemoveHolding(Course &course)
	{
		int input;
		do
		{
			system("CLS");
			for (int i = 0; i < course.holdings.size(); ++i)
			{
				cout
				<<i+1<<". ";
				course.holdings.at(i).printHolding();
				cout<<endl;
			}
			cout
			<<endl<<"0. Back"<<endl;
			cin>>input;
			if (input > 0 && input <= course.holdings.size())
			{
				course.holdings.erase(course.holdings.begin() + input-1);
				system("PAUSE");
				return;
			}
			if (input > course.holdings.size())
			{
				continue;
			}
		} while (input !=0 );
	}

/*====================*/
	void courseShowHoldings(Course &course)
	{
		system("CLS");
			for (int i = 0; i < course.holdings.size(); ++i)
			{
				cout
				<<i+1<<". ";
				course.holdings.at(i).printHolding();
				cout<<endl;
			}
		system("PAUSE");
	}

/*====================*/
	void courseSetTeacher(Course &course,vector<Teacher>& teachers)
	{
		int input;
		do
		{
			system("CLS");
			for (int i = 0; i < teachers.size(); ++i)
			{
				cout
				<<i+1<<". ";
				teachers.at(i).printTeacher();
				cout<<endl;
			}
			cout
			<<endl<<"0. Back"<<endl;
			cin>>input;
			if (input > 0 && input <= teachers.size())
			{
				for (int i = 0; i < teachers.at(input-1).courses.size(); ++i)
				{
					if (teachers.at(input-1).courses.at(i)->isNested(course))
					{
						cout<<"Teacher's is Nested With This Course Holding Time"<<endl;
						system("PAUSE");
						return;
					}
				}
				if (course.haveTeacher())
				{
					for (int i = 0; i < course.getTeacher()->courses.size(); ++i)
					{
						if (*(course.getTeacher()->courses.at(i)) == course)
						{
                            course.getTeacher()->courses.erase(course.getTeacher()->courses.begin() + i-1);
							break;
						}
					}
				}
				course.setTeacher(teachers.at(input-1));
				teachers.at(input-1).courses.push_back(&course);
				cout<<"Teacher Added For This Course Successfully"<<endl;
				system("PAUSE");
				return;
			}
			if (input > teachers.size())
			{
				continue;
			}
		} while (input != 0);
	}

/*====================*/
	void courseAddPrereqCourse(Course &course,vector<Course> &courses)
	{
		int input;
		do
		{
			system("CLS");
			for (int i = 0; i < courses.size(); ++i)
			{
				cout
				<<i+1<<". ";
				courses.at(i).printCourse();
				cout<<endl;
			}
			cout
			<<endl<<"0. Back"<<endl;
			cin>>input;
			if (input > 0 && input <= courses.size())
			{
				if (course == courses.at(input-1))
				{
					cout<<"You Can Not Select This Course"<<endl;
					system("PAUSE");
					continue;
				}
				for (int i = 0; i < course.preReqCourses.size(); ++i)
				{
					if (*(course.preReqCourses.at(i)) == (courses.at(input-1)))
					{
						cout<<"You Have Selected This Course Before"<<endl;
						system("PAUSE");
						continue;
					}
				}
				course.addPreReqCourse(courses.at(input-1));
				cout<<"Course added Successfully"<<endl;
				system("PAUSE");
				return;
			}
			if (input > courses.size())
			{
				continue;
			}
		} while (input != 0);
	}

/*====================*/
	void courseAddPage(vector<Course> &courses)
	{
		system("CLS");
		int crsCode,crsGroup,crsUnit,crsCapacity;
		string crsName;
		cout<<"Enter Course Code: ";
		cin>>crsCode;
		cout<<"Enter Course Group Number: ";
		cin>>crsGroup;
		Course tmp(crsCode,crsGroup);
		for (int i = 0; i < courses.size(); ++i)
		{
			if (courses.at(i) == tmp)
			{
				cout<<"This Course Added before"<<endl;
				system("PAUSE");
				return;
			}
		}
		cout<<"Enter Course Name: ";
		cin>>crsName;
		cout<<"Enter Coure Unit: ";
		cin>>crsUnit;
		cout<<"Enter Course Capacity: ";
		cin>>crsCapacity;
		Course t(crsCode,crsName,crsUnit,crsGroup,crsCapacity);
		courses.push_back(t);
		cout<<"Course Added Successfully"<<endl;
		system("PAUSE");
	}