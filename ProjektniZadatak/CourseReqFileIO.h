#pragma once
#include<vector>
#include<fstream>
#include<filesystem>
#include"CourseReq.h"

namespace learningPlatform
{
	//ucitava zahtjeve za odredjeni kurs
	namespace fs = std::filesystem;
	class CourseReqFileIO
	{
	private:
		static const std::string dirPath;//courses podrazumjeva da postoji
		fs::path filePath;
	public:
		CourseReqFileIO();
		void writeCourseReq(const CourseReq&)const;
		void writeAllCourseReq(std::string,const std::vector<CourseReq>&)const;
		void readAllCourseReq(std::string,std::vector<CourseReq>&);
	private:
		fs::path createPath(std::string)const;
		
	};
}
