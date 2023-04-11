#pragma once
#include"Course.h"
#include"Student.h"
#include"CourseReq.h"
#include"CourseManagerFileIO.h"
#include"CourseReqFileIO.h"

namespace learningPlatform
{
	class CourseDetail
	{
	private:
		Course& course;
		std::vector<std::string> currentStudents;
		std::vector<std::string> passedStudents;
		std::vector<CourseReq> courseReq;
	public:
		CourseDetail(Course&);

		Course& getCourse();
		const Course& getCourse()const;

		std::vector<std::string>& getCurrentStudents();
		const std::vector<std::string>& getCurrentStudents()const;

		std::vector<std::string>& getPassedStudents();
		const std::vector<std::string>& getPassedStudents()const;

		std::vector<CourseReq>& getCourseReq();
		const std::vector<CourseReq>& getCourseReq()const;

		static CourseDetail CourseDetailCreater(Course&);

		static std::vector<std::string> setUnion(std::vector<std::string>&, std::vector<std::string>&);
		static std::vector<std::string> setIntersection(std::vector<std::string>&, std::vector<std::string>&);
		static std::vector<std::string> setDifference(std::vector<std::string>&, std::vector<std::string>&);
	};
}