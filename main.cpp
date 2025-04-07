#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <math.h>
using namespace std;

void merge(vector<int> &a, vector<int> aux, int l, int m, int r)
{
    int i = l, j = m + 1, k = l;
    aux = a;
    while (i <= m && j <= r)
    {
        if (aux[i] < aux[j])
        {
            a[k++] = aux[i++];
        }
        else
        {
            a[k++] = aux[j++];
        }
    }
    while (i <= m)
    {
        a[k++] = aux[i++];
    }
    while (j <= r)
    {
        a[k++] = aux[j++];
    }
}

void mergeSort(vector<int> &a, vector<int> aux, int l, int r)
{
    if (l >= r)
        return;
    int m = l + (r - l) / 2;
    mergeSort(a, aux, l, m);
    mergeSort(a, aux, m + 1, r);
    merge(a, aux, l, m, r);
}

void mergeSort(vector<int> &a)
{
    int n = a.size();
    vector<int> aux(n);
    mergeSort(a, aux, 0, n - 1);
}

int binarySearch(vector<int> a, int low, int high, int target)
{
    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        if (a[mid] == target)
        {
            return mid;
        }
        else if (a[mid] > target)
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }
    return low;
}

void insertionBinarySort(vector<int> &a, int low, int high)
{
    for (int i = low + 1; i <= high; i++)
    {
        int j = i - 1;
        int target = a[i];
        int idx = binarySearch(a, low, j, target);
        while (idx <= j)
        {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = target;
    }
}

void insertionBinarySort(vector<int> &a)
{
    int n = a.size();
    insertionBinarySort(a, 0, n - 1);
}

void heapify(vector<int> &a, int i, int n)
{
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    int largest = i;
    if (l < n && a[l] > a[largest])
    {
        largest = l;
    }
    if (r < n && a[r] > a[largest])
    {
        largest = r;
    }
    if (largest != i)
    {
        swap(a[i], a[largest]);
        heapify(a, largest, n);
    }
}

void heapSort(vector<int> &a)
{
    int n = a.size();
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(a, i, n);
    }
    for (int i = n - 1; i >= 0; i--)
    {
        swap(a[0], a[i]);
        heapify(a, 0, i);
    }
}

void naturalMergeSort(vector<int>& a){
    int n = a.size();
    vector <int> starts(n + 1);
    starts[0] = 0;
    int runCount = 0;
    for(int i = 1; i <= n; i++){
        if(i == n || a[i] < a[i - 1])
            starts[++runCount] = i;
    }

    vector <int> aux(n);
    while(runCount > 1){
        int newRunCount = 0;
        for(int i = 0; i < runCount - 1; i += 2){
            merge(a, aux, starts[i], starts[i + 1] - 1, starts[i + 2] - 1);
            starts[newRunCount++] = starts[i];
        }

        if(runCount % 2 == 1){
            starts[newRunCount++] = starts[runCount - 1];
        }

        starts[newRunCount] = n;
        runCount = newRunCount;
    }
}

void insertionSort(vector<int>& a){
    int n = a.size();
    for(int i = 1; i < n; i++){
        int v = a[i], j;
        for(j = i; j > 0 && v < a[j - 1]; j--)
            a[j] = a[j - 1];
        a[j] = v;
    }
}

void radixSort(vector<int>& a){
    int n = a.size();
    vector <int> aux(n);

    int iMax = 0;
    for(int i = 1; i < n; i++){
        if(a[i] > a[iMax]){
            iMax = i;
        }
    }
    int maxBit = (a[iMax] == 0) ? -1 : log2(a[iMax]);
    
    for(int i = 0; i <= maxBit; i++){
        int id = 0;
        int mask = 1 << i;
        for(int j = 0; j < n; j++)
            if(!(a[j] & mask)) aux[id++] = a[j];
        for(int j = 0; j < n; j++)
            if(a[j] & mask) aux[id++] = a[j];
        a = aux;
    }
}

vector<int> generateRandomSortedArray(const vector<int>& rdArr){
    int n = rdArr.size();
    vector <int> rdsArr(n);
    rdsArr = rdArr;
    mergeSort(rdsArr);
    return rdsArr;
}

vector<int> generateRandomArray(int k, int n)
{
    vector<int> a(n);
    for (int i = 0; i < n; i++)
    {
        a[i] = rand() % (k + 1);
    }
    return a;
}

int main()
{
    srand(time(NULL));
    int n, k;
    cout << "Enter the number of elements (n): ";
    cin >> n;
    cout << "Enter the maximum value (k): ";
    cin >> k;

    vector<int> a = generateRandomArray(k, n);
    for (auto x : a)
    {
        cout << x << " ";
    }
    cout << endl;

    radixSort(a);
    for (auto x : a)
    {
        cout << x << " ";
    }

    return 0;
}