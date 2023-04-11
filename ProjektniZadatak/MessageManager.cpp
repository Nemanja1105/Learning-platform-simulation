#include "MessageManager.h"

namespace learningPlatform
{
	const std::string MessageManager::dirName = "chats";
	MessageManager::MessageManager()
	{
		fs::path dir = fs::current_path() / MessageManager::dirName;
		if (!fs::exists(dir))
			fs::create_directories(dir);
		this->dirPath = dir;
	}

	//kreira se fajl u odnosu ko prvi posalje poruku
	void MessageManager::sendMessage(const Message& mess)
	{
		fs::path path1 = this->dirPath / (mess.getSender() + "-" + mess.getReceiver()+".txt");
		fs::path path2 = this->dirPath / (mess.getReceiver() + "-" + mess.getSender() + ".txt");
		fs::path path;
		if (fs::exists(path1))
			path = path1;
		else if (fs::exists(path2))
			path = path2;
		else
			path = path1;//kreiranje

		std::ofstream output(path, std::ios::app);
		if (!output)
			throw std::runtime_error("Greska prilikom otvaranja fajla");
		output << mess << std::endl;
		output.close();
	}


	void MessageManager::readMessages(std::string id1, std::string id2, std::vector<Message>& chatHistory)
	{
		fs::path p1 = this->dirPath/(id1 + "-" + id2 + ".txt");
		fs::path p2 = this->dirPath / (id2 + "-" + id1 + ".txt");
		fs::path path;
		if (fs::exists(p1))
			path = p1;
		else if (fs::exists(p2))
			path = p2;
		else
			throw std::exception("Chat je prazan!!");
		std::ifstream input(path,std::ios::in);
		if (!input)
			std::runtime_error("Greska prilikom otvranja fajla!!");
		Message temp;
		while (input >> temp)
			chatHistory.push_back(temp);
		input.close();
	}

	void MessageManager::readMessagesWithFilter(std::string id1, std::string id2, std::string filter, std::vector<Message>& messages)
	{
		std::vector<Message> temp;
		this->readMessages(id1, id2, temp);
		std::copy_if(temp.begin(), temp.end(), std::back_inserter(messages), [&filter](const Message& m) {
			 size_t poz=m.getText().find(filter);
			 if (poz == std::string::npos)
				 return false;
			 return true;
		});
	}

	void MessageManager::getInbox(std::string id, std::vector<std::string>& inbox,std::vector<User*>&users)
	{
		fs::path temp = this->dirPath;
		for (auto x : fs::directory_iterator(temp))
		{
			std::string filename = x.path().filename().string();
			int poz = filename.find(".txt");
			filename.erase(poz, 4);
			int pozLine = filename.find('-');
			std::string id1 = filename.substr(0,pozLine);
			std::string id2 = filename.substr(pozLine+1, filename.size() - 1);
			std::string pushId;
			if (id == id1)
				pushId = id2;
			else if (id == id2)
				pushId = id1;
			auto it = std::find_if(users.begin(), users.end(), [&pushId](User* u) {return pushId == u->getId(); });
			if (it != users.end())
				inbox.push_back(pushId);
		}
	}
}