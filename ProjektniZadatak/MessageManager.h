#pragma once
#include"Message.h"
#include"User.h"
#include<vector>
#include<fstream>
#include<filesystem>

namespace learningPlatform
{
	namespace fs = std::filesystem;
	class MessageManager
	{
	private:
		static const std::string dirName;
		fs::path dirPath;
	public:
		MessageManager();
		void sendMessage(const Message&);
		void readMessages(std::string, std::string,std::vector<Message>&);
		void readMessagesWithFilter(std::string, std::string,std::string, std::vector<Message>&);
		//funkcija vraca id svih korisnika sa kojima sam razmjenjivao poruke
		void getInbox(std::string, std::vector<std::string>&,std::vector<User*>&);
		
	};
}