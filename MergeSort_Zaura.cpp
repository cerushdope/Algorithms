#include <bits/stdc++.h>
using namespace std;
int numElems;

void printVector(vector<long>* vec){
  for(int i=0; i<vec->size(); i++)
    cout<<vec->at(i)<<" ";
  cout<<endl;
}

//for index = 0, returns first half of the vector, as a vector
//for index = 1, returns second half of the vector, as a vector
vector<long>* subVector(vector<long>* vec, int index){
  int startIndex = index == 0 ? 0 : vec->size()/2;
  int endIndex = index == 0 ? vec->size()/2-1 : vec->size()-1;

  
  vector<long>* thisVector = new vector<long>();
  for(int i = startIndex; i <=endIndex; i++){
    thisVector->push_back(vec->at(i));
  }
  return thisVector;
}

void merge(vector<long>* first, vector<long>* second, vector<long>* together){
  first->push_back(LONG_MAX); second->push_back(LONG_MAX);
  int firstIndex = 0;
  int secondIndex = 0;

  while( firstIndex < first->size()-1 || secondIndex < second->size()-1 ){
    if(first->at(firstIndex) < second->at(secondIndex)){
      together->at(firstIndex + secondIndex) = first->at(firstIndex);
      firstIndex++;
    }
    else{
      together->at(firstIndex + secondIndex) = second->at(secondIndex);
      secondIndex++;
    }
  }
}

vector<long>* mergeSort(vector<long>* vec){
  if(vec->size() == 1)
    return vec;
  
  vector<long>* first = subVector(vec, 0);
  vector<long>* second = subVector(vec, 1);

  mergeSort(first);
  mergeSort(second);
  merge(first, second, vec);
  
  delete(first); delete(second);
  return vec;
}

//reads raw numbers from inputFile and creates vector with those
void readInput(vector<long>* vec){
  ifstream inputStream; inputStream.open("inputFiles/MergeSort_input.txt");
  inputStream >> numElems;

  long x;
  for(int i=0; i<numElems; i++){
    inputStream >> x;
    vec->push_back(x);
  }
}

//writes random numbers inside input file to be sorted
void randomInput(){
  ofstream outStream; outStream.open("inputFiles/MergeSort_input.txt");
  srand(time(NULL));
  int numElems = 1000000;
  outStream << numElems << "\n";
  for(int i=0; i<numElems; i++){
    int curElement = rand()%(10000000);
    outStream << curElement <<" ";
  }
}

main(){
  vector<long>* vec = new vector<long>();

  //uncomment this if you want to run mergeSort on your own tests:
  randomInput();
  readInput(vec);
  mergeSort(vec);

  //printVector(vec);
  cout<<"done working"<<endl;
}
