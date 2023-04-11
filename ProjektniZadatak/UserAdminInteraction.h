#pragma once
#include"Student.h"
#include"Professor.h"
#include"StudentFileIO.h"
#include"ProfessorFileIO.h"
#include<vector>
#include<iostream>
#include<iomanip>

namespace learningPlatform
{
	class UserAdminInteraction
	{
	private:
		UserAdminInteraction();
	public:
		static void showStudents(std::vector<Student>&);//
		static void showProfessors(std::vector<Professor>&);//
		static void userCreate(std::vector<Professor>&, std::vector<Student>&);//
		static void deleteUser(std::vector<Professor>&, std::vector<Student>&,std::vector<Course>&);//
		static void modifyUser(std::vector<Professor>&, std::vector<Student>&);//
	private:
		static void createStudent(std::vector<Student>&);
		static void createProfessors(std::vector<Professor>&);
		static void inputUser(std::string&, std::string&, int&, std::string&, Date&);
		static void showAccTrait(std::string&, std::string&);
		//brisanje chat i brisanje zahtjeva je optimizovano
		//brisanje prijatelja i studenta iz kurseva nije(vrse se prebrisivanje)
		//todo u narednim verzijama
		static void deleteStudent(std::vector<Student>&);
		static void deleteProfessor(std::vector<Professor>&,std::vector<Course>&);
		static Professor& professorChoise(std::vector<Professor>&);
		static void modifyStudent(std::vector<Student>&);
		static void modifyProfessors(std::vector<Professor>&);
	};
}
