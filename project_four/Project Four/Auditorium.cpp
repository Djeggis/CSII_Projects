//Andrew Gerungan CS2337.003 NETID:AWG190000
#include "Auditorium.h"

Auditorium::Auditorium(std::string filename, int n){
   num = n;
   std::ifstream infile;
   infile.open(filename);
   std::string filedata;

   num_row=0;
   num_col=0;
   if(infile){
      while(getline(infile,filedata)){
         if(filedata.length()>0){
            num_row++;
            num_col=(int)filedata.length();
         }
      }
   }
   else{ //if file doesn't open
      std::cout << "\"" << filename << "\" did not open correctly.";
   }

   infile.close();
   infile.open(filename);


   first = new Node;
   Node* p = first;
   for(int r=0;r<num_row;r++){ //creates the auditorium as a doubly linked list
      getline(infile,filedata);
      for(int c=0;c<num_col;c++){
         p->setpayload(new Seat(r,(char)(c+65),filedata.at(c)));
         if(r!=num_row-1 || c+1<num_col){
            Node* right = new Node;
            p->setright(right);
            right->setleft(p);
            p=right;
            right=nullptr;
         }
      }
   }
   //reset pointer p and create new one num_col away from the beginning (at the next row)
   p = first;
   Node* p2 = first;
   for(int x=0;x<num_col;x++){
      p2 = p2->getright();
   }

   while(true){
      //sets ups and downs together
      p->setdown(p2);
      p2->setup(p);
      //if we haven't reached the end yet
      if(p2->getright()!=nullptr){
         p = p->getright();
         p2 = p2->getright();
      }
      //end if we have
      else{
         break;
      }
   }
   //auditorium is now a quadruply linked list but we have to clean up the edges, starting with the rights
   while(true){
      //use p2 bc already at the end of the list
      p2->setright(nullptr);
      //if we can still move up
      if(p2->getup()!=nullptr){
         p2 = p2->getup();
      }
      //end if not
      else{
         break;
      }
   }
   //now clean up the lefts
   p = first;
   while(true){
      p->setleft(nullptr);
      //if we can still move down
      if(p->getdown()!=nullptr){
         p = p->getdown();
      }
      //end if not
      else{
         break;
      }
   }
   //auditorium is now constructed but need to clean up created pointers to not have pointer issues
   p = nullptr;
   p2 = nullptr;
}

std::string Auditorium::getauditorium(){
   std::string s = "";
   Node* p = first; //moving pointer
   Node* p2 = first; //keeps track of left side
   while(true){ //loops through row
      while(true){ //loops through column
         s += p2->getpayload()->getticktype();
         if(p2->getright()!=nullptr){
            p2 = p2->getright();
         }
         else{
            break;
         }
      }
      if(p->getdown()!=nullptr){ //keep going if down exists
         s+= "\n";
         p = p->getdown();
         p2 = p;
      }
      else{
         break;
      }
   }
   p=nullptr;
   p2=nullptr;
   return s;
}

std::string Auditorium::printauditorium(){
   std::string s = "";
   Node* p = first; //moving pointer
   Node* p2 = first; //keeps track of left side
   s+= "  ";
   //adds the column letters
   while(true){
      s+=p2->getpayload()->getseat();
      if(p2->getright()!=nullptr){
         p2 = p2->getright();
      }
      else{
         break;
      }
   }
   p2 = first;
   s+= "\n";

   //prints the actual auditorium
   while(true){ //loops through rows
      s+=(char)(p->getpayload()->getrow()+49); //since adding char need to convert to ascii
      s+=" ";
      while(true){ //loops through columns
         s += (p2->getpayload()->getticktype()!='.')?'#':'.';
         if(p2->getright()!=nullptr){
            p2 = p2->getright();
         }
         else{
            break;
         }
      }
      if(p->getdown()!=nullptr){ //keep going if down exists
         s+= "\n";
         p = p->getdown();
         p2 = p;
      }
      else{
         break;
      }
   }
   p=nullptr;
   p2=nullptr;
   return s;
}

Node* Auditorium::getindex(int row, int col){
   Node* p = first;
   for(int r=0;r<row;r++){ //move down row times
      p = p->getdown();
   }
   for(int c=0;c<col;c++){ //move right col times
      p = p->getright();
   }
   return p;
   p=nullptr;
}

bool Auditorium::availableinrow(int total, int row, int col){
   int tracker = 0; //keeps track of consecutive empty
   Node* p = getindex(row, col); //starting seat node
   while(true){ //loops through columns starting at node p
      if(p->getpayload()->getticktype()=='.'){
         tracker++;
         if(tracker==total){
            return true;
         }
      }
      else{ //if any stops before reach seats desired
         return false;
      }
      if(p->getright()!=nullptr){ //keeps going until can't go right anymore
         p = p->getright();
      }
      else{
         break;
      }
   }
   return false;
   p = nullptr;
}

void Auditorium::reserveseats(int a,int c,int s,int row, int col){
   int atrack = 0, ctrack = 0, strack = 0;
   Node* p = getindex(row, col); //starts from node @ index
   while(true){ //loops through columns
      if(atrack<a){
         p->getpayload()->setticktype('A');
         atrack++;
      }
      else if(ctrack<c){
         p->getpayload()->setticktype('C');
         ctrack++;
      }
      else if(strack<s){
         p->getpayload()->setticktype('S');
         strack++;
      }
      else{
         break;
      }
      p = p->getright(); //don't need to check if has right since validated before using this method
   }
   p = nullptr;
}

Node* Auditorium::bestavailable(int total){
   float middle_row = ((float)(num_row+1)/2)-1;
   int tracker = 0; //checks  for consecutive seats
   Node* p = first, *left = first, *best = nullptr;
   while(true){ //going through rows
      while(true){ //going through columns
         if(p->getpayload()->getticktype()=='.'){
            tracker++;
            if(tracker>=total && best == nullptr){ //if the best is null right now
               best = p;
            }
            else if(tracker>=total && closertomiddle(p,best,total)>-1){ //checks that the new is closer or the same to middle
               if(closertomiddle(p,best,total)==0 && abs((float)(p->getpayload()->getrow())-middle_row)<abs((float)(best->getpayload()->getrow())-middle_row)){ //if same, needs to be closer row
                  best = p;
               }
               else if(closertomiddle(p,best,total)==1){ //if distance is shorter
                  best = p;
               }
            }
            else if(tracker>=total){
            }
         }
         else{ //if any breaks, reset
            tracker = 0;
         }
         if(p->getright()!=nullptr){ //checks that right still exists
            p = p->getright();
         }
         else{
            break;
         }
      }
      if(left->getdown()!=nullptr){ //checks that down still exists
         tracker = 0;
         p = left->getdown();
         left = left->getdown();
      }
      else{
         break;
      }
   }
   return best;
   best = nullptr;
   p = nullptr;
}

int Auditorium::closertomiddle(Node* comp, Node* og, int total){
   float middle_col = ((float)(num_col+1)/2)-1;
   float middle_row = ((float)(num_row+1)/2)-1;
   float middle_seat = ((float)(total-1)/2); //makes sure the comparison of the seat set goes from the middle of the seat set
   //compare the distances using pythag to calculate distance to middle
   float comp2mid = (float)(sqrt(pow((float)(comp->getpayload()->getrow())-middle_row,2)+pow(((float)(comp->getpayload()->getseat())-middle_seat-65)-middle_col,2)));
   float og2mid = (float)(sqrt(pow((float)(og->getpayload()->getrow())-middle_row,2)+pow(((float)(og->getpayload()->getseat())-middle_seat-65)-middle_col,2)));
   if(comp2mid < og2mid){ //if distance is shorter
      return 1;
   }
   else if(comp2mid == og2mid){ //if distance is same
      return 0;
   }
   else{ //if not closer at all
      return -1;
   }
}
