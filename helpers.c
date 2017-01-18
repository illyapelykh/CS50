/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // TODO: implement a searching algorithm
    if (n < 0)
    return false;
    
    int start = 0;
    int finish = n-1;
    
    while(start <= finish)
    {
        int middle = (start + finish) / 2;
        
        if(values[middle] == value)
        {
            return true;
        }
        else if(value < values[middle])
        {
            finish = middle - 1;
        }
        else if(value > values[middle])
        {
            start = middle + 1;
        }
    }
    
    return false;
    
    
    /**else if (n > 0)
    {
        for (int i=0; i < n; i++)
        {
            if (values[i] == value)
            {
            return true;
            break;
            }
        }
    }
    return false;
    */
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
    for(int i=0; i < n - 1; i++)
    {
        int min = values[i];
        int min_pos = i;
        
        for(int j = i + 1; j < n; j++)
        {
            if(values[j] < min)
            {
                min = values[j];
                min_pos = j;
            }
            
        }
        
        int temp = values[i];
        values[i] = min;
        values[min_pos] = temp;
        
    }
    
    
    return;
}
