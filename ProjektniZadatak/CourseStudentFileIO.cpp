#include"CourseStudentFileIO.h"

namespace learningPlatform
{
	const std::string CourseStudentFileIO::dirName = "students";
	const std::string CourseStudentFileIO::currName = "currentCourses.txt";
	const std::string CourseStudentFileIO::passName = "passedCourses.txt";

	CourseStudentFileIO::CourseStudentFileIO()
	{
		fs::path path = fs::current_path() / dirName;
		if (!fs::exists(path))
			fs::create_directories(path);
		this->filePath = path;
	}

	void CourseStudentFileIO::writeStudentCurrCourse(const Student& stud, const Course& course)
	{
		fs::path path = this->filePath / stud.getId() / currName;
		std::ofstream output(path, std::ios::app);
		if (!output)
			throw std::runtime_error("Greska prilikom otvaranja fajla");
		output << course.getId() << std::endl;
		output.close();
	}

	void CourseStudentFileIO::writeAllStudentCurrCourses(const Student& stud)
	{
		fs::path path = this->filePath / stud.getId() / currName;
		std::ofstream output(path, std::ios::out);
		if (!output)
			throw std::runtime_error("Greska prilikom otvaranja fajla");
		auto& x = stud.getCurrCourses();
		for (auto el : x)
			output << el->getId() << std::endl;
		output.close();
	}

	void CourseStudentFileIO::readAllStudentCurrCourses(Student& stud, std::vector<Course>& courses)
	{
		fs::path path = this->filePath / stud.getId() / currName;
		std::ifstream input(path, std::ios::in);
		if (!input)
			throw std::runtime_error("Greska prilikom otvaranja fajla");
		std::string id;
		while (input >> id)
		{
			auto it = std::find_if(courses.begin(), courses.end(), [&id](Course& c)
			{
				return c.getId() == id;
			});
			stud.getCurrCourses().push_back(&(*it));
		}
		input.close();
	}

	void CourseStudentFileIO::writeStudentPassCourse(const Student& stud, const PassedCourse& course)
	{
		fs::path path = this->filePath / stud.getId() / passName;
		std::ofstream output(path, std::ios::app);
		if (!output)
			throw std::runtime_error("Greska prilikom otvaranja fajla");
		output << course.getCourse()->getId() << " " << course.getGrade() << std::endl;
		output.close();
	}

	void CourseStudentFileIO::writeAllStudentPassCourses(const Student& stud)
	{
		fs::path path = this->filePath / stud.getId() / passName;
		std::ofstream output(path, std::ios::out);
		if (!output)
			throw std::runtime_error("Greska prilikom otvaranja fajla");
		auto& x = stud.getPassCourses();
		for (auto el : x)
			output << el.getCourse()->getId() <<" "<<el.getGrade()<<std::endl;
		output.close();
	}

	void CourseStudentFileIO::readAllStudentPassCourses(Student& stud, std::vector<Course>& courses)
	{
		fs::path path = this->filePath / stud.getId() / passName;
		std::ifstream input(path, std::ios::in);
		if (!input)
			throw std::runtime_error("Greska prilikom otvaranja fajla");
		std::string id;
		double grade;
		while (input >> id>>grade)
		{
			auto it = std::find_if(courses.begin(), courses.end(), [&id](Course& c)
			{
				return c.getId() == id;
			});
			stud.getPassCourses().push_back(PassedCourse(&(*it), grade));
		}
		input.close();

	}
}