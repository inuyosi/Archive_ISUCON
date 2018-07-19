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

void isort3(status s[]) {
	int i, j, t;
	const char* c;
	for (i = 0;i < N;i++) {
		t = s[i].number;
		c = s[i].department;
		for (j = i;j > 0 && s[j - 1].number > t;j--) {
			s[j].number = s[j - 1].number;
			s[j].department = s[j - 1].department;
		}
		s[j].number = t;
		s[j].department = c;
	}

	for (i = 0;i < N;i++) {
		t = s[i].number;
		c = s[i].department;
		for (j = i;j > 0 && strcmp(s[j - 1].department, c) > 0;j--) {
			s[j].number = s[j - 1].number;
			s[j].department = s[j - 1].department;
		}
		s[j].number = t;
		s[j].department = c;
	}
}


void qsort4(status s[], int l, int u) {
	int temp;
	const char* tempc;

	if (u - l < cutoff)
		return;

	//int a = randint(u);
	int a = 3;
	swap(s, l, a);
	int t = s[l].number;
	int i = l;
	int j = u + 1;
	const char* c = s[l].department;

	while (1) {
		do { i++; } while (i <= u && s[i].number < t);
		do { j--; } while (s[j].number > t);
		if (i > j)
			break;
		temp = s[i].number;
		tempc = s[i].department;
		s[i].number = s[j].number;
		s[i].department = s[j].department;
		s[j].number = temp;
		s[j].department = tempc;
	}

	i = l;
	j = u + 1;
	while (1) {
		do { i++; } while (i <= u && strcmp(s[i].department , c) < 0);
		do { j--; } while (strcmp(s[j].department, c) > 0 );
		if (i > j)
			break;
		temp = s[i].number;
		tempc = s[i].department;
		s[i].number = s[j].number;
		s[i].department = s[j].department;
		s[j].number = temp;
		s[j].department = tempc;
	}
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

//	qsort4(student, 0, N - 1);		// qsort4はisort3とセットで使用してください
	isort3(student);

	printf("\n");
	for (int i = 0;i < N;i++)		// 確認用
		printf("%s%d ", student[i].department, student[i].number);

	printf("\n");

	return 0;
}

