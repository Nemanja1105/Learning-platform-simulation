#include "CourseInfoFileIO.h"

namespace learningPlatform
{
	const std::string CourseInfoFileIO::dirName = "courses";
	const std::string CourseInfoFileIO::fileName = "kursevi.txt";
	const std::string CourseInfoFileIO::currName = "currentStudents.txt";
	const std::string CourseInfoFileIO::passName = "passedStudents.txt";
	const std::string CourseInfoFileIO::preCondName = "coursePrecondtions.txt";
	const std::string CourseInfoFileIO::reqName = "courseReq.txt";
	CourseInfoFileIO::CourseInfoFileIO(std::vector<Professor>& professors):
		professors(professors)
	{
		fs::path temp = fs::current_path() / dirName;
		if (!fs::exists(temp))
			fs::create_directories(temp);
		this->filePath= (temp / fileName);
	}

	void CourseInfoFileIO::writeOneCourse(std::ostream& os, const Course& course)const
	{
		os << course.getId() << " " << course.getName() << " " << course.getKatedra() << " " <<
			course.getProfessor()->getId() << " "<< std::endl;;
	}

	void CourseInfoFileIO::writeCourse(const Course& course)const
	{
		std::ofstream output(this->filePath, std::ios::app);
		if (!output)
			throw std::runtime_error("Greska prilikom otvaranja fajla!!");
		this->writeOneCourse(output, course);
		output.close();
		createDirectory(course.getId());
		fs::path root = fs::current_path() / dirName / ("course-" + course.getId());
		fs::path create1 = root / currName;
		fs::path create2 = root / passName;
		fs::path create3 = root / preCondName;
		fs::path create4 = root / reqName;
		std::ofstream out1(create1, std::ios::out);
		std::ofstream out2(create2, std::ios::out);
		std::ofstream out3(create3, std::ios::out);
		std::ofstream out4(create4, std::ios::out);
		out1.close();
		out2.close();
		out3.close();
		out4.close();
	}

	void CourseInfoFileIO::createDirectory(const std::string& name)const
	{
		fs::path path = fs::current_path() / dirName /("course-"+name);
		fs::create_directories(path);
	}

	void CourseInfoFileIO::writeAllCourses(const std::vector<Course>& courses)const
	{
		std::ofstream output(this->filePath, std::ios::out);
		if (!output)
			throw std::runtime_error("Greska prilikom otvaranja fajla!!");
		for (auto x : courses)
			this->writeOneCourse(output,x);
		output.close();
	}

	Course CourseInfoFileIO::readOneCourse(std::istream& in)const
	{
		std::string id, name, katedra, profesor;
		in >> id >> name >> katedra >> profesor>>std::ws;
		auto it = std::find_if(professors.begin(), professors.end(), [&profesor](Professor& p)
		{
			return profesor == p.getId();
		});
		return Course(id, name, katedra,(*it));
	}

	void CourseInfoFileIO::readAllCourses(std::vector<Course>& courses)const
	{
		std::ifstream input(this->filePath, std::ios::in);
		if (!input)
			throw std::runtime_error("Greska priliko otvaranja fajla!!");
		while (!input.eof())
		{
			Course temp = std::move(this->readOneCourse(input));
			courses.push_back(temp);
		}
		input.close();
	}
}