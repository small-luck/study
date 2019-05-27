#ifndef _RB_TREE_H_
#define _RB_TREE_H_

#include <iostream>
#include <iomanip>
using namespace std;

#define rb_parent(r)            ((r)->parent)
#define rb_color(r)             ((r)->color)
#define rb_is_red(r)            ((r)->color == RED)
#define rb_is_black(r)          ((r)->color == BLACK)
#define rb_set_black(r)         do { (r)->color = BLACK; } while(0)
#define rb_set_red(r)           do { (r)->color = RED; } while(0)
#define rb_set_parent(r, p)     do { (r)->parent = (p); } while(0)
#define rb_set_color(r,c)       do { (r)->color = (c); } while(0)

enum RBTColor{
    RED,
    BLACK
};

template<class T>
class RBTNode {
    public:
        RBTColor color;     //颜色
        T key;              //键值
        RBTNode *left;      //左孩子
        RBTNode *right;     //右孩子
        RBTNode *parent;    //父节点

        RBTNode(T value, RBTColor c, RBTNode *p, RBTNode *l, RBTNode *r):
            key(value), color(c), parent(), left(l), right(r) {}
};

template<class T>
class RBTree {
    private:
        RBTNode<T> *mroot;  //根节点


    public:
        RBTree();
        ~RBTree();

        //前序遍历红黑树
        void pre_order();
        //中序遍历红黑树
        void in_order();
        //后序遍历红黑树
        void post_order();

        //递归实现查找红黑树中键值为key的节点
        RBTNode<T> *search(T key);
        //非递归实现查找红黑树中键值为key的节点
        RBTNode<T> *iterative_search(T key);

        //查找最小节点：返回最小节点的键值
        T mininum();
        //查找最大节点：返回最大节点的键值
        T maxinum();

        //找节点x的后继节点，即查找红黑树中数据值大于该节点的最小节点
        RBTNode<T> *successor(RBTNode<T> *x);
        //找节点x的前驱节点，即查找红黑树中数据值小于该节点的最大节点
        RBTNode<T> *predecessor(RBTNode<T> *x);

        //将节点插入红黑树中
        void insert(T key);

        //删除节点
        void remove(T key);

        //销毁红黑树
        void destroy();

        //打印红黑树
        void print();

    private:
        //前序遍历红黑树
        void pre_order(RBTNode<T> *tree) const;
        //中序遍历红黑树
        void in_order(RBTNode<T> *tree) const;
        //后序遍历红黑树
        void post_order(RBTNode<T> *tree) const;

        //递归实现查找红黑树x中键值为key的节点
        RBTNode<T> *search(RBTNode<T> *x, T key) const;
        //非递归实现查找红黑树x中键值为key的节点
        RBTNode<T> *iterative_search(RBTNode<T> *x, T key) const;

        //查找最小节点：返回tree为根节点的红黑树的最小节点
        RBTNode<T> *mininum(RBTNode<T> *tree);
        //查找最大节点：返回tree为根节点的红黑树的最大节点
        RBTNode<T> *maxinum(RBTNode<T> *tree);

        //左旋
        void left_rotate(RBTNode<T>* &root, RBTNode<T>* x);
        //右旋
        void right_rotate(RBTNode<T>* &root, RBTNode<T>* y);
        //插入函数
        void insert(RBTNode<T>* &root, RBTNode<T>* node);
        //插入修正函数
        void insert_fixup(RBTNode<T>* &root, RBTNode<T>* node);
        //删除函数
        void remove(RBTNode<T>* &root, RBTNode<T>* node);
        //删除修正函数
        void remove_fixup(RBTNode<T>* &root, RBTNode<T> *node, RBTNode<T> *parent);

        //销毁红黑树
        void destroy(RBTNode<T>* &tree);

        //打印红黑树
        void print(RBTNode<T>* tree, T key, int direction);
};

#endif