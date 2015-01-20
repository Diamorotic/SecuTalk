#ifndef SOCKNET_SET_H
#define SOCKNET_SET_H

#include "deklaracje.h"
#include "RawData.h"
#include "SharedQueue.h"

class SockNet;


class SockNetSet
{
	public:
	SockNet* sending;
	SockNet* receiving;
	SharedQueue<RawData>* sendingSttpQueue;
	SharedQueue<RawData>* receivingSttpQueue;

	SockNetSet(SockNet* s, SockNet* r);
	SockNetSet();
};


#endif
