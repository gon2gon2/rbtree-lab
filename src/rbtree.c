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

void free_node(rbtree *t, node_t *p) {
  if (p != t->nil) {
    free_node(t, p->left);
    free_node(t, p->right);
    free(p);
    p = NULL;
  }
}

void delete_rbtree(rbtree *t) {
  // TODO: reclaim the tree nodes's memory

  /*
  free_node               -> 9/2
  free_node, t            -> 9/5
  free_node, nil, t       -> 9/8
  free_node, nil, root, t -> double free

  erase root 에서 남는 뭔가 생겨서 해결해야 됨
  */
  free_node(t, t->root);
  free(t->nil);
  t->nil = NULL;
  free(t);
  t = NULL;
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
  // if z is the root, z's parent will be NIL
  z->parent = y;

  // set child of the parent y
  if (y == t->nil) {
    t->root = z;
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
  node_t *temp = t->root;
  while (temp != t->nil) {
    temp = temp->left;
  }
  return temp;
}

node_t *rbtree_max(const rbtree *t) {
  // TODO: implement find
  node_t *temp = t->root;
  while (temp != t->nil) {
    temp = temp->right;
  }
  return temp;
}

void rbtree_transplant(rbtree *t, node_t *u, node_t *v){
  // 1. plant v to u's children
  if (u->parent == t->nil) {
    t->root = v;
  }
  else if (u == u->parent->left) {
    u->parent->left = v;
  }
  else {
    u->parent->right = v;
  }

  // 2. set the parent of v as u
  v->parent = u->parent;
}

node_t *tree_minimum(rbtree *t, node_t * p) {
  // find minimum of the subtree
  while (p->left != t->nil) {
    p = p->left;
  }
  return p;
}

void rbtree_delete_fixup(rbtree *t, node_t *x) {
  node_t *w;
  while (x != t->root && x->color == RBTREE_BLACK) {
    if (x == x->parent->right) {
      w = x->parent->right;
      if (w->color == RBTREE_RED) {
        w->color = RBTREE_BLACK;
        x->parent->color = RBTREE_RED;
        left_rotate(t, x->parent);
        w = w->parent->right;
      }

      if (w->left->color == RBTREE_BLACK && w->right->color == RBTREE_BLACK) {
        w->color = RBTREE_RED;
        x = x->parent;
      }
      else {
        if (w->right->color == RBTREE_BLACK) {
          w->left->color = RBTREE_BLACK;
          w->color = RBTREE_RED;
          right_rotate(t, w);
          w = x->parent->right;
        }
        w->color = x->parent->color;
        x->parent->color = RBTREE_BLACK;
        w->right->color = RBTREE_BLACK;
        left_rotate(t, x->parent);
        x = t->root;
      }
    }

    else {
      // 위랑 같음
      w = x->parent->left;
      if (w->color == RBTREE_RED) {
        w->color = RBTREE_BLACK;
        x->parent->color = RBTREE_RED;
        right_rotate(t, x->parent);
        w = w->parent->left;
      }

      if (w->right->color == RBTREE_BLACK && w->left->color == RBTREE_BLACK) {
        w->color = RBTREE_RED;
        x = x->parent;
      }
      else {
        if (w->left->color == RBTREE_BLACK) {
          w->right->color = RBTREE_BLACK;
          w->color = RBTREE_RED;
          left_rotate(t, w);
          w = x->parent->left;
        }
        w->color = x->parent->color;
        x->parent->color = RBTREE_BLACK;
        w->left->color = RBTREE_BLACK;
        right_rotate(t, x->parent);
        x = t->root;
      }
    }
  }
  x->color = RBTREE_BLACK;
}

int rbtree_erase(rbtree *t, node_t *p) {
  // TODO: implement erase

  node_t *q = p;
  color_t q_original_color = q->color;
  node_t *r;

  if (p->left == t->nil) {
    r = p->right;
    rbtree_transplant(t, p, p->right);
  }
  else if (p->right == t->nil) {
    r = p->left;
    rbtree_transplant(t, p, p->left);
  }
  else {
    q = tree_minimum(t, p->right);
    q_original_color = q->color;
    r = q->right;
    
    if (q->parent == p) {
      r->parent = q;
    }
    else {
      rbtree_transplant(t, q, q->right);
      q->right = r->right;
      q->right->parent = q;
    }
    rbtree_transplant(t, p, q);
    q->left = r->left;
    q->left->parent = q;
    q->color = r->color;

  if (q_original_color == RBTREE_BLACK) {
    rbtree_delete_fixup(t, r);
    }
  }


  return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  return 0;
}