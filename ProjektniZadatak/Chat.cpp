#include "Chat.h"

namespace learningPlatform
{
	void Chat::sendMessage(const User& user1, const User& user2)
	{
		std::cout << "Unesite poruku:";
		std::string text;
		std::cin.get();
		std::getline(std::cin, text, '\n');
		Message novaPoruka(user1.getId(), user2.getId(), text);
		MessageManager manager;
		try
		{
			manager.sendMessage(novaPoruka);
		}
		catch (const std::runtime_error& e)
		{
			std::cout << e.what() << std::endl;
		}
		std::cout << "Poruka uspjesno poslata!!" << std::endl;
	}

	void Chat::printMessage(const User&user1,const User&user2,std::vector<Message>& messages)
	{
		for (auto x : messages)
		{
			if (x.getSender() == user1.getId())
				std::cout << user1.getName() << " " << user1.getSurname() << ":" << std::endl;
			else
				std::cout << user2.getName() << " " << user2.getSurname() << ":" << std::endl;
			std::cout << "\t" << x.getText() << std::endl;
			Date datum = x.getDateOfSend();
			std::cout << std::right << std::setw(30) << "(Poslato:" << datum << ")" << std::endl;
		}
	}
	//trenutni je user1, on je sender
	void Chat::showChat(const User& user1, const User& user2)
	{
		system("CLS");
		MessageManager manager;
		std::cout << "==================================================================" << std::endl;
		std::cout << "\tCHAT:" << user2.getName() << " " << user2.getSurname() << std::endl;
		std::cout << "==================================================================" << std::endl;
		std::vector<Message> messages;
		try
		{
			manager.readMessages(user1.getId(), user2.getId(), messages);
		}
		catch (const std::runtime_error& e)//greska pri otvaranju fajla
		{
			std::cout << e.what() << std::endl;
			return;
		}
		catch (const std::exception& e)//chat je prazan
		{
			std::cout << e.what() << std::endl;
			return;
		}

		Chat::printMessage(user1, user2, messages);
		std::cout << "==================================================================" << std::endl;
	}

	void Chat::printHeader()
	{
		std::cout << "=============== ===============:======" << std::endl;
		std::cout << "IME             PREZIME         ID" << std::endl;
		std::cout << "=============== ===============:======" << std::endl;
	}

	User* Chat::getUser(std::string id, std::vector<User*>& users)
	{
		auto it = std::find_if(users.begin(), users.end(),[&id](const User* x)
		{
			return id == x->getId();
		});
		return *it;
	}
	//user i njegovi prijatelji koji se dobiju na osnovu atribuna prijatelji + profesori na kursevima
	void Chat::showInbox(const User& user, std::vector<User*>& users)
	{
		system("CLS");
		std::cout << "====================================================" << std::endl;
		std::cout << "\t-=Pregled inboxa=-" << std::endl;
		std::cout << "\"Pregled svih korisnika sa kojima se razgovarali\"" << std::endl;
		std::cout << "====================================================" << std::endl << std::endl;
		MessageManager manager;
		std::vector<std::string> inbox;
		manager.getInbox(user.getId(), inbox,users);
		if (inbox.size() == 0)
		{
			std::cout << "Inbox je prazan!!" << std::endl;
			return;
		}
		Chat::printHeader();
		for (auto x : inbox)
		{
			User* ptr = Chat::getUser(x,users);
			std::cout << std::setw(15) << std::left << ptr->getName() << " " <<
				std::setw(15) << std::left << ptr->getSurname() << ":" << std::setw(15) << std::left
				<< ptr->getId() << std::endl;
		}
		std::cout << "=============== ===============:======" << std::endl;
		std::cout << "Da li zelite uci u chat sa nekim od korisnika!!" << std::endl;
		int opcija;
		do
		{
			std::cout << "DA(1) / NE(0) :";
			std::cin >> opcija;
			if (opcija != 0 && opcija != 1)
				std::cout << "Pogresna opcija!!" << std::endl;
		} while (opcija != 0 && opcija != 1);
		if (opcija == 1)
			Chat::chatInteraction(user, users);
	}

	//user i njegovi prijatelji koji se dobiju na osnovu atribuna prijatelji + profesori na kursevima
	void Chat::printFriends(const std::vector<User*>& friends)
	{
		Chat::printHeader();
		if (friends.size() == 0)
			std::cout << "Trenutno nemate prijatelja" << std::endl;
		else
		{
			for (auto x : friends)
				std::cout << std::setw(15) << std::left << x->getName() << " " <<
				std::setw(15) << std::left << x->getSurname() << ":" << std::setw(15) << std::left
				<< x->getId() << std::endl;
		}
		std::cout << "=============== ===============:======" << std::endl;
	}

	void Chat::showFilteredChat(const User& user1, const User& user2)
	{
		system("CLS");
		std::string filter;
		std::cout << "Unesite filter po kojem zelite da filtrirate poruke(rijec,znak):";
		std::cin >> filter;

		std::cout << "==================================================================" << std::endl;
		std::cout << "\tCHAT:" << user2.getName() << " " << user2.getSurname() << std::endl;
		std::cout << "==================================================================" << std::endl;
		MessageManager manager;
		std::vector<Message> messages;
		try
		{
			manager.readMessagesWithFilter(user1.getId(), user2.getId(),filter, messages);
		}
		catch (const std::runtime_error& e)//greska pri otvaranju fajla
		{
			std::cout << e.what() << std::endl;
			return;
		}
		catch (const std::exception& e)//chat je prazan
		{
			std::cout << e.what() << std::endl;
			return;
		}
		if (messages.size() == 0)
			std::cout << "Chat je prazan!!" << std::endl;
		else
			Chat::printMessage(user1, user2, messages);
		std::cout << "==================================================================" << std::endl;

	}

	void Chat::chatInteraction(const User& user, std::vector<User*>& users)
	{
		system("CLS");
		std::cout << "=================================================" << std::endl;
		std::cout << "\tIzabrali ste opciju za chat!!" << std::endl;
		std::cout << "=================================================" << std::endl;
		int opcija;
		do
		{
			std::cout << "Da li zelite pregledati listu vasih prijatelja?" << std::endl;
			std::cout << "DA(1) / NE(0) :";
			std::cin >> opcija;
			if (opcija != 0 && opcija != 1)
				std::cout << "Pogresna opcija!!" << std::endl;
		} while (opcija != 0 && opcija != 1);
		if (opcija == 1)
			Chat::printFriends(users);
		if (users.size() == 0)
			return;
		User* user1 = nullptr;
		while (true)
		{
			std::string id;
			std::cout << "Unesite id korisnika sa kojima zelite zapoceti chat:";
			std::cin >> id;
			auto it = std::find_if(users.begin(), users.end(), [&id](const User*x) 
			{
				return x->getId() == id;
			});
			if (it!=users.end())
			{
				user1 = *it;
				break;
			}
			else
				std::cout << "Ne postoji korisnik sa datim id sa kojim mozete razmjenjivati poruke!!!" << std::endl;
		}
		
		Chat::showChat(user, *user1);
		std::cout << "\t    -=Odaberite opciju=-" << std::endl;
		std::cout << "Nova poruku(1) | Filter poruka(2) | Kraj(3)" << std::endl;
		do
		{
			std::cout << "Opcija:";
			std::cin >> opcija;
			if (opcija != 1 && opcija != 2 && opcija!=3)
				std::cout << "Pogresna opcija!!" << std::endl;
		} while (opcija != 1 && opcija != 2&&opcija!=3);
		if (opcija == 1)
			Chat::sendMessage(user, *user1);
		else if (opcija == 2)
			Chat::showFilteredChat(user, *user1);
		else
			return;

	}

}