#include"CourseAdminInteraction.h"
#include"CourseProfessorInteraction.h"
#include<filesystem>

namespace learningPlatform
{
	void CourseAdminInteraction::showCourses(std::vector<Course>& courses)
	{
		system("CLS");
		std::cout << "============================================================" << std::endl;
		std::cout << "                   -=Pregled kurseva=-                      " << std::endl;
		std::cout << "============================================================" << std::endl << std::endl;
		std::cout << "====== ==================== ======== =========================" << std::endl;
		std::cout << "ID     NAZIV                KATEDRA  PROFESOR                 " << std::endl;
		std::cout << "====== ==================== ======== =========================" << std::endl;
		for (auto& x : courses)
			std::cout << x << std::endl;
		std::cout << "====== ==================== ======== =========================" << std::endl;
	}


	void CourseAdminInteraction::printProfHeader()
	{
		std::cout << "=============== ===============:======" << std::endl;
		std::cout << "IME             PREZIME         ID" << std::endl;
		std::cout << "=============== ===============:======" << std::endl;
	}

	void CourseAdminInteraction::printProfFooter()
	{
		std::cout << "=============== ===============:======" << std::endl;
	}

	void CourseAdminInteraction::printProf(const Professor& x)
	{
		std::cout << std::setw(15) << std::left << x.getName() << " " <<
			std::setw(15) << std::left << x.getSurname() << ":" << std::setw(15) << std::left
			<< x.getId() << std::endl;
	}

	Professor& CourseAdminInteraction::profChoise(std::vector<Professor>& professors)
	{
		std::string id;
		while (true)
		{
			std::cout << "Unesite id:";
			std::cin >> id;
			auto it = std::find_if(professors.begin(), professors.end(), [&id](Professor& c)
			{
				return id == c.getId();
			});
			if (it == professors.end())
				std::cout << "Pogresan id!" << std::endl;
			else
				return *it;
		}
	}


	void CourseAdminInteraction::createCourse(std::vector<Course>& courses, std::vector<CoursePrecondtion*>& precondtions, std::vector<Professor>& professors)
	{
		system("CLS");
		std::cout << "=======================================================" << std::endl;
		std::cout << "\t -=Kreiranje novog kursa=-" << std::endl;
		std::cout << "=======================================================" << std::endl;
		std::cout << "Unesite podatke o kursu!!" << std::endl;
		std::string naziv, katedra, id;
		std::cout << "Naziv:";
		std::cin.get();
		std::getline(std::cin, naziv, '\n');
		std::cout << "Katedra:";
		std::cin >> katedra;
		while (true)
		{
			std::cout << "ID kursa:";
			std::cin >> id;
			auto it = std::find_if(courses.begin(), courses.end(), [&id](Course& c)
			{
				return id == c.getId();
			});
			if (it != courses.end())
				std::cout << "Kurs sa unijetim id vec postoji!!" << std::endl;
			else
				break;
		}
		std::cout << "Izaberite profesora koji ce biti zaduzen za kurs!!" << std::endl;
		printProfHeader();
		for (auto x : professors)
			printProf(x);
		printProfFooter();
		Professor& prof = profChoise(professors);

		Course novi(id, naziv, katedra, prof);
		CourseInfoFileIO scanner(professors);
		courses.push_back(novi);
		scanner.writeCourse(novi);
		system("CLS");
		std::cout << "=====================================================" << std::endl;
		std::cout << "Izaberite preduslove za kurs!!" << std::endl;
		std::cout << "=====================================================" << std::endl;
		CourseManagerFileIO cmScanner;
		CoursePrecondtionFileIO cpScanner;
		int opcija = -1;
		do
		{
			std::cout << "Preduslov(1):\"Kurs polozen\"" << std::endl;
			std::cout << "Preduslov(2):\"Kurs polozen sa minimalnom ocjenom\"" << std::endl;
			std::cout << "Preduslov(3):\"Minimalan broj polozenih kurseva\"" << std::endl;
			std::cout << "Kraj(4)" << std::endl;
			std::cout << "Unesite opciju:";
			std::cin >> opcija;
			if (opcija == 1)
			{
				std::cout << "Unesite id kursa koji treba da bude polozen!!" << std::endl;
				Course& c = CourseProfessorInteraction::courseChoise(courses);
				CoursePassed* ptr = new CoursePassed(c.getId());
				precondtions.emplace_back(ptr);
				cmScanner.writeCoursePrecondtion(novi, ptr->getId());
				cpScanner.writeCoursePrecondtion(*ptr);
			}
			else if (opcija == 2)
			{
				double min;
				std::cout << "Unesite id kursa koji treba da bude polozen!!" << std::endl;
				Course& c = CourseProfessorInteraction::courseChoise(courses);
				std::cout << "Unesite minimalnu ocjenu:";
				std::cin.get();
				std::cin >> min;
				CoursePassedWithMinGrade* ptr = new CoursePassedWithMinGrade(c.getId(), min);
				precondtions.emplace_back(ptr);
				cmScanner.writeCoursePrecondtion(novi, ptr->getId());
				cpScanner.writeCoursePrecondtion(*ptr);
			}
			else if (opcija == 3)
			{
				int min;
				std::cout << "Unesite minimalni broj polozenih kurseva:";
				std::cin >> min;
				NumberOfPassedCourse* ptr = new NumberOfPassedCourse(min);
				precondtions.emplace_back(ptr);
				cmScanner.writeCoursePrecondtion(novi, ptr->getId());
				cpScanner.writeCoursePrecondtion(*ptr);
			}
			else if (opcija != 4)
				std::cout << "Pogresan unos!!" << std::endl;
			system("CLS");

		} while (opcija != 4);
		std::cout << "Kurs uspjesno kreiran!!" << std::endl;
	}

	void CourseAdminInteraction::deleteCourse(std::vector<Course>& courses, std::vector<Student>& students, std::vector<Professor>& professors)
	{
		std::cout << "======================================================" << std::endl;
		std::cout << "                  -=Brisanje kursa=-                    " << std::endl;
		std::cout << "======================================================" << std::endl;
		CourseProfessorInteraction::printCourseHeader();
		for (auto& x : courses)
			std::cout << std::left << std::setw(20) << x.getName() << ":" << std::left << std::setw(6) << x.getId() << std::endl;
		CourseProfessorInteraction::printCourseFooter();
		std::cout << "Unesite id kursa kojeg zelite obrisati!!" << std::endl;
		std::string id;
		std::vector<Course>::iterator it;
		while (true)
		{
			std::cout << "Unesite id:";
			std::cin >> id;
			it = std::find_if(courses.begin(), courses.end(), [&id](Course& c)
			{
				return id == c.getId();
			});
			if (it == courses.end())
				std::cout << "Ne postoji kurs sa datim id!!" << std::endl;
			else
				break;
		}
		//brisanje kursa iz svih fajlova njegovih studenata(tesko krampanje)
		CourseStudentFileIO csScanner;
		CourseDetail detail = CourseDetail::CourseDetailCreater(*it);
		auto& currStudent = detail.getCurrentStudents();
		auto& passStudent = detail.getPassedStudents();
		for (auto x : currStudent)
		{
			auto it = std::find_if(students.begin(), students.end(), [&x](Student& s)
			{
				return s.getId() == x;
			});
			auto& arr = it->getCurrCourses();
			arr.erase(std::remove_if(arr.begin(), arr.end(), [&id](Course* x) {return x->getId() == id; }));
			csScanner.writeAllStudentCurrCourses(*it);
		}
		for (auto x : passStudent)
		{
			auto it = std::find_if(students.begin(), students.end(), [&x](Student& s)
			{
				return s.getId() == x;
			});
			auto& arr = it->getPassCourses();
			arr.erase(std::remove_if(arr.begin(), arr.end(), [&id](PassedCourse& x) {return x.getCourse()->getId() == id; }));
			csScanner.writeAllStudentPassCourses(*it);
		}

		//brisanje foldera o kursa
		namespace fs = std::filesystem;
		fs::path path = (fs::current_path() / "courses") / ("course-" + id);
		fs::remove_all(path);

		//brisanje course info
		courses.erase(it);
		CourseInfoFileIO ciScanner(professors);
		ciScanner.writeAllCourses(courses);

		std::cout << "Kurs uspjesno obrisan!!" << std::endl;
	}

	void CourseAdminInteraction::modifyCourse(std::vector<Course>& courses, std::vector<Professor>& professors)
	{
		system("cls");
		std::cout << "=========================================================" << std::endl;
		std::cout << "                   -=Izmjena kursa=-                     " << std::endl;
		std::cout << "=========================================================" << std::endl;
		CourseProfessorInteraction::printCourseHeader();
		for (auto& x : courses)
			std::cout << std::left << std::setw(20) << x.getName() << ":" << std::left << std::setw(6) << x.getId() << std::endl;
		CourseProfessorInteraction::printCourseFooter();
		std::cout << "Unesite id kursa kojeg zelite izmjeniti!!" << std::endl;
		Course& c = CourseProfessorInteraction::courseChoise(courses);
		system("CLS");
		std::cout << "Stavke koje se mogu modifikovati!" << std::endl;
		std::cout << "(1)Naziv" << std::endl;
		std::cout << "(2)Profesor" << std::endl;
		int opcija;
		do
		{
			std::cout << "Unesite opciju:";
			std::cin >> opcija;
			if (opcija != 1 && opcija != 2)
				std::cout << "Pogresan unos" << std::endl;
		} while (opcija != 1 && opcija != 2);
		if (opcija == 1)
		{
			std::cout << "Unesite novi naziv kursa:";
			std::string naziv;
			std::cin >> naziv;
			c.setName(naziv);
		}
		else if (opcija == 2)
		{
			std::cout << "Unesite id profesora koji preuzima kurs:";
			Professor& p = profChoise(professors);
			c.setProfessor(p);
		}
		CourseInfoFileIO ciScanner(professors);
		ciScanner.writeAllCourses(courses);
		std::cout << "Kurs uspjesno modifikovan!!" << std::endl;

	}

	void CourseAdminInteraction::courseSetOperation(std::vector<Course>& courses, std::vector<Student>& students)
	{
		system("CLS");
		std::cout << "=========================================================" << std::endl;
		std::cout << "            -=Skupovne operacije sa kursevima=-          " << std::endl;
		std::cout << "=========================================================" << std::endl;
		std::cout << "Operacije:" << std::endl;
		std::cout << "(1)Presjek studenata na kurseva" << std::endl;
		std::cout << "(2)Unija studenata na kursevima" << std::endl;
		std::cout << "(3)Razlika studenata na kursevima" << std::endl;
		int opcija;
		do
		{
			std::cout << "Unesite opciju:";
			std::cin >> opcija;
			if (opcija != 1 && opcija != 2 && opcija != 3)
				std::cout << "Pogresan unos!!" << std::endl;
		} while (opcija != 1 && opcija != 2 && opcija != 3);
		std::vector<std::string> studentsId;
		std::cout << "Unesite id dva kursa sa kojima zelite manipulisati!" << std::endl;
		Course& c1 = CourseProfessorInteraction::courseChoise(courses);
		Course& c2 = CourseProfessorInteraction::courseChoise(courses);
		CourseDetail cd1 = CourseDetail::CourseDetailCreater(c1);
		CourseDetail cd2 = CourseDetail::CourseDetailCreater(c2);
		std::cout << "Da li zelite izvrsiti operaciju nad:" << std::endl;
		std::cout << "(1)Studentima koji trenutno slusaju kurs" << std::endl;
		std::cout << "(2)Studentima koji su polozili kurs" << std::endl;
		int opcija1;
		do
		{
			std::cout << "Unesite opciju:";
			std::cin >> opcija1;
			if (opcija1 != 1 && opcija1 != 2)
				std::cout << "Pogresan unos" << std::endl;
		} while (opcija1 != 1 && opcija1 != 2);
		auto& vec1 = (opcija1 == 1) ? cd1.getCurrentStudents() : cd1.getPassedStudents();
		auto& vec2 = (opcija1 == 1) ? cd2.getCurrentStudents() : cd2.getPassedStudents();
		if (opcija == 1)
			studentsId = CourseDetail::setIntersection(vec1, vec2);
		else if (opcija == 2)
			studentsId = CourseDetail::setUnion(vec1, vec2);
		else if (opcija == 3)
			studentsId = CourseDetail::setDifference(vec1, vec2);
		system("CLS");
		std::cout << "=================================================================" << std::endl;
		std::cout << "                   -=Rezultati obrade=-                          " << std::endl;
		std::cout << "=================================================================" << std::endl << std::endl;
		CourseProfessorInteraction::printStudHeader();
		if (studentsId.size() == 0)
			std::cout << "       Skup je prazan!!      " << std::endl;
		else
			for (auto x : studentsId)
			{
				Student& stud = CourseProfessorInteraction::getStudent(x, students);
				CourseProfessorInteraction::printStudent(stud);
			}
		CourseProfessorInteraction::printStudFooter();

	}


}

