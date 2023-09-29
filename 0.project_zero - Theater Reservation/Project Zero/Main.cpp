//Andrew Gerungan CS2337.003 NETID:AWG190000
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cmath>

using namespace std;

void printrow(int row, int cols, char t[10][26]){ //prints a row of the theater
   cout << "\nThis is what the reserved seats for this row currently looks like.\n";
   string chart = "  ";
   for(int c=65;c<cols+65;c++){ //adds the cols of the theater; using ASCII values so start from 65
      chart += (char)c;
   }
   chart += "\n";
   chart += (char)(row+48); //prints out row number (treated as char so use ASCII value)
   chart += " ";
   //loop through given row
   for(int c=0;c<cols;c++){
      if(t[row-1][c]=='.'){ //if empty place .
            chart += ".";
         }
         else{
            chart += "#"; //else place #
         }
   }
   cout << chart;
}

void printtheater(int rows, int cols, char t[10][26]){ //prints the entire theater
   cout << "\nThis is what the reserved seats for this theater currently looks like.\n";
   string chart = "  ";
   for(int c=65;c<cols+65;c++){ //adds the cols of the theater; using ASCII values so start from 65
      chart += (char)c;
      //cout<<"adding col";
   }
   chart += "\n";
   //loop through entire theater
   for(int r=0;r<rows;r++){
      chart += (char)(r+49); //prints out row number (treated as char so use ASCII value)
      chart += " ";
      for(int c=0;c<cols;c++){
         //chart += t[r][c];
         if(t[r][c]=='.'){ //if empty place '.'
            chart += ".";
         }
         else{
            chart += "#"; //else place '#'
         }
      }
      chart += "\n"; //move to next row
   }
   cout << chart;
}

//checks if given row, given starting seat, and total number of tickets is available
int availableinrow (int row, int cols, char t[10][26], int seat1, int total){
   //0=not available,1=available
   //loop through given row with given seat
   for(int c=0;c<cols&&c<total;c++){
      if(t[row-1][c+seat1-1]!='.'){ //if at any point in sequence the seat is not empty, the combination doesn't work and we terminate
         return 0;
      }
   }
   return 1;
}

//checks if given row has available seats for total number of tickets
int availableinrow (int row, int cols, char t[10][26],int total){
   //0=not available,1=available
   int ctr = 0;
   for(int c=0;c<cols;c++){
      if(t[row-1][c]!='.'){
         ctr=0;
         continue;
      }
      if(++ctr==total){
         return 1;
      }
   }
   return 0;
}

//reserves the seat section
void reserveseats (int row, char t[10][26], int seat1, int adult, int child, int senior){
   //for whatever reason, the program kept giving me mondo numbers when I didn't set new variables equivalent to the passed values (idk why tbh)
   int a = adult;
   int c = child;
   int s = senior;
   int total = a+c+s;
   //loop through given row with starting seat
   for(int x=0;x<total;x++){
      //go in order A,C,S
      if(a>0){
         t[row-1][x+seat1-1]='A'; //subtract 1 from seat to align with arrays that start from 0
         a--;
      }
      else if(c>0){
         t[row-1][x+seat1-1]='C';
         c--;
      }
      else if(s>0){
         t[row-1][x+seat1-1]='S';
         s--;
      }
   }
}

//finds best available seat in a row
char bestavailable(int row, int cols, char t[10][26], int total){
   int c_best = 100;
   double middle = ((double)(cols+1)/2)-1; //subtract 1 from middle to align with array (since start from 0)
   //loop through entire row
   for(int c=0;c<cols;c++){
      if(availableinrow(row,cols,t,c+1,total)){ //checks if current column is valid
         //if the current column is closer to the middle than the stored column AND the sides of each are more balanced
         if(abs(middle-c)<abs(middle-c_best)&&abs(abs(middle-c)-abs(middle-(c+total-1)))<=abs(abs(middle-c_best)-abs(middle-(c_best+total-1)))){
         //if(abs(middle-c)<abs(middle-c_best)&&abs(middle-(c+total-1))<abs(middle-(c_best+total-1))){
            c_best = c;
         }
      }
   }
   return (char)(c_best+65); //convert to equivalent ASCII value char
}

//prints out the theater report
void reporttheater(int rows, int cols, char t[10][26]){
   int t_seats, t_ticks, a, c, s; //initially also had an = 0 after s, see below for why changed
   t_seats = t_ticks = a = c = s = 0; //turns out syntax from java of defining and setting only one didn't work so I just put it in a separate line
   double t_price = 0;
   //loop through entire theater
   for(int r=0;r<rows;r++){
      for(int x=0;x<cols;x++){
         t_seats++;
         if(t[r][x]=='A'){
            t_ticks++;
            a++;
            t_price += 10;
         }
         else if(t[r][x]=='C'){
            t_ticks++;
            c++;
            t_price += 5;
         }
         else if(t[r][x]=='S'){
            t_ticks++;
            s++;
            t_price += 7.5;
         }
      }
   }

   //Print Report
   printf("\nTotal Seats: %6d", (int)t_seats);
   printf("\nTotal Tickets: %3d", (int)t_ticks);
   printf("\nAdult Tickets: %3d", (int)a);
   printf("\nChild Tickets: %3d", (int)c);
   printf("\nSenior Tickets: %1d", (int)s);
   printf("\nTotal Sales: %4c%5.2f", '$', (double)t_price);
}

int main(){
   string filename, menu, filedata;
   int menu_input, num_rows, num_cols, c_row, c_seat, c_adult, c_child, c_senior;
   int c_input = -1;
   const int MAX_ROWS = 10;
   const int MAX_COLUMNS = 26;
   char theater[MAX_ROWS][MAX_COLUMNS];
   char c_col;
   bool exit = false;

   num_rows = 0;

   ofstream outfile("A1.txt"); //output will be written into text file called A1
   ifstream infile;

   menu = "\nMENU\n------\n1: Reserve Ticket\n2: Exit\nChoice: ";

   cout << "Input File Name: ";

   cin >> filename; //prompts for filename
   infile.open(filename); //opens file called filename

   //determines theater's number of rows
   if(infile){ //makes sure file opened properly
      while(getline(infile, filedata)){ //go line by line in txt file
         if(filedata.length()>0){ //if current line isn't empty
            num_rows++;
            num_cols = (int)filedata.length();
         }
      }
   }
   else{ //if didn't open properly
      cout << "\"" << filename << "\" did not open correctly. Aborting program.";
      return -1;
   }

   //resets pointer of ifstream
   infile.close();
   infile.open(filename);

   //initializes theater array
   if(infile){ //same as line 184
      for(int r=0;r<num_rows;r++){ //used for loop just to see that it worked both ways *shrug*
         getline(infile, filedata); //stores the line of txt file in filedata
         for(int c=0;c<num_cols;c++){
            theater[r][c] = filedata.at(c); //grabs char at index c from the string (line of txt file)
         }
      }
   }
   else{ //same as line 192
      cout << "\"" << filename << "\" did not open correctly. Aborting program.";
      return -1;
   }
   infile.close();

   while(!exit){ //loops menu/workflow until exit is chosen
      cout << menu; //prints the menu
      cin >> menu_input; //stores input from menu
      if(menu_input == 1){ //reserve ticket
         printtheater(num_rows,num_cols,theater);
         do{ //until they put in a valid row
            cout << "\nPlease choose a row: ";
            cin >> c_input;
            if(c_input < 1 || c_input > num_rows){
               cout << "\nSorry, you have input an invalid row. Please try another row.";
            }
            else{
               printrow(c_input,num_cols,theater);
            }
         }while(c_input < 1 || c_input > num_rows);
         c_row = c_input; //stores inputed row

         //starting seat choice
         do{ //until they put in a valid seat
            cout << "\nPlease choose your starting seat (Seats will be reserved from starting seat consecutively towards the right): ";
            cin >> c_col;
            c_input = c_col-64; //convert char to int equivalent (col)
         }while(c_input < 1 || c_input > num_cols);
         c_seat = c_input; //stores inputed seat

         //# of adult tickets
         do{
            cout << "\nHow many adult tickets would you like?: ";
            cin >> c_input;
         }while(c_input < 0);
         c_adult = c_input; //stores # adult

         //# of child tickets
         do{
            cout << "\nHow many child tickets would you like?: ";
            cin >> c_input;
         }while(c_input < 0);
         c_child = c_input; //stores # child

         //# of senior tickets
         do{
            cout << "\nHow many senior tickets would you like?: ";
            cin >> c_input;
         }while(c_input < 0);
         c_senior = c_input; //stores # senior

         //check row if tickets are available

         //the requested combination is not valid
         if(availableinrow(c_row,num_cols,theater,c_seat,c_adult+c_child+c_senior)<1){
            cout << "Sorry, your desired set of seats is currently unavailable." << endl;
            //recommend best next seat in row
            //-first check that total is available in row
            if(availableinrow(c_row,num_cols,theater,c_adult+c_child+c_senior)<1){ //if total is not available in row
               cout << "no seats available" << endl;
            }
            else{ //total is available so now we search for the best available seat
               char bestseat = bestavailable(c_row,num_cols,theater,c_adult+c_child+c_senior);
               //convert to ASCII equivalence and back
               //subtract 1 from sum since including starting seat
               cout << "The Best Available Seats Are: " << c_row << bestseat << " - " << c_row << (char)((int)(bestseat)+c_adult+c_child+c_senior-1) << endl;
               cout << "Would you like to reserve (Y/N)?"; //prompts user to reserve
               char in;
               cin >> in;
               if(in=='Y'){ //if reserve
                  reserveseats(c_row,theater,(int)(bestseat-64),c_adult,c_child,c_senior); //convert bestseat(char) to int equivalent(col)
                  cout << "\nYour purchase has been processed.";
               }
            }
         }
         //the purchase is valid
         else{
            reserveseats(c_row,theater,c_seat,c_adult,c_child,c_senior);
            cout << "\nYour purchase has been processed.";
         }
      }
      else if(menu_input == 2){ //exit
         exit = true;
      }
      else{ //invalid input
         cout << "Invalid Input. Try Again" << endl;
      }
   }
   //prints the theater report
   reporttheater(num_rows,num_cols,theater);

   //writes the theater to a text file
   for(int r=0;r<num_rows;r++){
      for(int c=0;c<num_cols;c++){
         if(theater[r][c]=='A'){
            outfile << "A";
         }
         else if(theater[r][c]=='C'){
            outfile << "C";
         }
         else if(theater[r][c]=='S'){
            outfile << "S";
         }
         else if(theater[r][c]=='.'){
            outfile << ".";
         }
      }
      outfile << endl;
   }
   return 0;
}

