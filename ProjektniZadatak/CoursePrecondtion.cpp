#include "CoursePrecondition.h"
#include<sstream>
#include<fstream>

namespace learningPlatform
{
	std::string CoursePrecondtion::lastId = "#0";
	CoursePrecondtion::CoursePrecondtion(std::string id) :id(id) {};
	bool CoursePrecondtion::operator()(const Student& stud)const
	{
		return this->precondtion(stud);
	}

	CoursePrecondtion::CoursePrecondtion()
	{
		this->id = generateId();
	}

	void CoursePrecondtion::setLastId(std::string id)
	{
		lastId = id;
	}

	void CoursePrecondtion::setId(std::string id)
	{
		this->id = id;
	}

	std::string CoursePrecondtion::generateId()
	{
		std::string temp = CoursePrecondtion::lastId;
		std::string number = temp.substr(1);//0 je taraba
		std::stringstream stream(number);
		int iNum = -1;
		stream >> iNum; iNum++;
		std::string newId = "#" + std::to_string(iNum);
		CoursePrecondtion::lastId = newId;
		return newId;
	}

	std::string CoursePrecondtion::getId()const
	{
		return this->id;
	}

	std::ostream& operator<<(std::ostream&os, const CoursePrecondtion& cp)
	{
		return cp.output(os);
	}

	std::ifstream& operator>>(std::ifstream& in, CoursePrecondtion& cp)
	{
		return cp.input(in);
	}


	CoursePassed::CoursePassed(std::string courseId) :courseId(courseId) {};
	CoursePassed::CoursePassed(std::string id, std::string courseId) :CoursePrecondtion(id), courseId(courseId) {};

	std::string CoursePassed::getType()const
	{
		return "CP";
	}

	std::string CoursePassed::getInfo()const
	{
		return "Kurs koji treba biti polozen";
	}

	bool CoursePassed::precondtion(const Student& stud)const
	{
		auto& arr = stud.getPassCourses();
		for (auto& x : arr)
			if (x.getCourse()->getId() == this->courseId)
				return true;
		return false;
	}

	
	std::ostream& CoursePassed::output(std::ostream& os)const
	{
		os <<this->id<<" "<<this->getType()<<" " << this->courseId << " " << std::endl;
		return os;
	}
	//id i tip se rucno citaju
	std::ifstream& CoursePassed::input(std::ifstream& in)
	{
		in >> this->courseId;
		return in;
	}

	CoursePassedWithMinGrade::CoursePassedWithMinGrade(std::string courseId, double grade) :courseId(courseId), minGrade(grade) {};
	CoursePassedWithMinGrade::CoursePassedWithMinGrade(std::string id, std::string courseId, double grade) :CoursePrecondtion(id), courseId(id), minGrade(grade) {};

	std::string CoursePassedWithMinGrade::getType()const
	{
		return "CPWMG";
	}

	std::string CoursePassedWithMinGrade::getInfo()const
	{
		return "Kurs koji treba biti polozen sa minimalnom ocjenom";
	}

	bool CoursePassedWithMinGrade::precondtion(const Student& s)const
	{
		auto& arr = s.getPassCourses();
		auto id = this->courseId;
		auto it = std::find_if(arr.begin(), arr.end(), [&id](const PassedCourse& x)
		{
			return x.getCourse()->getId() == id;
		});
		if (it == arr.end())
			return false;
		if (it->getGrade() >= this->minGrade)
			return true;
		return false;
	}

	//id i tip se rucno ucitaju
	std::ifstream& CoursePassedWithMinGrade::input(std::ifstream& in)
	{
		in >> this->courseId;
		in.get();
		in >> this->minGrade;
		return in;
	}
	
	std::ostream& CoursePassedWithMinGrade::output(std::ostream& out)const
	{
		out << this->id << " " << this->getType() << " " << this->courseId << " " << this->minGrade << std::endl;
		return out;
	}

	NumberOfPassedCourse::NumberOfPassedCourse(int num) :num(num) {};
	NumberOfPassedCourse::NumberOfPassedCourse(std::string id, int num) :CoursePrecondtion(id), num(num) {};

	std::string NumberOfPassedCourse::getType()const
	{
		return "NOPS";
	}

	std::string NumberOfPassedCourse::getInfo()const
	{
		return "Minimalni broj polozenih kurseva";
	}

	bool NumberOfPassedCourse::precondtion(const Student& s)const
	{
		if (s.getPassCourses().size() >= this->num)
			return true;
		return false;
	}

	//id i tip se rucno unesu
	std::ifstream& NumberOfPassedCourse::input(std::ifstream& in)
	{
		in >> this->num;
		return in;
	}

	std::ostream& NumberOfPassedCourse::output(std::ostream& os)const
	{
		os << this->id << " " << this->getType() << " " << this->num << std::endl;
		return os;
	}
	
}