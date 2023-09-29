//Andrew Gerungan CS2337.003 NETID:AWG190000
#include "HashTable.h"
#include <iostream>

HashTable::HashTable(){
   tsize=11;
   hashTable = new int[tsize];
   for(int x=0;x<tsize;x++){
      hashTable[x]=0;
   }
   numElements=0;
}

void HashTable::print(){
   for(int x=0;x<tsize;x++){
      if(hashTable[x]==0){
         std::cout << "_ ";
      }
      else{
         std::cout << hashTable[x] << " ";
      }
   }
}
void HashTable::resizeHash(){
   int newsize = closestPrime(tsize*2);
   int* temp = new int[newsize];
   for(int x=0;x<newsize;x++){
      temp[x]=0;
   }
   for(int x=0;x<tsize;x++){
      if(hashTable[x]!=0){
         for(int i=0;i<newsize;i++){
            int hashValue = ((hashTable[x]%newsize)+(i*i))%newsize;
            if(temp[hashValue]==0){
               temp[hashValue]=hashTable[x];
               break;
            }
         }
      }
   }
   tsize = newsize;
   delete[]hashTable;
   hashTable = temp;
   temp = nullptr;

}
void HashTable::add(int x){
   for(int i=0;i<tsize;i++){
      int hashValue = ((x%tsize)+(i*i))%tsize;
      if(hashTable[hashValue]==0){
         hashTable[hashValue]=x;
         numElements++;
         break;
      }
   }
   if((float)((float)(numElements)/(float)tsize)>=.5){ //loadFactor >= .5
      resizeHash();
   }
}
int HashTable::closestPrime(int x){
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
