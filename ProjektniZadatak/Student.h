#pragma once
#include "User.h"
#include "Course.h"
#include "PassedCourse.h"
#include<vector>

namespace learningPlatform
{
	enum class StudentStatus{REDOVNI,VANDREDNI,NOT_DEFINED};
	class Student :public User
	{
	private:
		std::string index;
		StudentStatus status;
		std::vector<Course*> currentCourses;
		std::vector<PassedCourse> passedCourses;
		std::vector<Student*> friends;
	public:
		Student();
		Student(std::string, std::string, std::string, std::string, const Date&, const Genders&, std::string, std::string, const StudentStatus&);
		Student(std::string, std::string, std::string, std::string, std::string, const Date&, const Genders&, std::string, std::string, const StudentStatus&);
		virtual~Student() {};

		std::string getIndex()const;
		StudentStatus getStudentStatus()const;

		void setIndex(const std::string&);
		void setStatus(const StudentStatus&);

		virtual Student* clone()const override;
		virtual std::string getType()const override;

		std::vector<Student*>& getFriends();
		const std::vector<Student*>& getFriends()const;

		std::vector<Course*>& getCurrCourses();
		const std::vector<Course*>& getCurrCourses()const;

		std::vector<PassedCourse>& getPassCourses();
		const std::vector<PassedCourse>& getPassCourses()const;


	protected:
		virtual std::ostream& print(std::ostream&)const override;

	};
}
