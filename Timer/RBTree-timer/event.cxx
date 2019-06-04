#include "event.h"

void event_init(event_t *ev, unsigned int _fd, event_handler_pt _handler)
{
    ev->fd = _fd;
    ev->handler = _handler;
    ev->timeout = 0;
    ev->timer_set = 0;
}

