#include "rbtree.h"

#include <stdlib.h>

rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  // TODO: initialize struct if needed

  // NIL 노드 생성과 색깔 설정
  node_t *NIL = (node_t *)calloc(1, sizeof(node_t));
  NIL->color = RBTREE_BLACK;


  // 트리의 root포인터와 nil 포인터가 NIL노드를 가리키게 함
  p->root = NIL;
  p->nil = NIL;

  return p;
}

void delete_rbtree(rbtree *t) {
  // TODO: reclaim the tree nodes's memory
  free(t->nil);
  free(t);
}

void left_rotate(rbtree *t, node_t *p) {
  // 1. set q(right of p)
  node_t *q = p->right;

  // 2. transplant left of q to right of p
  p->right = q->left;
  if (q->left != t->nil){
    q->left->parent = p;
  }
  // 3. set p's parent as q
  p->parent = q;
  if (p->parent == t->nil) {
    t->root = q;
  } else if (p->parent->left == p) {
    p->parent->left = q;
  } else {
    p->parent->right = q;
  }

  // 4. set q's left as p
  q->left = p;
  p->parent = q;
}

void right_rotate(rbtree *t, node_t *p) {
  // 1. set q(left of p)
  node_t *q = p->left;

  // 2. transplant right of q to left of p
  p->left = q->right;
  if (q->right != t->nil){
    q->right->parent = p;
  }
  // 3. set p's parent as q
  p->parent = q;
  if (p->parent == t->nil) {
    t->root = q;
  } else if (p->parent->right == p) {
    p->parent->right = q;
  } else {
    p->parent->left = q;
  }

  // 4. set q's right as p
  q->right = p;
  p->parent = q;
}

void insert_fixup(rbtree *t, node_t *z) { 
  // while the parent of z has red color
  while ( z->parent->color == RBTREE_RED) {

    // 1. if parent is left child
    if (z->parent == z->parent->parent->left) {
      node_t *y = z->parent->parent->right;
      
      // case 1-1. if uncle has red color
      if ( y->color == RBTREE_RED ) {
        z->parent->color = RBTREE_BLACK;
        y->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        z = z->parent->parent;
      }
      else {
        // case 1-2. if uncle has black color (triangle, < -> /)
        // it makes z - parent - grandparent straight
        if ( z == z->parent->right) {
          z = z->parent;
          left_rotate(t, z);
        }
        // case 1-3. if uncle has black color (line)
        z->parent->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        right_rotate(t, z->parent->parent);
      }
    }
    // 2. if parent is right child
    else {
      node_t *y = z->parent->parent->left;

      // case 2-1. if uncle has red color
      if ( y->color == RBTREE_RED ) {
        z->parent->color = RBTREE_BLACK;
        y->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        z = z->parent->parent;
      }
      else {
        // case 2-2. if uncle has black color (triangle, > -> \)
        // it makes z - parent - grandparent straight
        if ( z == z->parent->left) {
          z = z->parent;
          right_rotate(t, z);
        }
        // case 2-3. if uncle has black color (line)
        z->parent->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        left_rotate(t, z->parent->parent);
      }
    }
  }
  t->root->color = RBTREE_BLACK;
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
  // TODO: implement insert

  node_t *z = (node_t *)calloc(1, sizeof(node_t));
  z->color = RBTREE_RED;
  z->key = key;
  
  node_t *y = t->nil;
  node_t *x = t->root;

  // find termianl node y, the parent of the new node z
  while ( x != t->nil ) {
    y = x;
    if (z->key < x->key) {
      x = x->left;
    } else {
      x = x->right;
    }
  }

  // set z as a child of the parent y
  z->parent = y;
  if (y == t->nil) {
    t->root = z;
    z->parent = t->nil;  // set the parent of the root 
  } else if ( z->key < y->key ) {
    y->left = z;
  } else {
    y->right = z;
  }
  
  // set the children of the new node z
  z->left = t->nil;
  z->right = t->nil;
  z->color = RBTREE_RED;

  insert_fixup(t, z);

  return z;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
  // TODO: implement find
  return t->root;
}

node_t *rbtree_min(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

node_t *rbtree_max(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

int rbtree_erase(rbtree *t, node_t *p) {
  // TODO: implement erase
  return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  return 0;
}