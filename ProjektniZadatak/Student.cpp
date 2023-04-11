#include "Student.h"
#include<iomanip>

namespace learningPlatform
{
	Student::Student() :User(), index(""), status(StudentStatus::NOT_DEFINED) {};

	Student::Student(std::string username, std::string password, std::string name, std::string surname, const Date& dob,
		const Genders& gender, std::string email, std::string index, const StudentStatus& status) :
		User(username, password, name, surname, dob, gender, email), index(index), status(status) {};

	Student::Student(std::string username, std::string password, std::string id, std::string name, std::string surname, const Date& dob,
		const Genders& gender, std::string email, std::string index, const StudentStatus& status) :
		User(username, password, id, name, surname, dob, gender, email), index(index), status(status) {};

	std::string Student::getIndex()const
	{
		return this->index;
	}

	StudentStatus Student::getStudentStatus()const
	{
		return this->status;
	}

	void Student::setIndex(const std::string& value)
	{
		this->index = value;
	}

	void Student::setStatus(const StudentStatus& value)
	{
		this->status = status;
	}

	Student* Student::clone()const
	{
		return new Student(*this);
	}

	std::string Student::getType()const
	{
		return "STUD";
	}

	std::ostream& Student::print(std::ostream& os)const
	{
		User::print(os);
		os << std::left << std::setw(8) << this->index << " "<<std::left<<std::setw(9);
		if (this->status == StudentStatus::VANDREDNI)
			os << "Vandredni";
		else
			os << "Redovni";
		return os;
	}

	std::vector<Student*>& Student::getFriends()
	{
		return this->friends;
	}

	const std::vector<Student*>& Student::getFriends()const
	{
		return this->friends;
	}

	std::vector<Course*>& Student::getCurrCourses()
	{
		return this->currentCourses;
	}

	const std::vector<Course*>& Student::getCurrCourses()const
	{
		return this->currentCourses;
	}

	std::vector<PassedCourse>& Student::getPassCourses()
	{
		return this->passedCourses;
	}

	const std::vector<PassedCourse>& Student::getPassCourses()const
	{
		return this->passedCourses;
	}

}