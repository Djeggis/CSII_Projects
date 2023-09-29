//Andrew Gerungan CS2337.003 NETID:AWG190000
#include <iostream>
#include "VectorTemplate.h"
#include <vector>

using namespace std;

int main()
{
   vector<string>s;
   s.push_back("z");
   s.push_back("a");
   s.push_back("m");
   s.push_back("b");

   vector<int>i;
   i.push_back(101);
   i.push_back(-2);
   i.push_back(50);
   i.push_back(7);

   vector<float>f;
   f.push_back(2.2f);
   f.push_back(2.1f);
   f.push_back(-1.3f);
   f.push_back(2.24f);

   VectorTemplate<string> vt1(s);
   VectorTemplate<int> vt2(i);
   VectorTemplate<float> vt3(f);

   vt1.setVector("j");
   for(int x=0;x<(int)vt1.getVector().size();x++){
      cout << vt1.getVector().at(x) << endl;
   }
   cout << endl;
   vt1.InsertionSort();
   for(int x=0;x<(int)vt1.getVector().size();x++){
      cout << vt1.getVector().at(x) << endl;
   }
   cout << vt1.BinarySearch("i") << endl;
   cout << endl;

   vt2.setVector(-1);
   for(int x=0;x<(int)vt2.getVector().size();x++){
      cout << vt2.getVector().at(x) << endl;
   }
   cout << endl;
   vt2.InsertionSort();
   for(int x=0;x<(int)vt2.getVector().size();x++){
      cout << vt2.getVector().at(x) << endl;
   }
   cout << vt2.BinarySearch(-1) << endl;
   cout << endl;

   vt3.setVector(1.1f);
   for(int x=0;x<(int)vt3.getVector().size();x++){
      cout << vt3.getVector().at(x) << endl;
   }
   cout << endl;
   vt3.InsertionSort();
   for(int x=0;x<(int)vt3.getVector().size();x++){
      cout << vt3.getVector().at(x) << endl;
   }
   cout << vt3.BinarySearch(2.2f) << endl;
   cout << endl;
}
