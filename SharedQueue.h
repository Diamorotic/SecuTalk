#ifndef SHARED_QUEUE
#define SHARED_QUEUE

#include "deklaracje.h"

template <class T>
class SharedQueue
{
	private:
	std::queue<T> q;     //w³aœciwa kolejka
	CRITICAL_SECTION* CS;
	CONDITION_VARIABLE* empty;

	public:
	SharedQueue()
	{
		CS = new CRITICAL_SECTION;
		empty = new CONDITION_VARIABLE;
		InitializeCriticalSectionAndSpinCount(CS,1);
		InitializeConditionVariable(empty);
	};

	~SharedQueue()
	{
		DeleteCriticalSection(CS);
		delete empty;
		delete CS;
	};

    void push(T const& t)
	{
		EnterCriticalSection (CS);
		q.push(t);
		LeaveCriticalSection(CS);
		WakeConditionVariable(empty);
	};

	T pull()
	{
		EnterCriticalSection (CS);
		if (q.empty())
			SleepConditionVariableCS(empty, CS, INFINITE);

		T t = q.front();
		q.pop();

		return t;
	};

};

/*
template <typename T>
inline T const& Max (T const& a, T const& b)
{
    return a < b ? b:a;
}
*/

#endif
