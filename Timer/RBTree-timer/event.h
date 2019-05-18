#ifndef _EVEBT_H_
#define _EVEBT_H_

#include "rbtree.h"

typedef event_s event_t;

struct event_s {
    unsigned int fd;

    unsigned int set;

    unsigned int timeout;
    
    rbtree_node_t timer;
};


#endif /*_EVEBT_H_*/