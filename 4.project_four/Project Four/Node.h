//Andrew Gerungan CS2337.003 NETID:AWG190000
#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

#include "Seat.h"

class Node{
public:
   Node(){up=nullptr;down=nullptr;left=nullptr;right=nullptr;payload=nullptr;};
   Node(Node* u, Node* d, Node* l, Node* r, Seat* p){up=u;down=d;left=l;right=r;payload=p;};

   Node* getup(){return up;};
   Node* getdown(){return down;};
   Node* getleft(){return left;};
   Node* getright(){return right;};
   Seat* getpayload(){return payload;};

   void setup(Node* u){up = u;};
   void setdown(Node* d){down = d;};
   void setleft(Node* l){left = l;};
   void setright(Node* r){right = r;};
   void setpayload(Seat* p){payload = p;};
private:
   Node* up;
   Node* down;
   Node* left;
   Node* right;
   Seat* payload;
};


#endif // NODE_H_INCLUDED
