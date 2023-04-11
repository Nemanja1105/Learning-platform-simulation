#pragma once
#include "Course.h"

namespace learningPlatform
{
	class PassedCourse
	{
	private:
		Course* course;
		double grade;
	public:
		PassedCourse();
		PassedCourse(Course*, double);

		Course* getCourse()const;
		double getGrade()const;
	};
}
