#include "event_queue.hpp"

#include "event.hpp"

EventQ::EventQ
{
}

void EventQ::add(Event* ev)
{
    _sem.acquire();
    _q.push(ev);
    _sem.release();
}

Event* EventQ::next()
{
    _sem.acquire();
    assert(_q.size() > 0);
    Event* e = _q.front();
    _q.pop();
    _sem.release();

    return e;
}
