#include "timer.h"
#include <stddef.h>

static rbtree_node_t event_timer_sentinel;
pthread_mutex_t event_timer_mutex;
rbtree_t event_timer_rbtree;
/*
 * the event timer rbtree may contain the duplicate keys, however,
 * it should not be a problem, because we use the rbtree to find
 * a minimum timer value only
 */

int event_timer_init(void)
{
    rbtree_init(&event_timer_rbtree, &event_timer_sentinel, 
                rbtree_insert_timer_value);

    mutex_lock_init(&event_timer_mutex);

    return 0;
}

uint64_t event_find_timer(void)
{
    int64_t timer;
    uint64_t now;
    rbtree_node_t *node, *root, *sentinel;

    if (event_timer_rbtree.root == &event_timer_sentinel) {
        std::cout << "event_timer_rbtree is empty" << std::endl;
        return TIMER_INFINITE;
    }

    do_mutex_lock(&event_timer_mutex);

    root = event_timer_rbtree.root;
    sentinel = event_timer_rbtree.sentinel;
    node = rbtree_min(root, sentinel);

    do_mutex_unlock(&event_timer_mutex);

    now = get_current_msec();
    timer = node->key - now;

    return (timer > 0 ? timer : 0);
}

void event_expire_timers(void)
{
    event_t         *ev;
    rbtree_node_t   *node, *root, *sentinel;
    uint64_t         now;

    sentinel = event_timer_rbtree.sentinel;

    for ( ;; ) {
        do_mutex_lock(&event_timer_mutex);

        root = event_timer_rbtree.root;
        if (root == sentinel) {
            break;
        }

        node = rbtree_min(root, sentinel);

        /* node->key <= current_time*/
        now = get_current_msec();
        int64_t res = node->key - now;
        if (res <= 0) {
            ev = (event_t *) ((char *)node - offsetof(event_t, timer));

            rbtree_delete(&event_timer_rbtree, &ev->timer);

            do_mutex_unlock(&event_timer_mutex);

            ev->timer.left = NULL;
            ev->timer.right = NULL;
            ev->timer.parent = NULL;
            ev->timer_set = 0;
            ev->timeout = 1;

            ev->handler(ev);
            
            continue;
        }

        break;
    }

    do_mutex_unlock(&event_timer_mutex);
}