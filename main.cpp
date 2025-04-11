#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <random>
#include <chrono>
#include <algorithm>
using namespace std;
using namespace chrono;

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

void binaryInsertionSort(vector<int> &a, int low, int high)
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

void binaryInsertionSort(vector<int> &a)
{
    int n = a.size();
    binaryInsertionSort(a, 0, n - 1);
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

void naturalMergeSort(vector<int> &a)
{
    int n = a.size();
    vector<int> starts(n + 1);
    starts[0] = 0;
    int runCount = 0;
    for (int i = 1; i <= n; i++)
    {
        if (i == n || a[i] < a[i - 1])
            starts[++runCount] = i;
    }

    vector<int> aux(n);
    while (runCount > 1)
    {
        int newRunCount = 0;
        for (int i = 0; i < runCount - 1; i += 2)
        {
            merge(a, aux, starts[i], starts[i + 1] - 1, starts[i + 2] - 1);
            starts[newRunCount++] = starts[i];
        }

        if (runCount % 2 == 1)
        {
            starts[newRunCount++] = starts[runCount - 1];
        }

        starts[newRunCount] = n;
        runCount = newRunCount;
    }
}

void insertionSort(vector<int> &a)
{
    int n = a.size();
    for (int i = 1; i < n; i++)
    {
        int v = a[i], j;
        for (j = i; j > 0 && v < a[j - 1]; j--)
            a[j] = a[j - 1];
        a[j] = v;
    }
}

void radixSort(vector<int> &a)
{
    int n = a.size();
    vector<int> aux(n);

    int iMax = 0;
    for (int i = 1; i < n; i++)
    {
        if (a[i] > a[iMax])
        {
            iMax = i;
        }
    }
    int maxBit = (a[iMax] == 0) ? -1 : log2(a[iMax]);

    for (int i = 0; i <= maxBit; i++)
    {
        int id = 0;
        int mask = 1 << i;
        for (int j = 0; j < n; j++)
            if (!(a[j] & mask))
                aux[id++] = a[j];
        for (int j = 0; j < n; j++)
            if (a[j] & mask)
                aux[id++] = a[j];
        a = aux;
    }
}

void countingSort(vector<int> &v, int k)
{
    int n = int(v.size());
    vector<int> output(n);
    vector<int> count(k + 1, 0);
    for (int i = 0; i < n; i++)
    {
        count[v[i]]++;
    }
    for (int r = 1; r <= k; r++)
    {
        count[r] += count[r - 1];
    }
    for (int i = n - 1; i >= 0; i--)
    {
        output[--count[v[i]]] = v[i];
    }
    for (int i = 0; i < n; i++)
    {
        v[i] = output[i];
    }
}

void shakerSort(vector<int> &v)
{
    int l = 0;
    int r = v.size() - 1;
    while (r > l)
    {
        for (int i = l; i < r; i++)
        {
            if (v[i] > v[i + 1])
            {
                swap(v[i], v[i + 1]);
            }
        }
        r--;
        for (int i = r; i > l; i--)
        {
            if (v[i] < v[i - 1])
            {
                swap(v[i], v[i - 1]);
            }
        }
        l++;
    }
}

void selectionSort(vector<int> &v)
{
    for (int i = 0; i < v.size(); i++)
    {
        int min = i;
        for (int j = i + 1; j < v.size(); j++)
        {
            if (v[min] > v[j])
            {
                min = j;
            }
        }
        swap(v[i], v[min]);
    }
}

void shellSort(vector<int> &v)
{
    int n = v.size();

    for (int gap = n / 2; gap > 0; gap /= 2)
    {

        for (int i = gap; i < n; ++i)
        {
            int temp = v[i];
            int j = i;

            while (j >= gap && v[j - gap] > temp)
            {
                v[j] = v[j - gap];
                j -= gap;
            }

            v[j] = temp;
        }
    }
}

void bubbleSort(vector<int> &v)
{
    int n = v.size();
    for (int i = 0; i < n - 1; ++i)
    {
        for (int j = 0; j < n - i - 1; ++j)
        {
            if (v[j] > v[j + 1])
            {
                swap(v[j], v[j + 1]);
            }
        }
    }
}

int partition(vector<int> &v, int low, int high)
{
    int pivot = v[high]; // lay phan tu cuoi lam pivot
    int i = low - 1;
    for (int j = low; j < high; j++)
    {
        if (v[j] < pivot)
        {
            i++;
            swap(v[i], v[j]);
        }
    }
    swap(v[i + 1], v[high]);
    return i + 1;
}

// Ham quick sort de quy
void quickSort(vector<int> &v, int low, int high)
{
    if (low < high)
    {
        int pi = partition(v, low, high);
        quickSort(v, low, pi - 1);
        quickSort(v, pi + 1, high);
    }
}

void quickSort(vector<int> &v){
    int n = v.size();
    quickSort(v, 0, n - 1);
}

void stdSort(vector <int> &v){
    sort(v.begin(), v.end());
}

vector<int> randomNearlySorted(const vector<int> &v)
{
    vector<int> result = v; // Sao chep vector goc

    int n = result.size();
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, n - 1);
    for (int i = 0; i < n / 5; ++i)
    {
        int idx1 = dis(gen);
        int idx2 = dis(gen);
        if (idx1 != idx2)
        {
            swap(result[idx1], result[idx2]);
        }
    }

    return result;
}

vector<int> generateRandomSortedArray(const vector<int> &rdArr)
{
    int n = rdArr.size();
    vector<int> rdsArr(n);
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

vector<int> generateReverseSortedArray(const vector<int> &a)
{
    vector<int> arr = a;
    selectionSort(arr);
    for (int i = 0; i < arr.size() / 2; i++)
    {
        swap(arr[i], arr[arr.size() - 1 - i]);
    }
    return arr;
}

template <typename Func, typename... Args>
double measureExecutionTime(Func func, Args...args)
{
    auto start = high_resolution_clock::now();
    func(args...);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    return duration.count() / 1000.0;
}

using sortFunc = void(*)(vector<int>&);

sortFunc sortFunc1[] = {
    selectionSort,
    insertionSort,
    binaryInsertionSort,
    bubbleSort,
    shakerSort,
    shellSort
};
string sortName1[] = {"Selection sort", "Insertion sort", "Binary insertion sort", "Bubble sort", "Shaker sort", "Shell sort"};

sortFunc sortFunc2[] = {
    heapSort,
    mergeSort,
    naturalMergeSort,
    quickSort,
    stdSort
};
string sortName2[] = {"Heap sort", "Merge sort", "Natural merge sort", "Quick sort", "std::sort"};

sortFunc sortFunc3[] = {
    radixSort,
    countingSort
};
string sortName3[] = {"Radix sort", "Counting sort"};

int main()
{
    srand(time(NULL));
    cout << "Chon nhom thuat toan sap xep de tien hanh danh gia: ";
    int type; cin >> type;
    sortFunc* sf;
    string* sn;
    if(type == 1){
        sf = sortFunc1;
        sn = sortName1;
    }
    else if(type == 2){
        sf = sortFunc2;
        sn = sortName2;
    }
    else if(type == 3){
        sf = sortFunc3;
        sn = sortName3;
    }
    else{
        return cout << "Khong hop le!\n", 0;
    }

    
    return 0;
}