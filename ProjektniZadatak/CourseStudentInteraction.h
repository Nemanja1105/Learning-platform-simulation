#pragma once
#include "Course.h"
#include "Student.h"
#include "CourseRegisterManager.h"

namespace learningPlatform
{
	class CourseStudentInteraction
	{
	public:
		virtual ~CourseStudentInteraction() = 0;
		static void sendCourseReq(Student&, std::vector<Course>&,std::vector<CoursePrecondtion*>&);//stavljeno
		static void showCurrCourses(Student&);//stavljeno
		static void showPassCourses(Student&);//stavljeno
	private:
		static bool containCurr(Course&, std::vector<Course*>&);
		static bool containPass(Course&, std::vector<PassedCourse>&);
		static void printHeader();
		static void printFooter();
		static void printCourse(const Course&);
	};
}