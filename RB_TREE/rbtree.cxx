#include "rbtree.h"

/*构造函数*/
template<class T>
RBTree<T>::RBTree():mroot(NULL)
{
    mroot = NULL;
}

/*析构函数*/
template<class T>
RBTree<T>::~RBTree()
{
    destroy();
}

/*前序遍历红黑树*/
template<class T>
void RBTree<T>::pre_order(RBTNode < T > * tree) const
{
    if (tree != NULL) {
        cout << tree->key << " ";
        pre_order(tree->left);
        pre_order(tree->right);
    }
}

template<class T>
void RBTree<T>::pre_order()
{
    pre_order(mroot);
}

/*中序遍历红黑树*/
void RBTree<T>::in_order(RBTNode < T > * tree) const
{
    if (tree != NULL) {
        in_order(tree->left);
        cout << tree->key << " ";
        in_order(tree->right);
    }
}

template<class T>
void RBTree<T>::in_order()
{
    in_order(mroot);
}

/*后序遍历红黑树*/
template<class T>
void RBTree<T>::post_order(RBTNode < T > * tree) const
{
    if (tree != NULL) {
        post_order(tree->left);
        post_order(tree->right);
        cout << tree->key << " ";
    }
}

template<class T>
void RBTree<T>::post_order()
{
    post_order(mroot);
}

/*递归实现查找红黑树x中键值为key的节点*/
template<class T>
RBTree<T>* RBTree<T>::search(RBTNode<T>* x, T key) const
{
    if (x == NULL || x->key == key)
        return x;

    if (key < x->key)
        return search(x->left, key);
    else
        return search(x->right, key);
}

template<class T>
RBTNode<T>* RBTree<T>::search(T key)
{
    search(mroot, key);
}

/*非递归实现查找红黑树x中键值为key的节点*/
template<class T>
RBTree<T>* RBTree<T>::iterative_search(RBTNode < T > * x, T key) const
{
    while ((x != NULL) && (x->key != key)) {
        if (key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    return x;
}

template<class T>
RBTree<T>* RBTree<T>::iterative_search(T key)
{
    iterative_search(mroot, key);
}

/*查找最小节点：返回tree为根节点的红黑树的最小节点*/
template<class T>
RBTree<T>* RBTree<T>::mininum(RBTNode < T > * tree)
{
    if (tree == NULL)
        return NULL;

    while (tree->left != NULL)
        tree = tree->left;

    return tree;
}

template<class T>
T RBTree<T>::mininum()
{
    RBTNode<T> *p = minunum(mroot);
    if (r != NULL)
        return p->key;

    return NULL;
}


/*查找最大节点：返回tree为根节点的红黑树的最大节点*/
template<class T>
RBTNode<T>* RBTree<T>::maxinum(RBTNode < T > * tree)
{
    if (tree == NULL)
        return NULL;

    while(tree->right !+ NULL)
        tree = tree->right;

    return tree;
}

template<class T>
T RBTree<T>::maxinum()
{
    RBTNode<T>* p = maxinum(mroot);
    if (p != NULL)
        return p->key;

    return NULL;
}

/*找节点x的后继节点。即查找红黑树中数据大于该节点的最小节点*/
template<class T>
RBTNode<T>* RBTree<T>::successor(RBTNode < T > * x)
{
    //如果x存在右孩子，则x的后继节点为以其右孩子为根的子树的最小节点
    if (x->right != NULL)
        return mininum(x->right);

    //如果没有右孩子，则x有以下两种可能
    //01：x是一个左孩子，则x的后继节点是他的父节点
    //02：x是一个右孩子，则查找x的最低父节点，并且该父节点要具有左孩子，找到的这个最低的父节点就是x的后继节点
    RBTNode<T>* y = x->parent;
    while ((y != NULL) && (x == y->left)) {
        x = y;
        y = y->parent;
    }

    return y;
}



/*
* 对红黑树的节点(x)进行左旋转
*
* 左旋示意图(对节点x进行左旋)：
*      px                              px
*     /                               /
*    x                               y
*   /  \      --(左旋)-->           / \                #
*  lx   y                          x  ry
*     /   \                       /  \
*    ly   ry                     lx  ly
*
*
*/
template<class T>
void RBTree<T>::left_rotate(RBTNode < T > * & root, RBTNode < T > * x)
{
    //设置x的右孩子为y
    RBTNode<T>* y = x->right;

    //将y的左孩子设为x的右孩子
    //如果y的左孩子非空，将x设为y的左孩子的父亲
    x->right = y->left;
    if (y->left != NULL)
        y->left->parent = x;

    //将x的父亲设为y的父亲
    y->parent = x->parent;

    if (x->parent == NULL) {
        root = y;
    } else {
        if (x->parent->left == x)
            x->parent->left = y;
        else
            x->parent->right = y;
    }

    y->left = x;
    x->parent = y;
}



/*
* 对红黑树的节点(y)进行右旋转
*
* 右旋示意图(对节点y进行左旋)：
*            py                               py
*           /                                /
*          y                                x
*         /  \      --(右旋)-->            /  \                     #
*        x   ry                           lx   y
*       / \                                   / \                   #
*      lx  rx                                rx  ry
*
*/
template<class T>
void RBTree<T>::right_rotate(RBTNode < T > * & root, RBTNode < T > * y)
{
    //设置x是当前节点的左孩子
    RBTNode<T>* x = y->left;

    //将x的右孩子设为y的左孩子
    //如果x的右孩子不为空的话，将y设为x的右孩子的父亲
    y->left = x->right;
    if (x->right != NULL)
        x->right->parent = y;

    //将y的父亲设为x的父亲
    x->parent = y->parent;

    if (y->parent == NULL) {
        root = x;
    } else {
        if (y == y->parent->right)
            y->parent->right = x;
        else
            y->parent->left = x;
    }

    x->parent = y;
    y->parent = x;
}


/*
* 红黑树插入修正函数
*
* 在向红黑树中插入节点之后(失去平衡)，再调用该函数；
* 目的是将它重新塑造成一颗红黑树。
*
* 参数说明：
*     root 红黑树的根
*     node 插入的结点        // 对应《算法导论》中的z
*/
template<class T>
void RBTree<T>::insert_fixup(RBTNode < T > * & root, RBTNode < T > * node)
{
    RBTNode<T>* parent, *gparent;

    //若父节点存在，并且父节点的颜色是红色
    while ((parent = rb_parent(node)) && rb_is_red(parent)) {
        gparent = rb_parent(parent);

        //若父节点是祖父节点的左孩子
        if (parent = gparent->left) {
            //case 1:叔叔节点是红色
            {
                RBTNode<T>* uncle = gparent->right;
                if (uncle && rb_is_red(uncle)) {
                    rb_set_black(uncle);
                    rb_set_black(parent);
                    rb_set_red(gparent);
                    node = gparent;
                    continue;
                }
            }

            //case 2:叔叔是黑色，并且当前节点是右孩子
            if (parent->right == node) {
                RBTNode<T>* tmp;
                left_rotate(root, parent);
                tmp = parent;
                parent = node;
                node = tmp;
            }

            //case 3:叔叔是黑色，且当前节点是左孩子
            rb_set_black(parent);
            rb_set_red(gparent);
            right_rotate(root, gparent);
        }else { //如果z的父亲是z的祖父节点的右孩子
            //case 1:叔叔节点是红色
            {
                RBTNode<T>* uncle = gparent->left;
                if (uncle && rb_is_red(uncle)) {
                    rb_set_black(uncle);
                    rb_set_black(parent);
                    rb_set_red(gparent);
                    node = gparent;
                    continue;
                }
            }

            //case 2:叔叔是黑色，且当前节点是左孩子
            if (parent->left == node) {
                RBTNode<T>* tmp;
                right_rotate(root, parent);
                tmp = parent;
                parent = node;
                node = tmp;
            }

            //case 3:叔叔是黑色，且当前节点是右孩子
            rb_set_black(parent);
            rb_set_red(gparent);
            left_rotate(root, gparent);
        }
    }

    //将根节点设为黑色
    rb_set_black(root);
}


/*
* 将结点插入到红黑树中
*
* 参数说明：
*     root 红黑树的根结点
*     node 插入的结点        // 对应《算法导论》中的node
*/
template<class T>
void RBTree<T>::insert(RBTNode < T > * & root, RBTNode < T > * node)
{
    RBTNode<T>* y = NULL;
    RBTNode<T>* x = root;

    //1.将红黑树当作一颗二叉查找树，将节点添加到二叉查找树中
    while (x != NULL) {
        y = x;
        if (node->key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    node->parent = y;
    if (y != NULL) {
        if (node->key < y->key)
            y->left = node;
        else
            y->right = node;
    } else {
        root = node;
    }

    //2.设直节点的颜色为红色
    node->color = RED;

    //3.将它重新修正为一颗二叉查找树
    insert_fixup(root, node);
}


/*
 * 将结点(key为节点键值)插入到红黑树中
 *
 * 参数说明：
 *     tree 红黑树的根结点
 *     key 插入结点的键值
*/
template<class T>
void RBTree<T>::insert(T key)
{
    RBTNode<T>* z = NULL;

    if ((z = new RBTNode<T>(key, BLACK, NULL, NULL, NULL)) == NULL)
        return;

    insert(mroot, z);
}

/*
  * 红黑树删除修正函数
  *
  * 在从红黑树中删除插入节点之后(红黑树失去平衡)，再调用该函数；
  * 目的是将它重新塑造成一颗红黑树。
  *
  * 参数说明：
  *     root 红黑树的根
  *     node 待修正的节点
*/
template<class T>
void RBTree<T>::remove_fixup(RBTNode < T > * & root, RBTNode < T > * node, RBTNode < T > * parent)
{
    RBTNode<T> *other;

    while ((!node || rb_is_black(node)) && node != root) {
        if (parent->left == node) {
            other = parent->right;
            if (rb_is_red(other)) {
                //case 1:x的兄弟w是红色
                rb_set_black(other);
                rb_set_red(parent);
                left_rotate(root, parent);
                other = parent->right;
            }
            if ((!other->left || rb_is_black(other->left)) &&
                (!other->right || rb_is_black(other->right))) {
                //case 2:x的兄弟w是黑色，且w的两个孩子也都是黑色
                rb_set_red(other);
                node = parent;
                parent = rb_parent(node);
            } else {
                if (!other->right || rb_is_black(other->right)) {
                    //case 3:x的兄弟w是黑色，并且w的左孩子是红色，右孩子是黑色
                    rb_set_black(other->left);
                    rb_set_red(other);
                    right_rotate(root, other);
                    other = parent->right;
                }
                //case 4:x的兄弟w是黑色，并且w的右孩子是红色，左孩子任意颜色
                rb_set_color(other, rb_color(parent));
                rb_set_black(parent);
                rb_set_black(other->right);
                left_rotate(root, parent);
                node = root;
                break;
            }
        }else {
            other = parent->left;
            if (rb_is_red(other)) {
                //case 1:x的兄弟w是红色
                rb_set_black(other);
                rb_set_red(parent);
                right_rotate(root, parent);
                other = parent->left;
            }
            if ((!other->left || rb_is_black(other->left)) &&
                (!other->right || rb_is_black(other->right))) {
                //case 2:x的兄弟w是黑色，并且w的两个孩子也都是黑色的
                rb_set_red(other);
                node = parent;
                parent = rb_parent(node);
            } else {
                if (!other->left || rb_is_black(other->left)) {
                    //case 3:x的兄弟w是黑色的，并且w的左孩子是红色，右孩子是黑色
                    rb_set_black(other->right);
                    rb_set_red(other);
                    left_rotate(root, other);
                    other = parent->left;
                }
                //case 4:x的兄弟节点w是黑色的，并且w的右孩子是红色的，左孩子任意颜色
                rb_set_color(other, rb_color(parent));
                rb_set_black(parent);
                rb_set_black(other->left);
                right_rotate(root, parent);
                node = root;
                break;
            }
        }
    }
    if (node)
        rb_set_black(node);
}


/*
 * 删除结点(node)，并返回被删除的结点
 *
 * 参数说明：
 *     root 红黑树的根结点
 *     node 删除的结点
*/
template<class T>
void RBTree<T>::remove(RBTNode < T > * & root, RBTNode < T > * node)
{
    RBTNode<T> *child, *parent;
    RBTColor color;

    //被删除节点的左右孩子都不为空的情况
    if ((node->left != NULL) && (node->right) != NULL) {
        //被删节点的后继节点。（称为取代节点）
        //用它来取代被删节点的位置，然后再将被删节点去叼
        RBTNode<T> *replace = node;

        //获取后继节点
        replace = replace->right;
        while (replace->left != NULL)
            replace = replace->left;

        //node节点不是根节点（只有根节点不存在父节点）
        if (rb_parent(node)) {
            if (rb_parent(node)->left == node)
                rb_parent(node)->left = replace;
            else
                rb_parent(node)->right = replace;
        } else {
            //node节点是根节点，更新根节点
            root = replace;
        }

        //child是取代节点的右孩子，也是需要调整的节点
        //取代节点肯定不存在左孩子，因为它是一个后继节点
        child = replace->right;
        parent = rb_parent(replace);
        //保存取代节点的颜色
        color = rb_color(replace);

        //被删除节点是它的后继节点的父节点
        if (parent == node) {
            parent = replace;
        } else {
            //child不为空
            if (child)
                rb_set_parent(child, parent);
            parent->left = child;

            replace->right = node->right;
            rb_set_parent(node->right, replace);
        }

        replace->parent = node->parent;
        replace->color = node->color;
        replace->left = node->left;
        node->left->parent = replace;

        if (color == BLACK)
            remove_fixup(root, child, parent);

        delete node;
        return;
    }

    if (node->left != NULL)
        child = node->left;
    else
        child = node->right;

    parent = node->parent;
    //保存取代节点的颜色
    color = node->color;

    if (child)
        child->parent = parent;

    //node节点不是根节点
    if (parent) {
        if (parent->left == node)
            parent->left = child;
        else
            parent->right= child;
    } else {
        root = child;
    }

    if (color == BLACK)
        remove_fixup(root, child, parent);
    delete node;
}


/*
 * 删除红黑树中键值为key的节点
 *
 * 参数说明：
 *     tree 红黑树的根结点
*/
template<class T>
void RBTree<T>::remove(T key)
{
    RBTNode<T> *node;

    //查找key对应的节点node，找到的话就删除该节点
    if ((node = search(mroot, key)) != NULL)
        remove(mroot, node);
}


/*销毁红黑树*/
template<class T>
void RBTree<T>::destroy(RBTNode < T > * & tree)
{
    if (tree == NULL)
        return;

    if (tree->left != NULL)
        return destroy(tree->left);
    if (tree->right != NULL)
        return destroy(tree->right);

    delete tree;
    tree = NULL;
}

template<class T>
void RBTree<T>::destroy()
{
    destroy(mroot);
}

/*
* 打印"二叉查找树"
*
* key        -- 节点的键值
* direction  --  0，表示该节点是根节点;
*               -1，表示该节点是它的父结点的左孩子;
*                1，表示该节点是它的父结点的右孩子。
*/
template<class T>
void RBTree<T>::print(RBTNode < T > * tree, T key, int direction)
{
    if (tree != NULL) {
        if (direction == 0) //tree是根节点
            cout << setw(2) << tree->key << "(B) is root" << endl;
        else
            cout << setw(2) << tree->key << (rb_is_red(tree) ? "(R)" : "(B)") << " is " << setw(2) << key << "'s" << setw(12) << (direction == 1 ? "right child" : "left child") << endl;

        print(tree->left, tree->key, -1);
        print(tree->right, tree->key, 1);
    }
}

template<class T>
void RBTree<T>::print()
{
    if (mroot != NULL)
        print(mroot, mroot->key, 0);
}

