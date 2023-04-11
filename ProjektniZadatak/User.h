#pragma once
#include<string>
#include"Date.h"
#include"IPrintable.h"
#include"ICloneable.h"


namespace learningPlatform
{
	enum class Genders { MALE, FEMALE, NOT_DEFINED };
	class User:public virtual IPrintable,public virtual ICloneable
	{
	protected:
		static std::string lastId;

		std::string username;
		std::string password;
		std::string id;
		std::string name;
		std::string surname;
		Date dateOfBirth;
		Genders gender;
		std::string email;
	public:
		//konstruktori
		User();
		//konstruktor pri kreiranju objekta
		//samo administrator kreira korisnike, pa on moze odma da postavi pocetne sifre
		User(std::string, std::string, std::string, std::string, const Date&, const Genders&, std::string);
		//konstruktor za ucitavanje iz datoteke
		User(std::string, std::string, std::string, std::string, std::string, const Date&, const Genders&, std::string);
		virtual ~User() {};

		//geteri
		std::string getUsername()const;
		std::string getPassword()const;
		std::string getId()const;
		std::string getName()const;
		std::string getSurname()const;
		Date getDateOfBirth()const;
		Genders getGender()const;
		std::string getEmail()const;
		static std::string getLastId();

		//seteri
		void setId(const std::string&);
		void setUsername(const std::string&);//rijetko ce se koristiti
		void setPassword(const std::string&);
		void setName(const std::string&);
		void setSurname(const std::string&);
		void setDateOfBirth(const Date&);
		void setGender(const Genders&);
		void setEmail(const std::string&);
		static void setLastId(const std::string&);

		//operatori za poredjenje
		//poredjenje po id koji se automatski generise
		bool operator==(const User&)const;
		bool operator!=(const User&)const;

		virtual std::string getType()const = 0;
		
	protected:
		virtual std::ostream& print(std::ostream&)const override;
	private:
		static std::string generateId();
	};
}