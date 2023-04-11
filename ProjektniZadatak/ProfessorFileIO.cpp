#include"ProfessorFileIO.h"
#include<fstream>

namespace learningPlatform
{
	const std::string ProfessorFileIO::dirName = "professors";
	const std::string ProfessorFileIO::fileName = "profesori.txt";
	ProfessorFileIO::ProfessorFileIO() :path(path)
	{
		fs::path path = fs::current_path() / dirName;
		if (!fs::exists(path))
			fs::create_directories(path);
		this->path = (path) / fileName;
	};

	void ProfessorFileIO::writeOneUser(std::ostream& os, const Professor& prof)const
	{
		os << prof.getId() << " " << prof.getUsername() << " " << prof.getPassword() << " " << prof.getName() << " " <<
			prof.getSurname() << " " << prof.getDateOfBirth() << " " << (int)prof.getGender() << " " <<
			prof.getEmail() << " " << prof.getKatedra() << " " << (int)prof.getZvanje() << '\n';
	}

	void ProfessorFileIO::writeUser(const Professor& stud)const
	{
		std::ofstream output(this->path, std::ios::app);
		if (!output)
			throw std::runtime_error("Greska prilikom otvaranja fajla");
		this->writeOneUser(output, stud);
		output.close();
	}

	void ProfessorFileIO::writeAllUser(const std::vector<Professor>& prof)const
	{
		std::ofstream output(this->path, std::ios::out);
		if (!output)
			throw std::runtime_error("Greska prilikom otvaranja fajla");
		for (auto x : prof)
			this->writeOneUser(output, x);
		output.close();
	}

	Professor ProfessorFileIO::readOneUser(std::istream& in)const
	{
		std::string id, username, password, name, surname, email, katedra;
		Date dob;
		int gender, zvanje;
		in >> id >> username >> password >> name >> surname >> dob >> gender >> email >> katedra >> zvanje >> std::ws;
		return Professor(username, password, id, name, surname, dob, (Genders)gender, email, katedra, (Zvanja)zvanje);
	}

	void ProfessorFileIO::readAllUser(std::vector<Professor>& prof)const
	{
		std::ifstream input(this->path, std::ios::in);
		if (!input)
			throw std::runtime_error("Greska prilikom otvaranja fajla");
		while (!input.eof())
		{
			Professor temp = readOneUser(input);
			prof.push_back(temp);
		}
		input.close();
	}


}