#include "rbtree.h"
#include <iostream>
#include <stdlib.h>

static inline void 
rbtree_left_rotate(rbtree_node_t **root, rbtree_node_t *sentinel,
        rbtree_node_t *node)
{
    rbtree_node_t *temp = NULL;

    temp = node->right;
    node->right = temp->left;

    if (temp->left != sentinel) {
        temp->left->parent = node;
    }

    temp->parent = node->parent;

    if (node == *root) {
        *root = temp;
    } else if (node == node->parent->left) {
        node->parent->left = temp;
    } else {
        node->parent->right = temp;
    }

    temp->left = node;
    node->parent = temp;
}

static inline void
rbtree_right_rotate(rbtree_node_t **root, rbtree_node_t *sentinel,
        rbtree_node_t *node)
{
    rbtree_node_t *temp = NULL;

    temp = node->left;
    node->left = temp->right;

    if (temp->right != sentinel) {
        temp->right->parent = node;
    }

    temp->parent = node->parent;

    if (node == *root) {
        *root = temp;
    } else if (node == node->parent->right) {
        node->parent->right = temp;
    } else {
        node->parent->left = temp;
    }

    temp->right = node;
    node->parent = temp;
}

void rbtree_insert(rbtree_t * tree, rbtree_node_t * node)
{
    rbtree_node_t   **root;
    rbtree_node_t    *temp = NULL;
    rbtree_node_t    *sentinel = NULL;

    /*a binary tree insert*/
    root = (rbtree_node_t **) &tree->root;
    sentinel = tree->sentinel;

    if (*root == sentinel) {
        node->parent = NULL;
        node->left = sentinel;
        node->right = sentinel;
        rbt_blcak(node);
        *root = node;

        return;
    }

    tree->insert(*root, node, sentinel);

    /*re-balance tree*/
    while (node != *root && rbt_is_red(node->parent)) {
        if (node->parent == node->parent->parent->left) {
            temp = node->parent->parent->right;

            if (rbt_is_red(temp)) {
                rbt_blcak(node->parent);
                rbt_blcak(temp);
                rbt_red(node->parent->parent);
                node = node->parent->parent;
            } else {
                if (node = node->parent->right) {
                    node = node->parent;
                    rbtree_left_rotate(root, sentinel, node);
                }

                rbt_blcak(node->parent);
                rbt_red(node->parent->parent);
                rbtree_right_rotate(root, sentinel, node);
            }
            
        } else  {
            temp = node->parent->parent->left;

            if (rbt_is_red(temp)) {
                rbt_blcak(node->parent);
                rbt_blcak(temp);
                rbt_red(node->parent->parent);
                node = node->parent->parent;
            } else {
                if (node == node->parent->left) {
                    node = node->parent;
                    rbtree_right_rotate(root, sentinel, node);
                }

                rbt_blcak(node->parent);
                rbt_red(node->parent->parent);
                rbtree_left_rotate(root, sentinel, node);
            }
        }
    }

    rbt_blcak(*root);
}

void rbtree_insert_value(rbtree_node_t * temp, rbtree_node_t * node, rbtree_node_t * sentinel)
{
    rbtree_node_t **p;

    for ( ;; ) {
        p = (node->key < temp->key) ? &temp->left : &temp->right;

        if (*p == sentinel) {
            break;
        }

        temp = *p;
    }

    *p = node;
    node->parent = temp;
    node->left = sentinel;
    node->right = sentinel;
    rbt_red(node);
}

void rbtree_insert_timer_value(rbtree_node_t *temp, rbtree_node_t * node, rbtree_node_t * sentinel)
{
    rbtree_node_t **p;

    for ( ;; ) {
        /*
         * Timer values
         * 1) are spread in small range, usually several minutes,
         * 2) and overflow each 49 days, if milliseconds are stored in 32 bits.
         * The comparison takes into account that overflow.
         */

        /*  node->key < temp->key */

        p = (node->key < temp->key) ? &temp->left : &temp->right;

        if (*p == sentinel) {
            break;
        }

        temp = *p;
    }

    *p = node;
    node->parent = temp;
    node->left = sentinel;
    node->right = sentinel;
    rbt_red(node);
}

void rbtree_delete(rbtree_t * tree, rbtree_node_t * node)
{
    uint32_t        red;
    rbtree_node_t   **root;
    rbtree_node_t   *sentinel = NULL;
    rbtree_node_t   *subst = NULL;
    rbtree_node_t   *temp = NULL;
    rbtree_node_t   *w = NULL;

    /* a binary tree delete */
    root = (rbtree_node_t **) &tree->root;
    sentinel = tree->sentinel;

    if (node->left == sentinel) {
        temp = node->right;
        subst = node;
    } else if (node->right == sentinel) {
        temp = node->left;
        subst = node;
    } else {
        subst = rbtree_min(node->right, sentinel);

        if (subst->left != sentinel) {
            temp = subst->left;
        } else {
            temp = subst->right;
        }
    }

    if (subst == *root) {
        *root = temp;
        rbt_blcak(temp);

        /*DEBUG stuff*/
        node->left = NULL;
        node->right = NULL;
        node->parent = NULL;
        node->key = 0;

        return;
    }

    red = rbt_is_red(subst);

    if (subst == subst->parent->left) {
        subst->parent->left = temp;
    } else {
        subst->parent->right = temp;
    }

    if (subst == node) {
        temp->parent = subst->parent;
    } else {
        if (subst->parent == node) {
            temp->parent = subst;
        } else {
            temp->parent = subst->parent;
        }

        subst->left = node->left;
        subst->right = node->right;
        subst->parent = node->parent;
        rbt_copy_color(subst, node);

        if (node == *root) {
            *root = subst;
        } else {
            if (node == node->parent->left) {
                node->parent->left = subst;
            } else {
                node->parent->right = subst;
            }
        }

        if (subst->left != sentinel) {
            subst->left->parent = subst;
        }

        if (subst->right != sentinel) {
            subst->right->parent = subst;
        }
    }

    /* DEBUG stuff */
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    node->key = 0;

    if (red) {
        return;
    }

    /* a delete fixup */
    while (temp != *root && rbt_is_black(temp)) {

        if (temp == temp->parent->left) {
            w = temp->parent->right;

            if (rbt_is_red(w)) {
                rbt_blcak(w);
                rbt_red(temp->parent);
                rbtree_left_rotate(root, sentinel, temp->parent);
                w = temp->parent->right;
            }

            if (rbt_is_black(w->left) && rbt_is_black(w->right)) {
                rbt_red(w);
                temp = temp->parent;
            } else {
                if (rbt_is_black(w->right)) {
                    rbt_blcak(w->left);
                    rbt_red(w);
                    rbtree_right_rotate(root, sentinel, w);
                    w = temp->parent->right; 
                }

                rbt_copy_color(w, temp->parent);
                rbt_blcak(temp->parent);
                rbt_blcak(w->right);
                rbtree_left_rotate(root, sentinel, temp->parent);
                temp = *root;
            }
        }else {
            w = temp->parent->left;

            if (rbt_is_red(w)) {
                rbt_blcak(w);
                rbt_red(temp->parent);
                rbtree_right_rotate(root, sentinel, temp->parent);
                w = temp->parent->left;
            }

            if (rbt_is_black(w->left) && rbt_is_black(w->right)) {
                rbt_red(w);
                temp = temp->parent;
            } else {
                if (rbt_is_black(w->left)) {
                    rbt_blcak(w->right);
                    rbt_red(w);
                    rbtree_left_rotate(root, sentinel, w);
                    w = temp->parent->left;
                }

                rbt_copy_color(w, temp->parent);
                rbt_blcak(temp->parent);
                rbt_blcak(w->left);
                rbtree_right_rotate(root, sentinel, temp->parent);
                temp = *root;
            }
        }
    }

    rbt_blcak(temp);
}
