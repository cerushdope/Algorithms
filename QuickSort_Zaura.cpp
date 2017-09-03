#include <bits/stdc++.h>
using namespace std;
void printVector(vector<long long>* vec);

int numElems;
vector<long long>* vec = new vector<long long>();

void swapElems(vector<long long>* vec, int first, int second){
  if(first == second) return;

  long long tmp = vec->at(first);
  vec->at(first) = vec->at(second);
  vec->at(second) = tmp;
}

//randomly chooses the pivot (randomness is crucial for average n*log(n) running time)
int choosePivot(vector<long long>* vec, int start, int end){
  int segment = end-start+1;
  int curRand = rand() % segment;
  return start + curRand;
}

void quickSort(vector<long long>* vec, int start, int end){
  //base_case:
  if(start >= end) return;

  //logic:
  //always move pivot element in the beginning (makes coding easier)
  int pivotIndex = choosePivot(vec, start, end);
  swapElems(vec, pivotIndex, start);
  pivotIndex = start;
  
  int smallerPart = start;
  for(int j=start+1; j<=end; j++){
    if( vec->at(j) >= vec->at(pivotIndex) ){
      //all good
      continue;
    }
    
    if( vec->at(j) < vec->at(pivotIndex) ){
      smallerPart++;
      swapElems(vec, j, smallerPart);
    }
  }
  //carry pivot element to it's correct place:
  swapElems(vec, pivotIndex, smallerPart);
  pivotIndex = smallerPart;

  //sort left and right halves:
  quickSort(vec, start, pivotIndex-1);
  quickSort(vec, pivotIndex+1, end);
}

void readInput(){
  ifstream inputStream; inputStream.open("inputFiles/QuickSort_input.txt");
  inputStream >> numElems;
  
  long long x;
  for(int i=0; i<numElems; i++){
    inputStream >> x;
    vec->push_back(x);
  }
}

main(){
  //need it to initialize random generator:
  srand(time(NULL));
  
  readInput();
  quickSort(vec, 0, vec->size()-1);

  printVector(vec);
}



void printVector(vector<long long>* vec){
  cout<<"sorted vector looks like this: "<<endl;
  int size = vec->size();
  for(int i=0; i<size; i++){
    cout<< vec->at(i) <<" ";
  }cout << endl;
}
