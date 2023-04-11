#include "CourseManagerFileIO.h"

namespace learningPlatform
{
	const std::string CourseManagerFileIO::dirName = "courses";
	const std::string CourseManagerFileIO::currName = "currentStudents.txt";
	const std::string CourseManagerFileIO::passName = "passedStudents.txt";
	const std::string CourseManagerFileIO::preCondName = "coursePrecondtions.txt";
	CourseManagerFileIO::CourseManagerFileIO()
	{
		/*this->filePath = fs::current_path() / dirName / ("course-" + courseId);
		if (status == true)
			this->filePath = this->filePath / currName;
		else
			this->filePath = this->filePath / passName;*/
		this->dirPath = fs::current_path() / dirName;
	}

	void CourseManagerFileIO::writeStudentToCourse(fs::path path,const std::string& studentId)
	{
		std::ofstream output(this->dirPath/path, std::ios::app);
		if (!output)
			throw std::runtime_error("Greska prilikom otvaranja fajla");
		output << studentId << std::endl;
		output.close();
	}

	void CourseManagerFileIO::writeAllStudentsToCourse(fs::path path,const std::vector<std::string>& students)
	{
		std::ofstream output(this->dirPath/path, std::ios::out);
		if (!output)
			throw std::runtime_error("Greska prilikom otvaranja fajla");
		for (auto x : students)
			output << x << std::endl;
		output.close();
	}

	void CourseManagerFileIO::readAllStudentsFromCourse(fs::path path,std::vector<std::string>& students)
	{
		std::ifstream input(this->dirPath/path, std::ios::in);
		if (!input)
			throw std::runtime_error("Greska prilikom otvaranja fajla");
		std::string temp;
		while (input >> temp)
			students.push_back(temp);
		input.close();
	}

	void CourseManagerFileIO::writeStudentToCurrCourse(const Course& course, std::string studId)
	{
		this->writeStudentToCourse(fs::path("course-" + course.getId()) / currName, studId);
	}

	void CourseManagerFileIO::writeStudentToPassCourse(const Course& course, std::string studId)
	{
		this->writeStudentToCourse(fs::path("course-" + course.getId()) / passName, studId);
	}

	void CourseManagerFileIO::writeAllStudentsToCurrCourse(const Course& course, std::vector<std::string>& students)
	{
		this->writeAllStudentsToCourse(fs::path("course-" + course.getId()) / currName, students);
	}

	void CourseManagerFileIO::writeAllStudentsToPassCourse(const Course& course, std::vector<std::string>& students)
	{
		this->writeAllStudentsToCourse(fs::path("course-" + course.getId()) / passName, students);
	}

	void CourseManagerFileIO::readAllStudentsFromCurrCourse(const Course& course, std::vector<std::string>& students)
	{
		this->readAllStudentsFromCourse(fs::path("course-" + course.getId()) / currName, students);
	}

	void CourseManagerFileIO::readAllStudentsFromPassCourse(const Course& course, std::vector<std::string>& students)
	{
		this->readAllStudentsFromCourse(fs::path("course-" + course.getId()) / passName, students);
	}

	void CourseManagerFileIO::writeCoursePrecondtion(const Course& course, std::string cp)
	{
		std::ofstream output((this->dirPath / ("course-" + course.getId())) / preCondName, std::ios::app);
		if (!output)
			throw std::runtime_error("Greska prilikom otvaranja fajla");
		output << cp << std::endl;
		output.close();
	}

	void CourseManagerFileIO::writeAllCoursePrecondtion(const Course& course, std::vector<std::string>&cps)
	{
		std::ofstream output((this->dirPath / ("course-" + course.getId())) / preCondName, std::ios::out);
		if (!output)
			throw std::runtime_error("Greska prilikom otvaranja fajla");
		for (auto x : cps)
			output << x << std::endl;
		output.close();
	}

	void CourseManagerFileIO::readAllCoursePrecondtion(const Course& course, std::vector<std::string>& cps)
	{
		std::ifstream input((this->dirPath / ("course-" + course.getId())) / preCondName, std::ios::in);
		if (!input)
			throw std::runtime_error("Greska prilikom otvaranja fajla");
		std::string temp;
		while (input >> temp)
			cps.push_back(temp);
		input.close();
	}

	
}