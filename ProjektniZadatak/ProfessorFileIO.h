#pragma once
#include "Professor.h"
#include<vector>
#include<filesystem>

namespace learningPlatform
{
	namespace fs = std::filesystem;
	class ProfessorFileIO
	{
	private:
		static const std::string dirName;
		static const std::string fileName;
		fs::path path;
	public:
		ProfessorFileIO();
		void writeUser(const Professor&)const;
		void writeAllUser(const std::vector<Professor>&)const;
		void readAllUser(std::vector<Professor>&)const;
	private:
		void writeOneUser(std::ostream&, const Professor&)const;
		Professor readOneUser(std::istream&)const;
	};
}
