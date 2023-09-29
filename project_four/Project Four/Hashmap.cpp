//Andrew Gerungan CS2337.003 NETID:AWG190000
#include "Hashmap.h"

Hashmap::Hashmap(){
   tsize=11;
   hashmap = new struct user[tsize];
   for(int x=0;x<tsize;x++){
      struct user t;
      hashmap[x]=t;
      hashmap[x].username="n/a";
   }
   numElements=0;
}

void Hashmap::print(){
   for(int x=0;x<tsize;x++){
      if(hashmap[x].username=="n/a"){
         std::cout << "_ ";
      }
      else{
         std::cout << hashmap[x].username << ", " << hashmap[x].password << " | ";
      }
   }
}
void Hashmap::resizeHash(){
   int newsize = closestPrime(tsize*2);
   struct user* temp = new struct user[newsize];
   for(int x=0;x<newsize;x++){
      struct user t;
      temp[x]=t;
      temp[x].username="n/a";
   }
   for(int x=0;x<tsize;x++){
      if(hashmap[x].username!="n/a"){
         for(int i=0;i<newsize;i++){
            int hashvalue = (int)(calcHash(hashmap[x].username)%newsize);
            hashvalue = ((hashvalue)+(i*i))%newsize;
            if(temp[hashvalue].username=="n/a"){
               temp[hashvalue]=hashmap[x];
               break;
            }
         }
      }
   }
   tsize = newsize;
   delete[]hashmap;
   hashmap = temp;
   temp = nullptr;

}
void Hashmap::add(struct user x){
   for(int i=0;i<tsize;i++){
      int hashvalue = (int)(calcHash(x.username)%tsize);

      hashvalue = ((hashvalue)+(i*i))%tsize;
      if(hashmap[hashvalue].username=="n/a"){
         hashmap[hashvalue]=x;
         numElements++;
         break;
      }
   }
   if((float)((float)(numElements)/(float)tsize)>=.5){ //loadFactor >= .5
      resizeHash();
   }
}
int Hashmap::closestPrime(int x){
   int z = x;
   while(true){
      bool prime = true;
      for(int i=2;i<z;i++){
         if(z%i==0){
            prime = false;
         }
      }
      if(prime){
         return z;
         break;
      }
      z++;
   }
}

long long int Hashmap::calcHash(std::string x){
   long long int hashvalue = 0;
   //calculates the polynomial hash code
   for(int i=0;i<(int)(x.length());i++){
      hashvalue+=(long long int)(x.at(i))*(long long int)(pow(4,(int)(x.length())-i-1));
   }
   return hashvalue;
}

struct user& Hashmap::findUser(std::string usname){
   int hashvalue = (int)(calcHash(usname)%tsize);
   //search hashmap for username
   for(int x=0;x<tsize;x++){
      hashvalue = ((hashvalue)+(x*x))%tsize;
      if(hashmap[hashvalue].username==usname){
         return hashmap[hashvalue];
      }
   }
   //return a base case of nothing
   return hashmap[hashvalue];
}
