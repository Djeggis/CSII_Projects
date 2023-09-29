//Andrew Gerungan CS2337.003 NETID:AWG190000
#include <iostream>
#include <fstream>
#include "DVD.h"
#include "BSTree.h"
#include <sstream>
#include <iomanip>

using namespace std;

bool isanumber(string);
bool adddvd(string, BSTree<DVD*>&);
bool removedvd(string, BSTree<DVD*>&);
bool rentdvd(string, BSTree<DVD*>&);
bool returndvd(string, BSTree<DVD*>&);
void printreport(BSTree<DVD*>);

int main()
{
   string filename, filedata, title, op;
   int quantA, quantR;
   BSTree<DVD*> tree;

   ifstream infile;
   ofstream outfile("error.log");

   //gets the inventory file and opens it
   cout << "Input inventory file name: ";
   cin >> filename;
   infile.open(filename);

   if(infile){ //builds the BSTree
      while(getline(infile,filedata)){ //for each line of the file
         //look for next comma
         int comma_index = (int)filedata.find(',',0);
         //substr from after quotation marks (1) to before quotation marks (next comma-2)
         title = filedata.substr(1,comma_index-2);

         //look for next comma
         int next_comma = (int)filedata.find(',',comma_index+1);
         //substr from after comma to right before next comma
         quantA = stoi(filedata.substr(comma_index+1,next_comma-comma_index-1));

         //look for next comma
         comma_index = next_comma;
         next_comma = (int)filedata.find(',',comma_index+1);
         //substr from after comma to right before next comma
         quantR = stoi(filedata.substr(comma_index+1,next_comma-comma_index-1));

         DVD* d = new DVD(title,quantA,quantR);
         tree.insertnode(new Node<DVD*>(d),tree.getroot());
         d=nullptr;
      }
   }
   else{ //if file doesn't open
      cout << "\"" << filename << "\" did not open correctly. Aborting program.";
      return -1;
   }

   infile.close();

   //gets the transaction file and opens it
   cout << "Input transaction file name: ";
   cin >> filename;
   infile.open(filename);

   if(infile){ //processes the transactions
      while(getline(infile,filedata)){
         //looks for first space for operation
         int space_index = (int)filedata.find(' ',0);
         op = filedata.substr(0,space_index);

         if(op == "add"){
            //attempt to add substr from after operation to end, if not able to, add to error log
            if(!adddvd(filedata.substr(space_index+1),tree)){ //if invalid
               outfile << filedata << endl;
            }
         }
         else if(op == "remove"){
            //attempt to add substr from after operation to end, if not able to, add to error log
            if(!removedvd(filedata.substr(space_index+1),tree)){ //if invalid
               outfile << filedata << endl;
            }
         }
         else if(op == "rent"){
            //attempt to add substr from after operation to end, if not able to, add to error log
            if(!rentdvd(filedata.substr(space_index+1),tree)){ //if invalid
               outfile << filedata << endl;
            }
         }
         else if(op == "return"){
            //attempt to add substr from after operation to end, if not able to, add to error log
            if(!returndvd(filedata.substr(space_index+1),tree)){ //if invalid
               outfile << filedata << endl;
            }
         }
         //invalid operation
         else{
            outfile << filedata << endl;
         }
      }
   }
   else{ //if file didn't open :/
      cout << "\"" << filename << "\" did not open correctly. Aborting program.";
      return -1;
   }

   infile.close();

   //prints out the report by getting a string and parsing so that I can format
   printreport(tree);

   return 0;
}

bool adddvd(string s, BSTree<DVD*>& t){
   //gets index of comma
   int comma_index = (int)s.find(',',0);
   //substrings from beginning of what should be quotations to right before what should be end quotations
   string title = s.substr(1,comma_index-2);
   //checks that from comma to end is just a number, if not doesn't add
   if(isanumber(s.substr(comma_index+1))){
      //parses the int from comma to end
      int quant = stoi(s.substr(comma_index+1));
      Node<DVD*>* node = new Node<DVD*>(new DVD(title,quant,0));
      //checks that title exists
      Node<DVD*>* existing = t.searchnode(node,t.getroot());
      //if it exists, add to already existing
      if(existing!=nullptr){
         existing->getpayload()->setavailable(existing->getpayload()->getavailable()+quant);
      }
      //else add to tree
      else{
         t.insertnode(node,t.getroot());
      }
      return true;
   }
   return false;
}

bool removedvd(string s, BSTree<DVD*>& t){
   //gets index of comma
   int comma_index = (int)s.find(',',0);
   //substrings from beginning of what should be quotations to right before what should be end quotations
   string title = s.substr(1,comma_index-2);
   //checks that from comma to end is just a number, if not doesn't add
   if(isanumber(s.substr(comma_index+1))){
      //parses the int from comma to end
      int quant = stoi(s.substr(comma_index+1));
      //checks that the title exists
      Node<DVD*>* node = t.searchnode(new Node<DVD*>(new DVD(title,quant,0)),t.getroot());
      //if exists in the tree but removing would be over the available + rented then delete
      if(node!= nullptr && node->getpayload()->getavailable()+node->getpayload()->getrented()-quant<=0){
         t.deletenode(node,t.getroot());
      }
      //else just decrease available
      else if(node!=nullptr){
         node->getpayload()->setavailable(node->getpayload()->getavailable()-quant);
      }
      else{
         return false;
      }
      return true;
      node = nullptr;
   }
   return false;
}

bool rentdvd(string s, BSTree<DVD*>& t){
   //substrings from beginning of what should be quotations to right before what should be end quotations
   string title = s.substr(1,s.length()-2);
   Node<DVD*>* node = t.searchnode(new Node<DVD*>(new DVD(title,0,0)),t.getroot());
   //if the node exists in the tree
   if(node!=nullptr){
      //decrease amount available and increase amount rented
      node->getpayload()->setavailable(node->getpayload()->getavailable()-1);
      node->getpayload()->setrented(node->getpayload()->getrented()+1);
      return true;
      node = nullptr;
   }
   return false;
}

bool returndvd(string s, BSTree<DVD*>& t){
   //substrings from beginning of what should be quotations to right before what should be end quotations
   string title = s.substr(1,s.length()-2);
   Node<DVD*>* node = t.searchnode(new Node<DVD*>(new DVD(title,0,0)),t.getroot());
   //if the node exists in the tree
   if(node!=nullptr){
      //increase amount available and decrease amount rented
      node->getpayload()->setavailable(node->getpayload()->getavailable()+1);
      node->getpayload()->setrented(node->getpayload()->getrented()-1);
      return true;
      node = nullptr;
   }
   return false;
}

void printreport(BSTree<DVD*> t){
   cout << endl;
   string full = t.ordered(t.getroot());
   istringstream iss(full);
   string line;
   while(getline(iss,line)){
      //finds next comma
      int comma_index = (int)line.find(',',0);
      string title = line.substr(0,comma_index);

      //look for next comma
      int next_comma = (int)line.find(',',comma_index+1);
      //substr from after comma to right before next comma
      string quantA = (line.substr(comma_index+1,next_comma-comma_index-1));

      //substr from after next comma to end
      string quantR = (line.substr(next_comma+1));

      //prints it out formatted neat
      cout << left << setw(45) << title;
      cout << left << setw(5) << quantA;
      cout << right << quantR << endl;
   }
}

bool isanumber(string s){
   //goes through entire string but first checks that string exists
   if((int)s.length()==0){
      return false;
   }
   for(int x=0;x<(int)s.length();x++){
      //if any character is not an integer, false (-1)
      if(s.at(x)<'0' || s.at(x)>'9'){
         return false;
      }
   }
   //return true (0)
   return true;
}


