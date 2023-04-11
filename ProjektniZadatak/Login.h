#pragma once
#include<iostream>
#include<map>
#include"Student.h"
#include"Professor.h"

namespace learningPlatform
{
	class Login
	{
	public:
		static User* loginMenu(std::vector<User*>&);
	};
}
