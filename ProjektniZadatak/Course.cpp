#include "Course.h"
#include<iomanip>

namespace learningPlatform
{
	Course::Course() :id(""), name(""), katedra(""), professorId(nullptr) {};
	Course::Course(std::string id, std::string name, std::string katedra, Professor& prof)
		:id(id), name(name), katedra(katedra), professorId(&prof) {};

	std::string Course::getId()const
	{
		return this->id;
	}

	std::string Course::getName()const
	{
		return this->name;
	}

	std::string Course::getKatedra()const
	{
		return this->katedra;
	}

	Professor* Course::getProfessor()const
	{
		return this->professorId;
	}


	void Course::setId(const std::string& value)
	{
		this->id = value;
	}

	void Course::setName(const std::string& value)
	{
		this->name = value;
	}

	void Course::setKatedra(const std::string& value)
	{
		this->katedra = katedra;
	}

	void Course::setProfessor(Professor& value)
	{
		this->professorId = &value;
	}

	bool Course::operator==(const Course& other)const
	{
		return this->id == other.id;
	}

	bool Course::operator!=(const Course& other)const
	{
		return !((*this) == other);
	}

	std::ostream& Course::print(std::ostream& os)const
	{
		os << std::left << std::setw(6) << this->id << " " << std::left << std::setw(20) << this->name << " " << std::left <<
			std::setw(8) << this->katedra << " " << std::left << std::setw(25) << (professorId->getName() + " " + professorId->getSurname());
		return os;
	}
}