#ifndef PRIORITABLE_RAWDATA_H
#define PRIORITABLE_RAWDATA_H


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
	};

	PrioritableRawData()
	{
		data = RawData();
		urgent = false;
	};
};


#endif