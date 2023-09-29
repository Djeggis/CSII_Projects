//Andrew Gerungan CS2337.003 NETID:AWG190000


#include <iostream>
#include "Auditorium.h"
#include <ctype.h>

using namespace std;

void printtheater(Auditorium*);
bool isanumber(string);

int main()
{
   string filename, menu;
   int c_input, row, atick, ctick, stick;
   string temp = "";
   char col = '!';
   bool exit = false;

   menu = "\nMENU\n------\n1: Reserve Ticket\n2: Exit\nChoice: ";
   ofstream outfile("A1.txt");

   cout << "Input File Name: ";
   cin >> filename;

   Auditorium* a = new Auditorium(filename);

   while(!exit){ //keep looping until done with auditorium functions
      c_input = -1;
      cout << menu;
      cin >> temp; //input into string first for validation
      try{ //attempt to parse an int
         c_input = isanumber(temp)?stoi(temp):-1; //ensures that it only grabs a number
         if(c_input==1){ //reserve seats
            cout << a->printauditorium() << endl;
            c_input = -1;
            do{
               cout << "\nPlease choose a row: ";
               cin >> temp;
               try{ //attempt to parse an int
                  c_input = isanumber(temp)?stoi(temp):-1; //ensures that it only grabs a number
                  if(c_input < 1 || c_input > a->getrow()){ //checks that the input is within bounds
                     cout << "\nSorry, you have input an invalid row. Please try another row." << endl;
                  }
               }
               catch (...){
                  cout << "\nSorry, you have input an invalid row. Please try another row." << endl;
               }
            }while(c_input < 1 || c_input > a->getrow());
            row = c_input - 1;

            do{
               cout << "\nPlease choose your starting seat (Seats will be reserved from starting seat consecutively towards the right): ";
               cin >> temp;
               if(temp.length()==1){ //checks that input was only one character long
                  col = (char)toupper(temp.at(0)); //makes the character uppercase
                  if(col < 'A' || col > (char)(a->getcol()+64)){ //checks that the input is within bounds
                     cout << "\nSorry, you have input an invalid seat. Please try another row." << endl;
                  }
               }
               else{
                  cout << "\nSorry, you have input an invalid seat. Please try another row." << endl;
               }
            }while(col < 'A' || col > (char)(a->getcol()+64));

            c_input = -1;
            do{
               cout << "\nHow many adult tickets would you like?: ";
               cin >> temp;
               try{ //attempts to parse an int
                  c_input = isanumber(temp)?stoi(temp):-1; //ensures that it only grabs a number
                  if(c_input < 0){
                     cout << "\nSorry, you have input an invalid number. Please try another number." << endl;
                  }
               }
               catch (...){
                  cout << "\nSorry, you have input an invalid number. Please try another number." << endl;
               }
            }while(c_input < 0);
            atick = c_input;

            c_input = -1;
            do{
               cout << "\nHow many child tickets would you like?: ";
               cin >> temp;
               try{ //attempts to parse an int
                  c_input = isanumber(temp)?stoi(temp):-1; //ensures that it only grabs a number
                  if(c_input < 0){
                     cout << "\nSorry, you have input an invalid number. Please try another number." << endl;
                  }
               }
               catch (...){
                  cout << "\nSorry, you have input an invalid number. Please try another number." << endl;
               }
            }while(c_input < 0);
            ctick = c_input;

            c_input = -1;
            do{
               cout << "\nHow many senior tickets would you like?: ";
               cin >> temp;
               try{ //attempts to parse an int
                  c_input = isanumber(temp)?stoi(temp):-1; //ensures that it only grabs a number
                  if(c_input < 0){
                     cout << "\nSorry, you have input an invalid number. Please try another number." << endl;
                  }
               }
               catch (...){
                  cout << "\nSorry, you have input an invalid number. Please try another number." << endl;
               }
            }while(c_input < 0);
            stick = c_input;

            if(!a->availableinrow(atick+ctick+stick,row,(int)(col)-65)){ //need to recommend best available
               Node* best = a->bestavailable(atick+ctick+stick);
               if(best!=nullptr){ //seats exist in the auditorium
                  //since best returns the right side, need to subtract the total + 1 for starting seat col
                  cout << "\nThe best available seat set is [" << best->getpayload()->getrow()+1 << (char)(best->getpayload()->getseat()-(atick+ctick+stick)+1) << "-" << best->getpayload()->getrow()+1 << best->getpayload()->getseat() << "], would you like to reserve (Y/N)?: ";
                  do{
                     cin >> temp;
                     if(temp.length()==1){ //makes sure that the input was only one character long
                        col = (char)toupper(temp.at(0)); //makes the character uppercase
                        if(col != 'Y' && col!='N'){
                           cout << "\nSorry, you have input an invalid input. Please try again." << endl;
                        }
                     }
                     else{
                        cout << "\nSorry, you have input an invalid input. Please try again." << endl;
                     }
                  }while(col!='Y'&&col!='N');
                  if(col=='Y'){
                     //have to reserve seat starting from the left so subtract 65 (convert from ascii) and then subtract the total + 1 for the left
                     a->reserveseats(atick,ctick,stick,best->getpayload()->getrow(),(int)(best->getpayload()->getseat())-65-(atick+ctick+stick)+1);
                     cout << "\nYour purchase has been processed.";
                  }
                  else{
                     cout << "\nCanceling reservation";
                  }
               }
               else{ //no available seats
                  cout << "\nno seats available";
               }
            }
            else{ //seats are available
               a->reserveseats(atick,ctick,stick,row,(int)(col)-65);
               cout << "\nYour purchase has been processed.";
            }

         } //exit
         else if(c_input==2){
            exit = true;
         }
         else{
            cout << "Invalid Input. Try Again" << endl;
         }
      } //if couldn't parse an int, loop again
      catch (...){
         cout << "Invalid Input. Try Again" << endl;
      }
   }
   //report the theater
   int t_seats, t_ticks, ad, c, s;
   t_seats = t_ticks = ad = c = s = 0;
   double t_price = 0;
   //loop through entire theater
   for(int r=0;r<a->getrow();r++){
      for(int x=0;x<a->getcol();x++){
         t_seats++;
         if(a->getindex(r,x)->getpayload()->getticktype()=='A'){
            t_ticks++;
            ad++;
            t_price += 10;
         }
         else if(a->getindex(r,x)->getpayload()->getticktype()=='C'){
            t_ticks++;
            c++;
            t_price += 5;
         }
         else if(a->getindex(r,x)->getpayload()->getticktype()=='S'){
            t_ticks++;
            s++;
            t_price += 7.5;
         }
      }
   }

   printf("\nTotal Seats: %6d", (int)t_seats);
   printf("\nTotal Tickets: %3d", (int)t_ticks);
   printf("\nAdult Tickets: %3d", (int)ad);
   printf("\nChild Tickets: %3d", (int)c);
   printf("\nSenior Tickets: %1d", (int)s);
   printf("\nTotal Sales: %4c%5.2f", '$', (double)t_price);
   //print out to file
   outfile << a->getauditorium();

   return 0;
}

bool isanumber(string s){
   for(int x=0;x<(int)s.length();x++){
      if(s.at(x)<'0' || s.at(x)>'9'){
         return false;
      }
   }
   return true;
}

