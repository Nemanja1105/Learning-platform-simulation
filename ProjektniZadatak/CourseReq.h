#pragma once
#include<string>
#include<iostream>

namespace learningPlatform
{
	class CourseReq
	{
	private:
		std::string courseId;
		std::string studentId;
	public:
		CourseReq();
		CourseReq(std::string, std::string);

		std::string getCourseId()const;
		std::string getStudentId()const;

		bool operator==(const CourseReq&)const;
		bool operator!=(const CourseReq&)const;
		friend std::ostream& operator<<(std::ostream&, const CourseReq&);
		friend std::istream& operator>>(std::istream&, CourseReq&);
	};
	std::ostream& operator<<(std::ostream&, const CourseReq&);
	std::istream& operator>>(std::istream&, CourseReq&);
}
