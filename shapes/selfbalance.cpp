// Self Balancing Binary Search Tree
// Adapted from https://www.tutorialspoint.com/cplusplus-program-to-implement-self-balancing-binary-search-tree

#include<shapes/selfbalance.hpp>

int avl_tree::height(avl *t)
{
   int h = 0;
   if (t != NULL)
   {
      int l_height = height(t->l);
      int r_height = height(t->r);
      int max_height = max(l_height, r_height);
      h = max_height + 1;
   }
   return h;
}
int avl_tree::difference(avl *t)//calculte difference between left and right tree
{
   int l_height = height(t->l);
   int r_height = height(t->r);
   int b_factor = l_height - r_height;
   return b_factor;
}
avl *avl_tree::rr_rotat(avl *parent)//right right rotation
{
   avl *t;
   t = parent->r;
   parent->r = t->l;
   t->l = parent;
   //cout<<"Right-Right Rotation";
   return t;
}
avl *avl_tree::ll_rotat(avl *parent)//left left rotation
{
   avl *t;
   t = parent->l;
   parent->l = t->r;
   t->r = parent;
   //cout<<"Left-Left Rotation";
   return t;
}
avl *avl_tree::lr_rotat(avl *parent)//left right rotation
{
   avl *t;
   t = parent->l;
   parent->l = rr_rotat(t);
   //cout<<"Left-Right Rotation";
   return ll_rotat(parent);
}
avl *avl_tree::rl_rotat(avl *parent)//right left rotation
{
   avl *t;
   t= parent->r;
   parent->r = ll_rotat(t);
   //cout<<"Right-Left Rotation";
   return rr_rotat(parent);
}
avl *avl_tree::balance(avl *t)
{
   int bal_factor = difference(t);
   if (bal_factor > 1)
   {
      if (difference(t->l) > 0)
      t = ll_rotat(t);
      else
      t = lr_rotat(t);
   }
   else if (bal_factor < -1)
   {
      if (difference(t->r) > 0)
      t = rl_rotat(t);
      else
      t = rr_rotat(t);
   }
   return t;
   }
avl *avl_tree::insert(avl *r, int v, int i)
   {
      if (r == NULL)
      {
         r = new avl;
         r->d = v;
         r->index = i;
         r->l = NULL;
         r->r= NULL;
         return r;
      }
      else if (v< r->d)
      {
        r->l= insert(r->l, v, i);
         r = balance(r);
      }
      else if (v >= r->d)
      {
        r->r= insert(r->r, v, i);
         r = balance(r);
      }
      return r;
   }


int avl_tree::search(avl *r, int key){
	if(r != NULL){
		if(key == r->d){
      return r->index;
		}
		if(key < r->d){
			return search(r->l, key);
		}else{
			return search(r->r, key);
		}
	}else{
		return -1;
	}
}




   void avl_tree::show(avl *p, int l)//show the tree
   {
      int i;
      if (p != NULL)
      {
        show(p->r, l+ 1);
         cout<<" ";
         if (p == r)
         cout << "Root → ";
         for (i = 0; i < l&& p != r; i++)
         cout << " ";
         cout << p->d;
         show(p->l, l + 1);
      }
   }
   void avl_tree::inorder(avl *t)//inorder traversal
   {
      if (t == NULL)
      return;
      inorder(t->l);
      cout << t->d << " ";
      inorder(t->r);
   }
   void avl_tree::preorder(avl *t)//preorder traversal
   {
      if (t == NULL)
      return;
      cout << t->d << " ";
      preorder(t->l);
      preorder(t->r);
   }
   void avl_tree::postorder(avl *t)//postorder traversal
   {
      if (t == NULL)
      return;
      postorder(t ->l);
      postorder(t ->r);
      cout << t->d << " ";
   }
