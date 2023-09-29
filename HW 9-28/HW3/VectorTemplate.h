//Andrew Gerungan CS2337.003 NETID:AWG190000
#ifndef VECTORTEMPLATE_H_INCLUDED
#define VECTORTEMPLATE_H_INCLUDED

#include <vector>
using namespace std;

template <typename T>
class VectorTemplate{
private:
   vector<T> stored;
public:
   VectorTemplate(vector<T> v){stored = v;};
   vector<T> getVector(){return stored;};
   void setVector(T x){stored.push_back(x);};
   void InsertionSort();
   bool BinarySearch(T);
};

template <typename T>
void VectorTemplate<T>::InsertionSort(){
   for(int x = 1;x<(int)stored.size();x++){
      T compare = stored.at(x);
      int hold = x;
      while(hold>0 && stored[hold-1] > compare){
         stored.at(hold) = stored.at(hold-1);
         hold = hold-1;
      }
      stored.at(hold) = compare;
   }
}
template <typename T>
bool VectorTemplate<T>::BinarySearch(T x){
   int s = 0;
   int e = (int)stored.size()-1;
   while(s <= e){
      int mid = (s+e)/2;
      if(stored.at(mid) == x){
         return true;
      }
      else if(stored.at(mid) > x){
         e = mid-1;
      }
      else{
         s = mid+1;
      }
   }
   return false;
}



#endif // VECTORTEMPLATE_H_INCLUDED
