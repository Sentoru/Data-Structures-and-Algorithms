#include <iostream>
#define MAX 100
using namespace std;

void input(int a[], const int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << "a[" << i << "] = ";
        cin >> a[i];
    }
}

void search(const int a[], const int n, int key)
{
    for (int i = 0; i < n; i++)
    {
        if (a[i] == key)
        {
            cout << "Tim thay so " << key << endl;
            return;
        }
    }
    cout << "Khong tim thay so " << key << endl;
}

int binarySearch(int a[], int n, int key)
{
    int left = 0;
    int right = n - 1;
    int mid;

    while (left <= right)
    {
        mid = (left + right) / 2;
        if (a[mid] == key)
            return mid;
        else if (a[mid] > key)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return -1;
}

int findMax(int a[], int n)
{
    int max = a[0];
    for (int i = 1; i < n; i++)
    {
        if (a[i] > max)
            max = a[i];
    }
    return max;
}

int findMax2(int a[], int n)
{
    if (n < 2)
    {
        cout << "Danh sach khong du phan tu de tim gia tri!\n";
        return -1;
    }

    int max = a[0];
    int max2 = a[1];

    if (max < max2)
        swap(max, max2);
    
    for (int i = 2; i < n; i++)
    {
        if (a[i] > max)
        {
            max2 = max;
            max = a[i];
        }
        else if (a[i] > max2 && a[i] != max)
            max2 = a[i];
    }

    return max2;
}

void addLast(int a[], int &n, int key)
{
    if (n < MAX)
        a[n++] = key;
}

void addPos(int a[], int &n, int pos, int key)
{
    if (pos >= 0 && pos < n)
    {
        n++;
        for (int i = n; i >= pos; i--)
        {
            a[i] = a[i - 1];
        }
        a[pos] = key;
    }
    else cout << "Vi tri khong hop le!\n";
}

void deleteLast(int a[], int &n)
{
    n--;
}

void deletePos(int a[], int &n, int pos)
{
    if (pos >= 0 && pos < n)
    {
        for (int i = pos; i < n; i++)
        {
            a[i] = a[i + 1];
        }
        n--;
    }
    else cout << "Vi tri khong hop le!\n";
}

void output(const int a[], const int n)
{
    for (int i = 0; i < n; i++)
        cout << a[i] << "\t";
    cout << endl;
}

void selectionSort(int a[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int max = i;
        for (int j = i + 1; j < n; j++)
        {
            if (a[j] > a[max])
                max = j;
        }
        swap(a[max], a[i]);
    }
}

void insertionSort(int a[], int n)
{
    int x, j;
    for (int i = 0; i < n; i++)
    {
        x = a[i];
        j = i - 1;
        while (j >= 0 && x > a[j])
        {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = x;
    }   
}

void bubbleSort(int a[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = n - 1; j > i; j--)
        {
            if (a[j - 1] < a[j])
                swap(a[j-1], a[j]);
        }
    }
}

void interchangeSort(int a[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (a[i] < a[j])
                swap(a[i], a[j]);
        }
    }    
}

void quickSort(int a[], int left, int right)
{
    int pivot = a[(left + right)/2];
    int i = left;
    int j = right;

    while (i <= j)
    {
        while (a[i] > pivot)
            i++;
        while (a[j] < pivot)
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

void quickSortNoRec(int a[], int left, int right)
{
    int pivot, i, j;
    int l = left, r = right;

    while (l < r)
    {
        pivot = a[(l + r) / 2];
        i = l;
        j = r;

        while (i <= j)
        {
            while (a[i] > pivot)
                i++;
            while (a[j] < pivot)
                j--;
            if (i <= j)
            {
                swap(a[i], a[j]);
                i++;
                j--;
            }
        }

        if (l < j)
        {
            // l = l;
            r = j;
        }
        else
        {
            l = i;
            r = right;
        }
    }
}

void merge(int a[], int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int L[n1], R[n2];
    
    // Copy elements from the original array to new arrays L[], R[]
    for (int i = 0; i < n1; i++)
        L[i] = a[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = a[mid + 1 + j];

    // Combine two arrays to array a[]
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
    {
        if (L[i] >= R[j])
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
}

void mergeSort(int a[], int left, int right)
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

void heapify(int a[], int n, int i)
{
    int min = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && a[left] < a[min])
        min = left;
    
    if (right < n && a[right] < a[min])
        min = right;

    if (min != i)
    {
        swap(a[i], a[min]);
        heapify(a, n, min);
    }
}

void heapSort(int a[], int n)
{
    for (int i = n/2 - 1; i >= 0; i--)
        heapify(a, n, i);

    for (int i = n - 1; i >= 0; i--)
    {
        swap(a[0], a[i]);
        heapify(a, i, 0);
    }
}

int main()
{
    int a[MAX];
    int n, key, pos;

    cout << "Nhap so luong phan tu: ";
    cin >> n;
    input(a, n);

    cout << "=== DANH SACH ===\n";
    output(a, n);

    heapSort(a, n);
    cout << "=== DANH SACH SAU KHI SAP XEP ===\n";
    output(a, n);

    cout << "Nhap so can tim: ";
    cin >> key;

    if (binarySearch(a, n, key) != -1)
        cout << "Tim thay " << key << endl;
    else cout << "Khong tim thay!\n";   

    return 0;
}