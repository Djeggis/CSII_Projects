//Andrew Gerungan CS2337.003 NETID:AWG190000
#include <iostream>
#include <fstream>
#include "Gold.h"
#include "Platinum.h"
#include <cmath>
#include <sstream>
#include <iomanip>

using namespace std;

int IDexists(Customer** &, Customer** &, string, int, int);
float getprice(char, string, float, int);
void promote(Customer** &, Customer** &, int, int&, int&, float);

int main()
{
   Customer **regular, **preferred;
   string filename, filedata, fn, ln, ID, drinktype, endcheck, hold;
   char dsize;
   float spent, p_bonus, sqinp;
   int r_length = 0, p_length = 0, o_length = 0, quant = 0, ind = 0;
   bool valid = true;

   ifstream infile;


   //gets the regular customer file and opens it
   cout << "Input regular customer file name: ";
   cin >> filename;
   infile.open(filename);

   if(infile){
      //determines initial size then initializes with said size
      while(getline(infile, filedata)){ //go line by line in data file
         r_length++;
      }
      regular = new Customer*[r_length];
   }
   else{
      cout << "\"" << filename << "\" did not open correctly. Aborting program.";
      return -1;
   }

   //resets
   infile.close();
   infile.open(filename);

   if(infile){
   //sets up the regular customer array with the values in the file
      for(int index=0;index<r_length;index++){
         getline(infile,filedata);
         //parses each line for the individual values
         int space_index = (int)filedata.find(' ', 0); //finds the index of the next space
         ID = filedata.substr(0,space_index); //parses to the space

         int next_space = (int)filedata.find(' ', space_index + 1); //finds the index of the next space after the space before it
         fn = filedata.substr(space_index + 1,next_space - space_index - 1); //parses between the two spaces

         space_index = next_space; //reset starting space
         next_space = (int)filedata.find(' ', space_index + 1); //finds the index of the next space after the space before it
         ln = filedata.substr(space_index + 1, next_space - space_index - 1); //parses between the two spaces

         space_index = next_space; //reset starting space
         next_space = (int)filedata.find(' ', space_index + 1); //finds the index of the next space after the space before it
         spent = stof(filedata.substr(space_index + 1, next_space - space_index - 1)); //parses between the two spaces

         //creates a customer pointer of the found values and sets the index of regular equal to said customer pointer
         Customer* c = new Customer(fn,ln,ID,spent);
         regular[index] = c;
         c = nullptr;
      }
   }
   else{
      cout << "\"" << filename << "\" did not open correctly. Aborting program.";
      return -1;
   }
   infile.close();

   //gets the preferred customer file and opens it
   cout << "Input preferred customer file name: ";
   cin >> filename;
   infile.open(filename);

   if(infile){
      //determines initial size then initializes with said size
      while(getline(infile, filedata)){ //go line by line in data file
         if(filedata.length()>0){
            p_length++;
         }
      }
   }
   //should only initialize if file given was not empty
   if(p_length > 0){
      preferred = new Customer*[p_length];

      //resets
      infile.close();
      infile.open(filename);

      if(infile){
         //sets up the regular customer array with the values in the file
         for(int index=0;index<p_length;index++){
            getline(infile,filedata);
            //parses each line for the individual values
            int space_index = (int)filedata.find(' ', 0); //finds the index of the next space
            ID = filedata.substr(0,space_index); //parses to the space

            int next_space = (int)filedata.find(' ', space_index + 1); //finds the index of the next space after the space before it
            fn = filedata.substr(space_index + 1,next_space - space_index - 1); //parses between the two spaces

            space_index = next_space; //reset starting space
            next_space = (int)filedata.find(' ', space_index + 1); //finds the index of the next space after the space before it
            ln = filedata.substr(space_index + 1, next_space - space_index - 1); //parses between the two spaces

            space_index = next_space; //reset starting space
            next_space = (int)filedata.find(' ', space_index + 1); //finds the index of the next space after the space before it
            spent = stof(filedata.substr(space_index + 1, next_space - space_index - 1)); //parses between the two spaces

            space_index = next_space; //reset starting space
            //if percent sign exists before the next space (last character), then Gold 25 - 28
            if(filedata.at(filedata.length()-1)=='%'){
               p_bonus = stof(filedata.substr(space_index + 1, filedata.length() - space_index - 2));
               Gold* g = new Gold(fn,ln,ID,spent,p_bonus);
               preferred[index] = g;
               g = nullptr;
            }
            //else Platinum
            else{
               p_bonus = stof(filedata.substr(space_index + 1, filedata.length() - space_index - 1));
               Platinum* p = new Platinum(fn,ln,ID,spent,p_bonus);
               preferred[index] = p;
               p = nullptr;
            }
         }
      }
   }


   //load order file and process it
   infile.close();
   cout << "Input order input file name: ";
   cin >> filename;
   infile.open(filename);

   if(infile){
      while(getline(infile,filedata)){
         o_length++;
      }
   }
   else{
      cout << "\"" << filename << "\" did not open correctly. Aborting program.";
      return -1;
   }
   infile.close();
   infile.open(filename);
   if(infile){
      for(int xx=0;xx<o_length;xx++){
         //each loop grabs the order files corresponding line
         getline(infile,filedata);
         valid = true;

         //finds the index of the first space
         int space_index = (int)filedata.find(' ', 0);
         ID=filedata.substr(0,space_index);
         //if ID is a valid ID
         ind = IDexists(regular,preferred,ID,r_length,p_length);
         if(ind>-1){
            int next_space = (int)filedata.find(' ', space_index + 1); //finds the index of the next space after the space before it
            hold = filedata.substr(space_index + 1,next_space - space_index - 1); //parses between the two spaces and stores the substring
            dsize = filedata.at(space_index + 1);
            //if the substring is ONLY a character AND it is a valid size
            if(hold.length()==1 && (dsize == 'S' || dsize == 'M' || dsize == 'L')){
               space_index = next_space; //reset starting space
               next_space = (int)filedata.find(' ', space_index + 1); //finds the index of the next space after the space before it
               drinktype = filedata.substr(space_index + 1,next_space - space_index - 1); //parses between the two spaces
               //if it is a valid drink
               if(drinktype == "soda" || drinktype == "tea" || drinktype == "punch"){
                  space_index = next_space; //reset starting space
                  next_space = (int)filedata.find(' ', space_index + 1); //finds the index of the next space after the space before it
                  sqinp = -1;
                  //if able to parse a float from the substring
                  sqinp=stof(filedata.substr(space_index + 1,next_space - space_index - 1));
                  if(sqinp>=0){ //do need to check decimal since float
                     //then need to check that it only parsed a float
                     for(int x=1;x<next_space-space_index;x++){ //check through the substring
                        //check each individual character to see if it's a number
                        if(((filedata.at(space_index+x)!='.') && (filedata.at(space_index+x))<'0')||(filedata.at(space_index+x))>'9'){
                           valid = false;
                        }
                     }
                     //if successfully parsed only a float (no junk characters)
                     if(valid){
                        space_index = next_space; //reset starting space
                        //since should be the last space before next line, can also check that there are no additional parameters here
                        next_space = (int)filedata.length();
                        quant = -1;
                        //if able to parse an int from the substring
                        quant=stoi(filedata.substr(space_index + 1,next_space - space_index - 1));
                        //need to again check that only parsed an int from the substring
                        if(quant>=0){
                           for(int x=1;x<next_space-space_index;x++){ //check through the substring
                              //check each individual character to see if it's a number
                              if((filedata.at(space_index+x))<'0'||(filedata.at(space_index+x))>'9'){ //don't need to check decimal for int
                                 valid = false;
                              }
                           }
                           //if successfully parsed only an int (no junk characters) and there are no additional parameters
                           if(valid){
                              //processing the order
                              if(ind>=10000){ //was found in the preferred array
                                 ind -= 10000;

                                 //check for what type of preferred
                                 Customer *goldcheck = nullptr;
                                 goldcheck = dynamic_cast<Gold*>(preferred[ind]);
                                 //checks if it was able to be dynamically cast as a gold
                                 if(goldcheck){ //is a gold
                                    //calculates current total with discount
                                    float total = preferred[ind]->getspent() + getprice(dsize,drinktype,sqinp,quant)*((float)1-dynamic_cast<Gold*>(preferred[ind])->getdp()*(float).01);

                                    //if the current discount percentage is less than 10% and the total reaches over the $100 threshold
                                    if(total>=100 && dynamic_cast<Gold*>(preferred[ind])->getdp()<10){
                                       //set new discount
                                       dynamic_cast<Gold*>(preferred[ind])->setdp(10);

                                       //recalculate using the 10% discount then check again for next promotion
                                       total = preferred[ind]->getspent() + getprice(dsize,drinktype,sqinp,quant)*((float)1-dynamic_cast<Gold*>(preferred[ind])->getdp()*(float).01);
                                    }
                                    //if the current discount percentage is less than 15% and the total reaches over the $150 threshold
                                    if(total>=150 && dynamic_cast<Gold*>(preferred[ind])->getdp()<15){
                                       //set new discount
                                       dynamic_cast<Gold*>(preferred[ind])->setdp(15);

                                       //recalculate using the 15% discount then check again for next promotion
                                       total = preferred[ind]->getspent() + getprice(dsize,drinktype,sqinp,quant)*((float)1-dynamic_cast<Gold*>(preferred[ind])->getdp()*(float).01);
                                    }
                                    //now check if we can promote to platinum (should only be promoting when we've already reached 15% threshold)
                                    if(total>=200 && dynamic_cast<Gold*>(preferred[ind])->getdp()==15){
                                       //calculate bonus bucks
                                       int bonus_bucks = (int)(total-(float)200)/5;

                                       //then turn into Platinum using total

                                       //first create platinum pointer to hold old gold information except with the new spent value
                                       Platinum *newp = new Platinum(preferred[ind]->getfn(),preferred[ind]->getln(),preferred[ind]->getgID(),total,(float)bonus_bucks);

                                       //then remove allocated memory for old gold
                                       preferred[ind]=nullptr;

                                       //finally set the index equal to the created platinum pointer
                                       preferred[ind] = newp;

                                       //then have newp not point to same as to not have multiple pointers pointing to same
                                       newp = nullptr;

                                    }
                                    //else we just set the new spent amount since its still a gold
                                    else{
                                       preferred[ind]->setspent(total);
                                    }
                                 }
                                 else{ //is a plat since couldn't be cast as gold
                                    //calculates the amount spent with the bonus bucks discount added, making sure that the amount spent is not negative
                                    float discountspent = (getprice(dsize,drinktype,sqinp,quant)-dynamic_cast<Platinum*>(preferred[ind])->getbb()<0)?0:getprice(dsize,drinktype,sqinp,quant)-dynamic_cast<Platinum*>(preferred[ind])->getbb();
                                    //calculates the remaining amount of bonus bucks after applying discount, making sure that the bonus bucks don't become negative
                                    float remainingbb = (dynamic_cast<Platinum*>(preferred[ind])->getbb()-getprice(dsize,drinktype,sqinp,quant)<0)?0:dynamic_cast<Platinum*>(preferred[ind])->getbb()-getprice(dsize,drinktype,sqinp,quant);
                                    //calculates the new total amount spent with discount
                                    float total = dynamic_cast<Platinum*>(preferred[ind])->getspent() + discountspent;
                                    //calculates the amount of bonus bucks gained from the discounted purchase
                                    int newbb = ((int)(total-(float)200)/5)-((int)(preferred[ind]->getspent()-(float)200)/5);
                                    //adds the discount spent to the total amount spent and sets the index's spent to it
                                    preferred[ind]->setspent(total);
                                    //sets the amount of bonus bucks equal to the remaining amount plus the newly calculated amount gained from the discounted purchase
                                    dynamic_cast<Platinum*>(preferred[ind])->setbb(remainingbb + (float)newbb);
                                 }
                                 //sets to nullptr as to not have a dangling pointer
                                 goldcheck = nullptr;
                              }
                              else{ //was found in the regular array
                                 //calculate total spent first
                                 float total = regular[ind]->getspent() + getprice(dsize,drinktype,sqinp,quant);
                                 int discount = 0;
                                 //check for gold promotions then
                                 if(total>=50){
                                    //recalculate using the 5% discount then check again for next promotion
                                    total = regular[ind]->getspent() + (float).95*getprice(dsize,drinktype,sqinp,quant);

                                    discount = 5;

                                    if(total>=100){
                                       //recalculate using the 10% discount then check again for next promotion
                                       total = regular[ind]->getspent() + (float).9*getprice(dsize,drinktype,sqinp,quant);
                                       discount=10;
                                    }
                                    if(total>=150){
                                       //recalculate using the 15% discount then check again for final promotion
                                       total = regular[ind]->getspent() + (float).85*getprice(dsize,drinktype,sqinp,quant);
                                       discount=15;
                                    }
                                    if(total>=200){
                                       //we promote to platinum so calculate bonus bucks (discount is used for bonus bucks)
                                       discount=(int)(total-(float)200)/5;
                                    }
                                    regular[ind]->setspent(total);
                                    promote(regular,preferred,ind,r_length,p_length,(float)discount);
                                 }
                                 else{
                                    regular[ind]->setspent(total);
                                 }
                              }
                           }
                        }
                     }
                  }
               }
            }
         }
      }
   }
   else{
      cout << "\"" << filename << "\" did not open correctly. Aborting program.";
      return -1;
   }
   infile.close();

   //Write output into file
   ofstream outfile("customer.dat");
   for(int x=0;x<r_length;x++){ //customer.dat
      outfile << regular[x]->getgID() << " ";
      outfile << regular[x]->getfn() << " ";
      outfile << regular[x]->getln() << " ";
      outfile << setprecision(2) << fixed << (float)regular[x]->getspent() << endl;
   }
   outfile = ofstream("preferred.dat");
   for(int x=0;x<p_length;x++){ //preferred.dat
      outfile << preferred[x]->getgID() << " ";
      outfile << preferred[x]->getfn() << " ";
      outfile << preferred[x]->getln() << " ";
      outfile << setprecision(2) << fixed << (float)preferred[x]->getspent() << " ";
      //check if the given index is a gold or platinum
      Customer *goldcheck = nullptr;
      goldcheck = dynamic_cast<Gold*>(preferred[x]);
      if(goldcheck){
         outfile << (int)(dynamic_cast<Gold*>(preferred[x])->getdp()) << '%';
      }
      else{
         outfile << setprecision(0) << fixed << dynamic_cast<Platinum*>(preferred[x])->getbb();
      }
      outfile << endl;
   }

}

int IDexists(Customer** &ptr, Customer** &ptr2, string ID, int rlength, int plength){
   //loop through regular array to find if ID exists
   for(int x=0;x<rlength;x++){
      if(ptr[x]->getgID()==ID){
         return x;
      }
   }

   //loop through preferred array to find if ID exists
   for(int x=0;x<plength;x++){
      if(ptr2[x]->getgID()==ID){
         return x+10000;
      }
   }
   return -1;
}

float getprice(char s, string dt, float sqp, int q){
   float p = 0;
   float d,h,oz,dmult;
   if(dt=="soda"){
      dmult=(float).20;
   }
   else if(dt=="tea"){
      dmult=(float).12;
   }
   else{
      dmult=(float).15;
   }
   //calculates the price based on the factors; 2pirh=SA
   if(s=='S'){ //d = 4in, h = 4.5in, 12oz
      d=(float)4;
      h=(float)4.5;
      oz=(float)12;
   }
   else if(s=='M'){ //d = 4.5in, h = 5.75in, 20oz
      d=(float)4.5;
      h=(float)5.75;
      oz=(float)20;
   }
   //if size is L
   else{ //d = 5.5in, h = 7in, 32oz
      d=(float)5.5;
      h=(float)7;
      oz=(float)32;
   }

   float surf_area = ((float)M_PI*d*h*sqp);
   float drink = dmult*oz;
   p = (float)(surf_area+drink)*(float)q;

   return p;
}

void promote(Customer** &ptr, Customer** &ptr2, int index, int& rlength, int& plength, float hd){
   //setup promoted customer
   Customer *promoted = nullptr;
   //grab the original values
   Customer *original = ptr[index];
   string hfn = original->getfn();
   string hln = original->getln();
   string hID = original->getgID();
   float hspent = original->getspent();

   //check if going to be a platinum
   if(hspent>=200){
      promoted = new Platinum(hfn,hln,hID,hspent,hd);
   }
   //else it will be a gold
   else{
      promoted = new Gold(hfn,hln,hID,hspent,hd);
   }
   //removing from regular
   Customer **place = new Customer*[rlength-1];
   int ni = 0;
   for(int x=0;x<rlength;x++){
      if(x==index){
         continue;
      }
      place[ni] = ptr[x];
      ni++;
   }

   //delete everything inside of ptr before deleting pointer to array
   for(int x=0;x<rlength;x++){
      ptr[x]=nullptr;
   }
   delete[]ptr;
   ptr = place;
   place = nullptr;
   rlength--;

   //add to preferred
   place = new Customer*[plength+1];
   for(int x=0;x<plength+1;x++){
      if(x==plength){
         place[x]=promoted;
         promoted = nullptr;
      }
      else{
         place[x]=ptr2[x];
      }
   }

   //delete everything inside of ptr2 before deleting pointer to array
   for(int x=0;x<plength;x++){
      ptr2[x]=nullptr;
   }
   if(plength>0){
      delete[]ptr2;
   }
   ptr2 = place;
   place = nullptr;
   plength++;

   original = nullptr;
   promoted = nullptr;
}
