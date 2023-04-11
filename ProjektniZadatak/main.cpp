#include<vector>
#include<chrono>
#include<thread>
#include "Student.h"
#include "StudentFileIO.h"
#include"ProfessorFileIO.h"
#include "FriendReqManager.h"
#include "MessageManager.h"
#include "Chat.h"
#include"HelpFunction.h"
#include"Login.h"
#include"FriendReqInteraction.h"
#include "Course.h"
#include "CourseInfoFileIO.h"
#include "CourseReq.h"
#include "CourseReqFileIO.h"
#include "CourseManagerFileIO.h"
#include "CourseRegisterManager.h"
#include "CourseDetails.h"
#include "CourseAdministration.h"
#include "CourseStudentInteraction.h"
#include"CourseProfessorInteraction.h"
#include"UserAdminInteraction.h"
#include"CoursePrecondition.h"
#include"CoursePrecondtionFileIO.h"
#include"CourseAdminInteraction.h"
#include"Graph.h"

void courseTest()
{
	using namespace learningPlatform;
	std::vector<Course> kursevi;
	std::vector<Professor> profesori;
	std::vector<Student> studenti;
	std::vector<CoursePrecondtion*> preduslovi;
	ProfessorFileIO scanner;
	scanner.readAllUser(profesori);
	CourseInfoFileIO scan(profesori);
	scan.readAllCourses(kursevi);
	StudentFileIO scan1;
	scan1.readAllUser(studenti, kursevi);
	CourseDetail detaljni = CourseDetail::CourseDetailCreater(kursevi[0]);
	CourseAdministration manager(detaljni);
	/*manager.evaluateStudent(studenti[0], 10);
	std::cout << studenti[0].getCurrCourses().size() << std::endl;
	std::cout << studenti[0].getPassCourses().size() << std::endl;
	std::cout << detaljni.getCurrentStudents().size() << std::endl;
	std::cout << detaljni.getPassedStudents().size() << std::endl;
	std::cout << studenti[0].getPassCourses()[0].getGrade() << std::endl;
	//auto x = detaljni.getCurrentStudents();*/
	//for (auto el : x)
		//std::cout << el << std::endl;

	//CourseRegisterManager regManager(preduslovi);
	//regManager.enrollToCourse(studenti[0], kursevi[0]);




	//CourseReq zahtjev(kursevi[0].getId(), "#1");
	//CourseReqFileIO crScanner("#1");
	//std::vector<CourseReq> zahtjevi;
	//crScanner.readAllCourseReq(zahtjevi);

	//std::cout << zahtjevi[0].getStudentId() << std::endl;
	//crScanner.writeCourseReq(zahtjev);*/
}

void pocetna()
{
	using namespace learningPlatform;
	std::vector<Course> kursevi;
	std::vector<Professor> professors;
	std::vector<Student> students;
	std::vector<CoursePrecondtion*> preduslovi;
	std::vector<User*>users;
	ProfessorFileIO scanner;
	scanner.readAllUser(professors);
	CourseInfoFileIO scan(professors);
	scan.readAllCourses(kursevi);
	StudentFileIO scan1;
	scan1.readAllUser(students, kursevi);
	hf::mergeVector(users, students, professors);
	//hf::setNextId(students, professors);
	User* user = Login::loginMenu(users);
	FriendReqManager manager;
	Student* ptr = dynamic_cast<Student*>(user);
	manager.getFriendsForUser(*ptr, students);
}

int main()
{
	using namespace learningPlatform;
	std::vector<Course> kursevi;
	std::vector<Professor> professors;
	std::vector<Student> students;
	std::vector<User*>users;
	std::vector<CoursePrecondtion*> precondtions;//dinamicki osloboditi
	ProfessorFileIO scanner;
	CourseInfoFileIO scan(professors);
	StudentFileIO scan1;
	CoursePrecondtionFileIO cpScanner;
	try
	{
		scanner.readAllUser(professors);
		scan.readAllCourses(kursevi);
		scan1.readAllUser(students, kursevi);
		cpScanner.readAllCoursePrecondtion(precondtions);
	}
	catch (std::exception)
	{
		std::cout << "Greska prilikom ucitavanja ulaznih podataka!!" << std::endl;
		exit(-1);
	}

	CoursePrecondtion::setLastId(hf::lastIdPre(precondtions));
	hf::mergeVector(users, students, professors);
	User::setLastId(hf::lastId(students, professors));
	Admin admin("admin", "admin", "/", "/", Date(), Genders::NOT_DEFINED, "/");
	users.push_back(&admin);

	User* user = Login::loginMenu(users);
	Student* stud = dynamic_cast<Student*>(user);
	Professor* prof = dynamic_cast<Professor*>(user);
	Admin* adm = dynamic_cast<Admin*>(user);
	if (stud != nullptr)
	{
		FriendReqManager manager;
		manager.getFriendsForUser(*stud, students);
		int opcija;
		do
		{
			system("CLS");
			std::cout << "===============================================================" << std::endl;
			std::cout << "                 -=Studentski nalog=-                          " << std::endl;
			std::cout << "-=Chat=-" << std::endl;
			std::cout << "	(1)Zapocni caskanje" << std::endl;
			std::cout << "	(2)Pregled inboks-a" << std::endl;
			std::cout << "-=Prijatelji=-" << std::endl;
			std::cout << "	(3)Pregled prijatelja" << std::endl;
			std::cout << "	(4)Pregled zahtjeva za prijateljstvo" << std::endl;
			std::cout << "	(5)Prihvati/Odbij zahtjev za prijateljstvo" << std::endl;
			std::cout << "	(6)Slanje zahtjeva za prijateljstvo" << std::endl;
			std::cout << "	(7)Uklanjanje prijateljstva" << std::endl;
			std::cout << "-=Kursevi=-" << std::endl;
			std::cout << "	(8)Pregled trenutnih kurseva" << std::endl;
			std::cout << "	(9)Pregled polozenih kurseva" << std::endl;
			std::cout << "	(10)Upis na kurs" << std::endl;
			std::cout << "-=Ostalo=-" << std::endl;
			std::cout << "	(11)Kraj" << std::endl;
			std::cout << "===============================================================" << std::endl;
			std::cout << "Unesite opciju:";
			std::cin >> opcija;
			if (opcija == 1)
			{
				std::vector<User*> allFriends;
				hf::getAllFriend(*stud, allFriends);
				Chat::chatInteraction(*stud, allFriends);
				std::this_thread::sleep_for(std::chrono::milliseconds(3000));
			}
			else if (opcija == 2)
			{
				std::vector<User*> allFriends;
				hf::getAllFriend(*stud, allFriends);
				Chat::showInbox(*stud, allFriends);
				std::this_thread::sleep_for(std::chrono::milliseconds(3000));
			}
			else if (opcija == 3)
			{
				FriendReqInteraction::showFriends(*stud);
				std::this_thread::sleep_for(std::chrono::milliseconds(3000));
			}
			else if (opcija == 4)
			{
				FriendReqInteraction::showFriendReq(*stud, manager, students);
				std::this_thread::sleep_for(std::chrono::milliseconds(3000));
			}
			else if (opcija == 5)
			{
				FriendReqInteraction::reqForFriendShip(*stud, manager, students);
				std::this_thread::sleep_for(std::chrono::milliseconds(3000));
			}
			else if (opcija == 6)
			{
				FriendReqInteraction::sendFriendReq(*stud, manager, students);
				std::this_thread::sleep_for(std::chrono::milliseconds(3000));
			}
			else if (opcija == 7)
			{
				FriendReqInteraction::deleteFriend(*stud, manager);
				std::this_thread::sleep_for(std::chrono::milliseconds(3000));
			}
			else if (opcija == 8)
			{
				CourseStudentInteraction::showCurrCourses(*stud);
				std::this_thread::sleep_for(std::chrono::milliseconds(3000));
			}
			else if (opcija == 9)
			{
				CourseStudentInteraction::showPassCourses(*stud);
				std::this_thread::sleep_for(std::chrono::milliseconds(3000));
			}
			else if (opcija == 10)
			{
				CourseStudentInteraction::sendCourseReq(*stud, kursevi, precondtions);
				std::this_thread::sleep_for(std::chrono::milliseconds(3000));
			}
			else if (opcija == 11)
			{
				break;
			}
			else
			{
				std::cout << "Pogresan unos" << std::endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			}
		} while (opcija != 11);
	}
	else if (prof != nullptr)
	{
		int opcija;
		do
		{
			system("CLS");
			std::cout << "===============================================================" << std::endl;
			std::cout << "                 -=Profesorski nalog=-                          " << std::endl;
			std::cout << "-=Chat=-" << std::endl;
			std::cout << "	(1)Zapocni caskanje" << std::endl;
			std::cout << "	(2)Pregled inboks-a" << std::endl;
			std::cout << "-=Kursevi=-" << std::endl;
			std::cout << "	(3)Pregled zaduzenih kurseva" << std::endl;
			std::cout << "	(4)Pregled studenata na  kursevima" << std::endl;
			std::cout << "	(5)Zahtjevi za kurseve" << std::endl;
			std::cout << "	(6)Upis ocjene" << std::endl;
			std::cout << "-=Ostalo=-" << std::endl;
			std::cout << "	(7)Kraj" << std::endl;
			std::cout << "===============================================================" << std::endl;
			std::cout << "Unesite opciju:";
			std::cin >> opcija;
			if (opcija == 1)
			{
				std::vector<User*> userForChat;
				hf::getProfessorsFriend(*prof, students, userForChat);
				Chat::chatInteraction(*prof, userForChat);
				std::this_thread::sleep_for(std::chrono::milliseconds(3000));
			}
			else if (opcija == 2)
			{
				std::vector<User*> userForChat;
				hf::getProfessorsFriend(*prof, students, userForChat);
				Chat::showInbox(*prof, userForChat);
				std::this_thread::sleep_for(std::chrono::milliseconds(3000));
			}
			else if (opcija == 3)
			{
				system("CLS");
				CourseProfessorInteraction::showProfessorsCourses(*prof, kursevi);
				std::this_thread::sleep_for(std::chrono::milliseconds(3000));
			}
			else if (opcija == 4)
			{
				CourseProfessorInteraction::showStudentsOnCourses(*prof, kursevi, students);
				std::this_thread::sleep_for(std::chrono::milliseconds(3000));
			}
			else if (opcija == 5)
			{
				CourseProfessorInteraction::reqForCourse(*prof, kursevi, students);
				std::this_thread::sleep_for(std::chrono::milliseconds(3000));
			}
			else if (opcija == 6)
			{
				CourseProfessorInteraction::writeGrade(*prof, kursevi, students);
				std::this_thread::sleep_for(std::chrono::milliseconds(3000));
			}
			else if (opcija == 7)
			{
				break;
			}
			else
			{
				std::cout << "Pogresan unos" << std::endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			}
		} while (opcija != 7);
	}
	else if (adm != nullptr)
	{
		FriendReqManager manager;
		hf::getAllFriend(students, manager);
		Graph<Student*, std::string> graf = hf::createGraph(students);
		int opcija;
		do
		{
			system("CLS");
			std::cout << "===============================================================" << std::endl;
			std::cout << "                 -=Administratorski nalog=-                          " << std::endl;
			std::cout << "-=Nalozi=-" << std::endl;
			std::cout << "	(1)Pregled studenata" << std::endl;
			std::cout << "	(2)Pregled profesora" << std::endl;
			std::cout << "	(3)Kreiranje naloga" << std::endl;
			std::cout << "	(4)Brisanje naloga" << std::endl;
			std::cout << "	(5)Izmjena naloga" << std::endl;
			std::cout << "-=Kursevi=-" << std::endl;
			std::cout << "	(6)Pregled kurseva" << std::endl;
			std::cout << "	(7)Kreiranje kursa" << std::endl;
			std::cout << "	(8)Brisanje kursa" << std::endl;
			std::cout << "	(9)Izmjena kursa" << std::endl;
			std::cout << "	(10)Skupovne operacije sa kursevima" << std::endl;
			std::cout << "-=Prijateljstvo=-" << std::endl;
			std::cout << "	(11)Analiza prijateljstva" << std::endl;
			std::cout << "-=Ostalo=-" << std::endl;
			std::cout << "	(12)Kraj" << std::endl;
			std::cout << "===============================================================" << std::endl;
			std::cout << "Unesite opciju:";
			std::cin >> opcija;
			if (opcija == 1)
			{
				UserAdminInteraction::showStudents(students);
				std::this_thread::sleep_for(std::chrono::milliseconds(3000));
			}
			else if (opcija == 2)
			{
				UserAdminInteraction::showProfessors(professors);
				std::this_thread::sleep_for(std::chrono::milliseconds(3000));
			}
			else if (opcija == 3)
			{
				UserAdminInteraction::userCreate(professors, students);
				std::this_thread::sleep_for(std::chrono::milliseconds(3000));
			}
			else if (opcija == 4)
			{
				UserAdminInteraction::deleteUser(professors, students, kursevi);
				std::this_thread::sleep_for(std::chrono::milliseconds(3000));
			}
			else if (opcija == 5)
			{
				UserAdminInteraction::modifyUser(professors, students);
				std::this_thread::sleep_for(std::chrono::milliseconds(3000));
			}
			else if (opcija == 6)
			{
				CourseAdminInteraction::showCourses(kursevi);
				std::this_thread::sleep_for(std::chrono::milliseconds(3000));
			}
			else if (opcija == 7)
			{
				CourseAdminInteraction::createCourse(kursevi, precondtions, professors);
				std::this_thread::sleep_for(std::chrono::milliseconds(3000));
			}
			else if (opcija == 8)
			{
				CourseAdminInteraction::deleteCourse(kursevi, students, professors);
				std::this_thread::sleep_for(std::chrono::milliseconds(3000));
			}
			else if (opcija == 9)
			{
				CourseAdminInteraction::modifyCourse(kursevi, professors);
				std::this_thread::sleep_for(std::chrono::milliseconds(3000));
			}
			else if (opcija == 10)
			{
				CourseAdminInteraction::courseSetOperation(kursevi, students);
				std::this_thread::sleep_for(std::chrono::milliseconds(3000));
			}
			else if (opcija == 11)
			{
				FriendReqInteraction::graphAnalizer(students, graf);
				std::this_thread::sleep_for(std::chrono::milliseconds(3000));
			}
			else if (opcija == 12)
				break;
			else
			{
				std::cout << "Pogresan unos" << std::endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			}
		} while (opcija != 12);
	}
	for (auto& x : precondtions)
		delete x;


}



