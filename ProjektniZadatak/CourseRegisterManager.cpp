#include "CourseRegisterManager.h"
#include "CourseManagerFileIO.h"
#include<iostream>

namespace learningPlatform
{
	CourseRegisterManager::CourseRegisterManager(std::vector<CoursePrecondtion*>& precondtions):precondtions(precondtions){};

	CoursePrecondtion* CourseRegisterManager::getPrecondtion(std::string id)const
	{
		auto it = std::find_if(this->precondtions.begin(), this->precondtions.end(), [&id](CoursePrecondtion* x)
		{
			return id == x->getId();
		});
		if (it == this->precondtions.end())
			return nullptr;
		return *it;
	}

	void CourseRegisterManager::enrollToCourse(const Student& stud, const Course& course)
	{
		CourseManagerFileIO cmScanner;
		std::vector<std::string> precondtions;
		cmScanner.readAllCoursePrecondtion(course, precondtions);
		for (auto x : precondtions)
		{
			CoursePrecondtion* cp = this->getPrecondtion(x);
			if((*cp)(stud)==false)
				throw std::exception("Student ne ispunjava preduslove za kurs");
		}

		std::vector<CourseReq>vec;
		this->scanner.readAllCourseReq(course.getId(), vec);
		CourseReq newReq(course.getId(), stud.getId());
		std::string id = stud.getId();
		auto it = std::find_if(vec.begin(), vec.end(), [&id](CourseReq& cr) 
		{
			return id == cr.getStudentId();
		});
		if (it != vec.end())
			throw std::exception("Student je vec poslao zahtjev za kurs!!");
		this->scanner.writeCourseReq(newReq);//baca izuzetak uhvatiti ako dodje do greske
	}
}