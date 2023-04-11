#include "FriendReqManager.h"

namespace learningPlatform
{
	FriendReqManager::FriendReqManager()
	{
		scanner.readAllFriendReq(this->requirements);
	}

	bool FriendReqManager::contain(const FriendReq& fr)const
	{
		auto it = std::find_if(this->requirements.begin(), this->requirements.end(), [&fr](const FriendReq& x)
		{
			return fr == x;
		});
		if (it == this->requirements.end())
			return false;
		return true;
	}

	std::vector<FriendReq>::iterator FriendReqManager::searchFr(const FriendReq& fr)
	{
		auto it = std::find_if(this->requirements.begin(), this->requirements.end(), [&fr](const FriendReq& x)
		{
			return fr == x;
		});
		return it;
	}

	void FriendReqManager::saveChanges()const
	{
		this->scanner.writeAllFriendReq(this->requirements);
	}

	void FriendReqManager::saveFR(const FriendReq& fr)const
	{
		this->scanner.writeFriendReq(fr);
	}

	void FriendReqManager::makeFriendReq(const Student& s1, const Student& s2)
	{
		if(&s1==&s2)
			throw std::invalid_argument("Ne mozete biti prijatelj sami sa sobom!!");
		FriendReq noviZahtjev(s1.getId(), s2.getId(), false);
		if(this->contain(noviZahtjev))
			throw std::invalid_argument("Zahtjev za prijateljstvo vec postoji!!");

		this->requirements.push_back(noviZahtjev);
		this->saveFR(noviZahtjev);
	}

	void FriendReqManager::deleteFriendReq(const Student& s1, const Student& s2)
	{
		if (&s1 == &s2)
			throw std::invalid_argument("Ne mozete biti prijatelj sami sa sobom!!");
		FriendReq test(s1.getId(), s2.getId(),false);
		auto it = this->searchFr(test);
		if (it == this->requirements.end())
			throw std::invalid_argument("Ne postoji zahtjev za prijateljestvo za date studente!!");
		this->requirements.erase(it);
		this->saveChanges();
	}

	void FriendReqManager::getFriendsForUser(Student& stud,std::vector<Student>&students)const
	{
		std::vector<std::string> temp;
		std::string id = stud.getId();
		for (auto x : this->requirements)
		{
			std::string id1 = "";
			if (id == x.getSender() && x.getStatus() == true)
				id1 = x.getReceiver();
			else if (id == x.getReceiver() && x.getStatus() == true)
				id1 = x.getSender();
			if (id1 != "")
			{
				auto it = std::find_if(students.begin(), students.end(), [&id1](const Student& x) {
					return id1 == x.getId();
				});
				stud.getFriends().push_back(&(*it));
			}
		}
	}

	std::vector<const FriendReq*> FriendReqManager::getFrindReqForUser(const Student& stud)const
	{
		std::vector<const FriendReq*> temp;
		std::string id = stud.getId();
		for (auto it=this->requirements.begin();it!=this->requirements.end();it++)
		{
			if (id == it->getReceiver() && it->getStatus() == false)
				temp.push_back(&(*it));
		}
		return temp;
	}

	//sender-receiver
	void FriendReqManager::acceptFriendReq(Student& s1,Student&s2)
	{
		FriendReq temp(s1.getId(), s2.getId(), false);
		auto it = this->searchFr(temp);
		if (it == this->requirements.end())
			throw std::invalid_argument("Ne postoji zahtjev za prijateljstvo za date studente");
		if (it->getStatus() == true)
			throw std::invalid_argument("Zahtjev je vec prihvacen!!");
		it->setStatus(true);
		this->saveChanges();
		s1.getFriends().push_back(&s2);
		s2.getFriends().push_back(&s1);
	}
}