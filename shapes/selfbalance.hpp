// Self Balancing Binary Search Tree
// Adapted from https://www.tutorialspoint.com/cplusplus-program-to-implement-self-balancing-binary-search-tree

#include<iostream>
#include<cstdio>
#include<sstream>
#include<algorithm>
#define pow2(n) (1 << (n))
using namespace std;
struct avl//node declaration
{
  int d;
  int index;
  struct avl *l;
  struct avl *r;
};
class avl_tree
{
public://declare functions
  int height(avl *);
  int difference(avl *);
  avl * rr_rotat(avl *);
  avl * ll_rotat(avl *);
  avl * lr_rotat(avl*);
  avl * rl_rotat(avl *);
  avl * balance(avl *);
  avl * insert(avl *, int, int);
  int search (avl *, int);
  void show(avl *, int);
  void inorder(avl *);
  void preorder(avl *);
  void postorder(avl*);
  avl_tree()
  {
    r = NULL;
  }
  avl *r;
};
