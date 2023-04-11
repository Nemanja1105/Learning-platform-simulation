#include "PassedCourse.h"

namespace learningPlatform
{
	PassedCourse::PassedCourse() :course(nullptr), grade(0) {};
	PassedCourse::PassedCourse(Course* course, double grade) :course(course), grade(grade) {};

	Course* PassedCourse::getCourse()const
	{
		return this->course;
	}

	double PassedCourse::getGrade()const
	{
		return this->grade;
	}
}