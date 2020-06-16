#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <vector>
#include <string>

int max(int a, int b)
{
    return a > b ? a : b;
}

int getRandom(int lower, int upper)
{
    return rand() % (upper - lower + 1) + lower;
}

void printArray(int *rank, int array[], int *count, std::string title)
{
    std::string result="";
    result+=std::to_string(*rank)+": " + title + " : [";

    for (int i = 0; i < *count; i++)
    {
        if (i != *count - 1)
        {
            result+=std::to_string(*rank) +", ";
        }
        else
        {
            result+=std::to_string(*rank)+"]\n";
        }
    }
    std::cout<<result;
}

void check_thread_support(int provided)
{
    printf("THREAD SUPPORT: %d\n", provided);
    switch (provided)
    {
    case MPI_THREAD_SINGLE:
        printf("Brak wsparcia dla wątków, kończę\n");
        MPI_Finalize();
        exit(-1);
        break;
    case MPI_THREAD_FUNNELED:
        printf("tylko te wątki, ktore wykonaly mpi_init_thread mogą wykonać wołania do biblioteki mpi\n");
        break;
    case MPI_THREAD_SERIALIZED:
        printf("tylko jeden watek naraz może wykonać wołania do biblioteki MPI\n");
        break;
    case MPI_THREAD_MULTIPLE:
        printf("Pełne wsparcie dla wątków\n");
        break;
    default:
        printf("Nikt nic nie wie\n");
    }
}