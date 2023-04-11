#include"FriendReqFileIO.h"
#include<fstream>

namespace learningPlatform
{
	const std::string FriendReqFileIO::fileName = "zahtjevi.txt";
	FriendReqFileIO::FriendReqFileIO() 
	{
		this->path = fs::current_path() / "students" / fileName;
	};

	void FriendReqFileIO::writeFriendReq(const FriendReq& fr)const
	{
		std::ofstream output(this->path, std::ios::app);
		if (!output)
			throw std::runtime_error("Greska prilikom otvaranja datoteke!!");
		output << fr << std::endl;
		output.close();
	}

	void FriendReqFileIO::writeAllFriendReq(const std::vector<FriendReq>& frVector)const
	{
		std::ofstream output(this->path, std::ios::out);
		if (!output)
			throw std::runtime_error("Greska pilikom otvaranja datoteke!!");
		for (auto x : frVector)
			output << x << std::endl;
		output.close();
	}

	void FriendReqFileIO::readAllFriendReq(std::vector<FriendReq>& frVector)const
	{
		std::ifstream input(this->path, std::ios::in);
		if (!input)
			throw std::runtime_error("Greska prilikom otvaranja datoteke!!");
		FriendReq temp;
		while (input >> temp)
			frVector.push_back(temp);
		input.close();
	}
}