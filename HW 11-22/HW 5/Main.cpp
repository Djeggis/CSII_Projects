//Andrew Gerungan CS2337.003 NETID:AWG190000
#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <algorithm>

using namespace std;

class Graph{
private:
   vector<vector<int>*> adjacency;
   int curr_size;
   int max_size;
   vector<int> visited;
public:
   Graph(){curr_size=0;max_size=10;};
   Graph(int i){curr_size=0;max_size=i;};

   bool isEmpty(){return curr_size==0;};
   void createGraph(string);
   bool isConnected(int,bool);
};

void Graph::createGraph(string s){
   ifstream infile;
   infile.open(s);
   string filedata;
   int currvert = 0;

   if(infile){
      while(getline(infile,filedata)){
         if(filedata.length()>0){
            if(isEmpty()){
               for(int x=0;x<stoi(filedata);x++){
                  adjacency.push_back(new vector<int>);
                  curr_size++;
               }
            }
            else{
               int index = 0;
               string hold = filedata;
               //cout << hold << endl;
               index = (int)hold.find(' ');
               currvert = stoi(hold.substr(0,index))-1;
               //cout << index << endl;
               if((int)hold.length()>1){
                  while((int)hold.length()>0){
                     //cout << currvert << ": " << stoi(hold.substr(0, index))-1 << endl;
                     adjacency.at(currvert)->push_back(stoi(hold.substr(0, index))-1);
                     if((int)hold.length()==1){
                        break;
                     }
                     hold.erase(0, index+1);
                     //cout << hold.length() << endl;
                     index = (int)hold.find(' ');
                  }
               }
            }
         }
      }
   }
}

bool Graph::isConnected(int vertex=0,bool start=true){
   if(start){
      for(int v=0;v<curr_size;v++){
         if(!isConnected(v,false)){
            cout << v << ": " << "sucks!" << endl;
            return false;
         }
         else{
            cout << v << ": " << "is good!" << endl;
         }
         visited.clear();
      }
   }
   else{
      //start @ index 0
      visited.push_back(vertex);
      for(int x=0;x<(int)adjacency.at(vertex)->size();x++){
         bool found = false;
         for(int i=0;i<(int)visited.size();i++){
            if(adjacency.at(vertex)->at(x)==visited.at(i)){
               cout << "already found " << adjacency.at(vertex)->at(x) << endl;
               found = true;
            }
         }
         if(!found){
            isConnected(adjacency.at(vertex)->at(x),false);
         }
      }
      return (int)visited.size()==curr_size;
   }
   return true;
}

int main()
{
   Graph g;
   string input = "";
   cout << "Enter filename: " << endl;
   cin >> input;

   g.createGraph(input);

   if(g.isConnected()){
      cout << "connected" << endl;
   }
   else{
      cout << "not connected" << endl;
   }

   return 0;
}
