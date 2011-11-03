#ifndef TREAP_H_
#define TREAP_H_

#include<iostream>

template<class T, class D>
class TreapNode {
public:
    T key;
    D data;
    unsigned int prio;

    TreapNode *parent;
    TreapNode *left;
    TreapNode *right;

    TreapNode()
            : parent(0), left(0), right(0) {
    }
};

template<class T, class D>
class Treap {
public:
    bool contains(T key);
    bool remove(T key);
    bool add(T key, D data);

private:
    TreapNode<T, D> *root;
    TreapNode<T, D>** rotate(TreapNode<T, D>* node);
};

template<class T, class D>
bool Treap<T, D>::add(T key, D data) {
    // Afdalen naar een blad.
    TreapNode<T, D> **node = &root;
    TreapNode<T, D> *parent = 0;
    while ((*node) != 0 && (*node)->key != key) {
        parent = (*node); // ouder bijhouden.
        if (key < (*node)->key) {
            node = &((*node)->left);
        }
        else {
            node = &((*node)->right);
        }
    }

    // Geen dubbels..
    if ((*node) != 0 && (*node)->key == key) {
        return false;
    }

    // Knoop toevoegen.
    *node = new TreapNode<T, D>();
    (*node)->key = key;
    (*node)->data = data;
    (*node)->parent = parent;

    // Prioriteit instellen (-1 zodat we de max value kunnen gebruiken bij het verwijderen.)
    (*node)->prio = rand() % (1000 - 1);

    // Heap voorwaarde controleren.
    // Kleinste prioriteit staat bovenaan.
    while ((*node)->parent != 0 && (*node)->prio < (*node)->parent->prio) {
        node = rotate((*node));
    }

    return true;
}

template<class T, class D>
TreapNode<T, D>** Treap<T, D>::rotate(TreapNode<T, D>* node) {
    // Kijk of we naar links of naar rechts moeten roteren
    bool rotate_left = true;
    TreapNode<T, D> *parent = node->parent;
    if (parent->right == node) {
        rotate_left = false;
    }

    TreapNode<T, D> *grand_parent = parent->parent;
    if (rotate_left) {
        parent->left = node->right;
        parent->parent = node;
        node->right = node->parent;
    }
    else {
        parent->right = node->left;
        parent->parent = node;
        node->left = parent;
    }

    if (grand_parent != 0) {
        node->parent = grand_parent;
        if (grand_parent->left == parent) {
            grand_parent->left = node;
        }
        else
            grand_parent->right = node;
    }
    else {
        root = node;
        node->parent = 0;
    }
    return &node;

}

template<class T, class D>
bool Treap<T, D>::contains(T key) {
    TreapNode<T, D> *node = root;
    if (node == 0) {
        return false;
    }

    while (node != 0 && node->key != key) {
        if (key < node->key) {
            node = node->left;
        }
        else {
            node = node->right;
        }
    }

    return (node != 0 && node->key == key);
}

#endif
