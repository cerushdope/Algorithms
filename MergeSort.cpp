#include <iostream>
#include <vector>
using namespace std;

//Given three arrays - main array, right array and left array,
//copys left and right arrays elements into main array in sorted order
void merge_arrays(vector <int>& main_array, vector <int>& left_array_to_merge, vector <int>& right_array_to_merge){
    //Counters to keep track of each arrays current number
    int left_counter = 0;
    int right_counter = 0;
    int main_counter = 0;
    
    //While both arrays still have elements to use take the minimum element from them and
    //push it into main array.
    while(left_counter != left_array_to_merge.size() && right_counter != right_array_to_merge.size()){
        if(left_array_to_merge[left_counter] < right_array_to_merge[right_counter]){
            main_array[main_counter] = left_array_to_merge[left_counter];
            left_counter++;
        }else{
            main_array[main_counter] = right_array_to_merge[right_counter];
            right_counter++;
        }
        main_counter++;
    }

    //When one of the side array's elements are used, take the other array
    //and push its elements into the main array.
    while(left_counter != left_array_to_merge.size()){
        main_array[main_counter] = left_array_to_merge[left_counter];
        left_counter++;
        main_counter++;
    }

    while(right_counter != right_array_to_merge.size()){
        main_array[main_counter] = right_array_to_merge[right_counter];
        right_counter++;
        main_counter++;
    }
}

//Given an array, left margin and right margin, creates and returns the sub array containing
//elements from given array's left margin index (inclusive) to its right margin index (not inclusive)
vector <int> get_subarray(vector <int>& array_to_split, int left_margin, int right_margin){
    //Create the subarray
    vector <int> subarray;
    
    //Push elements from give arrays left margin to its right margin in newly allocated array
    for(int i = left_margin; i < right_margin; i++){
        subarray.push_back(array_to_split[i]);
    }

    return subarray;
}

//Given an array splits it, sorts the split arrays and merges them
//into the given array.
void merge_sort(vector <int>& array_to_sort){
    //Get the size of the array.
    int size_of_array = array_to_sort.size();
    //If size is already 1 (i.e is already sorted) return.
    if(size_of_array == 1)
        return;
    
    //Split the array into to arrays of equal length
    vector <int> left_array = get_subarray(array_to_sort, 0, size_of_array / 2);
    vector <int> right_array = get_subarray(array_to_sort, size_of_array / 2, array_to_sort.size());
    
    //Sort each of the given array.
    merge_sort(left_array);
    merge_sort(right_array);
    
    //Merge the sorted arrays.
    merge_arrays(array_to_sort, left_array, right_array);
}

int main(){
    int array_size;
    cin>>array_size;

    vector <int> array_to_sort;

    for(int i = 0; i < array_size; i++){
        int next_number;
        cin >> next_number;

        array_to_sort.push_back(next_number);
    }

    merge_sort(array_to_sort);

    cout<<"Sorted the array and elements now look like: "<<endl;
    for(int i = 0; i < array_to_sort.size(); i ++){
        cout<<array_to_sort[i]<<" ";
    }
    return 0;
}
