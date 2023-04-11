#include "CourseReqFileIO.h"

namespace learningPlatform
{
	const std::string CourseReqFileIO::dirPath = "courses";
	CourseReqFileIO::CourseReqFileIO()
	{
		//this->filePath = fs::current_path() / dirPath / ("course-" + courseId) / ("courseReq.txt");
		this->filePath = fs::current_path() / dirPath;
	}

	fs::path CourseReqFileIO::createPath(std::string courseId)const
	{
		return this->filePath / ("course-" + courseId) / ("courseReq.txt");
	}

	void CourseReqFileIO::writeCourseReq(const CourseReq& cr)const
	{
		std::ofstream output(this->createPath(cr.getCourseId()), std::ios::app);
		if (!output)
			throw std::runtime_error("Greska prilikom otvaranja fajla!!");
		output << cr.getStudentId() << std::endl;
		output.close();
	}

	//svi elemente su iz istog kurse
	void CourseReqFileIO::writeAllCourseReq(std::string courseId,const std::vector<CourseReq>& crVec)const
	{
		std::ofstream output(this->createPath(courseId), std::ios::out);
		if (!output)
			throw std::runtime_error("Greska prilikom otvaranja fajla!!");
		for (auto x : crVec)
			output << x.getStudentId() << std::endl;
		output.close();
	}

	void CourseReqFileIO::readAllCourseReq(std::string courseId,std::vector<CourseReq>& crVec)
	{
		std::ifstream input(this->createPath(courseId), std::ios::in);
		if (!input)
			throw std::runtime_error("Greska prilikom otvaranja fajla!!");
		std::string id;
		while (input >> id)
			crVec.push_back(CourseReq(courseId,id));
		input.close();
	}

	
}