#pragma once
#include<string>
#include<filesystem>
#include<fstream>
#include "Course.h"

namespace learningPlatform
{
	namespace fs = std::filesystem;
	class CourseManagerFileIO
	{
	private:
		static const std::string dirName;
		static const std::string currName;
		static const std::string passName;
		static const std::string preCondName;
		fs::path dirPath;
	public:
		CourseManagerFileIO();
		void writeStudentToCurrCourse(const Course&, std::string);
		void writeStudentToPassCourse(const Course&, std::string);

		void writeAllStudentsToCurrCourse(const Course&, std::vector<std::string>&);
		void writeAllStudentsToPassCourse(const Course&, std::vector<std::string>&);

		void readAllStudentsFromCurrCourse(const Course&, std::vector<std::string>&);
		void readAllStudentsFromPassCourse(const Course&, std::vector<std::string>&);

		void writeCoursePrecondtion(const Course&, std::string);//id preduslova
		void writeAllCoursePrecondtion(const Course&, std::vector<std::string>&);
		void readAllCoursePrecondtion(const Course&, std::vector<std::string>&);

	private:
		void writeStudentToCourse(fs::path,const std::string&);
		void writeAllStudentsToCourse(fs::path,const std::vector<std::string>&);
		void readAllStudentsFromCourse(fs::path,std::vector<std::string>&);


	};
}
