#ifndef SOCKNET_SET_H
#define SOCKNET_SET_H

#include "deklaracje.h"
#include "RawData.h"

class SockNet;


class SockNetSet
{
	public:
	SockNet* sending;
	SockNet* receiving;
	std::queue<RawData>* sendingSttpQueue;
	std::queue<RawData>* recevingSttpQueue;

	SockNetSet(SockNet* s, SockNet* r);
	SockNetSet();
};


#endif
