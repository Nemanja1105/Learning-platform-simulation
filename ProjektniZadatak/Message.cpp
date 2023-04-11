#include"Message.h"

namespace learningPlatform
{

	Message::Message() :sender(""), receiver(""), text(""), dateOfSend() {};
	Message::Message(std::string sender, std::string receiver, std::string text) :sender(sender), receiver(receiver), text(text)
	{
		this->dateOfSend = Date::getCurrentDate();
	}

	std::string Message::getSender()const
	{
		return this->sender;
	}

	std::string Message::getReceiver()const
	{
		return this->receiver;
	}

	std::string Message::getText()const
	{
		return this->text;
	}

	Date Message::getDateOfSend()const
	{
		return this->dateOfSend;
	}

	void Message::setSender(const std::string& value)
	{
		this->sender = value;
	}

	void Message::setReceiver(const std::string& value)
	{
		this->receiver = value;
	}

	void Message::setText(const std::string& value)
	{
		this->text = value;
	}

	std::ostream& operator<<(std::ostream& os, const Message& mess)
	{
		os << mess.sender << " " << mess.receiver << " " << mess.dateOfSend << " " << mess.text;
		return os;
	}

	std::istream& operator>>(std::istream& in, Message& mess)
	{
		in >> mess.sender >> mess.receiver >> mess.dateOfSend;
		in.ignore(1);
		getline(in, mess.text, '\n');
		return in;
	}

}