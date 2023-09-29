//Andrew Gerungan CS2337.003 NETID:AWG190000
#include "fraction.h"
#include <iostream>

Fraction& Fraction::simplify(){
   int i=1;
   //Check if numerator and denominator are divisible by each number less than or equal to the numerator
   while(i<=num){
      //if the numerator and denominator are divisible by i
      if(i!=1 && num%i==0 && denom%i==0){
         num = num/i;
         denom = denom/i;
         i=1;
         continue; //loop through to check if it can be simplified further
      }
      i++;
   }
   return *this;
}

Fraction& Fraction::operator+(const Fraction& f){
   int n_denom = denom*f.denom;
   num = (num*(n_denom/denom)) + (f.num*(n_denom/f.denom));
   denom = denom*f.denom;
   simplify();
   return *this;
}
Fraction& Fraction::operator-(const Fraction& f){
   int n_denom = denom*f.denom;
   num = (num*(n_denom/denom)) - (f.num*(n_denom/f.denom));
   denom = denom*f.denom;
   simplify();
   return *this;
}
Fraction& Fraction::operator*(const Fraction& f){
   num = num*f.num;
   denom = denom*f.denom;
   simplify();
   return *this;
}
Fraction& Fraction::operator/(const Fraction& f){
   num = num*f.denom;
   denom = denom*f.num;
   simplify();
   return *this;
}

bool Fraction::operator<(const Fraction& f){
   int n_denom = denom*f.denom;
   int num1 = (num*(n_denom/denom));
   int num2 = (f.num*(n_denom/f.denom));
   return num1 < num2;
}
bool Fraction::operator>(const Fraction& f){
   int n_denom = denom*f.denom;
   int num1 = (num*(n_denom/denom));
   int num2 = (f.num*(n_denom/f.denom));
   return num1 > num2;
}
bool Fraction::operator==(const Fraction& f){
   int n_denom = denom*f.denom;
   int num1 = (num*(n_denom/denom));
   int num2 = (f.num*(n_denom/f.denom));
   return num1 == num2;
}

std::ostream& operator<<(std::ostream& o,const Fraction& f){
   o << f.num << '/' << f.denom;
   return o;
}
std::istream& operator>>(std::istream& i,Fraction& f){
   i >> f.num;
   i >> f.denom;
   return i;
}



