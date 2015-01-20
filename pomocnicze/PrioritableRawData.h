#ifndef PRIORITABLE_RAW_DATA_H
#define PRIORITABLE_RAW_DATA_H

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

#endif /*PRIORITABLE_RAW_DATA_H*/
