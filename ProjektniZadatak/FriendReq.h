#pragma once
#include<iostream>
#include<string>
#include<vector>

namespace learningPlatform
{
	class FriendReq
	{
	private:
		std::string sender;
		std::string receiver;
		bool status;
	public:
		FriendReq();
		FriendReq(std::string, std::string, bool);

		std::string getSender()const;
		std::string getReceiver()const;
		bool getStatus()const;

		void setStatus(bool);
		bool operator==(const FriendReq&)const;
		bool operator!=(const FriendReq&)const;

		friend std::ostream& operator<<(std::ostream&, const FriendReq&);
		friend std::istream& operator>>(std::istream&, FriendReq&);

		
	};
	std::ostream& operator<<(std::ostream&, const FriendReq&);
	std::istream& operator>>(std::istream&, FriendReq&);
}
