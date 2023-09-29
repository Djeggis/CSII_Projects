//Andrew Gerungan CS2337.003 NETID:AWG190000
#ifndef GOLD_H_INCLUDED
#define GOLD_H_INCLUDED
#include "Customer.h"
class Gold : public Customer{
private:
   float dp;
public:
   Gold(std::string, std::string, std::string, float, float);

   float getdp(){return dp;};
   void setdp(float d){dp=d;};
};


#endif // GOLD_H_INCLUDED
