#include "CourseDetails.h"
#include<unordered_set>
#include<set>

namespace learningPlatform
{
	CourseDetail::CourseDetail(Course &course) :course(course) {};

	CourseDetail CourseDetail::CourseDetailCreater(Course& course)
	{
		CourseDetail temp(course);
		std::vector<std::string> currStud;
		std::vector<std::string> passStud;
		std::vector<CourseReq> courseReq;
		CourseReqFileIO reqScanner;
		reqScanner.readAllCourseReq(course.getId(), courseReq);
		CourseManagerFileIO managScanner;
		managScanner.readAllStudentsFromCurrCourse(course, currStud);
		managScanner.readAllStudentsFromPassCourse(course, passStud);
		temp.currentStudents = std::move(currStud);
		temp.passedStudents = std::move(passStud);
		temp.courseReq = std::move(courseReq);
		return temp;
	}

	Course& CourseDetail::getCourse()
	{
		return this->course;
	}

	const Course& CourseDetail::getCourse()const
	{
		return this->course;
	}

	std::vector<std::string>& CourseDetail::getCurrentStudents()
	{
		return this->currentStudents;
	}

	const std::vector<std::string>& CourseDetail::getCurrentStudents()const
	{
		return this->currentStudents;
	}

	std::vector<std::string>& CourseDetail::getPassedStudents()
	{
		return this->passedStudents;
	}

	const std::vector<std::string>& CourseDetail::getPassedStudents()const
	{
		return this->passedStudents;
	}

	std::vector<CourseReq>& CourseDetail::getCourseReq()
	{
		return this->courseReq;
	}

	const std::vector<CourseReq>& CourseDetail::getCourseReq()const
	{
		return this->courseReq;
	}

	std::vector<std::string> CourseDetail::setUnion(std::vector<std::string>& s1, std::vector<std::string>& s2)
	{
		std::vector<std::string> temp(s1);
		for (auto x : s2)
		{
			auto it = std::find(s1.begin(), s1.end(), x);
			if (it == s1.end())
				temp.push_back(x);
		}
		return temp;
		
		
	}

	std::vector<std::string> CourseDetail::setIntersection(std::vector<std::string>& s1, std::vector<std::string>& s2)
	{
		/*std::vector<std::string> temp;
		for (auto x : s1)
		{
			auto it = std::find(s2.begin(), s2.end(), x);
			if (it != s2.end())
				temp.push_back(x);
		}
		return temp;*/
		std::vector<std::string> rez;
		std::unordered_set<std::string> set(s1.begin(), s1.end());
		for (auto x : s2)
			if (set.contains(x))
				rez.push_back(x);
		return rez;
		
	}

	std::vector<std::string> CourseDetail::setDifference(std::vector<std::string>& s1, std::vector<std::string>& s2)
	{
		std::vector<std::string> temp(s1);
		for (auto x : s2)
		{
			auto it = std::find(temp.begin(), temp.end(), x);
			if (it != temp.end())
				temp.erase(it);
		}
		return temp;
	}
}