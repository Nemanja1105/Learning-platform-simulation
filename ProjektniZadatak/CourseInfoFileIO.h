#pragma once
#include"Course.h"
#include<filesystem>
#include<fstream>
#include<vector>

namespace learningPlatform
{
	namespace fs = std::filesystem;
	class CourseInfoFileIO
	{
	private:
		static const std::string dirName;
		static const std::string fileName;
		static const std::string currName;
		static const std::string preCondName;
		static const std::string passName;
		static const std::string reqName;
		fs::path filePath;
		std::vector<Professor>& professors;
	public:
		CourseInfoFileIO(std::vector<Professor>&);
		void writeCourse(const Course&)const;
		void writeAllCourses(const std::vector<Course>&)const;
		void readAllCourses(std::vector<Course>&)const;
	private:
		void writeOneCourse(std::ostream&,const Course&)const;
		Course readOneCourse(std::istream&)const;
		void createDirectory(const std::string&)const;

	};
}
