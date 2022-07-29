#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>
#include <math.h>
#include <string.h>

/***** Begin *****/
int main(int argc,char* argv[])
{
    int n, myid, numprocess, ans, tag;
    int a[5][5], send_num[2], recv_num[2];
    for(int i = 0; i < 5; i++) a[i][0] = a[i][i] = 1;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);  //
    MPI_Comm_size(MPI_COMM_WORLD, &numprocess);
    if(myid == 0)
    {
        scanf("%d", &n);
        for(int i = 2; i < n; i++)
        {
            for(int j = 1; j < i; j++)
            {
                send_num[0] = a[i-1][j-1];
                send_num[1] = a[i-1][j];
                MPI_Send(send_num, 2, MPI_INT, j, 0, MPI_COMM_WORLD);
            }
            for(int j = 1; j < i; j++)
            {
                MPI_Recv(&ans, 1, MPI_INT, j, 2, MPI_COMM_WORLD, &status);
                a[i][j] = ans;
            }
        }
        for(int j = 1; j < 4; j++)
        {
            MPI_Send(send_num, 2, MPI_INT, j, 3, MPI_COMM_WORLD);
        }
        printf("[");
        for(int i = 0; i < n; i++)
        {
            printf("[");
            for(int j = 0; j <= i;j++)
            {
                printf("%d", a[i][j]);
                if(j != i) printf(",");
            }
            printf("]");
            if(i != n-1) printf(",");
        }
        printf("]\n");
    }
    else
    {
        while(1)
        {
            MPI_Recv(recv_num, 2, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            tag = status.MPI_TAG;
            if(tag == 3) break;
            ans = recv_num[0] + recv_num[1];
            MPI_Send(&ans, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
        }
    }
    MPI_Finalize();
	return 0;
}
/***** End *****/
