/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>

#include "helpers.h"


bool binarySearch(int key, int values[], int min, int max) {
    // if you are at the end of the array, it isn't in there
    if (min > max) {
        return false;
    }
    else if (min < max) {
        // get the midpoint, bit shift right returns a midpoint that's half and always an int
        int mid = (max + min) >> 1;
        
        // if the midpoint less than the key, only focus on higher half
        if (values[mid] < key) {
            return binarySearch(key, values, mid+1, max);
        }
        // if the midpoint is more than the key, need to look in lower end
        else if (values[mid] > key) {
            return binarySearch(key, values, min, mid-1);
        }
        // if the midpoint is equal to the key we have our man!
        else {
            return true;
        }
    }
    // if min and max are equal, only one item in array, if it matches key, all good
    else if (max == min && values[max] == key) {
        return true;
    }
    // if we get here, min and max must be equal (only one item in array)
    // but if that last value doesn't match the key, it's not in the array
    else return false;
}


/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    unsigned int min = 0;
    unsigned int max = n-1;
    
    if(binarySearch(value, values, min, max)) return true;
    else return false;
}


/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    int count;
    
    do {
        count = 0;
        for (int c = 0; c < n-1; c++) {
            if (values[c] > values[c+1]) {
                int temp = values[c];
                values[c] = values[c+1];
                values[c+1] = temp;  
                count++;
            }
        }
    }    
    while (count > 0);
    

    return;
}