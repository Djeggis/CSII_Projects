//Andrew Gerungan CS2337.003 NETID:AWG190000
#ifndef BSTREE_H_INCLUDED
#define BSTREE_H_INCLUDED

#include "Node.h"
#include <string>
template <typename T>
class BSTree{
private:
   Node<T>* root;
public:
   BSTree(){root=nullptr;};
   BSTree(Node<T>* r){root=r;};

   Node<T>* getroot(){return root;};
   void setroot(Node<T>* r){root=r;};

   void insertnode(Node<T>*, Node<T>*);
   Node<T>* searchnode (Node<T>*, Node<T>*); //will return the parent node of the searched node
   void deletenode (Node<T>*, Node<T>*);
   std::string ordered(Node<T>*); //used to get the nodes sorted from least to greatest
};

template <typename T>
void BSTree<T>::insertnode(Node<T>* i, Node<T>* base){
   if(root==nullptr){ //first checks if tree is empty, if so, should be root
      root=i;
   }
   else{
      //if value want to insert is less than current
      if(*(i->getpayload()) < *(base->getpayload())){
         //if left is currently empty, set left to insert
         if(base->getleft()==nullptr){
            base->setleft(i);
         }
         //keep inserting from curr's left
         else{
            insertnode(i,base->getleft());
         }
      }
      //if value want to insert is greater than current
      else{
         //if right is currently empty, set right to insert
         if(base->getright()==nullptr){
            base->setright(i);
         }
         //keep inserting from curr's right
         else{
            insertnode(i,base->getright());
         }
      }
   }
}

template <typename T>
Node<T>* BSTree<T>::searchnode(Node<T>* s, Node<T>* base){
   if(base==nullptr){ //first checks if empty
      return nullptr;
   }
   else{
      //if current node is what I'm looking for
      if(*(s->getpayload())==*(base->getpayload())){
         return base;
      }
      //if value looking for is less than current
      else if(*(s->getpayload()) < *(base->getpayload())){
         //if left is empty, then doesn't exist
         if(base->getleft()==nullptr){
            return nullptr;
         }
         //keep searching from curr's left
         else{
            return searchnode(s,base->getleft());
         }
      }
      //if value is greater than current
      else{
         //if right is empty, then doesn't exist
         if(base->getright()==nullptr){
            return nullptr;
         }
         //keep searching from curr's right
         else{
            return searchnode(s,base->getright());
         }
      }
   }
}

template <typename T>
void BSTree<T>::deletenode(Node<T>* d, Node<T>* base){
   if(base!=nullptr){ //first checks if empty
      if(base==root&&*(d->getpayload())==*(base->getpayload())){ //if my deletion is my root
         if(base->getleft()==nullptr&&base->getright()==nullptr){ //if has 0 children
            root = nullptr;
         }
         else if(base->getleft()==nullptr||base->getright()==nullptr){ //if has one child
            root = (base->getleft()==nullptr)?base->getright():base->getleft(); //set to the non null side
         }
         else{ //has two children
            //get the left most part of the right child
            Node<T>* temp = base->getright();
            while(temp->getleft()!=nullptr){
               temp = temp->getleft();
            }
            T tempdata = temp->getpayload(); //stores the leftmost payload of the right child
            deletenode(temp, root); //deletes that payload
            base->setpayload(tempdata); //moves that payload to the base (root)
            //deallocates memory
            temp = nullptr;
            tempdata = nullptr;
         }
      }
      else if(base->getleft()!=nullptr&&*(d->getpayload())==*(base->getleft()->getpayload())){ //if my base's left exists and is what I want to delete
         Node<T>* temp = base->getleft(); //gets the left child of my curr base
         if(temp->getleft()==nullptr&&temp->getright()==nullptr){ //if the left child has no children
            base->setleft(nullptr);
         }
         else if(temp->getleft()==nullptr||temp->getright()==nullptr){ //if the left child has one child
            base->setleft((temp->getleft()==nullptr)?temp->getright():temp->getleft());
         }
         else{ //has two children
            //get the left most part of the right child of the left child
            temp = temp->getright();
            while(temp->getleft()!=nullptr){
               temp = temp->getleft();
            }
            T tempdata = temp->getpayload(); //stores the leftmost payload of the right child of the left child
            deletenode(temp, root); //deletes that payload
            base->getleft()->setpayload(tempdata); //moves that payload to the base's left
            //deallocates memory
            temp = nullptr;
            tempdata = nullptr;
         }
      }
      else if(base->getright()!=nullptr&&*(d->getpayload())==*(base->getright()->getpayload())){ //if my base's right exists and is what I want to delete
         Node<T>* temp = base->getright(); //gets the right child of my curr base
         if(temp->getleft()==nullptr&&temp->getright()==nullptr){ //if the right child has no children
            base->setright(nullptr);
         }
         else if(temp->getleft()==nullptr||temp->getright()==nullptr){ //if the right child has one child
            base->setright((temp->getleft()==nullptr)?temp->getright():temp->getleft());
         }
         else{ //has two children
            //get the left most part of the right child of the right child
            temp = temp->getright();
            while(temp->getleft()!=nullptr){
               temp = temp->getleft();
            }
            T tempdata = temp->getpayload(); //stores the leftmost payload of the right child of the right child
            deletenode(temp, root); //deletes that payload
            base->getright()->setpayload(tempdata); //moves that payload to the base's right
            //deallocates memory
            temp = nullptr;
            tempdata = nullptr;
         }
      }
      if(*(d->getpayload())<*(base->getpayload())){ //if not found and is less than curr, move left
         deletenode(d,base->getleft());
      }
      else if(*(d->getpayload())>*(base->getpayload())){
         deletenode(d,base->getright()); //if not found and is greater than curr, move right
      }
   }
}

template <typename T>
std::string BSTree<T>::ordered(Node<T>* base){
   //if my tree is completely empty
   if(root==nullptr){
      return "";
   }
   std::string s = "";
   //if my current is empty, return an empty string
   if(base==nullptr){
      return "";
   }
   //add the left's cumulative string
   s+=ordered(base->getleft());
   //add current string
   s+=base->getpayload();
   s+="\n"; //separates each payload
   //add right's cumulative string
   s+=ordered(base->getright());
   //return cumulative string
   return s;
}


#endif // BSTREE_H_INCLUDED
