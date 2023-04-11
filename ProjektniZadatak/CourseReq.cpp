#include"CourseReq.h"

namespace learningPlatform
{
	CourseReq::CourseReq() :courseId(""), studentId("") {};
	CourseReq::CourseReq(std::string courseId, std::string studentId): courseId(courseId), studentId(studentId) {};

	std::string CourseReq::getCourseId()const
	{
		return this->courseId;
	}

	std::string CourseReq::getStudentId()const
	{
		return this->studentId;
	}

	bool CourseReq::operator==(const CourseReq& other)const
	{
		return (this->courseId == other.courseId) && (this->studentId == other.studentId);
	}

	bool CourseReq::operator!=(const CourseReq& other)const
	{
		return !((*this) == other);
	}

	std::ostream& operator<<(std::ostream& os, const CourseReq& cr)
	{
		os << cr.courseId << " " << cr.studentId << std::endl;
		return os;
	}
	
	std::istream& operator>>(std::istream& in, CourseReq& cr)
	{
		in >> cr.courseId >> cr.studentId;
		return in;
	}
}