//Andrew Gerungan CS2337.003 NETID:AWG190000
#ifndef FRACTION_H_INCLUDED
#define FRACTION_H_INCLUDED
#include <iostream>

class Fraction{
private:
   int num, denom;
public:
   Fraction(){num=0;denom=0;};
   Fraction(int Num){num=Num;denom=1;};
   Fraction(int Num, int Denom){num=Num;denom=Denom;};

   int getnum(){return num;};
   void setnum(int Num){num=Num;};
   int getdenom(){return denom;};
   void setdenom(int Denom){denom=Denom;};

   Fraction& simplify();

   Fraction& operator+(const Fraction&);
   Fraction& operator-(const Fraction&);
   Fraction& operator*(const Fraction&);
   Fraction& operator/(const Fraction&);

   bool operator<(const Fraction&);
   bool operator>(const Fraction&);
   bool operator==(const Fraction&);

   friend std::ostream& operator<<(std::ostream&,const Fraction&);
   friend std::istream& operator>>(std::istream&,Fraction&);
};

#endif // FRACTION_H_INCLUDED
