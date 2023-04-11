#pragma once
#include<iostream>

namespace learningPlatform
{
	class IPrintable
	{
	public:
		friend std::ostream& operator<<(std::ostream&, const IPrintable&);
	protected:
		virtual std::ostream& print(std::ostream&)const = 0;
	};
	std::ostream& operator<<(std::ostream&, const IPrintable&);
}
