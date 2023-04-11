#pragma once
#include<string>
#include"Professor.h"
#include"IPrintable.h"


namespace learningPlatform
{
	class Course:public IPrintable
	{
	private:
		std::string id;
		std::string name;
		std::string katedra;
		Professor* professorId;
	public:
		Course();
		Course(std::string, std::string, std::string, Professor&);

		std::string getId()const;
		std::string getName()const;
		std::string getKatedra()const;
		Professor* getProfessor()const;

		void setId(const std::string&);
		void setName(const std::string&);
		void setKatedra(const std::string&);
		void setProfessor(Professor&);

		bool operator==(const Course&)const;
		bool operator!=(const Course&)const;
	protected:
		virtual std::ostream& print(std::ostream&)const override;
	};
}
