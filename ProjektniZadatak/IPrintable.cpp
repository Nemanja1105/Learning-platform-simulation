#include "IPrintable.h"

namespace learningPlatform
{
	std::ostream& operator<<(std::ostream& os, const IPrintable& ip)
	{
		return ip.print(os);
	}
}