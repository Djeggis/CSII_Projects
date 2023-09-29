//Andrew Gerungan CS2337.003 NETID:AWG190000
#ifndef SEAT_H_INCLUDED
#define SEAT_H_INCLUDED

class Seat{
public:
   Seat(){row=0;seat=' ';ticktype=' ';};
   Seat(int r, char s, char tt){row=r;seat=s;ticktype=tt;};

   int getrow(){return row;};
   char getseat(){return seat;};
   char getticktype(){return ticktype;};

   void setrow(int r){row = r;};
   void setseat(char s){seat = s;};
   void setticktype(char tt){ticktype=tt;};
private:
   int row;
   char seat;
   char ticktype;
};


#endif // SEAT_H_INCLUDED
