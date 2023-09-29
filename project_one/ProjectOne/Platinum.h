//Andrew Gerungan CS2337.003 NETID:AWG190000
#ifndef PLATINUM_H_INCLUDED
#define PLATINUM_H_INCLUDED
#include "Customer.h"
class Platinum : public Customer{
private:
   float bb;
public:
   Platinum(std::string, std::string, std::string, float, float);

   float getbb(){return bb;};
   void setbb(float b){bb=b;};
};


#endif // PLATINUM_H_INCLUDED
