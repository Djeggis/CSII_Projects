//Andrew Gerungan CS2337.003 NETID:AWG190000
#include "DVD.h"
std::string& operator+=(std::string& s,DVD* d){
   s+=d->gettitle();
   s+=",";
   s+=(char)(d->getavailable()+48);
   s+=",";
   s+=(char)(d->getrented()+48);
   return s;
}

