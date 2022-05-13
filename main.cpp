#include <iostream>
#include <time.h>
#include <thread>
#include <chrono>
#include <math.h>

using namespace std;
using namespace std::chrono;

int gap = 4;

void merge(int array[], int left, int mid, int right)
{
    int leftSize = mid - left + 1;
    int rightSize = right - mid;
    int* leftArr = new int[leftSize];
    int* rightArr = new int[rightSize];

    for (int i = 0; i < leftSize; i++)
    {
        leftArr[i] = array[left + i];
    }
    for (int i = 0; i < rightSize; i++)
    {
        rightArr[i] = array[mid + 1 + i];
    }
    int leftIndex = 0;
    int rightIndex = 0;
    int mergedIndex = left;
    while(leftIndex < leftSize && rightIndex < rightSize)
    {
        if (leftArr[leftIndex] <= rightArr[rightIndex])
        {
            array[mergedIndex] = leftArr[leftIndex];
            leftIndex++;
        }
        else
        {
            array[mergedIndex] = rightArr[rightIndex];
            rightIndex++;
        }
        mergedIndex++;
    }
    while (leftIndex < leftSize)
    {
        array[mergedIndex] = leftArr[leftIndex];
        leftIndex++;
        mergedIndex++;
    }
    while (rightIndex < rightSize)
    {
        array[mergedIndex] = rightArr[rightIndex];
        rightIndex++;
        mergedIndex++;
    }
}

void MergeSort(int array[], int first, int last)
{
    if (first >= last)
    {
        return;
    }
    int mid = first + (last - first) / 2;
    //MergeSort(array, first, mid);
    //MergeSort(array, mid + 1, last);
    thread t1(MergeSort, array, first, mid);
    thread t2(MergeSort, array, mid + 1, last);
    t1.join();
    t2.join();
    merge(array, first, mid, last);
}

int* CreateArray(int size)
{
    int* arr = new int[size];
    for (int i = 0; i < size; i++)
    {
        arr[i] = rand();
    }
    return arr;
}

void PrintArray(int* const arr, int const size)
{
    for (int i = 0; i < size; i++)
    {
        cout<<arr[i]<<" ";
    }
    cout<<'\n';
}

int main()
{
    srand(time(NULL));
    int size, exponents;
    cout<<"Input base size: ";
    cin>>size;
    cout<<"Input highest power of 10 to multiply by: ";
    cin>>exponents;
    for (int i = 0; i < exponents; i++)
    {
        int tempSize = size * pow(10, i);
        int* arr = CreateArray(size);
        auto start = high_resolution_clock::now();
        MergeSort(arr, 0, size - 1);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout<<"Execution time for array of size "<<tempSize<<" : "<<duration.count()<<" microseconds\n";
    }


}