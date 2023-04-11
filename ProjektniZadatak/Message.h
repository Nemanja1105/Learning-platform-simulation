#pragma once
#include<string>
#include"Date.h"

namespace learningPlatform
{
	class Message
	{
	private:
		std::string sender;
		std::string receiver;
		std::string text;
		Date dateOfSend;
	public:
		Message();
		Message(std::string, std::string, std::string);

		std::string getSender()const;
		std::string getReceiver()const;
		std::string getText()const;
		Date getDateOfSend()const;

		void setSender(const std::string&);
		void setReceiver(const std::string&);
		void setText(const std::string&);

		friend std::ostream& operator<<(std::ostream&, const Message&);
		friend std::istream& operator>>(std::istream&, Message&);
	};
	std::ostream& operator<<(std::ostream&, const Message&);
	std::istream& operator>>(std::istream&, Message&);
}
