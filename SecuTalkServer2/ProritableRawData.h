#include "RawData.h"

//priorytety danych
#define HIGH true
#define LOW false

class PrioritableRawData
{
	public:
	RawData data;
	bool priority;
	
	PrioritableRawData(RawData d, bool pri)
	{
		data = d;
		priority = pri;
	}
};