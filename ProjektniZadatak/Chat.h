#pragma once
#include "Message.h"
#include "MessageManager.h"
#include "Student.h"
#include "Professor.h"
#include<map>

namespace learningPlatform
{
	class Chat
	{
	public:
		//funckija koja salje poruku korisniku kojeg smo proslijedili preko id
		static void sendMessage(const User& user1, const User& user2);
		static void showChat(const User&, const User&);
		static void showInbox(const User&, std::vector<User*>&);//prikazano
		static void showFilteredChat(const User&, const User&);

		//chat glavna funkcija
		static void chatInteraction(const User&, std::vector<User*>&);//prikazano
	private:
		static void printHeader();
		static void printFriends(const std::vector<User*>&);
		static User* getUser(std::string, std::vector<User*>&);
		static void printMessage(const User&,const User&,std::vector<Message>&);

	};
}
