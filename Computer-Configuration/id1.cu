#include <stdio.h>

__global__ void f(void){
        int myid = blockIdx.x * blockDim.x + threadIdx.x;

        printf("myid=%-2d,bDim=(%d,%d,%d),bIdx=(%d,%d,%d),tIdx=(%d,%d,%d)\n",
                myid,
                blockDim.x,blockDim.y,blockDim.z,
                blockIdx.x,blockIdx.y,blockIdx.z,
                threadIdx.x,threadIdx.y,threadIdx.z
);
}

int main(void){
        f<<<3, 4>>>();
        cudaDeviceSynchronize();
        return 0;
}
