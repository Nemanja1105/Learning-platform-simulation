#pragma once
#include<vector>
#include"User.h"
#include"Graph.h"
#include"Student.h"
#include"Professor.h"
#include"CoursePrecondition.h"
#include"FriendReqManager.h"
#include"Admin.h"

namespace hf
{
	namespace lp = learningPlatform;
	void mergeVector(std::vector<lp::User*>& users, std::vector<lp::Student>& students, std::vector<lp::Professor>& professors)
	{
		for (lp::Student& x : students)
			users.push_back(&x);
		for (lp::Professor&x:professors)
			users.push_back(&x);
	}

	std::string lastId(std::vector<lp::Student>& students, std::vector<lp::Professor>& professors)
	{
		std::string id1;
		std::string id2;
		if (students.size() == 0)
			id1 = "#1";
		else
			id1 = students[students.size() - 1].getId();
		int k=0;
		if (professors.size() == 0)
			id2 = "#1";
		else
			id2 = professors[professors.size() - 1].getId();
		return std::max(id1, id2);
	}

	std::string lastIdPre(std::vector<lp::CoursePrecondtion*>& precondtions)
	{
		std::string id1;
		if (precondtions.size() == 0)
			id1 = "#1";
		else
			id1 = precondtions[precondtions.size() - 1]->getId();
		return id1;
	}

	void getAllFriend(std::vector<lp::Student>& students, lp::FriendReqManager& manager)
	{
		for (auto &x : students)
			manager.getFriendsForUser(x, students);
	
	}

	Graph<lp::Student*, std::string> createGraph(std::vector<lp::Student>& students)
	{
		Graph<lp::Student*, std::string> graph;
		for (lp::Student& x : students)
			graph.add(x.getId(), &x);
		for (auto &x : students)
		{
			auto& arr = x.getFriends();
			for (auto& el : arr)
				graph.connect(x.getId(), el->getId());
		}
		return graph;
	}

	void getAllFriend(lp::Student& stud,std::vector<lp::User*>& users)
	{
		for (auto& x : stud.getFriends())
			users.push_back(x);
		for (auto& x : stud.getCurrCourses())
			users.push_back(x->getProfessor());
	}

	void getProfessorsFriend(lp::Professor& prof, std::vector<lp::Student>& students, std::vector<lp::User*>& users)
	{
		for (auto&stud : students)
		{
			auto& arr = stud.getCurrCourses();
			for(auto&course:arr)
				if (*course->getProfessor() == prof)
				{
					users.push_back(&stud);
					break;
				}
		}
	}

	
}
