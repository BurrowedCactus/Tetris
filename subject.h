#ifndef _SUBJECT_H_
#define _SUBJECT_H_
#include <vector>
#include "observer.h"
#include "info.h"

class Subject {
	std::vector<Observer*> observers;

public:
	Subject();
	void attach(Observer *o);
	void detach(Observer *o);
	void notifyObservers();
	virtual ~Subject()=0;
	virtual Info getInfo() const = 0;
};

#endif
