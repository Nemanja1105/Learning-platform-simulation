#include"Professor.h"
#include<iomanip>

namespace learningPlatform
{
	Professor::Professor() :User(), katedra(""), zvanje(Zvanja::NOT_DEFINIDED) {};
	Professor::Professor(std::string username, std::string password, std::string name, std::string surname, const Date& dob, const Genders& gender, std::string email, std::string katedra, const Zvanja& zvanje) :
		User(username, password, name, surname, dob, gender, email), katedra(katedra), zvanje(zvanje) {
		this->username = this->username + this->id;
	};

	Professor::Professor(std::string username, std::string password, std::string id, std::string name, std::string surname, const Date& dob, const Genders& gender, std::string email, std::string katedra, const Zvanja& zvanje) :
		User(username, password, id, name, surname, dob, gender, email), katedra(katedra), zvanje(zvanje) {};

	std::string Professor::getKatedra()const
	{
		return this->katedra;
	}

	Zvanja Professor::getZvanje()const
	{
		return this->zvanje;
	}

	void Professor::setKatedra(const std::string& value)
	{
		this->katedra = value;
	}

	void Professor::setZvanje(const Zvanja& value)
	{
		this->zvanje = value;
	}

	Professor* Professor::clone()const
	{
		return new Professor(*this);
	}

	std::string Professor::getType()const
	{
		return "PROF";
	}

	std::ostream& Professor::print(std::ostream& os)const
	{
		User::print(os);
		os << std::left << std::setw(9);
		if (this->zvanje == Zvanja::ASISTENT)
			os << "Asistent";
		else if (this->zvanje == Zvanja::DOCENT)
			os << "Docent";
		else if (this->zvanje == Zvanja::VANDREDNI_PROFESOR)
			os << "Vand_Prof";
		else
			os << "Red_Prof";
		os << " " << std::right << std::setw(7) << this->katedra;
		return os;
	}
}