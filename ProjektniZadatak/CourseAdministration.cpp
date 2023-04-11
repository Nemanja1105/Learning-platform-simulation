#include "CourseAdministration.h"

namespace learningPlatform
{
	CourseAdministration::CourseAdministration(CourseDetail& cd) :courseDetail(cd) {};

	std::vector<CourseReq>::iterator CourseAdministration::findReq(const CourseReq& cr)const
	{
		auto& x = this->courseDetail.getCourseReq();
		auto it = std::find_if(x.begin(), x.end(), [&cr](CourseReq& c)
		{
			return cr == c;
		});
		return it;
	}

	void CourseAdministration::acceptCourseReq(Student& stud)
	{
		CourseReq temp(this->courseDetail.getCourse().getId(), stud.getId());
		auto it = findReq(temp);
		if (it == this->courseDetail.getCourseReq().end())
			throw std::invalid_argument("Ne postoji zahtjev za prijavu za datog studenta");
		//brisanje zahtjeva
		this->courseDetail.getCourseReq().erase(it);
		this->reqScanner.writeAllCourseReq(this->courseDetail.getCourse().getId(),this->courseDetail.getCourseReq());
		//pisanje u studenta
		this->courseStudScanner.writeStudentCurrCourse(stud, this->courseDetail.getCourse());
		stud.getCurrCourses().push_back(&this->courseDetail.getCourse());
	
		//pitanje u kurseve
		this->courseManagScanner.writeStudentToCurrCourse(this->courseDetail.getCourse(), stud.getId());
		this->courseDetail.getCurrentStudents().push_back(stud.getId());
	}

	void CourseAdministration::rejectCourseReq(const Student& stud)
	{
		CourseReq temp(this->courseDetail.getCourse().getId(), stud.getId());
		auto it = findReq(temp);
		if (it == this->courseDetail.getCourseReq().end())
			throw std::invalid_argument("Ne postoji zahtjev za prijavu za datog studenta");
		this->courseDetail.getCourseReq().erase(it);
		this->reqScanner.writeAllCourseReq(this->courseDetail.getCourse().getId(), this->courseDetail.getCourseReq());
	}

	void CourseAdministration::evaluateStudent(Student& stud,double grade)
	{
		PassedCourse temp(&this->courseDetail.getCourse(), grade);

		//student
		stud.getPassCourses().push_back(temp);
		this->courseStudScanner.writeStudentPassCourse(stud, temp);
		//brisanje iz trenutnog sa studenta
		auto& arr = stud.getCurrCourses();
		Course& pom = this->courseDetail.getCourse();
		auto it1 = std::find_if(arr.begin(), arr.end(), [&pom](Course* c) 
		{
			return pom == *c;
		});
		arr.erase(it1);
		this->courseStudScanner.writeAllStudentCurrCourses(stud);

		//dodavanje u zavrsene
		this->courseDetail.getPassedStudents().push_back(stud.getId());
		this->courseManagScanner.writeStudentToPassCourse(this->courseDetail.getCourse(), stud.getId());

		//brisanje iz trenutnih
		auto& x = this->courseDetail.getCurrentStudents();
		std::string id = stud.getId();
		auto it = std::find_if(x.begin(), x.end(), [&id](std::string& x)
		{
			return id == x;
		});
		x.erase(it);
		this->courseManagScanner.writeAllStudentsToCurrCourse(this->courseDetail.getCourse(),this->courseDetail.getCurrentStudents());
	}
}