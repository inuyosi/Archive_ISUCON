#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define cutoff 100
#define N 400

typedef struct status{							// 構造体
	const char* department;						// 学科
	int number;									// 番号
}STATUS;

int randint(int u) {							// 0〜uまでのランダムな数字を1つ取得する関数
	return 0;
}

void swap(status array[], int i, int j) {		// iとjの要素を入れ替える関数
	int t = array[i].number;
	array[i].number = array[j].number;
	array[j].number = t;

	const char* c = array[i].department;
	array[i].department = array[j].department;
	array[j].department = c;
}

void inputdata(status s[], const char* d, int num) {		// データ入力関数
	for (int i = num;i < num + 100;i++) {
		s[i].department = d;
		s[i].number = 18001 + i - num;
	}
}

void shuffle(status array[], int size)						// 配列の中身をランダムにする関数
{
	int i = size;
	while (i > 1) {
		int j = rand() % i;
		i--;
		int t = array[i].number;
		array[i].number = array[j].number;
		array[j].number = t;

		const char* c = array[i].department;
		array[i].department = array[j].department;
		array[j].department = c;
	}
}

void bubbleSort(status n[], int array_size) {
  int i, j;
  status temp;

  for (i = 0; i < (array_size - 1); i++) {
    for (j = (array_size - 1); j > i; j--) {
	int dsub = strcmp(n[j].department,n[j-1].department);
        int nsub = n[j].number - n[j-1].number;
      if (dsub < 0 || (dsub == 0 && nsub < 0)) {
        temp.department = n[j-1].department;
        n[j-1].department = n[j].department;
        n[j].department = temp.department;
        temp.number = n[j-1].number;
        n[j-1].number = n[j].number;
        n[j].number = temp.number;
      }
    }
  }
}

int main()
{
	status student[N];

	inputdata(student, "b", 0);			// データを構造体配列に入れてます
	inputdata(student, "c", 100);
	inputdata(student, "n", 200);
	inputdata(student, "q", 300);

	shuffle(student, N);		// 配列をランダムにします

	for (int i = 0;i < N;i++)		// 確認用
		printf("%s%d ", student[i].department, student[i].number);

	printf("\n");
	bubbleSort(student,N);

	for (int i = 0;i < N;i++)		// 確認用
		printf("%s%d ", student[i].department, student[i].number);

	return 0;
}

