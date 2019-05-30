#ifndef _EVEBT_H_
#define _EVEBT_H_

#include "rbtree.h"

struct event_s {
    unsigned int    fd:-1;

    unsigned int    timer_set:0;

    unsigned int    timeout:0;
    
    rbtree_node_t   timer; 

    event_handler_pt handler;
};

typedef event_s event_t;
typedef void (*event_handler_pt) (event_t *ev);

#endif /*_EVEBT_H_*/