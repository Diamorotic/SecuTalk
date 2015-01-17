#include "RawData.h"


class PrioritableRawData
{
	public:
	RawData data;
	bool urgent;
	
	PrioritableRawData(RawData d, bool urg)
	{
		data = d;
		urgent = urg;
	}
};