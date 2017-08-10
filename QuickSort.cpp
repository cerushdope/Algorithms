#include <iostream>
#include <vector>
using namespace std;


//Given array and two indexes, swaps elements on that indexes in that array.
void swap_elements(int array_to_modify [], int first_element_index, int second_element_index){
    int temporary_storage =  array_to_modify[first_element_index];
    array_to_modify[first_element_index] = array_to_modify[second_element_index];
    array_to_modify[second_element_index] = temporary_storage;
}

//Given array and two margins, makes a partitioning of array by making a
//element on last margin a pivot and rearranging array so that every element
//greater than pivot is right of pivot in array and every element less than pivot
//is left of pivot in array. returns the margin i.e index where elements bigger
//than pivot and elements lesser than pivot meet each other.
int partition_array(int array_to_partition [], int left_margin, int right_margin){
    //Get the value of the pivot i.e get the last element in subarray.
    int pivot_value = array_to_partition[right_margin-1];
    //Initialize counter for keeping track of where the
    //elements - lesser than pivot is no more.
    int lesser_elements_counter = left_margin - 1;

    //Iterate over all elements from left index to pivot index (not inclusive)
    //rearrange them so that element more than pivot is right
    //and elements less than pivot are left.
    for(int i = left_margin; i < right_margin - 1; i ++){
        //If curent element is equal or more than pivot then just increase i,
        //else case increment lesser element coutner by one (so that it points
        //first element that is greater than pivot) and swap that index with
        //i (which is guaranteed that is less than pivot.
        if(array_to_partition[i] < pivot_value){
            lesser_elements_counter ++;
            swap_elements(array_to_partition, lesser_elements_counter, i);
        }
    }

    //If the margin between elements more than and less than pivot is greater
    //than pivot itself swap the index of pivot and that margin.
    if(array_to_partition[lesser_elements_counter + 1] > pivot_value)
        swap_elements(array_to_partition, lesser_elements_counter + 1, right_margin - 1);

    //return margin.
    return lesser_elements_counter + 1;
}

//Sorts the given array from left margin to right margin (not inclusive).
//By partitioning on each element.
void quicksort(int array_to_sort [], int left_margin, int right_margin){
    //If there is only one or no element in the given borders finish working
    if(right_margin - left_margin <= 1)
        return;

    //Get the margin of where the partitioning made border of elements
    //more than and less than pivot.
    int middle_margin = partition_array(array_to_sort, left_margin, right_margin);

    //Provided the partition is already done on one element.
    //recursively sorts both subarrays left and right of middle margin.
    quicksort(array_to_sort, left_margin, middle_margin);
    quicksort(array_to_sort, middle_margin + 1, right_margin);
}

int main(){
    int array_size;
    cin>>array_size;

    int arr [array_size];

    for(int i = 0; i < array_size; i++){
        int next_number;
        cin >> arr[i];
    }

    quicksort(arr, 0, array_size);

    cout << "Finished sorting, elements are:" << endl;
    for(int i = 0; i < array_size; i ++){
        cout << arr[i] << " ";
    }

    return 0;
}
