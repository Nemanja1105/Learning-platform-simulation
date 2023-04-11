#pragma once
#include"Student.h"
#include"FriendReq.h"
#include"FriendReqManager.h"
#include"CoursePrecondition.h"
#include"Graph.h"
namespace learningPlatform
{
	class FriendReqInteraction
	{
	public:
		virtual ~FriendReqInteraction() = 0;//onemogucavanje kreiranja objekta
		static void showFriends(const Student&);//stavljeno
		static void showFriendReq(const Student&, FriendReqManager&, const std::vector<Student>&);//stavljeno
		static void reqForFriendShip(Student&,FriendReqManager&, std::vector<Student>&);//stavljeno
		static void sendFriendReq(Student&, FriendReqManager&, std::vector<Student>&);//stavljeno
		static void deleteFriend(Student&, FriendReqManager&);//stavljeno
		static void graphAnalizer(std::vector<Student>&,Graph<Student*,std::string>&);
	private:
		static void printHeader();
		static void printFooter();
		static void printStudent(const Student&);
		static const Student& getStudent(std::string, const std::vector<Student>&);
		static bool contain(Student&, std::vector<Student*>&);
		static CoursePrecondtion* precondtionChoise();
		

	};
}