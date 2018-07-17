#include <stdio.h>
#include <stdlib.h>

#define N 2048

#define BSX 64
#define BSY 64

void printMatrix(float a[][N],const char *str){
#if (N<=16)
        printf("==== %s ====\n", str);
        for (int i=0; i<N; i++){
                for (int j=0; j<N; j++){
                        printf("%4.0f ", a[i][j]);
                }
                printf("\n");
        }
#endif
}

void initMatrix(float a[][N]){
        for (int i=0; i<N; i++){
                for (int j=0; j<N; j++){
                        a[i][j] = (int)((rand()/(RAND_MAX + 1.0))*10);
                }
        }
}

__global__ void mulMatrix(float (*a)[N],float (*b)[N], float (*c)[N]){
        int xid = blockIdx.x * blockDim.x + threadIdx.x;
        int yid = blockIdx.y * blockDim.y + threadIdx.y;
        if (xid < N && yid < N){
                c[yid][xid] = 0.0;
                for(int k=0; k<N; k++){
                        c[yid][xid] += a[yid][k] * b[k][xid];
                }
        }
}

int main(void){
        float a[N][N],b[N][N],c[N][N],cs[N][N];
        float (*adev)[N],(*bdev)[N],(*cdev)[N];

        initMatrix(a);
        initMatrix(b);
        printMatrix(a, "a");
        printMatrix(b, "b");

//ここからGPU版行列積

cudaMalloc(&adev, sizeof(float)*N*N);
cudaMalloc(&bdev, sizeof(float)*N*N);
cudaMalloc(&cdev, sizeof(float)*N*N);

cudaMemcpy(adev, a, sizeof(float)*N*N, cudaMemcpyDeviceToHost);
cudaMemcpy(bdev, b, sizeof(float)*N*N, cudaMemcpyDeviceToHost);

dim3 bdim(BSX,BSY);
dim3 gdim(N/BSX, N/BSY);

printf("\nGPU上の行列積を開始します\n");
mulMatrix<<<gdim, bdim>>>(adev, bdev, cdev);
cudaDeviceSynchronize();

cudaMemcpy(c, cdev, sizeof(float)*N*N, cudaMemcpyDeviceToHost);
printMatrix(c, "c");

cudaFree(adev);
cudaFree(bdev);
cudaFree(cdev);

//ここまでGPU版行列積
printMatrix(cs, "cs");

return 0;
}
