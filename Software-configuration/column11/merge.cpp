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

void merge(status n[], int left, int mid, int right)
{
    int num = right - left;

    status *tmp = new status[num];

    int iw = 0;
    int il = left;
    int ir = mid;

    while (il < mid && ir < right)
    {
	int dsub = strcmp(n[il].department,n[ir].department);
	int nsub = n[il].number - n[ir].number;

	if(dsub < 0 ||( dsub ==0 && nsub < 0)){
		tmp[iw].department = n[il].department;
		tmp[iw++].number = n[il++].number;
        } else {
            tmp[iw].department = n[ir].department;
            tmp[iw++].number = n[ir++].number;
	}
    }

    while (il < mid) {
	tmp[iw].department = n[il].department;
	tmp[iw++].number = n[il++].number;
    }

    while (ir < right) {
	tmp[iw].department = n[ir].department;
	tmp[iw++].number = n[ir++].number;
    }

    for (int i=0; i<num; i++) {
	n[left + i].department = tmp[i].department;
	n[left + i].number = tmp[i].number;
    }

    delete[] tmp;

}


void merge_sort_sub(status n[], int left, int right)
{
    if (right - left <= 1) return;

    int mid = left + (right - left) / 2;
    merge_sort_sub(n, left, mid);
    merge_sort_sub(n, mid, right);
    merge(n, left, mid, right);

}


void merge_sort(status n[], int len)
{
    merge_sort_sub(n, 0, len);
}

int main()
{
	status student[N];

	inputdata(student, "b", 0);			// データを構造体配列に入れてます
	inputdata(student, "c", 100);
	inputdata(student, "n", 200);
	inputdata(student, "q", 300);

//	shuffle(student, N);		// 配列をランダムにします

	for (int i = 0;i < N;i++)		// 確認用
		printf("%s%d ", student[i].department, student[i].number);

	printf("\n");

	merge_sort(student,N);

	for (int i = 0;i < N;i++)		// 確認用
		printf("%s%d ", student[i].department, student[i].number);

	printf("\n");

	return 0;
}

