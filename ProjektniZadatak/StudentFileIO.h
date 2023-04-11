#pragma once
#include"CourseStudentFileIO.h"
#include<fstream>
#include<vector>
#include "Course.h"

namespace learningPlatform
{
	class StudentFileIO
	{
	private:
		static const std::string dirName;//vec je kreirano
		static const std::string fileName;
		static const std::string passName;
		static const std::string currName;
		fs::path dirPath;
		fs::path path;
	public:
		StudentFileIO();
		void writeUser(const Student&)const;
		void writeAllUser(const std::vector<Student>&)const;
		void readAllUser(std::vector<Student>&,std::vector<Course>&)const;
	private:
		void writeOneUser(std::ostream&, const Student&)const;
		Student readOneUser(std::istream&)const;
	};
}