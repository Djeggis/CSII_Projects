//Andrew Gerungan CS2337.003 NETID:AWG190000
#ifndef DVD_H_INCLUDED
#define DVD_H_INCLUDED

#include <string>
#include <iostream>
class DVD{
private:
   std::string title;
   int available;
   int rented;
public:
   DVD(std::string t, int a, int r){title=t;available=a;rented=r;};

   std::string gettitle(){return title;};
   int getavailable(){return available;};
   int getrented(){return rented;};

   void settitle(std::string t){title=t;};
   void setavailable(int a){available=a;};
   void setrented(int r){rented=r;};

   bool operator<(const DVD& d){return title<d.title;};
   bool operator>(const DVD& d){return title>d.title;};
   bool operator==(const DVD& d){return title==d.title;};

   friend std::string& operator+=(std::string&,DVD*);
};


#endif // DVD_H_INCLUDED
