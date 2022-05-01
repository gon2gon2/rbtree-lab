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
node_t *rbtree_insert(rbtree *t, const key_t key) {
  // TODO: implement insert
  return t->root;
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