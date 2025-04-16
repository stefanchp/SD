#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

void read(vector<long long> &arr, size_t &n, char *input_file)
{
	ifstream fin(input_file);
	fin >> n;
	arr.resize(n);
	for (size_t i = 0; i < n; ++i) 
		fin >> arr[i];
	fin.close();
	return;
}

void Interclasare(vector<long long>& v, long long st, long long mij, long long dr)
{
    long long k = 0;
    vector<long long> c(dr - st + 1);
    long long i=st, j=mij+1;

    while( i <= mij && j <= dr)
        if(v[i] < v[j])
           c[k++] = v[i++];
        else
           c[k++] = v[j++];

    while(i<=mij)
        c[k++] = v[i++];

    while(j<=dr)
        c[k++] = v[j++];

    j = 0;
    for(i = st; i<=dr; i++)
        v[i] = c[j++];
}

void MergeSort(vector<long long>& v, long long st, long long dr)
{
    if(st < dr)
    {
        long long mij = (st + dr) / 2;
        MergeSort(v, st, mij);
        MergeSort(v, mij+1, dr);
        Interclasare(v, st, mij, dr);
    }
}

void printArray(const vector<long long>& arr) 
{
    for (long long x : arr)
        cout << x << " ";
    cout << '\n';
}

int main(int argc, char *argv[])
{
    size_t n;
	vector<long long> array;
    read(array, n, argv[1]);
    MergeSort(array, 0, n - 1);
    //printArray(array);
    return 0;
}