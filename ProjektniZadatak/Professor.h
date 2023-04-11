#pragma once
#include "User.h"

namespace learningPlatform
{
	enum class Zvanja{ASISTENT,DOCENT,VANDREDNI_PROFESOR,REDOVNI_PROFESOR,NOT_DEFINIDED};
	class Professor:public User
	{
	private:
		std::string katedra;
		Zvanja zvanje;
	public:
		Professor();
		Professor(std::string, std::string, std::string, std::string, const Date&, const Genders&, std::string, std::string, const Zvanja&);
		Professor(std::string, std::string, std::string, std::string, std::string, const Date&, const Genders&, std::string, std::string, const Zvanja&);

		std::string getKatedra()const;
		Zvanja getZvanje()const;

		void setKatedra(const std::string&);
		void setZvanje(const Zvanja&);

		virtual Professor* clone()const override;
		virtual std::string getType()const override;
	protected:
		virtual std::ostream& print(std::ostream&)const override;

	};
}
