#include <iostream>
#include <array>
#include <list>
#include <cstdlib>

using namespace std;

void bsort(int[]);
void ssort(int[]);
void isort(int[]);

void qsort(int[],int,int,int&,int&);
void isort(int[]);
void msort(int[]);

int part(int[], int, int,int&,int&);
void swaps(int&,int&);

int main()
{
   int array1[5000];
   int array2[5000];
   int array3[5000];

   int array4[5000];
   int array6[5000];

   for(int x=0;x<5000;x++){
      int r = rand()%5000;

      array1[x]=r;
      array2[x]=r;
      array3[x]=r;
   }

   ////////////////////////////////////////////////////////////////

   for(int x=0;x<5000;x++){
      int r = rand()%5000;

      array4[x]=r;
      array6[x]=r;
   }

   bsort(array1);
   ssort(array2);
   isort(array3);

   int comp = 0;
   int asgn = 0;
   qsort(array4,0,4999,comp,asgn);
   cout << "Quick Sort on List Comparisons: " << comp << endl;
   cout << "Quick Sort on List Assignments: " << asgn << endl;
   /*
   msort(array6);*/
}

void bsort(int arr[]){
   int comp = 0;
   int asgn = 0;
   while(true){
      bool swapped = false;
      asgn+=2;
      for(int x=0;x<4999;x++){
         if(arr[x+1]<arr[x]){
            int hold = arr[x];
            asgn++;
            arr[x] = arr[x+1];
            asgn++;
            arr[x+1] = hold;
            asgn++;
            swapped=true;
         }
         comp+=2;
      }
      comp++;
      if(!swapped){
         break;
      }
      comp++;
   }
   cout << "Bubble Sort Comparison (Array): " << comp << endl;
   cout << "Bubble Sort Assignment (Array): " << asgn << endl;
}

void ssort(int arr[]){
   int comp = 0;
   int asgn = 0;
   asgn++;
   for(int x=0;x<5000;x++){
      int min_index = -1;
      asgn++;
      for(int i=x+1;i<5000;i++){
         if(arr[i]<arr[x]){
            min_index = i;
            asgn++;
         }
         comp+=2;
      }
      comp++;
      if(min_index>-1){
         int hold = arr[x];
         asgn++;
         arr[x] = arr[min_index];
         asgn++;
         arr[min_index] = hold;
         asgn++;
      }
      comp+=2;
   }
   comp++;
   cout << "Selection Sort Comparison (Array): " << comp << endl;
   cout << "Selection Sort Assignment (Array): " << asgn << endl;
}

void isort(int arr[]){
   int comp = 0;
   int asgn = 0;
   asgn++;
   for(int i=0;i<5000;i++){
      int temp = arr[i];
      asgn++;
      int j = i;
      asgn++;
      while(j>0&&arr[j-1]>temp){
         comp++;
         arr[j] = arr[j-1];
         asgn++;
         j = j-1;
         asgn++;
      }
      arr[j] = temp;
      asgn++;
      comp++;
   }
   comp++;
   cout << "Insertion Sort Comparison (Array): " << comp << endl;
   cout << "Insertion Sort Assignment (Array): " << asgn << endl;
}

void qsort(int arr[], int low, int high, int& c, int& a){
   if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
        at right place */
        int pi = part(arr, low, high,c,a);

        // Separately sort elements before
        // partition and after partition
        qsort(arr, low, pi - 1,c,a);
        qsort(arr, pi + 1, high,c,a);
    }
}

void msort(int arr[]){

}

int part(int arr[], int low, int high, int& c, int& a)
{
   int pivot = arr[high]; // pivot
   int i = (low - 1); // Index of smaller element
   a+=2;

   a++;
   for (int j = low; j <= high - 1; j++)
   {
     // If current element is smaller than the pivot
     if (arr[j] < pivot)
     {
         i++; // increment index of smaller element
         swaps(arr[i], arr[j]);
         a+=3;
     }
     c+=2;
   }
   c++;
   swaps(arr[i + 1], arr[high]);
   a+=3;
   return (i + 1);
}

void swaps(int& i, int& j){
   int hold = i;
   i=j;
   j=hold;
}
