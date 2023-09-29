//Andrew Gerungan CS2337.003 NETID:AWG190000
#include <iostream>
#include "fraction.h"

using namespace std;

int main()
{
   Fraction f1, f2;
   cout << "Insert First Fraction: " << endl;
   cin >> f1;
   cout << "Insert Second Fraction: " << endl;
   cin >> f2;

   cout << f1 << " + " << f2 << " = " << f1+f2 << endl;
   cout << f1 << " - " << f2 << " = " << f1-f2 << endl;
   cout << f1 << " * " << f2 << " = " << f1*f2 << endl;
   cout << f1 << " / " << f2 << " = " << f1/f2 << endl;

   cout << endl << "0 = false, 1 = true" << endl << endl;
   cout << f1 << " < " << f2 << ": " << (f1<f2) << endl;
   cout << f1 << " > " << f2 << ": " << (f1>f2) << endl;
   cout << f1 << " = " << f2 << ": " << (f1==f2) << endl;
   return 0;
}
