#include <vector>
#include <algorithm>
using namespace std;

struct Counter { int comparisons = 0; int assignments = 0; };

void heapify(vector<int>& arr,int n,int i,Counter& c){
    int largest=i,l=2*i+1,r=2*i+2;
    if(l<n){ c.comparisons++; if(arr[l]>arr[largest]) largest=l; }
    if(r<n){ c.comparisons++; if(arr[r]>arr[largest]) largest=r; }
    if(largest!=i){ swap(arr[i],arr[largest]); c.assignments+=3; heapify(arr,n,largest,c); }
}

void heapSort(vector<int>& arr,Counter& c){
    int n=arr.size();
    for(int i=n/2-1;i>=0;i--) heapify(arr,n,i,c);
    for(int i=n-1;i>=0;i--){ swap(arr[0],arr[i]); c.assignments+=3; heapify(arr,i,0,c); }
}

void heapifyTernary(vector<int>& arr,int n,int i,Counter& c){
    int largest=i,l=3*i+1,m=3*i+2,r=3*i+3;
    if(l<n){ c.comparisons++; if(arr[l]>arr[largest]) largest=l; }
    if(m<n){ c.comparisons++; if(arr[m]>arr[largest]) largest=m; }
    if(r<n){ c.comparisons++; if(arr[r]>arr[largest]) largest=r; }
    if(largest!=i){ swap(arr[i],arr[largest]); c.assignments+=3; heapifyTernary(arr,n,largest,c); }
}

void heapSortTernary(vector<int>& arr,Counter& c){
    int n=arr.size();
    for(int i=n/3-1;i>=0;i--) heapifyTernary(arr,n,i,c);
    for(int i=n-1;i>=0;i--){ swap(arr[0],arr[i]); c.assignments+=3; heapifyTernary(arr,i,0,c); }
}
