#include"Login.h"

namespace learningPlatform
{
	User* Login::loginMenu(std::vector<User*>& users)
	{
		std::string username, password;
		int counter = 1;
		std::cout << "=============================================================================================" << std::endl;
		std::cout << "-=Dobro dosli na platformu za ucenje=-" << std::endl;
		std::cout << "\"Da bi koristili sistem trebate da se prijavite!!\"" << std::endl;
		std::cout << "==============================================================================================" << std::endl;
		while (counter <= 3)
		{
			std::cout << "Unesite username:";
			std::cin >> username;
			std::cout << "Unesite password:";
			std::cin >> password;
			auto it = std::find_if(users.begin(), users.end(),[&username](User* x)
			{
				return x->getUsername() == username;
			});
			if (it == users.end())
			{
				std::cout << "Nalog sa datim username ne postoji, pokusajte ponovo!!" << std::endl;
				counter++;
				continue;
			}
			if ((*it)->getPassword() == password)
			{
				std::cout << "Prijava uspjesna!!" << std::endl;
				return *it;
			}
			else
			{
				std::cout << "Pogresna lozinka!!" << std::endl;
				counter++;
			}
		}
		std::cout << "Prekoracen maksimalni broj prijava,pokusajte ponovo!!" << std::endl;
		exit(-1);

	}
}