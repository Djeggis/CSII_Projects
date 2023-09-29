//Andrew Gerungan CS2337.003 NETID:AWG190000
#include <iostream>
#include "Auditorium.h"
#include "Hashmap.h"
#include <ctype.h>

using namespace std;

bool isanumber(string);
void printreport(Auditorium*,Auditorium*,Auditorium*);
void processorder(Auditorium*, struct user*);
void printordersnonumbers(struct user);
void printorders(struct user);
void printreceipt(struct user);

int main()
{
   string cmenu, amenu, filedata, uname, pword;
   struct user *curruser;
   int c_input, sel_order;
   string temp = "";
   filedata = "";
   bool exit = false;
   bool login = true;
   bool admin = false;
   bool cexit = false;
   ofstream outfile;
   ifstream infile;
   Hashmap hashmap = Hashmap();

   cmenu = "\n1. Reserve Seats\n2. View Orders\n3. Update Order\n4. Display Receipt\n5. Log Out\nChoice: ";
   amenu = "\n1. Print Report\n2. Logout\n3. Exit\nChoice: ";

   //first need to load the user database

   infile.open("userdb.dat");
   if(infile){
      while(getline(infile,filedata)){
         if(filedata.length()>0){
            struct user t;
            //separates by username and password and adds to hashmap
            int space_index = (int)filedata.find(' ',0);
            t.username = filedata.substr(0,space_index);
            t.password = filedata.substr(space_index+1);
            hashmap.add(t);
         }
      }
   }
   else{ //if file doesn't open
      cout << "\"" << "userdb.dat" << "\" did not open correctly. Aborting program.";
      return -1;
   }

   //now need to load the auditoriums

   Auditorium* a1 = new Auditorium("A1.txt", 1);

   Auditorium* a2 = new Auditorium("A2.txt", 2);

   Auditorium* a3 = new Auditorium("A3.txt", 3);

   //now need to go into the main sequence
   while(!exit){
      //go to menu sequence
      if(login){
         cout << "Please enter your username: ";
         cin >> uname;
         cout << endl;
         //finds the username (if doesn't exist, won't work regardless)
         curruser=&hashmap.findUser(uname);
         //loops thrice max
         for(int x=0;x<3;x++){
            cout << "Please enter your password: ";
            cin >> pword;
            cout << endl;
            //checks if the username and password match
            if(uname==curruser->username&&pword==curruser->password){
               login = false;
               //if admin, should go to admin workflow
               if(uname=="admin"){
                  admin = true;
               }
               break;
            }
            else{
               cout << "Invalid password" << endl;
            }
         }
      }
      //go to admin menu
      else if(admin){
         //input validation
         do{
            cout << amenu;
            cin >> temp;
            if(!isanumber(temp)){
               cout << "\nInvalid Input" << endl;
            }
         }while(!isanumber(temp));
         c_input = stoi(temp);
         //print report
         if(c_input==1){
            printreport(a1,a2,a3);
         }
         //go back to login
         else if(c_input==2){
            login = true;
         }
         //exit program
         else if(c_input==3){
            //writes the auditoriums to text files
            outfile.open("A1Final.txt");
            outfile << a1->getauditorium();
            outfile.close();

            outfile.open("A2Final.txt");
            outfile << a2->getauditorium();
            outfile.close();

            outfile.open("A3Final.txt");
            outfile << a3->getauditorium();
            outfile.close();

            exit = true;
         }
         else{
            cout << "\nInvalid Input" << endl;
         }
      }
      //go to customer menu
      else{
         //validate inputs
         do{
            cout << cmenu;
            cin >> temp;
            if(!isanumber(temp)){
               cout << "\nInvalid Input" << endl;
            }
         }while(!isanumber(temp));
         c_input = stoi(temp);
         //reserve seats
         if(c_input==1){
            //input validation
            do{
               cout << "\n1. Auditorium 1\n2. Auditorium 2\n3. Auditorium 3\nChoice: ";
               cin >> temp;
               if(!isanumber(temp)){
                  cout << "\nInvalid Input" << endl;
               }
            }while(!isanumber(temp));
            c_input = stoi(temp);
            //aud 1
            if(c_input==1){
               cout << a1->printauditorium() << endl;
               processorder(a1,curruser);
            }
            //aud 2
            else if(c_input==2){
               cout << a2->printauditorium() << endl;
               processorder(a2,curruser);
            }
            //aud 3
            else if(c_input==3){
               cout << a3->printauditorium() << endl;
               processorder(a3,curruser);
            }
            else{
               cout << "\nInvalid Input" << endl;
            }
         }
         //view orders
         else if(c_input==2){
            if(curruser->orders.size()>0){
               printordersnonumbers(*curruser);
            }
            else{
               cout << "\nNo orders" << endl;
            }
         }
         //update order
         else if(c_input==3){
            if(curruser->orders.size()>0){
               printorders(*curruser);
               //input validation
               do{
                  cout << "\nSelected Order to Update: ";
                  cin >> temp;
                  //checks that is of valid type
                  if(isanumber(temp)){
                     sel_order=stoi(temp);
                  }
                  else{
                     cout << "\nInvalid Input" << endl;
                  }
                  if(sel_order<1||sel_order>(int)curruser->orders.size()){
                     cout << "\nInvalid Order" << endl;
                  }
               }while(sel_order<1||sel_order>(int)curruser->orders.size());
               sel_order--; //decreases to match index

               //grabs by the current order by reference so can change things
               struct order* currorder = &curruser->orders.at(sel_order);

               int anum = currorder->audnum;

               //matches current auditorium
               Auditorium* a = a1;
               if(anum==1){
                  a = a1;
               }
               else{
                  a = (anum==2)?a2:a3;
               }

               cexit = false;
               do{
                  //input validation
                  do{
                     cout << "\n1. Add tickets to order\n2. Delete tickets from order\n3. Cancel Order\nChoice: ";
                     cin >> temp;
                     if(!isanumber(temp)){
                        cout << "\nInvalid Input" << endl;
                     }
                  }while(!isanumber(temp));
                  c_input = stoi(temp);
                  //Add tickets
                  if(c_input==1){
                     cout << a->printauditorium() << endl;

                     int row = -1;
                     string input;
                     //validates row
                     do{
                        cout << "Enter your row number: ";
                        cin >> input;
                        //checks is of valid type
                        if(isanumber(input)){
                           row=stoi(input);
                        }
                        else{
                           cout << "Invalid Input" << endl;
                        }
                        if(row<1||row>a->getrow()){
                           cout << "Invalid Row" << endl;
                        }
                     }while(row<1||row>a->getrow());
                     row--; //changes to match index

                     //validates col
                     int col = -1;
                     do{
                        cout << "Enter your starting seat letter: ";
                        cin >> input;
                        //checks is of valid type
                        if(input.length()==1){
                           //converts to number from char
                           col = (int)(toupper(input.at(0)))-65;
                        }
                        else{
                           cout << "Invalid Input" << endl;
                        }
                        if(col<0||col>=a->getcol()){
                           cout << "Invalid Starting Seat" << endl;
                        }
                     }while(col<0||col>=a->getcol());

                     //validates atick
                     int atick = -1;
                     do{
                        cout << "Enter your # of adult tickets: ";
                        cin >> input;
                        //checks is of valid type
                        if(isanumber(input)){
                           atick=stoi(input);
                        }
                        else{
                           cout << "Invalid Input" << endl;
                        }
                        if(atick<0){
                           cout << "Invalid Number" << endl;
                        }
                     }while(atick<0);

                     //validates ctick
                     int ctick = -1;
                     do{
                        cout << "Enter your # of child tickets: ";
                        cin >> input;
                        //checks is of valid type
                        if(isanumber(input)){
                           ctick=stoi(input);
                        }
                        else{
                           cout << "Invalid Input" << endl;
                        }
                        if(ctick<0){
                           cout << "Invalid Number" << endl;
                        }
                     }while(ctick<0);

                     //validates stick
                     int stick = -1;
                     do{
                        cout << "Enter your # of senior tickets: ";
                        cin >> input;
                        //checks is of valid type
                        if(isanumber(input)){
                           stick=stoi(input);
                        }
                        else{
                           cout << "Invalid Input" << endl;
                        }
                        if(stick<0){
                           cout << "Invalid Number" << endl;
                        }
                     }while(stick<0);

                     //checks if available in row or not
                     if(!a->availableinrow(atick+ctick+stick,row,col)){ //DOESN'T need to recommend best available
                        cout << "\nSeats selected are unavailable";
                     }
                     else{ //seats are available
                        a->reserveseats(atick,ctick,stick,row,col);
                        currorder->atick += atick;
                        currorder->ctick += ctick;
                        currorder->stick += stick;
                        //for each ticket, add the seat to CURRENT order
                        for(int x=0;x<atick+ctick+stick;x++){
                           Seat s(row,(char)((int)col+x+65),'.');
                           for(int i=0;i<(int)currorder->seats.size()+1;i++){
                              if(i==(int)currorder->seats.size()){
                                 currorder->seats.push_back(s);
                                 break;
                              }
                              else if(row<currorder->seats.at(i).getrow()||(row<=currorder->seats.at(i).getrow()&& s.getseat()<=currorder->seats.at(i).getseat())){
                                 currorder->seats.insert(currorder->seats.begin()+i,s);
                                 break;
                              }
                           }
                        }
                        cout << "\nYour purchase has been processed.";
                        cexit = true;
                     }
                     //clears out pointer as to not have redundant pointers
                  }
                  //Delete tickets
                  else if(c_input==2){
                     int row = -1;
                     string input;
                     //validates row
                     do{
                        cout << "Enter your row number you want to delete: ";
                        cin >> input;
                        //checks is of valid type
                        if(isanumber(input)){
                           row=stoi(input);
                        }
                        else{
                           cout << "Invalid Input" << endl;
                        }
                        if(row<1||row>a->getrow()){
                           cout << "Invalid Row" << endl;
                        }
                     }while(row<1||row>a->getrow());
                     row--; //changes to max index

                     //validates col
                     int col = -1;
                     do{
                        cout << "Enter your seat letter you want to delete: ";
                        cin >> input;
                        //checks is of valid type
                        if(input.length()==1){
                           col = (int)(toupper(input.at(0)))-65;
                        }
                        else{
                           cout << "Invalid Input" << endl;
                        }
                        if(col<0||col>=a->getcol()){
                           cout << "Invalid Starting Seat" << endl;
                        }
                     }while(col<0||col>=a->getcol());

                     bool valid = false;
                     int index = -1;
                     //checks that there is a matching row and col in the order
                     for(int x=0;x<(int)currorder->seats.size();x++){
                        Seat s = currorder->seats.at(x);
                        if(s.getrow()==row&&(int)(s.getseat())-65==col){
                           valid = true;
                           index = x;
                        }
                     }
                     if(valid){
                        //stores the type of ticket
                        char storedtype = a->getindex(row,col)->getpayload()->getticktype();
                        //clears the seat from the auditorium
                        a->getindex(row,col)->getpayload()->setticktype('.');
                        //deletes the seat from the order
                        currorder->seats.erase(currorder->seats.begin()+index);
                        //deletes the correct type of ticket
                        if(storedtype=='A'){
                           currorder->atick--;
                        }
                        else if(storedtype=='C'){
                           currorder->ctick--;
                        }
                        else{
                           currorder->stick--;
                        }
                        //if order is empty after removing, remove the order
                        if(currorder->atick==0&&currorder->ctick==0&&currorder->stick==0){
                           curruser->orders.erase(curruser->orders.begin()+sel_order);
                        }
                        cout << "Deleted Successfully" << endl;
                        cexit=true;
                     }
                     else{
                        cout << "Invalid Seat Chosen" << endl;
                     }
                  }
                  //Cancel order
                  else if(c_input==3){
                     //clears the auditorium of all seats in the order
                     for(int x=0;x<(int)currorder->seats.size();x++){
                        a->getindex(currorder->seats.at(x).getrow(),(int)(currorder->seats.at(x).getseat())-65)->getpayload()->setticktype('.');
                     }
                     currorder->seats.erase(currorder->seats.begin(),currorder->seats.begin()+(int)currorder->seats.size());
                     //removes order from the user
                     curruser->orders.erase(curruser->orders.begin()+sel_order);
                     cout << "Cleared Successfully" << endl;
                     cexit=true;
                  }
                  else{
                     cout << "\nInvalid Input" << endl;
                  }
               }while(!cexit);
               a=nullptr;
               currorder=nullptr;
            }
            else{
               cout << "\nNo orders" << endl;
            }
         }
         //display receipt
         else if(c_input==4){
            printreceipt(*curruser);
         }
         //logout
         else if(c_input==5){
            login = true;
         }
         else{
            cout << "\nInvalid Input" << endl;
         }
      }
   }

   return 0;
}

void printreport(Auditorium* a1, Auditorium* a2, Auditorium* a3){
   //total values
   int o_seats=0, t_ticks=0, ad=0, c=0, s=0;
   double t_price = 0;

   //loop through aud 1 and adds to proper values
   for(int r=0;r<a1->getrow();r++){
      for(int x=0;x<a1->getcol();x++){
         if(a1->getindex(r,x)->getpayload()->getticktype()=='A'){
            t_ticks++;
            ad++;
            t_price += 10;
         }
         else if(a1->getindex(r,x)->getpayload()->getticktype()=='C'){
            t_ticks++;
            c++;
            t_price += 5;
         }
         else if(a1->getindex(r,x)->getpayload()->getticktype()=='S'){
            t_ticks++;
            s++;
            t_price += 7.5;
         }
         else{
            o_seats++;
         }
      }
   }
   cout << "Auditorium 1\t" << o_seats << "\t" << t_ticks << "\t" << ad << "\t" << c << "\t" << s << "\t";
   printf("%c%.2f\n", '$', (double)t_price);

   //create temporary values
   int to=0, tr=0, ta=0, tc=0, ts=0;
   double tp=0;

   //go through aud 2 and adds to proper values
   for(int r=0;r<a2->getrow();r++){
      for(int x=0;x<a2->getcol();x++){
         if(a2->getindex(r,x)->getpayload()->getticktype()=='A'){
            tr++;
            ta++;
            t_ticks++;
            ad++;
            tp += 10;
            t_price += 10;
         }
         else if(a2->getindex(r,x)->getpayload()->getticktype()=='C'){
            tr++;
            tc++;
            t_ticks++;
            c++;
            tp += 5;
            t_price += 5;
         }
         else if(a2->getindex(r,x)->getpayload()->getticktype()=='S'){
            tr++;
            ts++;
            t_ticks++;
            s++;
            tp += 7.5;
            t_price += 7.5;
         }
         else{
            to++;
            o_seats++;
         }
      }
   }
   cout << "Auditorium 2" << "\t" << to << "\t" << tr << "\t" << ta << "\t" << tc << "\t" << ts << "\t";
   printf("%c%.2f\n", '$', (double)tp);

   //reset temporary values
   to=tr=ta=tc=ts=0;
   tp=0;

   //go through aud 3 and adds to proper values
   for(int r=0;r<a3->getrow();r++){
      for(int x=0;x<a3->getcol();x++){
         if(a3->getindex(r,x)->getpayload()->getticktype()=='A'){
            tr++;
            ta++;
            t_ticks++;
            ad++;
            tp += 10;
            t_price += 10;
         }
         else if(a3->getindex(r,x)->getpayload()->getticktype()=='C'){
            tr++;
            tc++;
            t_ticks++;
            c++;
            tp += 5;
            t_price += 5;
         }
         else if(a3->getindex(r,x)->getpayload()->getticktype()=='S'){
            tr++;
            ts++;
            t_ticks++;
            s++;
            tp += 7.5;
            t_price += 7.5;
         }
         else{
            to++;
            o_seats++;
         }
      }
   }
   cout << "Auditorium 3" << "\t" << to << "\t" << tr << "\t" << ta << "\t" << tc << "\t" << ts << "\t";
   printf("%c%.2f\n", '$', (double)tp);

   //print out total values
   cout << "Total\t" << "\t" << o_seats << "\t" << t_ticks << "\t" << ad << "\t" << c << "\t" << s << "\t";
   printf("%c%.2f\n", '$', (double)t_price);
}

bool isanumber(string s){
   //goes through entire string
   for(int x=0;x<(int)s.length();x++){
      //if anything isn't a number, string isn't a number
      if(s.at(x)<'0' || s.at(x)>'9'){
         return false;
      }
   }
   //if empty, also not a number
   if((int)s.length()==0)
      return false;
   return true;
}

void processorder(Auditorium* a, struct user* u){
   char ctemp = ' '; //user for Y/N

   int row = -1;
   string input = "";
   string temp = "";
   //validates row
   do{
      cout << "Enter your row number: ";
      cin >> input;
      //checks is of valid type
      if(isanumber(input)){
         row=stoi(input);
      }
      else{
         cout << "Invalid Input" << endl;
      }
      if(row<1||row>a->getrow()){
         cout << "Invalid Row" << endl;
      }
   }while(row<1||row>a->getrow());
   row--; //aligns row to index

   int col = -1;
   //validates col
   do{
      cout << "Enter your starting seat letter: ";
      cin >> input;
      //checks is of valid type
      if((int)input.length()==1){
         //converts from char to int col value
         col = (int)(toupper(input.at(0)))-65;
      }
      else{
         cout << "Invalid Input" << endl;
      }
      if(col<0||col>=a->getcol()){
         cout << "Invalid Starting Seat" << endl;
      }
   }while(col<0||col>=a->getcol());

   int atick = -1;
   //validates atick
   do{
      cout << "Enter your # of adult tickets: ";
      cin >> input;
      //checks is of valid type
      if(isanumber(input)){
         atick=stoi(input);
      }
      else{
         cout << "Invalid Input" << endl;
      }
      if(atick<0){
         cout << "Invalid Number" << endl;
      }
   }while(atick<0);

   int ctick = -1;
   //validates ctick
   do{
      cout << "Enter your # of child tickets: ";
      cin >> input;
      //checks is of valid type
      if(isanumber(input)){
         ctick=stoi(input);
      }
      else{
         cout << "Invalid Input" << endl;
      }
      if(ctick<0){
         cout << "Invalid Number" << endl;
      }
   }while(ctick<0);

   int stick = -1;
   //validates stick
   do{
      cout << "Enter your # of senior tickets: ";
      cin >> input;
      //checks is of valid type
      if(isanumber(input)){
         stick=stoi(input);
      }
      else{
         cout << "Invalid Input" << endl;
      }
      if(stick<0){
         cout << "Invalid Number" << endl;
      }
   }while(stick<0);

   if(!a->availableinrow(atick+ctick+stick,row,col)){ //need to recommend best available
      Node* best = a->bestavailable(atick+ctick+stick);
      if(best!=nullptr){ //seats exist in the auditorium
         //since best returns the right side, need to subtract the total + 1 for starting seat col
         cout << "\nThe best available seat set is [" << best->getpayload()->getrow()+1 << (char)(best->getpayload()->getseat()-(atick+ctick+stick)+1)
         << "-" << best->getpayload()->getrow()+1 << best->getpayload()->getseat() << "], would you like to reserve (Y/N)?: ";
         do{
            cin >> temp;
            if(temp.length()==1){ //makes sure that the input was only one character long
               ctemp = (char)toupper(temp.at(0)); //makes the character uppercase
               if(ctemp != 'Y' && ctemp!='N'){
                  cout << "\nSorry, you have input an invalid input. Please try again." << endl;
               }
            }
            else{
               cout << "\nSorry, you have input an invalid input. Please try again." << endl;
            }
         }while(ctemp!='Y'&&ctemp!='N');
         if(ctemp=='Y'){
            //have to reserve seat starting from the left so subtract 65 (convert from ascii) and then subtract the total + 1 for the left
            a->reserveseats(atick,ctick,stick,best->getpayload()->getrow(),(int)(best->getpayload()->getseat())-65-(atick+ctick+stick)+1);
            //enter as a new order
            struct order ord;
            ord.audnum = a->getnum();
            ord.atick = atick;
            ord.ctick = ctick;
            ord.stick = stick;
            //for each ticket, add corresponding seat
            for(int x=0;x<atick+ctick+stick;x++){
               Seat s(best->getpayload()->getrow(),(char)((int)(best->getpayload()->getseat())-(atick+ctick+stick)+1+x),'.');
               ord.seats.push_back(s);
            }
            //add as NEW order
            u->orders.push_back(ord);
            cout << "\nYour purchase has been processed.";
         }
         else{
            cout << "\nCanceling reservation";
         }
      }
      else{ //no available seats
         cout << "\nno seats available";
      }
      best = nullptr;
   }
   else{ //seats are available
      a->reserveseats(atick,ctick,stick,row,col);
      struct order ord;
      ord.audnum = a->getnum();
      ord.atick = atick;
      ord.ctick = ctick;
      ord.stick = stick;
      //for each ticket, add corresponding seat
      for(int x=0;x<atick+ctick+stick;x++){
         Seat s(row,(char)((int)col+x+65),'.');
         ord.seats.push_back(s);
      }
      //add as NEW order
      u->orders.push_back(ord);
      cout << "\nYour purchase has been processed.";
   }
}

void printordersnonumbers(struct user u){
   //go through all the orders
   for(int x=0;x<(int)u.orders.size();x++){
      struct order ord = u.orders.at(x);
      cout << "Auditorium " << ord.audnum << ", ";
      for(int i=0;i<(int)ord.seats.size();i++){
         cout << ord.seats.at(i).getrow()+1 << (char)(ord.seats.at(i).getseat());
         if(i+1<(int)ord.seats.size()){
            cout << ",";
         }
      }
      cout << endl << ord.atick << " adult, " << ord.ctick << " child, " << ord.stick << " senior" << endl;
   }
}

void printorders(struct user u){
   //go through all the orders
   for(int x=0;x<(int)u.orders.size();x++){
      struct order ord = u.orders.at(x);
      cout << "Order " << x+1 << ":Auditorium " << ord.audnum << ", ";
      for(int i=0;i<(int)ord.seats.size();i++){
         cout << ord.seats.at(i).getrow()+1 << (char)(ord.seats.at(i).getseat());
         if(i+1<(int)ord.seats.size()){
            cout << ",";
         }
      }
      cout << endl << ord.atick << " adult, " << ord.ctick << " child, " << ord.stick << " senior" << endl;
   }
}

void printreceipt(struct user u){
   double order_total = 0;
   double total = 0;
   for(int x=0;x<(int)u.orders.size();x++){
      struct order ord = u.orders.at(x);
      cout << "Auditorium " << ord.audnum << ", ";
      for(int i=0;i<(int)ord.seats.size();i++){
         cout << ord.seats.at(i).getrow()+1 << ord.seats.at(i).getseat();
         if(i+1<(int)ord.seats.size()){
            cout << ",";
         }
      }
      cout << endl << ord.atick << " adult, " << ord.ctick << " child, " << ord.stick << " senior" << endl;
      order_total = ord.atick*10 + ord.ctick*5 + ord.stick*7.5;
      printf("\nOrder Total: %c%.2f\n", '$', (double)order_total);
      total+=order_total;
   }
   printf("\nCustomer Total: %c%.2f\n", '$', (double)total);
}
