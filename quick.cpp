#if _OPENMP < 200805
#error You openmp version does not support tasks
#endif
#include<iostream>
#include<omp.h>
using namespace std;

class PQuick
{
	static void quicksort(int *a,int beg, int end);
	static int partition(int *a, int p, int r);//returns the element to partition from
	static void swap(int *a,int i, int j);
  public:
	static void QsOmp(int *array, const int size)
	{
        #pragma omp parallel
        {
            #pragma omp single nowait
            {
                quicksort(array, 0, size - 1);
            }
        }
    }
};
int main()
{
	int A[15],len;
	cout<<"Enter the number of elements to sort:";
	cin>>len;
	cout<<"Enter the array to sort:"<<endl;
	for(int i=0;i<len;i++)
	cin>>A[i];
	PQuick::QsOmp(A,len);
	cout<<"\n The sorted array is :"<<endl;
	for(int i=0;i<len;i++)
	cout<<A[i]<<"\t";
	return 0;
}
void PQuick::quicksort(int *a,int beg, int end)
{
	char ch;
	cout<<"\nThe thread is :"<<omp_get_thread_num()<<". The array it will sort is:"<<endl;
		for(int i=beg;i<=end;i++)
			cout<<a[i]<<"\t";
		cout<<endl;
	if(beg<end)
	{
		int mid=partition(a,beg,end);
		cout<<"Sorted array is:"<<endl;
		for(int i=beg;i<=end;i++)
			cout<<a[i]<<"\t";
        #pragma omp task default(none) firstprivate(a, mid, beg, end)
		quicksort(a,beg,mid);
		quicksort(a,mid+1,end);
	}
}
int PQuick::partition(int *a, int p, int r)
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
void PQuick::swap(int *a, int i, int j)
{
	int temp=a[i];
	a[i]=a[j];
	a[j]=temp;
}
/*************************************************
			OUTPUT
[suppu@localhost sem7]$ g++ -fopenmp -O3 quick.cpp -o quick -lgomp
[suppu@localhost sem7]$ ./quick
Enter the number of elements to sort:10
Enter the array to sort:
9 4 7 1 2 5 3 8 0 6

The thread is :2. The array it will sort is:
9	4	7	1	2	5	3	8	0	6	
Sorted array is:
6	4	7	1	2	5	3	8	0	9	
The thread is :2. The array it will sort is:
9	

The thread is :1. The array it will sort is:
6	4	7	1	2	5	3	8	0	
Sorted array is:
0	4	3	1	2	5	7	8	6	
The thread is :1. The array it will sort is:
7	8	6	
Sorted array is:
6	8	7	
The thread is :2. The array it will sort is:
6	

The thread is :1. The array it will sort is:
8	7	
Sorted array is:
7	8	
The thread is :3. The array it will sort is:
0	4	3	1	2	5	
Sorted array is:
0	4	3	1	2	5	
The thread is :3. The array it will sort is:
4	3	1	2	5	
Sorted array is:
2	3	1	4	5	
The thread is :3. The array it will sort is:
4	5	
Sorted array is:
4	5	
The thread is :3. The array it will sort is:
5	
The thread is :
The thread is :0. The array it will sort is:
0	

The thread is :0. The array it will sort is:
2	3	1	
Sorted array is:
1	3	2	
The thread is :0. The array it will sort is:
3	2	
Sorted array is:
2	3	
The thread is :0. The array it will sort is:
3	

The thread is :0. The array it will sort is:
4	

The thread is :0. The array it will sort is:
1	

The thread is :0. The array it will sort is:
2	
1. The array it will sort is:
8	


The thread is :2. The array it will sort is:
7	

 The sorted array is :
0	1	2	3	4	5	6	7	8	9	[suppu@localhost sem7]$ 


**************************************************/
