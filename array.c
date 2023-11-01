#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>
#include <omp.h>

#define COUNT 65535

void Test(int n)
{
    for (int i = 0; i < 30000; i++){}
    printf("%d, ==线程编号： %d ", n , omp_get_thread_num());

}

void sum()
{
    int sum = 0;
    for (int i = 0; i < COUNT; i++)
    {
        Test(i);
        sum += i;
        printf("sum: %d\n", sum);
    }
     printf("\n\n");
      printf("end sum: %d\n", sum);
}

int main(int argc,char **argv){
    MPI_Init(NULL, NULL);

// Get the rank and size in the original communicator
    int world_rank, world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int color = world_rank / 4; // Determine color based on row

    // Split the communicator based on the color and use original rank for ordering
    MPI_Comm row_comm;
    MPI_Comm_split(MPI_COMM_WORLD, color, world_rank, &row_comm);

    int row_rank, row_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &row_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &row_size);

    sum();

    printf("WORLD RANK/SIZE: %d/%d  --- ROW RANK/SIZE: %d/%d\n",
        world_rank,world_size,row_rank, row_size);

    MPI_Comm_free(&row_comm);
    int arr[3][3];
    int i, j;

    // Use a doudle loop to traverse a two-dimensional array and assign values.
    for (i = 0; i < 3; i++){
        for (j = 0; j < 3; j++){
            arr[i][j] = i * 3 + j + 1;
            printf("one %d \n", arr[i][j]);
        }
    }

    // Output the value of the two-dimensional array.
    for (i = 0; i < 3; i++){
        for (j = 0; j < 3; j++){
            printf("one %d \n", arr[i][j]);
        }
    }

    MPI_Finalize();
    
}
