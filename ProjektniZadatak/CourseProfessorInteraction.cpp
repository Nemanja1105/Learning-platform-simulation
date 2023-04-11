#include "CourseProfessorInteraction.h"

namespace learningPlatform
{

	void CourseProfessorInteraction::printCourseHeader()
	{
		std::cout << "====================:======" << std::endl;
		std::cout << "NAZIV                ID" << std::endl;
		std::cout << "====================:======" << std::endl;
	}

	void CourseProfessorInteraction::printCourseFooter()
	{
		std::cout << "====================:======" << std::endl;
	}

	void CourseProfessorInteraction::printStudHeader()
	{
		std::cout << "=============== ===============:======" << std::endl;
		std::cout << "IME             PREZIME         ID" << std::endl;
		std::cout << "=============== ===============:======" << std::endl;
	}

	void CourseProfessorInteraction::printStudFooter()
	{
		std::cout << "=============== ===============:======" << std::endl;
	}

	int CourseProfessorInteraction::showProfessorsCourses(const Professor& prof, std::vector<Course>& courses)
	{
		std::cout << "=======================================================" << std::endl;
		std::cout << "    -=Prikaz kurseva za koje je profesor zaduzen=-" << std::endl;
		std::cout << "=======================================================" << std::endl << std::endl;;
		printCourseHeader();
		int br = 0;
		for (auto& x : courses)
		{

			if (*x.getProfessor() == prof)
			{
				std::cout << std::left << std::setw(20) << x.getName() << ":" << std::left << std::setw(6) << x.getId() << std::endl;
				br++;
			}
		}
		if (br == 0)
		{
			std::cout << "Profesor trenutno nije zaduzen ni za jedan kurs" << std::endl;
			return 0;
		}
		printCourseFooter();
		return 1;
	}

	Student& CourseProfessorInteraction::getStudent(std::string studId, std::vector<Student>& students)
	{
		auto it = std::find_if(students.begin(), students.end(), [&studId](Student& s)
		{
			return studId == s.getId();
		});
		return *it;
	}

	void CourseProfessorInteraction::printStudent(const Student& x)
	{
		std::cout << std::setw(15) << std::left << x.getName() << " " <<
			std::setw(15) << std::left << x.getSurname() << ":" << std::setw(15) << std::left
			<< x.getId() << std::endl;
	}

	void CourseProfessorInteraction::showCurrStudentOnCourses(Course& course,std::vector<Student>&students)
	{
		system("CLS");
		std::cout << "==================================================" << std::endl;
		std::cout << " -=Prikaz studenata koji trenutno slucaju kurs=-  " << std::endl;
		std::cout << "==================================================" << std::endl;
		std::cout << std::endl;
		CourseDetail detail = CourseDetail::CourseDetailCreater(course);
		auto& currArr = detail.getCurrentStudents();
		printStudHeader();
		if (currArr.size() == 0)
		{
			std::cout << "Trenutno nema studenata na kursu!!" << std::endl;
			return;
		}
		for (auto& x : currArr)
		{
			Student& trenutni = getStudent(x, students);
			printStudent(trenutni);
		}
		printStudFooter();
	}

	void CourseProfessorInteraction::showPassStudentOnCourses(Course& course, std::vector<Student>& students)
	{
		system("CLS");
		std::cout << "==================================================" << std::endl;
		std::cout << " -=Prikaz studenata koji su polozili kurs=-  " << std::endl;
		std::cout << "==================================================" << std::endl;
		std::cout << std::endl;
		CourseDetail detail = CourseDetail::CourseDetailCreater(course);
		auto& currArr = detail.getPassedStudents();
		printStudHeader();
		if (currArr.size() == 0)
		{
			std::cout << "Trenutno nema studenata  koji su polozili kurs!!" << std::endl;
			return;
		}
		for (auto& x : currArr)
		{
			Student& trenutni = getStudent(x, students);
			printStudent(trenutni);
		}
		printStudFooter();
	}

	Course& CourseProfessorInteraction::courseChoise(std::vector<Course>& courses)
	{
		std::string id;
		while (true)
		{
			std::cout << "Unesite id:";
			std::cin >> id;
			auto it = std::find_if(courses.begin(), courses.end(), [&id](Course& c)
			{
				return id == c.getId();
			});
			if (it == courses.end())
				std::cout << "Ne postoji kurs sa unijetim id" << std::endl;
			else
				return *it;
		}
	}

	Student& CourseProfessorInteraction::studentChoise(std::vector<Student>& students)
	{
		std::string id;
		while (true)
		{
			std::cout << "Unesite id:";
			std::cin >> id;
			auto it = std::find_if(students.begin(), students.end(), [&id](Student& s)
			{
				return s.getId() == id;
			});
			if (it == students.end())
				std::cout << "Ne postoji student sa unijetim id" << std::endl;
			else
				return *it;
		}
	}

	void CourseProfessorInteraction::reqForCourse(Professor& prof, std::vector<Course>& courses,std::vector<Student>&students)
	{
		system("CLS");
		std::cout << "====================================================" << std::endl;
		std::cout << "\t-=Zahtjevi za kurs=-" << std::endl;
		std::cout << "====================================================" << std::endl;
		int status=showProfessorsCourses(prof, courses);//ispis njegovis kurseva
		if (status == 0)
			return;
		std::cout << "Unesite id kursa sa kojim zelite manipulisati?" << std::endl;
		Course& course = courseChoise(courses);//dobio sam kurs
		system("CLS");
		std::cout << "====================================================" << std::endl;
		std::cout << "Studenati koji cekaju za upis na kurs!!" << std::endl;
		std::cout << "====================================================" << std::endl;
		CourseDetail detail = CourseDetail::CourseDetailCreater(course);
		auto& reqArr = detail.getCourseReq();
		if (reqArr.size() == 0)
		{
			std::cout << "Trenutno nema novih zatjeva za kurs" << std::endl;
			return;
		}
		printStudHeader();
		for (auto& x : reqArr)
		{
			//Student& trenutni = getStudent(x.getStudentId(), students);
			std::string studId = x.getStudentId();
			auto it = std::find_if(students.begin(), students.end(), [&studId](Student& s)
			{
				return studId == s.getId();
			});
			if(it!=students.end())
				printStudent(*it);
		}
		printStudFooter();
		std::cout << "Unesite id studenta ciji zahtjev zelite obraditi!!" << std::endl;
		Student& stud = studentChoise(students);
		std::cout << "Da li zelite prihvati/odbiti zahtjev?" << std::endl;
		int opcija;
		do
		{
			std::cout << "Prihvati(1)/Odbij(0):";
			std::cin >> opcija;
			if (opcija != 0 && opcija != 1)
				std::cout << "Pogresna opcija" << std::endl;
		} while (opcija != 0 && opcija != 1);
		CourseAdministration manager(detail);
		if (opcija == 1)
		{
			try
			{
				manager.acceptCourseReq(stud);
			}
			catch (const std::invalid_argument& e)
			{
				std::cout << e.what() << std::endl;
				return;
			}
			catch (const std::runtime_error& e)
			{
				std::cout << e.what() << std::endl;
				return;
			}
			std::cout << "Zahtjev prihvacen!!" << std::endl;
		}
		else
		{
			try
			{
				manager.rejectCourseReq(stud);
			}
			catch (const std::invalid_argument& e)
			{
				std::cout << e.what() << std::endl;
				return;
			}
			catch (const std::runtime_error& e)
			{
				std::cout << e.what() << std::endl;
				return;
			}
			std::cout << "Zahtjev odbijen!!" << std::endl;
		}
	}

	void CourseProfessorInteraction::writeGrade(Professor& prof, std::vector<Course>& courses, std::vector<Student>& students)
	{
		system("CLS");
		std::cout << "============================================================" << std::endl;
		std::cout << "\t     -=Upis ocjene=-" << std::endl;
		std::cout << "============================================================" << std::endl<<std::endl;
		int status=showProfessorsCourses(prof, courses);//ispis njegovis kurseva
		if (status == 0)
			return;
		std::cout << "Unesite id kursa sa kojim zelite manipulisati?" << std::endl;
		Course& course = courseChoise(courses);//izbor kursa
		showCurrStudentOnCourses(course, students);//prikaz studenta
		std::cout << "Unesite id studenta kojeg zelite ocijeniti!!" << std::endl;
		Student& stud = studentChoise(students);
		double ocjena;
		do
		{
			std::cout << "Unesite ocjenu:";
			std::cin >> ocjena;
			if (ocjena <6 || ocjena>10)
				std::cout << "Pogresan unos!" << std::endl;
		} while (ocjena < 6 || ocjena>10);
		CourseDetail detail = CourseDetail::CourseDetailCreater(course);
		CourseAdministration manager(detail);
		try
		{
			manager.evaluateStudent(stud, ocjena);
		}
		catch (const std::runtime_error& e)
		{
			std::cout << e.what() << std::endl;
			return;
		}
		std::cout << "Ocjena uspjesno upisana!!" << std::endl;

	}

	void CourseProfessorInteraction::showStudentsOnCourses(const Professor&professor,std::vector<Course>&courses, std::vector<Student>&students)
	{
		system("CLS");
		int status=showProfessorsCourses(professor, courses);
		if (status == 0)
			return;
		std::cout << "Unesite id kursa sa kojim zelite manipulisati?" << std::endl;
		Course& course = courseChoise(courses);
		system("CLS");
		std::cout << "================================================================" << std::endl;
		std::cout << "             -=Pregled studenata na kursu=-                      " << std::endl;
		std::cout << "================================================================" << std::endl;
		std::cout << "(1)Pregled trenutnih studenata na kursu" << std::endl;
		std::cout << "(2)Pregled studenata koji su polozili kurs" << std::endl;
		int opcija;
		do
		{
			std::cout << "Unesite opciju:";
			std::cin >> opcija;
			if (opcija != 1 && opcija != 2)
				std::cout << "Pogresan unos";
		} while (opcija != 1 && opcija != 2);
		if (opcija == 1)
			showCurrStudentOnCourses(course, students);
		else
			showPassStudentOnCourses(course, students);
		

	}
}