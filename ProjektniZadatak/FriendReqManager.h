#pragma once
#include<map>
#include"FriendReq.h"
#include"Student.h"
#include"FriendReqFileIO.h"

namespace learningPlatform
{
	class FriendReqManager
	{
	private:
		std::vector<FriendReq> requirements;
		FriendReqFileIO scanner;
	public:
		//konstruktor ocitava zahtjeve i prijateljstva iz fajl sistema
		FriendReqManager();
		//salje se zahtjev
		void makeFriendReq(const Student&, const Student&);
		//odbijanje zahtjeva, korisnik je pregledao listu za zahtjeve i proslijedio je odgovarajuce id
		//takodje se moze koristti za brisanje prijatelja
		void deleteFriendReq(const Student&,const Student&);

		//funkcija za prihvacanje zahtjeva na osnovu id studenta
		//sender-receiver
		void acceptFriendReq(Student&,Student&);

		//vraca vector prijatelja(id) za nekog studenta
		void getFriendsForUser(Student&,std::vector<Student>&)const;
		//vraca vector zahtjeva za nekog studenta
		std::vector<const FriendReq*> getFrindReqForUser(const Student&)const;
	private:
		std::vector<FriendReq>::iterator searchFr(const FriendReq&);
		bool contain(const FriendReq&)const;
		void saveChanges()const;
		void saveFR(const FriendReq&)const;
	};
}