#pragma once
#include "FriendReq.h"
#include<string>
#include<vector>
#include<filesystem>

namespace learningPlatform
{
	namespace fs = std::filesystem;
	class FriendReqFileIO
	{
	private:
		static const std::string fileName;
		fs::path path;
	public:
		FriendReqFileIO();
		void writeFriendReq(const FriendReq&)const;
		void writeAllFriendReq(const std::vector<FriendReq>&)const;
		void readAllFriendReq(std::vector<FriendReq>&)const;

	};
}
