#pragma once
#include "Course.h"
#include "CourseReq.h"
#include "CourseDetails.h"
#include "CourseStudentFileIO.h"

namespace learningPlatform
{
	class CourseAdministration
	{
	private:
		CourseDetail& courseDetail;
		CourseReqFileIO reqScanner;
		CourseStudentFileIO courseStudScanner;
		CourseManagerFileIO courseManagScanner;
	public:
		CourseAdministration(CourseDetail&);

		//imam vec kurs
		void acceptCourseReq(Student&);
		void rejectCourseReq(const Student&);
		void evaluateStudent(Student&,double);
	private:
		std::vector<CourseReq>::iterator findReq(const CourseReq&)const;
	};
}