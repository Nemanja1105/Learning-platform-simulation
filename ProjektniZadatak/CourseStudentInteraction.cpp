#include "CourseStudentInteraction.h"
#include "CourseRegisterManager.h"

namespace learningPlatform
{

	bool CourseStudentInteraction::containCurr(Course& course, std::vector<Course*>& courses)
	{
		auto it = std::find_if(courses.begin(), courses.end(), [&course](Course* c) 
		{
			return *c == course;
		});
		if (it == courses.end())
			return false;
		return true;
	}

	bool CourseStudentInteraction::containPass(Course& course, std::vector<PassedCourse>& pass)
	{
		auto it = std::find_if(pass.begin(), pass.end(), [&course](PassedCourse& c)
		{
			return *c.getCourse() == course;
		});
		if (it == pass.end())
			return false;
		return true;
	}

	void CourseStudentInteraction::printHeader()
	{
		std::cout << "===============:======" << std::endl;
		std::cout << "NAZIV           ID" << std::endl;
		std::cout << "===============:======" << std::endl;
	}

	void CourseStudentInteraction::printFooter()
	{
		std::cout << "===============:======" << std::endl;
	}

	void CourseStudentInteraction::printCourse(const Course&c)
	{
		std::cout << std::left << std::setw(15) << c.getName() << ":" << std::left << std::setw(6) << c.getId() << std::endl;
	}
	void CourseStudentInteraction::sendCourseReq(Student& stud, std::vector<Course>& courses,std::vector<CoursePrecondtion*>&precondtions)
	{
		system("CLS");
		std::cout << "==============================================" << std::endl;
		std::cout << "\t-=Prijava na kurs=-" << std::endl;
		std::vector<Course*> razlika;
		for (auto& x : courses)
			if (containCurr(x, stud.getCurrCourses()) == false && containPass(x, stud.getPassCourses())==false)
				razlika.push_back(&x);
		printHeader();
		for (auto x : razlika)
			printCourse(*x);
		printFooter();
		std::cout << "Unesite id kursa na koji zelite da se prijavite!" << std::endl;
		std::string id;
		Course* course = nullptr;
		while (true)
		{
			std::cout << "Unesite id:";
			std::cin >> id;
			auto it = std::find_if(razlika.begin(), razlika.end(), [&id](Course*s)
			{
				return id == s->getId();
			});
			if (it == razlika.end())
				std::cout << "Ne postoji kurs sa unijetim id" << std::endl;
			else
			{
				course = (*it);
				break;
			}
		}
		CourseRegisterManager manager(precondtions);
		try
		{
			manager.enrollToCourse(stud, *course);
		}
		catch (const std::runtime_error& e)
		{
			std::cout << e.what() << std::endl;
			return;
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
			return;
		}
		std::cout << "Zahtjev uspjesno poslat!!" << std::endl;
	}


	void CourseStudentInteraction::showCurrCourses(Student& stud)
	{
		system("CLS");
		std::cout << "=========================================================" << std::endl;
		std::cout << "  -=Pregled kurseva koje student trenutnoslusa=-" << std::endl;
		std::cout << "====== =============== ======== =========================" << std::endl;
		std::cout << "ID     NAZIV           KATEDRA  PROFESOR                 " << std::endl;
		std::cout << "====== =============== ======== =========================" << std::endl;
		auto& arr = stud.getCurrCourses();
		if (arr.size() == 0)
			std::cout << "Student trenutno ne pohadja ni jedan kurs" << std::endl;
		else
		{
			for (auto x : arr)
				std::cout << *x << std::endl;
		}
		std::cout << "====== =============== ======== =========================" << std::endl;
	}

	void CourseStudentInteraction::showPassCourses(Student& stud)
	{
		system("CLS");
		std::cout << "================================================================" << std::endl;
		std::cout << "  -=Pregled kurseva koje je student polozio=-" << std::endl;
		std::cout << "====== ==================== ======== ========================= ======" << std::endl;
		std::cout << "ID     NAZIV                KATEDRA  PROFESOR                  OCJENA" << std::endl;
		std::cout << "====== ==================== ======== ========================= ======" << std::endl;
		auto& arr = stud.getPassCourses();
		for (auto x : arr)
			std::cout << *(x.getCourse()) << " " << std::right << std::setw(6) << std::setprecision(2) << x.getGrade() << std::endl;
		std::cout << "====== ==================== ======== ========================= ======" << std::endl;
	}
}