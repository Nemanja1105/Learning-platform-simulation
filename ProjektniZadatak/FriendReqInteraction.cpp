#include "FriendReqInteraction.h"
#include<iomanip>
#include<memory>

namespace learningPlatform
{
	void FriendReqInteraction::printHeader()
	{
		std::cout << "=============== ===============:======" << std::endl;
		std::cout << "IME             PREZIME         ID" << std::endl;
		std::cout << "=============== ===============:======" << std::endl;
	}

	void FriendReqInteraction::printFooter()
	{
		std::cout << "=============== ===============:======" << std::endl;
	}

	void FriendReqInteraction::printStudent(const Student& x)
	{
		std::cout << std::setw(15) << std::left << x.getName() << " " <<
			std::setw(15) << std::left << x.getSurname() << ":" << std::setw(15) << std::left
			<< x.getId() << std::endl;
	}

	void FriendReqInteraction::showFriends(const Student& stud)
	{
		system("CLS");
		std::cout << "============================================" << std::endl;
		std::cout << "\t-=Pregled prijatelja=-" << std::endl;
		printHeader();
		auto friends = stud.getFriends();
		if (friends.size() == 0)
		{
			std::cout << "Trenutno nemate prijatelja!!" << std::endl;
		}
		for (auto x : friends)
			printStudent(*(Student*)x);
		printFooter();
	}

	const Student& FriendReqInteraction::getStudent(std::string id, const std::vector<Student>& users)
	{
		auto it = std::find_if(users.begin(), users.end(), [&id](const Student& x)
		{
			return id == x.getId();
		});
		return (*it);
	}

	void FriendReqInteraction::showFriendReq(const Student& stud, FriendReqManager& manager, const std::vector<Student>& students)
	{
		system("CLS");
		std::vector<const FriendReq*> zahtjevi = manager.getFrindReqForUser(stud);
		std::cout << "============================================" << std::endl;
		std::cout << "\t-=Pregled zahtjeva za prijateljstvo=-" << std::endl;
		printHeader();
		if (zahtjevi.size() == 0)
			std::cout << "Trenutno nema novih zahtjeva!!" << std::endl;
		else
		{
			for (auto x : zahtjevi)
			{
				std::string id = x->getSender();
				const Student& temp = getStudent(id, students);
				printStudent(temp);
			}
		}
		printFooter();
		
	}

	void FriendReqInteraction::reqForFriendShip(Student& stud, FriendReqManager& manager, std::vector<Student>& students)
	{
		FriendReqInteraction::showFriendReq(stud, manager, students);
		std::vector<const FriendReq*> zahtjevi = manager.getFrindReqForUser(stud);
		if (zahtjevi.size() == 0)
			return;
		std::cout << "Da li zelite prihvati/odbiti neke od zahtjeva?" << std::endl;
		int opcija;
		do
		{
			std::cout << "DA(1)/NE(0):";
			std::cin >> opcija;
			if (opcija != 0 && opcija != 1)
				std::cout << "Pogresan unos!!" << std::endl;
		} while (opcija != 0 && opcija != 1);

		if (opcija == 0)
			return;
		std::cout << "Unesite id korisnika ciji zahtjev zelite prihvatiti!" << std::endl;;
		std::string id;
		Student* ptr = nullptr;
		while (true)
		{
			std::cout << "Unesite id:";
			std::cin >> id;
			auto it = std::find_if(students.begin(), students.end(), [&id](const Student& s)
			{
				return id == s.getId();
			});
			if (it == students.end())
				std::cout << "Ne postoji student sa unijetim id" << std::endl;
			else
			{
				ptr = &(*it);
				break;
			}
		}
		std::cout << "Da li zelite prihvatiti zahtjev?" << std::endl;
		do
		{
			std::cout << "DA(1)/NE(0):";
			std::cin >> opcija;
			if (opcija != 0 && opcija != 1)
				std::cout << "Pogresan unos!!" << std::endl;

		} while (opcija != 0 && opcija != 1);
		if (opcija == 1)
		{
			try
			{
				manager.acceptFriendReq(stud, *ptr);
			}
			catch (const std::invalid_argument& e)
			{
				std::cout << e.what() << std::endl;
			}
			std::cout << "Zahtjev za prijateljstvo prihvacen!!" << std::endl;
		}
		else if (opcija == 0)
		{
			try
			{
				manager.deleteFriendReq(stud, *ptr);
			}
			catch (const std::invalid_argument& e)
			{
				std::cout << e.what() << std::endl;
			}
			std::cout << "Zahtjev za prijateljstvo je odbijen!!" << std::endl;
		}
	}

	bool FriendReqInteraction::contain(Student& stud, std::vector<Student*>& students)
	{
		auto it = std::find_if(students.begin(), students.end(), [&stud](const Student* x) {
			return stud == *x;
		});
		if (it == students.end())
			return false;
		return true;
	}

	void FriendReqInteraction::sendFriendReq(Student& stud, FriendReqManager& manager, std::vector<Student>& students)
	{
		system("cls");
		std::vector<Student*> temp;
		for (auto &x : students)
			if (contain(x, stud.getFriends()) == false&&x!=stud)
				temp.push_back(&x);
		std::cout << "===================================================" << std::endl;
		std::cout << "\t-=Slanje zahtjeva za prijateljstvo=-" << std::endl;
		std::cout << "===================================================" << std::endl;
		printHeader();
		if (temp.size() == 0)
		{
			std::cout << "Trenutno nema novih korisnika!!" << std::endl;
			return;
		}
		for (auto& x : temp)
			printStudent(*x);
		printFooter();
		std::cout << "Unesite id korisnika kojem zelite poslati zahtjev za prijateljstvo?" << std::endl;
		std::string id;
		Student* ptr = nullptr;
		while (true)
		{
			std::cout << "Unesite id:";
			std::cin >> id;
			auto it = std::find_if(temp.begin(), temp.end(), [&id](const Student* s)
			{
				return id == s->getId();
			});
			if (it == temp.end())
				std::cout << "Ne postoji student sa unijetim id" << std::endl;
			else
			{
				ptr =(*it);
				break;
			}
		}
		try
		{
			manager.makeFriendReq(stud, *ptr);
		}
		catch (const std::invalid_argument& e)
		{
			std::cout << e.what() << std::endl;
			return;
		}
		std::cout << "Zahtjev uspjesno poslat!!" << std::endl;
	}
	
	void FriendReqInteraction::deleteFriend(Student& stud, FriendReqManager& manager)
	{
		system("CLS");
		std::cout << "==============================================" << std::endl;
		std::cout << "\t-=Brisanje prijatelja=-" << std::endl;
		std::cout << "==============================================" << std::endl;
		showFriends(stud);
		std::vector<Student*>&temp = stud.getFriends();
		std::cout << "Unesite id korisnika kojeg zelite ukloniti iz prijatelja!!" << std::endl;
		if (temp.size() == 0)
			return;

		std::string id;
		Student* ptr = nullptr;
		while (true)
		{
			std::cout << "Unesite id:";
			std::cin >> id;
			auto it = std::find_if(temp.begin(), temp.end(), [&id](const Student* s)
			{
				return id == s->getId();
			});
			if (it == temp.end())
				std::cout << "Ne postoji prijatelj sa unijetim id" << std::endl;
			else
			{
				ptr = (*it);
				break;
			}
		}
		int opcija;
		std::cout << "Da li zelite obrisati prijatelja?" << std::endl;
		do
		{
			std::cout << "DA(1)/NE(0):";
			std::cin >> opcija;
			if (opcija != 0 && opcija != 1)
				std::cout << "Pogresna opcija!!" << std::endl;
		} while (opcija != 0 && opcija != 1);
		if (opcija == 1)
		{
			try
			{
				manager.deleteFriendReq(stud, *ptr);
			}
			catch (const std::invalid_argument& e)
			{
				std::cout << e.what() << std::endl;
				return;
			}
			std::vector<Student*>& temp = stud.getFriends();
			temp.erase(std::remove_if(temp.begin(), temp.end(), [&ptr](const Student* x) {return ptr->getId() == x->getId(); }));
			std::cout << "Prijatelj uspjesno uklonjen!!" << std::endl;
		}

	}

	void FriendReqInteraction::graphAnalizer(std::vector<Student>& students,Graph<Student*, std::string>&grafPrijateljstva)
	{
		
		system("CLS");
		std::cout << "===================================================" << std::endl;
		std::cout << "         -=Operacije sa grafom poznanstva=-        " << std::endl;
		std::cout << "===================================================" << std::endl;
		std::cout << "Operacije:" << std::endl;
		std::cout << "(1)Najkraca putanja izmedju dvije osobe" << std::endl;
		std::cout << "(2)Prosjecna najkraca putanja izmedju osoba koja zadovoljavaju krajnji i pocetni uslov" << std::endl;
		int opcija;
		do
		{
			std::cout << "Unesite opciju:";
			std::cin >> opcija;
			if (opcija != 1 && opcija != 2)
				std::cout << "Pogresan unos!" << std::endl;
		} while (opcija != 1 && opcija != 2);
		if (opcija == 1)
		{
			system("CLS");
			std::cout << "Unesite id dva studenta!!"<<std::endl;
			std::string id1, id2;
			std::vector<Student>::iterator it1;
			std::vector<Student>::iterator it2;
			while (true)
			{
				std::cout << "Unesite prvi id:";
				std::cin >> id1;
				std::cout << "Unesite drugi id:";
				std::cin >> id2;
				it1 = std::find_if(students.begin(), students.end(), [&id1](Student& s) {return s.getId() == id1; });
				it2 = std::find_if(students.begin(), students.end(), [&id2](Student& s) {return s.getId() == id2; });
				if (it1 == students.end() || it2 == students.end())
					std::cout << "Pogresan unos!" << std::endl;
				else
					break;
			}
			std::cout << "Najkraca putanja poznanstva izmedju studenata sa unijetim id:" <<
				grafPrijateljstva.shortestDistance(grafPrijateljstva, id1, id2) << std::endl;
		}
		else if (opcija == 2)
		{
			system("CLS");
			std::cout << "========================================================" << std::endl;
			std::cout << "Izaberite pocetne preduslove!!" << std::endl;
			std::cout << "(1)Student polozio kurs A" << std::endl;
			std::cout << "(2)Student polozio minimalni broj kurseva" << std::endl;
			std::cout << "========================================================" << std::endl;
			std::cout << "Izaberite preduslov za pocetnog studenta!" << std::endl;
			CoursePrecondtion* prec1 = precondtionChoise();
			std::cout << "Izaberite preduslov za krajnjeg studenta!" << std::endl;
			CoursePrecondtion* prec2 = precondtionChoise();

			int br = 0,suma=0;
			auto vec = grafPrijateljstva.getAdjacencyMatrixW();
			grafPrijateljstva.warshallAlgorithm(vec);
			int n = vec.size();
			for (int i = 0; i < n; i++)
			{
				if ((*prec1)(*grafPrijateljstva[i]) == true)
				{
					for (int j = 0; j < n; j++)
					{
						if (i != j && (*prec2)(*grafPrijateljstva[j]))
						{
							if (vec[i][j] != INT_MAX)
							{
								suma += vec[i][j];
								br++;
							}
						}	
					}
				}
			}
			double avg;
			if (br == 0)
				avg = 0;
			else
				avg = (double)suma / br;
			delete prec1; delete prec2;
			std::cout << "Prosjecna najkraca putanja:" << avg << std::endl;
		}
		
	}

	CoursePrecondtion* FriendReqInteraction::precondtionChoise()
	{
		int opcija;
		std::string id;
		do
		{
			std::cout << "Unesite opciju:";
			std::cin >> opcija;
			if (opcija != 1 && opcija != 2)
				std::cout << "Pogresan unos" << std::endl;
		} while (opcija != 1 && opcija != 2);
		if (opcija == 1)
		{
			std::cout << "Unesite id kursa koji treba biti polozen:";
			std::cin >> id;
			return new CoursePassed(id);
		}
		else if (opcija == 2)
		{
			int br;
			std::cout << "Unesite minimalni broj kurseva koji trebaju biti polozeni:";
			std::cin >> br;
			return new NumberOfPassedCourse(br);

		}
		
	}
}