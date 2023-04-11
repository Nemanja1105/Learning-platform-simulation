#pragma once
#include "Course.h"
#include "Student.h"
#include "CourseReq.h"
#include "CoursePrecondition.h"
#include "CourseReqFileIO.h"

namespace learningPlatform
{
	class CourseRegisterManager
	{
	private:
		//std::vector<Course>& courses;
		std::vector<CoursePrecondtion*>& precondtions;
		CourseReqFileIO scanner;
	public:
		CourseRegisterManager(std::vector<CoursePrecondtion*>&);
		void enrollToCourse(const Student&, const Course&);
	private:
		CoursePrecondtion* getPrecondtion(std::string)const;
	};
}