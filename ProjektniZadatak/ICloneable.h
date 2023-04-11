#pragma once

namespace learningPlatform
{
	class ICloneable
	{
	public:
		virtual ICloneable* clone()const = 0;
	};
}
