//Andrew Gerungan CS2337.003 NETID:AWG190000
#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

template <typename T>
class Node{
private:
   Node<T>* left;
   Node<T>* right;
   T payload;
public:
   Node(){left=nullptr;right=nullptr;payload=nullptr;};
   Node(T t){left=nullptr;right=nullptr;payload=t;};

   Node<T>* getleft(){return left;};
   Node<T>* getright(){return right;};
   T getpayload(){return payload;};

   void setleft(Node<T>* l){left=l;};
   void setright(Node<T>* r){right=r;};
   void setpayload(T p){payload=p;};
};


#endif // NODE_H_INCLUDED
