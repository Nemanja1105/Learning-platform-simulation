#pragma once
#include"User.h"

namespace learningPlatform
{


	class Admin :public User
	{
	public:
		using User::User;
		virtual std::string getType()const override
		{
			return "Admin";
		}
		virtual Admin* clone()const override
		{
			return new Admin(*this);
		}
	protected:
		virtual std::ostream& print(std::ostream& os)const override {
			return os;
		}
	};
}
