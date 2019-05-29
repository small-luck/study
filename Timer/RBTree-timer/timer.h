#ifndef _TIMER_H_
#define _TIMER_H_

#include "rbtree.h"
#include "utils.h"
#include "event.h"
#include <iostream>


#define TIMER_INFINITE      -1
#define TIMER_LAZY_DELAY    300


int event_timer_init(void);
uint64_t event_find_timer(void);
void event_expire_timers(void);

extern pthread_mutex_t *event_timer_mutex;


extern rbtree_t event_timer_rbtree;

static inline void
event_del_timer(event_t *ev) {
    std::cout << "event del timer" << std::endl;


    rbtree_delete(&event_timer_rbtree, &ev->timer);

    ev->timer.left = NULL;
    ev->timer.right = NULL;
    ev->timer.parent = NULL;
    
    ev->set = 0;
}

static inline void 
event_add_timer(event_t *ev, uint64_t timer)
{
    uint64_t key;
    int64_t  diff;
    uint64_t now;

    now = get_current_msec();

    key = now + timer;

    if (ev->set) {
        
        /*
         * Use a previous timer value if difference between it and a new
         * value is less than NGX_TIMER_LAZY_DELAY milliseconds: this allows
         * to minimize the rbtree operations for fast connections.
         */

        diff = key - ev->timer.key;
        if (abs(diff) < TIMER_LAZY_DELAY) {
            std::cout << "use previous timer" << std::endl;
            return;
        }

        
    }
}





#endif /*_TIMER_H_*/
