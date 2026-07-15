#ifndef MERGESORT_H_INCLUDED
#define MERGESORT_H_INCLUDED

#include "Vector.h"


// Does a merge sort algorithm based for the templated Vector.h


// ----------------------------------------------
// Merges two halves
template <class T>
void Merge(Vector<T>& data, T* temp, int left, int mid, int right)
{
    int leftIndex = left;           // to track left halve index
    int rightIndex = mid + 1;       // to track right halve index
    int tempIndex = left;           // to track the temp array index

    // Sorting goes here
    // Checks if any halve is depleted
    while(leftIndex <= mid && rightIndex <= right)
    {
        // im only building < operator on Vector
        // if left half is smaller
        if(!(data[rightIndex] < data[leftIndex]))
        {
            temp[tempIndex] = data[leftIndex];      // Insert the left one into the temp array
            ++leftIndex;                            // Increase the left index to check next element
        }
        // if right half is smaller
        else
        {
            temp[tempIndex] = data[rightIndex];     // Insert right one into the temp array
            ++rightIndex;                           // Increase the right index to check next element
        }

        ++tempIndex;
    }

    // if there are remaining elements in left halve, insert to the back of the temp array
    while(leftIndex <= mid)
    {
        temp[tempIndex] = data[leftIndex];
        ++leftIndex;
        ++tempIndex;
    }

    // if there are remaining elements in right halve, insert to the back of the temp array
    while(rightIndex <= right)
    {
        temp[tempIndex] = data[rightIndex];
        ++rightIndex;
        ++tempIndex;
    }

    // writes back into the vector
    for(int i = left; i <= right; ++i)
    {
        data[i] = temp[i];
    }
}

// ----------------------------------------------
// Recursive function to reduce left and right halves into single elements
// Vector, temp array, index left, index right
template <class T>
void MergeSort(Vector<T>& data, T* temp, int left, int right)
{
    // Escape clause for recursion (ensures there are at least 2 elements)
    if(left < right)
    {
        int mid = left + (right - left) / 2;        // Find the middle index

        MergeSort(data, temp, left, mid);           // Left half until single element (recursive)
        MergeSort(data, temp, mid + 1, right);      // Right half until single element (recursive)

        Merge(data, temp, left, mid, right);        // Merge two halves together (Sorting portion)
    }
}

// ----------------------------------------------
// Main function to start sorting
template <class T>
void MergeSort(Vector<T>& data)
{
    // Safety check for when Vector only has 1 or less element
    if(data.Size() <= 1)
    {
        return;
    }

    T* temp = new T[data.Size()];                   // Temporary array for merging

    // Start with index 0 for min and Size - 1 for max
    MergeSort(data, temp, 0, data.Size() - 1);      // Start the sorting recursion

    // Free the memory
    delete[] temp;
    temp = 0;
}

#endif // MERGESORT_H_INCLUDED
