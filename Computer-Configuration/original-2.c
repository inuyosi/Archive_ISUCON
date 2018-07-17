#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define SIZE 10000

void printTime(struct timespec startTime, struct timespec endTime){
    double time = 0.0;
	// printf("開始時刻　 = %10ld.%09ld\n", startTime.tv_sec, startTime.tv_nsec);
        // printf("終了時刻　 = %10ld.%09ld\n", endTime.tv_sec, endTime.tv_nsec);
        // printf("経過実時間 = ");
	if (endTime.tv_nsec < startTime.tv_nsec) {
		// printf("%10ld.%09ld", endTime.tv_sec - startTime.tv_sec - 1, (endTime.tv_nsec + 1000000000 - startTime.tv_nsec));
		time = (endTime.tv_sec - startTime.tv_sec - 1) + ((double)(endTime.tv_nsec + 1000000000 - startTime.tv_nsec) / 1000000000);
	} else {
		// printf("%10ld.%09ld", endTime.tv_sec - startTime.tv_sec, (endTime.tv_nsec - startTime.tv_nsec));
		time = (endTime.tv_sec - startTime.tv_sec) + ((double)(endTime.tv_nsec - startTime.tv_nsec) / 1000000000);
	}
	// printf("[秒]\n");
	printf("経過実時間 = %.2f [ns]\n", time*1000000000);
    //printf("%.2f\n", time*1000000000);
    return;
}
//ここを変更してください
int Min(int a[]){
    int min,i;
    min=a[0];
    for(i=1;i<SIZE;i=i+5){
        if(min>a[i]){
        min=a[i];
	}
        if(min>a[i+1]){
        min=a[i+1];
	}
        if(min>a[i+2]){
        min=a[i+2];
	}
        if(min>a[i+3]){
        min=a[i+3];
	}
        if(min>a[i+4]){
        min=a[i+4];
	}
    }
    return min;
}
//ここまで
int main(void)
{
    struct timespec startTime, endTime;
    int result,i;
    int array[SIZE];

    //配列の作成
    srand((unsigned int)time(NULL));
    for(i=0;i<SIZE;i++){
        array[i] = rand()%10000;
        }
    //配列の表示
    printf("array: ");
	for(i=0; i<SIZE; i++){
		printf("%d ", array[i]);
	}
    printf("\n");
    clock_gettime(CLOCK_REALTIME, &startTime);  //処理時間計測開始

    result =Min(array);

    clock_gettime(CLOCK_REALTIME, &endTime);    //処理時間計測終了

    printf("min=%d\n",result);
    printTime(startTime, endTime);
    return 0;
}
