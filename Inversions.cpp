#include <bits/stdc++.h>
using namespace std;
int numElems;

void printVector(vector<long long>* vec){
  int size = vec->size();
  for(int i=0; i<size; i++)
    cout<<vec->at(i)<<" ";
  cout<<endl;
}

//returns the first or the second half (specified by index, 0 and 1 respectively) 
//of the given vector as a new vector
vector<long long>* subVector(vector<long long>* vec, int index){
  int startIndex = index == 0 ? 0 : vec->size()/2;
  int endIndex = index == 0 ? vec->size()/2 -1 : vec->size() -1;

  vector<long long>* thisVector = new vector<long long>();
  for(int i=startIndex; i<=endIndex; i++)
    thisVector->push_back(vec->at(i));

  return thisVector;
}

//merges 2 subVectors into 1 vector
//while doing so, also counts how many inversions (a,b)
//are there, where
//a belongs to left and b belongs to right
long long merge_and_count(vector<long long>* left, vector<long long>* right, vector<long long>* both){
  left->push_back(LONG_MAX); right->push_back(LONG_MAX);
  int leftIndex = 0; int leftSize = left->size() -1;
  int rightIndex = 0; int rightSize = right->size() -1;

  long long splitInversions = 0;
  
  while( leftIndex < left->size() -1 || rightIndex < right->size() -1 ){
    if( left->at(leftIndex) <= right->at(rightIndex) ){
      both->at(leftIndex+rightIndex) = left->at(leftIndex);
      leftIndex++;
    } else {
      both->at(leftIndex+rightIndex) = right->at(rightIndex);
      splitInversions += leftSize - leftIndex;
      rightIndex++;
    }
  }
  
  return splitInversions;
}

//divide and conquer: (functions correctly returns the number of inversions)
//number of inversions inside this vector is
//number of inversions inside first half
//plus number of inversions inside second half
//plus number of inversions between this two splits
long long sort_and_count(vector<long long>* vec){
  if(vec->size() == 1)
    return 0;
  
  vector<long long>* left = subVector(vec, 0);
  vector<long long>* right = subVector(vec, 1);

  long long leftInversions = sort_and_count(left);
  long long rightInversions = sort_and_count(right);
  long long splitInversions = merge_and_count(left, right, vec);

  return leftInversions + rightInversions + splitInversions;
}

//this method build a vector from a raw numbers inside the "input.txt"
void readInput(vector<long long>* vec){
  ifstream inputStream; inputStream.open("inputFiles/advice.txt");
  inputStream >> numElems;
  long x;
  for(int i=0; i<numElems; i++){
    inputStream >> x;
    vec->push_back(x);
  }
}

main(){
  vector<long long>* vec = new vector<long long>();
  readInput(vec);

  long long numInversions = sort_and_count(vec);
  cout<<"number of inversions are: "<<numInversions<<endl;
}
