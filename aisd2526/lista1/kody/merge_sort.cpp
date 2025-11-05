#include <vector>
#include <climits>
using namespace std;

struct Counter { int comparisons = 0; int assignments = 0; };

void merge(vector<int>& arr,int left,int mid,int right,Counter& c){
    int n1 = mid-left+1, n2 = right-mid;
    vector<int> L(n1), R(n2);
    for(int i=0;i<n1;i++){ L[i]=arr[left+i]; c.assignments++; }
    for(int j=0;j<n2;j++){ R[j]=arr[mid+1+j]; c.assignments++; }
    int i=0,j=0,k=left;
    while(i<n1 && j<n2){
        c.comparisons++;
        if(L[i]<=R[j]){ arr[k]=L[i]; c.assignments++; i++; }
        else { arr[k]=R[j]; c.assignments++; j++; }
        k++;
    }
    while(i<n1){ arr[k++]=L[i++]; c.assignments++; }
    while(j<n2){ arr[k++]=R[j++]; c.assignments++; }
}

void mergeSort(vector<int>& arr,int left,int right,Counter& c){
    if(left<right){ int mid = left + (right-left)/2; mergeSort(arr,left,mid,c); mergeSort(arr,mid+1,right,c); merge(arr,left,mid,right,c);}
}

// zliczamy porównania przy scalaniu trzech części
void merge3(vector<int>& arr,int left,int right,Counter& c){
    if(left>=right) return;

    int third = (right-left)/3;
    int mid1 = left + third;
    int mid2 = left + 2*third + 1;

    merge3(arr,left,mid1,c);
    merge3(arr,mid1+1,mid2,c);
    merge3(arr,mid2+1,right,c);

    vector<int> temp;
    int i=left, j=mid1+1, k=mid2+1;

    while(i<=mid1 || j<=mid2 || k<=right){
        int val = INT_MAX;
        if(i<=mid1) val = arr[i];
        if(j<=mid2 && arr[j]<val){ val = arr[j]; c.comparisons++; } else if(j<=mid2) c.comparisons++;
        if(k<=right && arr[k]<val){ val = arr[k]; c.comparisons++; } else if(k<=right) c.comparisons++;

        temp.push_back(val); c.assignments++;

        if(i<=mid1 && arr[i]==val) i++;
        else if(j<=mid2 && arr[j]==val) j++;
        else k++;
    }

    for(int idx=0; idx<temp.size(); idx++){ arr[left+idx]=temp[idx]; c.assignments++; }
}
