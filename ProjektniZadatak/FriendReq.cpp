#include"FriendReq.h"

namespace learningPlatform
{
	FriendReq::FriendReq() :sender(""), receiver(""), status(false) {};
	FriendReq::FriendReq(std::string id1, std::string id2, bool status) :sender(id1), receiver(id2), status(status) {};

	std::string FriendReq::getSender()const
	{
		return this->sender;
	}

	std::string FriendReq::getReceiver()const
	{
		return this->receiver;
	}

	bool FriendReq::getStatus()const
	{
		return this->status;
	}

	void FriendReq::setStatus(bool value)
	{
		this->status = value;
	}

	bool FriendReq::operator==(const FriendReq& other)const
	{
		return (this->sender == other.sender && this->receiver == other.receiver)||
			(this->sender==other.receiver && this->receiver==other.sender);
	}

	bool FriendReq::operator!=(const FriendReq& other)const
	{
		return !((*this) == other);
	}

	std::ostream& operator<<(std::ostream& os, const FriendReq& fr)
	{
		os << fr.sender << " " << fr.receiver << " " << fr.status;
		return os;
	}

	std::istream& operator>>(std::istream& in, FriendReq& fr)
	{
		in >> fr.sender >> fr.receiver >> fr.status;
		return in;
	}

}