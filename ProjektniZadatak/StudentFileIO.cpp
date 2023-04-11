#include"StudentFileIO.h"
#include<sstream>
#include<filesystem>

namespace learningPlatform
{
	namespace fs = std::filesystem;
	const std::string StudentFileIO::dirName = "students";
	const std::string StudentFileIO::fileName = "studenti.txt";
	const std::string StudentFileIO::currName = "currentCourses.txt";
	const std::string StudentFileIO::passName = "passedCourses.txt";

	StudentFileIO::StudentFileIO()
	{
		fs::path path = fs::current_path() / dirName;
		if (!fs::exists(path))
			fs::create_directories(path);
		this->dirPath = path;
		this->path = (this->dirPath) / fileName;
	};

	void StudentFileIO::writeOneUser(std::ostream& os, const Student& stud)const
	{
		os << stud.getId() << " " << stud.getUsername() << " "<< stud.getPassword()<<" "<< stud.getName() << " " <<
			stud.getSurname() << " " <<stud.getDateOfBirth() << " " << (int)stud.getGender() << " " <<
			stud.getEmail() <<" "<<stud.getIndex() << " " << (int)stud.getStudentStatus() << '\n';
	}

	void StudentFileIO::writeUser(const Student& stud)const
	{
		std::ofstream output(this->path, std::ios::app);
		if (!output)
			throw std::runtime_error("Greska prilikom otvaranja fajla");
		this->writeOneUser(output,stud);
		fs::create_directory(this->dirPath / (stud.getId()));
		fs::path path1 = this->dirPath / stud.getId() / currName;
		fs::path path2 = this->dirPath / stud.getId() / passName;
		std::ofstream create1(path1, std::ios::out);
		std::ofstream create2(path2, std::ios::out);
		create1.close();
		create2.close();
		output.close();
	}

	void StudentFileIO::writeAllUser(const std::vector<Student>& students)const
	{
		std::ofstream output(this->path, std::ios::out);
		if (!output)
			throw std::runtime_error("Greska prilikom otvaranja fajla");
		for (auto x : students)
			this->writeOneUser(output,x);
		output.close();
	}

	Student StudentFileIO::readOneUser(std::istream& in)const
	{
		std::string id, username, password, name, surname,email,index;
		Date dob;
		int gender,status;
		in >> id >> username >> password >> name >> surname >> dob >> gender >> email >> index >> status >> std::ws;
		return Student(username, password, id, name, surname,dob,(Genders)gender, email, index, (StudentStatus)status);
	}

	void StudentFileIO::readAllUser(std::vector<Student>& students,std::vector<Course>&courses)const
	{
		CourseStudentFileIO scanner;
		std::ifstream input(this->path, std::ios::in);
		if (!input)
			throw std::runtime_error("Greska prilikom otvaranja fajla");
		while (!input.eof())
		{
			Student temp = readOneUser(input);
			scanner.readAllStudentCurrCourses(temp,courses);
			scanner.readAllStudentPassCourses(temp,courses);
			students.push_back(temp);
		}
		input.close();
	}
}