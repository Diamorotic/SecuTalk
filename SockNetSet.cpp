#include "SockNetSet.h"

SockNetSet::SockNetSet(SockNet* s, SockNet* r)
{
    sending = s;
	receiving = r;
	sendingSttpQueue = NULL;
	receivingSttpQueue = NULL;
};

SockNetSet::SockNetSet()
{
	sending = NULL;
    receiving = NULL;
	sendingSttpQueue = NULL;
	receivingSttpQueue = NULL;
};
