#include "the1.h"

// DO NOT CHANGE ABOVE THIS LINE!
// you may implement helper functions below
int recur = 0;
unsigned short result = 0;

void swapping(unsigned short* a, unsigned short* b) {
    unsigned short temp = *a;
    *a = *b;
    *b = temp;
}

void partition(unsigned short* A, int start, int end, long& swap) {
    recur++;

    if (start >= end) {
        return;
    }

    int i = start + 1;
    int j = start + 1;
    int k = end;
    unsigned short pivot = A[start];

    while (j <= k) {
        if (A[j] == pivot) {
            j++;
        } else if (A[j] < pivot) {
            swap++;
            swapping(&A[i], &A[j]);
            i++;
            j++;
        } else {
            swap++;
            swapping(&A[j], &A[k]);
            k--;
        }
    }

    swap++;
    swapping(&A[start], &A[i - 1]);

    partition(A, start, i - 2, swap); 
    partition(A, j, end, swap);      
}


std::pair<unsigned short, unsigned int> select_k_with_quick_sort3(unsigned short *arr,
                                                                  const unsigned int size,
                                                                  const unsigned int index,
                                                                  long &swap){
    recur = 0; 
    partition(arr, 0, size - 1, swap); 

    return std::make_pair(arr[index], recur);
}

void quick_partition(unsigned short* A, int start, int end, long& swap, const unsigned int index) {
    recur++;

    if (start >= end) {
        return;
    }

    int i = start + 1;
    int j = start + 1;
    int k = end;
    unsigned short pivot = A[start];

    while (j <= k) {
        if (A[j] == pivot) {
            j++;
        } else if (A[j] < pivot) {
            swap++;
            swapping(&A[i], &A[j]);
            i++;
            j++;
        } else {
            swap++;
            swapping(&A[j], &A[k]);
            k--;
        }
    }

    swap++;
    swapping(&A[start], &A[i - 1]);
    
    if(index < i-1){
        quick_partition(A, start, i - 2, swap, index); 
    }
    else if(index < j){
        result = A[i-1];
    }
    else{
        quick_partition(A, j, end, swap, index);    
    }
}


std::pair<unsigned short, unsigned int> quick_select3(unsigned short *arr,
                                                      const unsigned int size,
                                                      const unsigned int index,
                                                      long &swap){
    recur = 0; 
    result = 0;
    quick_partition(arr, 0, size - 1, swap, index); 

    return std::make_pair(result, recur);
}
