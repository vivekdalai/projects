#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

# define SIZE 1024


static unsigned long int mat1[SIZE][SIZE] , mat2[SIZE][SIZE] , res[SIZE][SIZE];

int no_of_threads ;
void matrix_read()
{
    int i,j,n;
    n=1;
    for(i=0;i<SIZE;i++){
        for(j=0;j<SIZE;j++)
            mat1[i][j]=n++;
    }
    
    n=1;
    for(i=0;i<SIZE;i++)
    {    for(j=0;j<SIZE;j++)
            mat2[i][j]=n++;
    }
    return;

}
void * multiplication(void *arg)
{
    long int num = (long int)arg;
    int start = (num*SIZE)/no_of_threads;
    int end = ((num+1)*SIZE)/ no_of_threads;

    int i,j,k;

    // matrix multiplication

    for(i=start; i<end; i++)
        for(j=0; j<SIZE; j++)
            for(k=0; k<SIZE; k++)
                res[i][j] += (mat1[i][k]*mat2[k][j]);
    
    /*printf("\nthread : %ld\n\n",num);
    for(i=0;i<SIZE;i++)
    {    for(j=0;j<SIZE;j++)
            printf("%ld\t",res[i][j]);
        printf("\n");
    } */
    
}

int main()
{
    double start_time = time(NULL);
    long int i,j;
    pthread_t tid[64];

    matrix_read();
    no_of_threads = 64;

    // create threads
    for (i =0; i<no_of_threads;i++)
    {
        if (pthread_create(&tid[i], NULL , multiplication, (void *)i) !=0 )
        {
            printf("\ncan't create thread \n");
            exit(-1);
        }
    }
    //multiplication(&tid[0]);

    for(j=0 ; j<no_of_threads;j++)
        pthread_join(tid[j], NULL);   
    
    double end_time = time(NULL);
    printf("time required : %f \n\n", (end_time - start_time));

    /*printf("\nfull matrix\n\n");
    for(i=0;i<SIZE;i++)
    {    for(j=0;j<SIZE;j++)
            printf("%ld\t",res[i][j]);
        printf("\n");
    }  */

    printf("time required : %f \n\n", (end_time - start_time));

   return 0;
}