#include "User.h"
#include<sstream>
#include<iomanip>

namespace learningPlatform
{
	std::string User::lastId = "#0";
	User::User() :username(""), password(""), id("#"), name(""), surname(""),
		dateOfBirth(), gender(Genders::NOT_DEFINED), email("") {};

	User::User(std::string username, std::string password, std::string name, std::string surname, const Date& dob, const Genders& gender, std::string email) :
		username(username), password(password), name(name), surname(surname), dateOfBirth(dob), gender(gender), email(email)
	{
		this->id = User::generateId();
	}

	User::User(std::string username, std::string password, std::string id, std::string name, std::string surname, const Date& dob, const Genders& gender, std::string email) :
		username(username), password(password), id(id), name(name), surname(surname), dateOfBirth(dob), gender(gender), email(email) {};

	std::string User::getUsername()const
	{
		return this->username;
	}

	std::string User::getPassword()const
	{
		return this->password;
	}

	std::string User::getId()const
	{
		return this->id;
	}

	std::string User::getName()const
	{
		return this->name;
	}

	std::string User::getSurname()const
	{
		return this->surname;
	}

	Date User::getDateOfBirth()const
	{
		return this->dateOfBirth;
	}

	Genders User::getGender()const
	{
		return this->gender;
	}

	std::string User::getEmail()const
	{
		return this->email;
	}

	std::string User::getLastId()
	{
		return User::lastId;
	}

	void User::setId(const std::string& value)
	{
		this->id = value;
	}

	void User::setUsername(const std::string& value)
	{
		this->username = value;
	}

	void User::setPassword(const std::string& value)
	{
		this->password = value;
	}

	void User::setName(const std::string& value)
	{
		this->name = value;
	}

	void User::setSurname(const std::string& value)
	{
		this->surname = value;
	}

	void User::setDateOfBirth(const Date& value)
	{
		this->dateOfBirth = value;
	}

	void User::setGender(const Genders& value)
	{
		this->gender = value;
	}

	void User::setEmail(const std::string& value)
	{
		this->email = value;
	}

	void User::setLastId(const std::string& value)
	{
		User::lastId = value;
	}

	bool User::operator==(const User& other)const
	{
		return this->id == other.id;
	}

	bool User::operator!=(const User& other)const
	{
		return !((*this) == other);
	}


	std::string User::generateId()
	{
		std::string temp = User::lastId;
		std::string number = temp.substr(1);//0 je taraba
		std::stringstream stream(number);
		int iNum = -1;
		stream >> iNum; iNum++;
		std::string newId = "#" + std::to_string(iNum);
		User::lastId=newId;
		return newId;
	}

	std::ostream& User::print(std::ostream& os)const
	{
		os << std::left << std::setw(5) << this->id << " " << std::left << std::setw(10) << this->name << " " << std::left << std::setw(12)
			<< this->surname << " " << std::left << this->dateOfBirth <<" "<< std::left << std::setw(6);
		if (this->gender == Genders::MALE)
			os << "Muski" << " ";
		else
			os << "Zenski" << " ";
		return os;
	}


}