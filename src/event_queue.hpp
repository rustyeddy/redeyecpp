#pragma once

#include <queue>
#include <semaphore>

#include "event.hpp"

using namespace std;


class EventQ
{
private:
    queue<Event*>       _q;
    counting_semaphore  _sem;

public:
    EventQ();
    
    Event*      next();
    void        add(Event* e);
}
