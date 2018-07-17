#include <stdio.h>
#include <stdlib.h>

#define N 2048

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

int main(void){
        float a[N][N],b[N][N],c[N][N],cs[N][N];
        float (*adev)[N],(*bdev)[N],(*cdev)[N];

        initMatrix(a);
        initMatrix(b);
        printMatrix(a, "a");
        printMatrix(b, "b");

//ここから、CPU版行列積

printf("\nCPU上の行列積を開始します\n");
for (int i=0; i<N;i++){
        for (int j=0;j<N; j++){
                cs[i][j] = 0.0;
        }
}
for (int i=0; i<N; i++){
        for (int k=0;k<N; k++){
                for (int j=0; j<N; j++){
                        cs[i][j] += a[i][k] * b[k][j];
                }
        }
}
printMatrix(cs, "cs");

return 0;
}
