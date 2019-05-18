#ifndef _TIMER_H_
#define _TIMER_H_

#include "rbtree.h"
#include "utils.h"
#include "event.h"
#include <iostream>


#define TIMER_INFINITE      -1
#define TIMER_LAZY_DELAY    300

typedef uint64_t msec_t;

int event_timer_init(void);
msec_t event_find_timer(void);
void event_expire_timers(void);

extern pthread_mutex_t *event_timer_mutex;


extern rbtree_t event_timer_rbtree;

static inline void
event_del_timer(event_t *ev) {
    std::cout << "event del timer" << std::endl;

    mutex_lock(event_timer_mutex);

    rbtree_delete(&event_timer_rbtree, &ev->timer);

    mutex_unlock(event_timer_mutex);    
}




#endif /*_TIMER_H_*/
