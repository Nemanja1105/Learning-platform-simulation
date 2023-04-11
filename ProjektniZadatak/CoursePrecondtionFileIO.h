#pragma once
#include"Course.h"
#include"CoursePrecondition.h"
#include<filesystem>
#include<fstream>

namespace learningPlatform
{
	namespace fs = std::filesystem;
	class CoursePrecondtionFileIO
	{
	private:
		static const std::string dirName;
		static const std::string fileName;
		fs::path path;
	public:
		CoursePrecondtionFileIO();
		void writeCoursePrecondtion(const CoursePrecondtion&);
		void readAllCoursePrecondtion(std::vector<CoursePrecondtion*>&);
	};
}
