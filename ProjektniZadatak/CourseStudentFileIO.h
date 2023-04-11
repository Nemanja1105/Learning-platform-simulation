#pragma once
#include<iostream>
#include<fstream>
#include<filesystem>
#include "Course.h"
#include "PassedCourse.h"
#include "Student.h"

namespace learningPlatform
{
	namespace fs = std::filesystem;
	
	class CourseStudentFileIO
	{
	private:
		static const std::string dirName;
		static const std::string currName;
		static const std::string passName;
		fs::path filePath;
	public:
		CourseStudentFileIO();
		//kada se prihvati zahtjev za predmet
		void writeStudentCurrCourse(const Student&, const Course&);
		//prebirsavanje
		void writeAllStudentCurrCourses(const Student&);
		void readAllStudentCurrCourses(Student&, std::vector<Course>&);

		void writeStudentPassCourse(const Student&, const PassedCourse&);
		void writeAllStudentPassCourses(const Student&);
		void readAllStudentPassCourses(Student&, std::vector<Course>&);


	};
}
