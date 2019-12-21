/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
 // #include "avltree.h"

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node* tmp = t->right;
    t->right = tmp->left;
    t->height = getHeight(t);
    tmp->left = t;
    t = tmp;
    t->height = getHeight(t);

}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node* tmp = t->left;
    t->left = tmp->right;
    t->height = getHeight(t);
    tmp->right = t;
    t = tmp;
    t->height = getHeight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    //your code here
    // if(rightHeavy(subtree)&&rightHeavy(subtree->right)) rotateLeft(subtree);
    // else if(leftHeavy(subtree)&&leftHeavy(subtree->left))  rotateRight(subtree);
    // else if(leftHeavy(subtree)&&rightHeavy(subtree->left))  rotateLeftRight(subtree);
    //  //else
    //  else {if(rightHeavy(subtree)&&leftHeavy(subtree->right)) rotateRightLeft(subtree);}
    // // else subtree->height = getHeight(subtree);
    // // subtree->height = getHeight(subtree);

    if(getBalance(subtree)==-2){
      if (getBalance(subtree->left)==-1) {
        //left, stick
        rotateRight(subtree);
      }
      else rotateLeftRight(subtree);
    }

    if(getBalance(subtree)==2){
      if (getBalance(subtree->right)==1) {
        //right, stick
        rotateLeft(subtree);
      }
      else rotateRightLeft(subtree);
    }


}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
    //rebalance(root);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if(subtree == NULL) subtree = new Node(key,value);
    else if(key < subtree->key) insert(subtree->left,key,value);
    else insert(subtree->right,key,value);
 // if(key > subtree->key)
    rebalance(subtree);
    subtree->height = getHeight(subtree);
    return;
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        remove(subtree->left, key);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right,key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            subtree = NULL;
            // your code here
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            Node* ptr = subtree->left;
            if(!ptr->right){
              ptr->right = subtree->right;
              subtree = ptr;
            }
            while(ptr->right) ptr = ptr->right;
            swap(ptr,subtree);
            remove(subtree->left,key);
            rebalance(subtree);

        } else {
            /* one-child remove */
            if(subtree->left) subtree = subtree->left;
            else subtree = subtree->right;
            rebalance(subtree);
            // your code here
        }
        // your code here
        rebalance(subtree);
    }
    rebalance(subtree);
}

template <class K, class V>
int AVLTree<K, V>::getBalance( Node*& subtree)
{
    if(!subtree) return 0;
    return heightOrNeg1(subtree->right)-heightOrNeg1(subtree->left);
}

template <class K, class V>
int AVLTree<K, V>::getHeight(const Node* subtree){
  // int lHeight = -1;
  // if(subtree->left) lHeight = subtree->left->height;
  // else lHeight = -1 ;
  // int rHeight = -1;
  // if(subtree->right) rHeight = subtree->right->height;
  // else rHeight = -1 ;
  // return  (lHeight > rHeight) ? lHeight : rHeight;
  if (!subtree) return -1;
  return (getHeight(subtree->left) > getHeight(subtree->right)) ? getHeight(subtree->left)+1 : getHeight(subtree->right)+1;
}
