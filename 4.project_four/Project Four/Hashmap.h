//Andrew Gerungan CS2337.003 NETID:AWG190000
#ifndef HASHMAP_H_INCLUDED
#define HASHMAP_H_INCLUDED

#include <math.h>
#include <string>
#include <vector>
#include <iostream>
#include "Seat.h"

struct order{
   int audnum;
   int atick;
   int ctick;
   int stick;
   std::vector<Seat> seats;
};

struct user{
   std::string username;
   std::string password;
   std::vector<struct order> orders;
};

class Hashmap{
private:
   struct user* hashmap;
   int tsize;
   int numElements;
public:
   Hashmap();
   void print();
   void resizeHash();
   void add(struct user);
   int closestPrime(int);
   long long int calcHash(std::string);
   user& findUser(std::string);
};


#endif // HASHMAP_H_INCLUDED
