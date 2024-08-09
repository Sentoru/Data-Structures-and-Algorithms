#include <iostream>
#include <fstream>
#include <time.h>
#include <iomanip>
using namespace std;

void swap(int &a, int &b)
{
    int c = a;
    a = b;
    b = c;
}

void selectionSort(long a[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < n; j++)
        {
            if (a[j] < a[min])
                min = j;
        }
        swap(a[min], a[i]);
    }
}

void insertionSort(long a[], int n)
{
    int x, j;
    for (int i = 0; i < n; i++)
    {
        x = a[i];
        j = i - 1;
        while (0 <= j && x < a[j])
        {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = x;
    }
}

void interchangeSort(long a[], int n)
{
    for (int i = 0; i < n-1; i++)
    {
        for (int j = i+1; j < n; j++)
        {
            if (a[i] > a[j])
                swap(a[i], a[j]);
        }
    }
}

void bubbleSort(long a[], int n)
{
    for (int i = 0; i < n-1; i++)
    {
        for (int j = n-1; j > i; j--)
        {
            if (a[j-1] > a[j])
                swap(a[j], a[j-1]);
        }   
    }
}

void merge(long a[], int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    long *L = NULL, *R = NULL;
    L = new long[n1];
    R = new long[n2];
    
    // Copy elements from the original array to new arrays L[], R[]
    for (int i = 0; i < n1; i++)
        L[i] = a[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = a[mid + 1 + j];

    // Combine two arrays to array a[]
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            a[k] = L[i];
            i++;
        }
        else
        {
            a[k] = R[j];
            j++;
        }
        k++;
    }
    
    // Copy remaining elements from array L[] to a[] if needed
    while (i < n1)
    {
        a[k] = L[i];
        i++;
        k++;
    }

    // Copy remaining elements from array R[] to a[] if needed
    while (j < n2)
    {
        a[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
    L = NULL;
    R = NULL;
}

/**
 * Average: O(nlogn)
 * Best time: 2.042s (Took time to create and delete dynamic memory allocation) 
 */
void mergeSort(long a[], int left, int right)
{
    if (left < right)
    {
        // Avoid interger overflow
        int m = left + (right - left)/2;
        mergeSort(a, left, m);
        mergeSort(a, m+1, right);
        merge(a, left, m, right);
    }
}

/**
 * Best: O(logn)
 * Worst: O(n^2)
 * Best time: 0.134s
 */
void quickSort(long a[], int left, int right)
{
    int pivot = a[(left + right)/2];
    int i = left;
    int j = right;
    while (i <= j)
    {
        while (a[i] < pivot)
            i++;
        while (a[j] > pivot)
            j--;
        if (i <= j)
        {
            swap(a[i], a[j]);
            i++;
            j--;
        }
    }
    if (left < j)
        quickSort(a, left, j);
    if (i < right)
        quickSort(a, i, right);
}

void printList(long a[], int n)
{
    ofstream outFile("SortedList.txt");
    if (outFile.is_open())
    {
        for (long i = 0; i < n; i++)
            outFile << a[i] << "\n";
    }
}

int main()
{
    ifstream inFile("Dayso.txt");
    long *a = NULL;
    long n;

    clock_t start, end;
    double duration;

    if (inFile.is_open())
    {
        inFile >> n;
        a = new long[n];
        for (long i = 0; i < n; i++)
            inFile >> a[i];
        inFile.close();
    }
    cout << "Da doc xong file!\n";
    
    start = clock();
    // selectionSort(a, n);
    // insertionSort(a, n);
    // interchangeSort(a, n);
    // mergeSort(a, 0, n-1);
    // quickSort(a, 0, n-1);
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "Takes " << fixed << setprecision(4) << duration << " seconds!";

    printList(a, n);

    delete[]a;
    a = NULL;

    return 0;
}