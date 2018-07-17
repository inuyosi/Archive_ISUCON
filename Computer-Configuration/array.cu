#include <stdio.h>
#include <stdlib.h>

#define N 8

void printArray(int a[],int size,const char *str){
        printf("%s: ",str);
        for (int i=0;i<size;i++){
                printf("%4d ",a[i]);
        }
        printf("\n");
}

void initArray(int a[], int size){
        for (int i=0;i<size;i++){
                a[i] = (int)((rand()/(RAND_MAX + 1.0)) * 100);
        }
}

__global__ void addArray(int *a, int *b, int *c){
        int id = blockIdx.x * blockDim.x + threadIdx.x;
        if(id < N){
                c[id] = a[id] + b[id];
        }
}

int main(void){
        int a[N],b[N],c[N];
        int *adev,*bdev,*cdev;

cudaMalloc(&adev,sizeof(int)*N);
cudaMalloc(&bdev,sizeof(int)*N);
cudaMalloc(&cdev,sizeof(int)*N);

initArray(a,N);
initArray(b,N);
printArray(a, N, "a");
printArray(b, N, "b");

cudaMemcpy(adev, a, sizeof(int)*N, cudaMemcpyHostToDevice);
cudaMemcpy(bdev, b, sizeof(int)*N, cudaMemcpyHostToDevice);

addArray<<<4, 4>>>(adev,bdev,cdev);
cudaDeviceSynchronize();

cudaMemcpy(cdev, c, sizeof(int)*N, cudaMemcpyDeviceToHost);
printArray(c, N, "c");

cudaFree(adev);
cudaFree(bdev);
cudaFree(cdev);

return 0;
}
