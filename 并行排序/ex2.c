#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include <stdlib.h>

typedef struct param
{
    int *a;
    int start;
    int end;
} Arg;
void sort(Arg *arg);
int main(void)
{
	int n;
	scanf("%d", &n);
	int a[1000];
	for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    pthread_t t1,t2;
    int ret[2];
    Arg arg1={a,0,n/2},arg2={a,n/2+1,n-1};
    ret[0] = pthread_create(&t1,NULL,sort,&arg1);
    ret[1] = pthread_create(&t2,NULL,sort,&arg2);
    for(int i=0;i<2;i++){
        if(ret[i]!=0) {
            printf("Create thread %d error\n",ret[0]);
            return -1;
        }
    }
	pthread_join(t1,NULL);
    pthread_join(t2,NULL);
	int b[1000];
	int p1 = 0, p2 = n/2+1, k=0;
	while(k < n)
	{
		if((p1 > n/2 || a[p1] > a[p2]) && p2 <= n-1)
		{
			b[k] = a[p2];
			p2++;
		}
		else if((p2 > n-1 || a[p1] <= a[p2]) && p1 <= n/2)
		{
			b[k] = a[p1];
			p1++;
		}
		k++;
	}

	for (int i = 0; i < n; i++) printf("%d ", b[i]);
	printf("\n");
	return 0;
}

void sort(Arg *arg)
{
	int *a=arg->a, start = arg->start, end = arg->end;
	if (end == start + 1 && a[start] < a[end]) return;
	if (start < end) {
		int left = start, right = end;
		int pivot = a[start];
		int index = left;
		while (start < end) {
			while (a[end] >= pivot && start < end) end--;
			if (a[end] < pivot && start < end)
			{
				a[index] = a[end];
				index = end;
				start++;
			}
			while (a[start] <= pivot && start < end) start++;
			if (a[start] > pivot && start < end)
			{
				a[index] = a[start];
				index = start;
				end--;
			}
		}
		a[index] = pivot;
		Arg arg1={a,left,index-1}, arg2={a,index+1,right};
		sort(&arg1);
		sort(&arg2);
	}
	return;
}

