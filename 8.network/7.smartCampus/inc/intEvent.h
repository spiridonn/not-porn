#ifndef __INT_EVENT_H__
#define __INT_EVENT_H__

#include "eventImp.h"

class IntEvent: public EventImp
{
public:
	IntEvent(){}
	IntEvent(int _data): m_data(_data){}
	virtual ~IntEvent(){}

	int GetData() {return m_data;}
	int m_data;
};

#endif /* __INT_EVENT_H__ */

