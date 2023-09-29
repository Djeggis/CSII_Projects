//Andrew Gerungan CS2337.003 NETID:AWG190000
#ifndef CUSTOMER_H_INCLUDED
#define CUSTOMER_H_INCLUDED
#include <string>
class Customer{
protected:
   std::string fn, ln, gID;
   float spent, hold;
public:
   Customer(std::string, std::string, std::string, float);
   virtual ~Customer() {hold=0;};

   std::string getfn(){return fn;};
   std::string getln(){return ln;};
   std::string getgID(){return gID;};
   float getspent(){return spent;};

   void setfn(std::string f){fn=f;};
   void setln(std::string l){ln=l;};
   void setgID(std::string g){gID=g;};
   void setspent(float s){spent=s;};
};


#endif // CUSTOMER_H_INCLUDED
