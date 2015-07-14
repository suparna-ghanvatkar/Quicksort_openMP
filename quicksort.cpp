#include<iostream>
using namespace std;
void quicksort(int *a,int beg, int end);
int partition(int *a, int p, int r);//returns the element to partition from
void swap(int *a,int i, int j);
int main()
{
	int A[15],len;
	cout<<"Enter the number of elements to sort:";
	cin>>len;
	cout<<"Enter the array to sort:"<<endl;
	for(int i=0;i<len;i++)
		cin>>A[i];
	quicksort(A,0,len-1);
	cout<<"\n The sorted array is :"<<endl;
	for(int i=0;i<len;i++)
		cout<<A[i]<<"\t";
	return 0;
}
void quicksort(int *a,int beg, int end)
{
	char ch;
	if(beg<end)
	{
		int mid=partition(a,beg,end);
		quicksort(a,beg,mid);
		quicksort(a,mid+1,end);
	}
}
int partition(int *a, int p, int r)
{
	int pivot=a[p];
	int i=p-1;
	int j=r+1;
	while(1)
	{
		do{
			j--;
		}while((a[j]>pivot)&&(j>p)&&(j<=r));
		do{
			i++;
		}while((a[i]<pivot)&&(i<r)&&(i>=p));
		if(i<j)
			swap(a,i,j);
		else
			return j;
	}
}
void swap(int *a, int i, int j)
{
	int temp=a[i];
	a[i]=a[j];
	a[j]=temp;
}
