//Andrew Gerungan CS2337.003 NETID:AWG190000
#ifndef AUDITORIUM_H_INCLUDED
#define AUDITORIUM_H_INCLUDED

#include "Node.h"
#include <fstream>
#include <iostream>
#include <string>
#include <cmath>

class Auditorium{
public:
   Auditorium(std::string);

   std::string getauditorium();
   std::string printauditorium();
   Node* getindex(int, int);
   bool availableinrow(int, int, int);
   void reserveseats(int,int,int,int,int);
   Node* bestavailable(int);
   int closertomiddle(Node*,Node*, int);

   Node* getfirst(){return first;};
   int getrow(){return num_row;};
   int getcol(){return num_col;};

   void setfirst(Node* f){first = f;};
   void setrow(int r){num_row=r;};
   void setcol(int c){num_col=c;};
private:
   Node* first;
   int num_row;
   int num_col;
};


#endif // AUDITORIUM_H_INCLUDED
