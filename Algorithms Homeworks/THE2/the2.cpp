#include "the2.h"

// DO NOT CHANGE ABOVE THIS LINE!
// you may implement helper functions below

int getCharValue(char ch) {
    if (ch == '?') return 0; 
    return (ch - 'A' + 1); 
}

long getGroupValue(const std::string &str, int start, int group_size) {
    long value = 0;
    long base = static_cast<long>(std::pow(27, group_size - 1)); 
    
    for (int i = start; i < start + group_size && i < str.size(); i++) {
        value += getCharValue(str[i]) * base;
        base /= 27;
    }
    return value;
}

long countingSort(std::string *arr, int size, int start, int group_size, bool ascending) {
    std::vector<std::string> output(size);
    long max_value = std::pow(27, group_size);
    std::vector<int> count(max_value, 0);
    long iterations = 0;

    for (int i = 0; i < size; i++) {
        long groupValue = getGroupValue(arr[i], start, group_size);
        count[groupValue]++;
        iterations++;
    }

    if (ascending) {
        for (int i = 1; i < max_value; i++) {
            count[i] += count[i - 1];
            iterations++;
        }
    } else {
        for (int i = max_value - 2; i >= 0; i--) {
            count[i] += count[i + 1];
            iterations++;
        }
    }

    for (int i = size - 1; i >= 0; i--) {
        long index = getGroupValue(arr[i], start, group_size);
        output[count[index] - 1] = arr[i];
        count[index]--;
        iterations++;
    }

    for (int i = 0; i < size; i++) {
        arr[i] = output[i];
        iterations++;
    }

    return iterations;
}

void trimPadding(std::string *arr, int size) {
    for (int i = 0; i < size; i++) {
        size_t pos = arr[i].find_last_not_of('?');
        if (pos != std::string::npos) {
            arr[i].erase(pos + 1);
        } else {
            arr[i].clear();
        }
    }
}

long multi_digit_string_radix_sort(std::string *arr, const int size, const bool ascending, const int group_size) {
    int maxLen = 0;
    long totalIterations = 0;

    for (int i = 0; i < size; i++) {
        int len = arr[i].length();
        if (len > maxLen) maxLen = len;
    }

    for (int i = 0; i < size; i++) {
        while (arr[i].length() < maxLen) {
            arr[i] += '?';
        }
    }

    int numPasses = (maxLen + group_size - 1) / group_size;
    
    int bucket_size = group_size;
    int start = maxLen;
    
    for (int i=0; i<numPasses; i++) { 
        start -= group_size;
        if(start<0){
            bucket_size += start;
            start=0;
        }
        
        totalIterations += countingSort(arr, size, start, bucket_size, ascending);
    }

    trimPadding(arr, size);

    return totalIterations;
}

