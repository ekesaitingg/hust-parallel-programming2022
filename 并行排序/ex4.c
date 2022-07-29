#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <mpi.h>

void sort(int a[], int start, int end);

int main(int argc, char* argv[])
{
	int n, myid, numprocess;
	int send_num[2], recv_num[2];
	// scanf("%d", &n);
	int a[1000], tmp[1000];
	
	for (int i = 0; i < n; i++) scanf("%d", &a[i]);	

	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocess);
	if(myid == 0)
	{
		// printf("This is process %d\n", myid);
		scanf("%d",&n);
		for(int i=0;i<n;i++) scanf("%d",&a[i]);
		send_num[0] = 0;
		send_num[1] = n/2;
		MPI_Send(send_num, 2, MPI_INT, 1, 0, MPI_COMM_WORLD);
		// printf("process 0: send %d %d\n", send_num[0], send_num[1]);
		MPI_Send(a, n/2+1 , MPI_INT, 1, 1, MPI_COMM_WORLD);
		// printf("process 0: send left a\n");
		send_num[0] = n/2 + 1;
		send_num[1] = n-1;
		MPI_Send(send_num, 2, MPI_INT, 2, 0, MPI_COMM_WORLD);
		// printf("process 0: send %d %d\n", send_num[0], send_num[1]);
		MPI_Send(&a[n/2+1], n-1-n/2, MPI_INT, 2, 1, MPI_COMM_WORLD);
		// printf("process 0: send right a\n");
		MPI_Recv(a, n/2+1, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);
		// printf("process 0: receive left a\n");
		MPI_Recv(&a[n/2+1], n-1-n/2, MPI_INT, 2, 0, MPI_COMM_WORLD, &status);
		// printf("process 0: receive right a\n");

		// for (int i = 0; i < n; i++) printf("%d ", a[i]);
		// printf("\n");
		int b[1000];			
		int p1 = 0, p2 = n/2+1, k = 0;
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
	}
	else if(myid == 1 || myid == 2)
	{
		// printf("This is process %d\n", myid);
		MPI_Recv(recv_num, 2, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
		// printf("process %d receive %d %d\n", myid, recv_num[0], recv_num[1]);
		MPI_Recv(tmp, recv_num[1] - recv_num[0] + 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
		// printf("process %d receive array\n", myid);
		sort(tmp, 0, recv_num[1] - recv_num[0]);
		MPI_Send(tmp, recv_num[1] - recv_num[0] + 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}
	MPI_Finalize();
	return 0;
}

void sort(int a[], int start, int end)
{
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
		sort(a, left, index-1);
		sort(a, index + 1, right);
	}
	return;
}


