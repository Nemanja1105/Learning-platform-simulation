#include"CoursePrecondtionFileIO.h"

namespace learningPlatform
{
	const std::string CoursePrecondtionFileIO::dirName = "precondtions";
	const std::string CoursePrecondtionFileIO::fileName = "preduslovi.txt";
	CoursePrecondtionFileIO::CoursePrecondtionFileIO()
	{
		fs::path temp = fs::current_path() / dirName;
		if (!fs::exists(temp))
			fs::create_directories(temp);
		this->path = (temp / fileName);
	}

	void CoursePrecondtionFileIO::writeCoursePrecondtion(const CoursePrecondtion& cp)
	{
		std::ofstream output(this->path, std::ios::app);
		if (!output)
			throw std::runtime_error("Greska prilikom otvaranja fajla");
		output << cp;
		output.close();
	}

	void CoursePrecondtionFileIO::readAllCoursePrecondtion(std::vector<CoursePrecondtion*>& precondtions)
	{
		std::ifstream input(this->path, std::ios::in);
		if (!input)
			throw std::runtime_error("Greska prilikom otvaranja fajla");
		std::string id, tip;
		while (input >> id >> tip)
		{
			if (tip == "CP")
			{
				CoursePassed cp;
				input >> cp;
				cp.setId(id);
				precondtions.push_back(new CoursePassed(cp));
			}
			else if (tip == "CPWMG")
			{
				CoursePassedWithMinGrade cp;
				input >> cp;
				cp.setId(id);
				precondtions.push_back(new CoursePassedWithMinGrade(cp));
			}
			else if (tip == "NOPS")
			{
				NumberOfPassedCourse cp;
				input >> cp;
				cp.setId(id);
				precondtions.push_back(new NumberOfPassedCourse(cp));
			}
		}
		input.close();
	}
}