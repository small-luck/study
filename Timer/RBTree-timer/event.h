#ifndef _EVEBT_H_
#define _EVEBT_H_

#include "rbtree.h"

typedef event_s event_t;

typedef void (*event_handler_pt) (event_t *ev);

struct event_s {
    unsigned int    fd;

    unsigned int    timer_set;

    unsigned int    timeout;
    
    rbtree_node_t   timer; 

    event_handler_pt handler;
};


#endif /*_EVEBT_H_*/