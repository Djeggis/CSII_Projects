//Andrew Gerungan CS2337.003 NETID:AWG190000
#ifndef HASHTABLE_H_INCLUDED
#define HASHTABLE_H_INCLUDED

class HashTable{
private:
   int* hashTable;
   int tsize;
   int numElements;
public:
   HashTable();
   void print();
   void resizeHash();
   void add(int);
   int closestPrime(int);
};


#endif // HASHTABLE_H_INCLUDED
