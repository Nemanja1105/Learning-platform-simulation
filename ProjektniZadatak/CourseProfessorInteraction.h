#pragma once
#include"Course.h"
#include"Student.h"
#include"CourseAdministration.h"

namespace learningPlatform
{
	class CourseProfessorInteraction
	{
	public:
		virtual ~CourseProfessorInteraction() = 0;
		static int showProfessorsCourses(const Professor&, std::vector<Course>&);//stavljeno
		//mozda premjestiti u neki kurs opsta interakciju
		static void showStudentsOnCourses(const Professor&,std::vector<Course>&, std::vector<Student>&);//stavljeno
		static void showCurrStudentOnCourses(Course&,std::vector<Student>&);//stavljeno
		static void showPassStudentOnCourses(Course&,std::vector<Student>&);//stavljeno
		static void reqForCourse(Professor&, std::vector<Course>&,std::vector<Student>&);
		static void writeGrade(Professor&, std::vector<Course>&, std::vector<Student>&);
		
		static Student& studentChoise(std::vector<Student>&);
		static Course& courseChoise(std::vector<Course>&);
		static void printCourseHeader();
		static void printCourseFooter();
		static void printStudHeader();
		static void printStudFooter();
		static Student& getStudent(std::string, std::vector<Student>&);
		static void printStudent(const Student&);
	private:
		//static void printCourseHeader();
		//static void printCourseFooter();
		//static void printStudHeader();
		//static void printStudFooter();
		//static Student& getStudent(std::string, std::vector<Student>&);
		//static void printStudent(const Student&);
		//univerzalne funkcije
		//static Course& courseChoise(std::vector<Course>&);
		//static Student& studentChoise(std::vector<Student>&);
	};
}
