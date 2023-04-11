#include "UserAdminInteraction.h"
#include"CourseProfessorInteraction.h"
#include"FriendReqFileIO.h"
#include "CourseInfoFileIO.h"
#include "Date.h"
#include<Windows.h>

namespace learningPlatform
{
	void UserAdminInteraction::showStudents(std::vector<Student>& students)
	{
		system("CLS");
		std::cout << "==================================================================" << std::endl;
		std::cout << "\t\t-=Pregled studenata=-                         " << std::endl;
		std::cout << "===== ========== ============ ========== ====== ======== =========" << std::endl;
		std::cout << "ID    IME        PREZIME      DATUM_RODJ POL    INDEKS   STATUS  " << std::endl;
		std::cout << "===== ========== ============ ========== ====== ======== =========" << std::endl;
		for (auto& x : students)
			std::cout << x << std::endl;
		std::cout << "===== ========== ============ ========== ====== ======== =========" << std::endl;
	}

	void UserAdminInteraction::showProfessors(std::vector<Professor>& professors)
	{
		system("CLS");
		std::cout << "=================================================================" << std::endl;
		std::cout << "\t\t-=Pregled profesora=-                         " << std::endl;
		std::cout << "===== ========== ============ ========== ====== ========= ========" << std::endl;
		std::cout << "ID    IME        PREZIME      DATUM_RODJ POL    ZVANJE    KATEDRA  " << std::endl;
		std::cout << "===== ========== ============ ========== ====== ========= ========" << std::endl;
		for (auto& x : professors)
			std::cout << x << std::endl;
		std::cout << "===== ========== ============ ========== ====== ========= ========" << std::endl;
	}

	void UserAdminInteraction::userCreate(std::vector<Professor>& professors, std::vector<Student>& students)
	{
		system("CLS");
		std::cout << "======================================================" << std::endl;
		std::cout << "\t-=Kreiranje novog naloga=-                            " << std::endl;
		std::cout << "======================================================" << std::endl;
		std::cout << "Da li zelite kreirati nalog za studenta ili profesora?" << std::endl;
		int opcija;
		do
		{
			std::cout << "Student(0)/Profesor(1):";
			std::cin >> opcija;
			if (opcija != 0 && opcija != 1)
				std::cout << "Pogresan unos" << std::endl;
		} while (opcija != 0 && opcija != 1);
		if (opcija == 0)
			createStudent(students);
		else
			createProfessors(professors);
	}

	void UserAdminInteraction::createProfessors(std::vector<Professor>& professors)
	{
		system("CLS");
		std::cout << "=======================================================" << std::endl;
		std::cout << "\t -=Kreiranje novog profesora=-" << std::endl;
		std::cout << "=======================================================" << std::endl;
		std::cout << "Unesite podatke o profesoru!!" << std::endl;
		std::string ime, prezime, email,katedra;
		int pol;
		Date datumRodjenja;
		UserAdminInteraction::inputUser(ime, prezime, pol, email, datumRodjenja);
		std::cout << "Katedra:";
		std::cin >> katedra;
		int zvanje;
		do
		{
			std::cout << "Zvanje-ASISTENT(0),DOCENT(1),VAND_PROF(2),RED_PROF(3):";
			std::cin >> zvanje;
			if (zvanje != 0 && zvanje != 1 && zvanje != 2 && zvanje != 3)
				std::cout << "Pogresan unos" << std::endl;
		}while (zvanje != 0 && zvanje != 1 && zvanje != 2 && zvanje != 3);
		std::string tempUser = "PROF";
		std::string password = ime + datumRodjenja.toString();
		Professor temp(tempUser, password, ime, prezime, datumRodjenja, (Genders)pol, email, katedra, (Zvanja)zvanje);
		professors.push_back(temp);
		ProfessorFileIO scanner;
		try
		{
			scanner.writeUser(temp);
		}
		catch (const std::runtime_error& e)
		{
			std::cout << "Registracija neuspesna, pokusajte ponovo" << std::endl;
			return;
		}
		UserAdminInteraction::showAccTrait(tempUser=temp.getUsername(), password);
	}

	void UserAdminInteraction::inputUser(std::string& ime, std::string& prezime, int& pol, std::string&email,Date& datumRodjenja)
	{
		std::cout << "Ime:";
		std::cin >> ime;
		std::cout << "Prezime:";
		std::cin >> prezime;
		std::cin.get();
		do
		{
			std::cout << "Pol-MUSKI(0)/ZENSKI(1):";
			std::cin >> pol;
			if (pol != 0 && pol != 1)
				std::cout << "Pogresan unos" << std::endl;
		} while (pol != 0 && pol != 1);
		std::cout << "Email:";
		std::cin >> email;
		std::cin.get();

		while (true)
		{
			std::cout << "Datum rodjenja(DD/MM/GGGG):";
			std::cin >> datumRodjenja;
			if (datumRodjenja.getDay() > 31 || datumRodjenja.getMonth() > 12 || datumRodjenja.getYear() < 1900 || datumRodjenja.getYear() > Date::getCurrentDate().getYear())
				std::cout << "Pogresan unos!!" << std::endl;
			else
				break;
		}
	}

	void UserAdminInteraction::showAccTrait(std::string& username, std::string& password)
	{
		system("CLS");
		std::cout << "======================================================" << std::endl;
		std::cout << "\t -=Pristupni podaci=-" << std::endl;
		std::cout << "Username:" << username << std::endl;
		std::cout << "Password:" << password << std::endl;
		std::cout << "======================================================" << std::endl;
		Sleep(2000);
	}

	void UserAdminInteraction::createStudent(std::vector<Student>& students)
	{
		system("CLS");
		std::cout << "=======================================================" << std::endl;
		std::cout << "\t -=Kreiranje novog studenta=-" << std::endl;
		std::cout << "=======================================================" << std::endl;
		std::cout << "Unesite podatke o studentu!!" << std::endl;
		std::string ime, prezime, email, index;
		int pol;
		Date datumRodjenja;
		UserAdminInteraction::inputUser(ime, prezime, pol, email, datumRodjenja);
		while (true)
		{
			std::cout << "Broj indeksa:";
			std::cin >> index;
			auto it = std::find_if(students.begin(), students.end(), [&index](Student& s)
			{
				return s.getIndex() == index;
			});
			if (it != students.end())
				std::cout << "Indeks vec postoji u sistemu!" << std::endl;
			else
				break;
		}
		std::cin.get();
		int status;
		do
		{
			std::cout << "Status studenta-REDOVNI(0)/VANDREDNI(1):";
			std::cin >> status;
			if (status != 0 && status != 1)
				std::cout << "Pogresan unos";
		} while (status != 1 && status != 0);
		std::string username = "STUD-" + index;
		std::string password = ime+datumRodjenja.toString();
		Student temp(username, password, ime, prezime, datumRodjenja, (Genders)pol, email, index, (StudentStatus)status);
		students.push_back(temp);
		StudentFileIO scanner;
		try
		{
			scanner.writeUser(temp);
		}
		catch (const std::runtime_error& e)
		{
			std::cout << "Registracija neuspesna, pokusajte ponovo" << std::endl;
			return;
		}
		UserAdminInteraction::showAccTrait(username, password);
	}

	void UserAdminInteraction::deleteUser(std::vector<Professor>& professors, std::vector<Student>& students,std::vector<Course>&course)
	{
		system("CLS");
		std::cout << "======================================================" << std::endl;
		std::cout << "\t  -=Brisanje naloga=-                            " << std::endl;
		std::cout << "======================================================" << std::endl;
		std::cout << "Da li zelite obrisati nalog za studenta ili profesora?" << std::endl;
		int opcija;
		do
		{
			std::cout << "Student(0)/Profesor(1):";
			std::cin >> opcija;
			if (opcija != 0 && opcija != 1)
				std::cout << "Pogresan unos" << std::endl;
		} while (opcija != 0 && opcija != 1);
		if (opcija == 0)
			deleteStudent(students);
		else
			deleteProfessor(professors,course);
	}

	void UserAdminInteraction::deleteStudent(std::vector<Student>& students)
	{
		system("CLS");
		std::cout << "=======================================================" << std::endl;
		std::cout << "           -=Brisanje studenta iz sistema=-            " << std::endl;
		std::cout << "=======================================================" << std::endl;
		std::cout << "Da li zelite pregledati sve studente?" << std::endl;
		int opcija;
		do
		{
			std::cout << "DA(1)/NE(0):";
			std::cin >> opcija;
			if (opcija != 1 && opcija != 0)
				std::cout << "Pogresna opcija" << std::endl;
		} while (opcija != 1 && opcija != 0);
		if (opcija == 1)
			UserAdminInteraction::showStudents(students);
		std::cout << "Unesite id studenta kojeg zelite obrisati?" << std::endl;
		Student& ptr = CourseProfessorInteraction::studentChoise(students);
		std::cout << "Potvrdite brisanje!" << std::endl;
		do
		{
			std::cout << "DA(1)/NE(0):";
			std::cin >> opcija;
			if (opcija != 1 && opcija != 0)
				std::cout << "Pogresna opcija" << std::endl;
		} while (opcija != 1 && opcija != 0);
		if (opcija == 0)
		{
			std::cout << "Brisanje neuspjesno!!" << std::endl;
			return;
		}
		//brisanje foldera o studentu
		fs::path path = fs::current_path() / "students" / ptr.getId();
		try
		{
			fs::remove_all(path);
		}
		catch (fs::filesystem_error)
		{
			std::cout << "Greska prilikom brisanje studentsog foldera, folder obrisite manuelno" << std::endl;
		}
		//studenta trebamo ispisati iz svih njegovih kurseva
		//TODO funkcija ispisi sa kursa
		auto& courseArr = ptr.getCurrCourses();
		CourseManagerFileIO cmScanner;
		std::string id = ptr.getId();
		for (auto& e : courseArr)//dobijamo course*
		{
			std::vector<std::string> currCourse;
			cmScanner.readAllStudentsFromCurrCourse(*e, currCourse);
			currCourse.erase(std::remove_if(currCourse.begin(), currCourse.end(), [&id](std::string& s) {return s == id; }));
			cmScanner.writeAllStudentsToCurrCourse(*e, currCourse);
		}
		auto& passArr = ptr.getPassCourses();
		for (auto& e : passArr)
		{
			Course* ptr = e.getCourse();
			std::vector<std::string> passCourse;
			cmScanner.readAllStudentsFromPassCourse(*ptr, passCourse);
			passCourse.erase(std::remove_if(passCourse.begin(), passCourse.end(), [&id](std::string& s) {return s == id; }));
			cmScanner.writeAllStudentsToPassCourse(*ptr, passCourse);
		}
		//brisanje iz svih zahtjeva i prijatelja
		FriendReqFileIO frScanner;
		std::vector<FriendReq> friendReqs;
		std::vector<FriendReq> temp;
		frScanner.readAllFriendReq(friendReqs);
		for (auto& x : friendReqs)
		{
			if (x.getReceiver() != id && x.getSender() != id)
				temp.push_back(x);
		}
		frScanner.writeAllFriendReq(temp);

		
		//brisanje iz niza i iz fajla o svim studentima
		students.erase(std::remove(students.begin(), students.end(), ptr));
		StudentFileIO studentsScanner;
		studentsScanner.writeAllUser(students);
	}

	void UserAdminInteraction::deleteProfessor(std::vector<Professor>& professors,std::vector<Course>&courses)
	{

		system("CLS");
		std::cout << "=======================================================" << std::endl;
		std::cout << "           -=Brisanje profesora iz sistema=-            " << std::endl;
		std::cout << "=======================================================" << std::endl;
		std::cout << "Da li zelite pregledati sve profesore?" << std::endl;
		int opcija;
		do
		{
			std::cout << "DA(1)/NE(0):";
			std::cin >> opcija;
			if (opcija != 1 && opcija != 0)
				std::cout << "Pogresna opcija" << std::endl;
		} while (opcija != 1 && opcija != 0);
		if (opcija == 1)
			UserAdminInteraction::showProfessors(professors);
		std::cout << "Unesite id profesora kojeg zelite obrisati?" << std::endl;
		Professor& prof = professorChoise(professors);
		std::cout << "Potvrdite brisanje!" << std::endl;
		do
		{
			std::cout << "DA(1)/NE(0):";
			std::cin >> opcija;
			if (opcija != 1 && opcija != 0)
				std::cout << "Pogresna opcija" << std::endl;
		} while (opcija != 1 && opcija != 0);
		if (opcija == 0)
		{
			std::cout << "Brisanje neuspjesno!!" << std::endl;
			return;
		}
		std::cout << "Izaberite zamjenskog profesora za njegove kurseve!!" << std::endl;
		for (auto& el : courses)
		{
			if (*el.getProfessor() == prof)
			{
				std::cout << "\tKurs:"<<el.getName() << std::endl;
				std::cout << "Izaberite zamjenskog profesora!" << std::endl;
				Professor& prof1 = professorChoise(professors);
				el.setProfessor(prof1);
			}
		}
		CourseInfoFileIO courseScanner(professors);
		courseScanner.writeAllCourses(courses);

		ProfessorFileIO profScanner;
		professors.erase(std::remove(professors.begin(), professors.end(), prof));
		profScanner.writeAllUser(professors);
		
	
	}

	Professor& UserAdminInteraction::professorChoise(std::vector<Professor>& professors)
	{
		std::string id;
		while (true)
		{
			std::cout << "Unesite id:";
			std::cin >> id;
			auto it = std::find_if(professors.begin(), professors.end(), [&id](Professor& p)
			{
				return id == p.getId();
			});
			if (it == professors.end())
				std::cout << "Ne postoji profesor sa unijetim id" << std::endl;
			else
			{
				return *it;
				break;
			}
		}
	}

	void UserAdminInteraction::modifyUser(std::vector<Professor>& professors, std::vector<Student>& students)
	{
		system("CLS");
		std::cout << "======================================================" << std::endl;
		std::cout << "\t  -=Izmjena naloga=-                            " << std::endl;
		std::cout << "======================================================" << std::endl;
		std::cout << "Da li zelite izmjeniti nalog za studenta ili profesora?" << std::endl;
		int opcija;
		do
		{
			std::cout << "Student(0)/Profesor(1):";
			std::cin >> opcija;
			if (opcija != 0 && opcija != 1)
				std::cout << "Pogresan unos" << std::endl;
		} while (opcija != 0 && opcija != 1);
		if (opcija == 0)
			modifyStudent(students);
		else
			modifyProfessors(professors);
	}

	void UserAdminInteraction::modifyStudent(std::vector<Student>& students)
	{
		system("CLS");
		std::cout << "======================================================" << std::endl;
		std::cout << "\t  -=Izmijena studentskog naloga=-                            " << std::endl;
		std::cout << "======================================================" << std::endl;
		std::cout << "Unesite id studenta kojeg zelite modifikovati?"<<std::endl;
		Student& stud = CourseProfessorInteraction::studentChoise(students);
		system("CLS");
		std::cout << "Stavke koje se mogu modifikovati!" << std::endl;
		std::cout << "(1)Sifra" << std::endl;
		std::cout << "(2)Email" << std::endl;
		std::cout << "(3)Status studenta" << std::endl;
		int opcija;
		do
		{
			std::cout << "Unesite opciju:";
			std::cin >> opcija;
			if (opcija != 1 && opcija != 2 && opcija != 3)
				std::cout << "Pogresna opcija"<<std::endl;
		} while (opcija != 1 && opcija != 2 && opcija != 3);
		if (opcija == 1)
		{
			std::string password;
			std::cout << "Unesite novu sifru:";
			std::cin >> password;
			stud.setPassword(password);
			std::cout << "Sifra uspjesno izmijenjena" << std::endl;
		}
		else if (opcija == 2)
		{
			std::string email;
			std::cout << "Unesite novi email:";
			std::cin >> email;
			stud.setEmail(email);
			std::cout << "Email uspjesno izmijenjen" << std::endl;
		}
		else if (opcija == 3)
		{
			std::cout << "Unesite novi status studenta?" << std::endl;
			int status;
			do
			{
				std::cout << "REDOVNI(0)/VANDREDNI(1)";
				std::cin >> status;
				if (status != 0 && status != 1)
					std::cout << "Pogresan unos" << std::endl;
			} while (status != 0 && status != 1);
			stud.setStatus((StudentStatus)status);
			std::cout << "Status studenta uspjesno izmijenjen" << std::endl;
		}
		StudentFileIO scanner;
		scanner.writeAllUser(students);

	}

	void UserAdminInteraction::modifyProfessors(std::vector<Professor>& professors)
	{
		system("CLS");
		std::cout << "======================================================" << std::endl;
		std::cout << "\t  -=Izmijena profesorskog naloga=-                            " << std::endl;
		std::cout << "======================================================" << std::endl;
		std::cout << "Unesite id profesora kojeg zelite modifikovati?" << std::endl;
		Professor& prof= UserAdminInteraction::professorChoise(professors);
		system("CLS");
		std::cout << "Stavke koje se mogu modifikovati!" << std::endl;
		std::cout << "(1)Sifra" << std::endl;
		std::cout << "(2)Email" << std::endl;
		std::cout << "(3)Zvanje" << std::endl;
		int opcija;
		do
		{
			std::cout << "Unesite opciju:";
			std::cin >> opcija;
			if (opcija != 1 && opcija != 2 && opcija != 3)
				std::cout << "Pogresna opcija" << std::endl;
		} while (opcija != 1 && opcija != 2 && opcija != 3);
		if (opcija == 1)
		{
			std::string password;
			std::cout << "Unesite novu sifru:";
			std::cin >> password;
			prof.setPassword(password);
			std::cout << "Sifra uspjesno izmijenjena" << std::endl;
		}
		else if (opcija == 2)
		{
			std::string email;
			std::cout << "Unesite novi email:";
			std::cin >> email;
			prof.setEmail(email);
			std::cout << "Email uspjesno izmijenjen" << std::endl;
		}
		else if (opcija == 3)
		{
			std::cout << "Unesite novo zvanje profesora?" << std::endl;
			int zvanje;
			do
			{
				std::cout << "Zvanje-ASISTENT(0),DOCENT(1),VAND_PROF(2),RED_PROF(3):";
				std::cin >> zvanje;
				if (zvanje != 0 && zvanje != 1 && zvanje != 2 && zvanje != 3)
					std::cout << "Pogresan unos" << std::endl;
			} while (zvanje != 0 && zvanje != 1 && zvanje != 2 && zvanje != 3);
			prof.setZvanje((Zvanja)zvanje);
			std::cout << "Zvanje profesora uspjesno izmijenjeno" << std::endl;
		}
		ProfessorFileIO scanner;
		scanner.writeAllUser(professors);
	}
}