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

void merge(status n[], int left, int mid, int right)
{
    int num = right - left;

    status *tmp = new status[num]; //tmpの生成

    int iw = 0;
    int il = left;
    int ir = mid;

    while (il < mid && ir < right)
    {
	int dsub = strcmp(n[il].department,n[ir].department);  	//文字列の比較
	int nsub = n[il].number - n[ir].number;			//数字の比較

	if(dsub < 0 ||( dsub ==0 && nsub < 0)){			//入れ替えるかどうか
		tmp[iw].department = n[il].department;
		tmp[iw++].number = n[il++].number;
        } else {
            tmp[iw].department = n[ir].department;
            tmp[iw++].number = n[ir++].number;
	}
    }

    while (il < mid) {				//中央から左側の値を退避
	tmp[iw].department = n[il].department;
	tmp[iw++].number = n[il++].number;
    }

    while (ir < right) {			//中央から右側の値を退避
	tmp[iw].department = n[ir].department;
	tmp[iw++].number = n[ir++].number;
    }

    for (int i=0; i<num; i++) {			//tmpに退避したデータの格納
	n[left + i].department = tmp[i].department;
	n[left + i].number = tmp[i].number;
    }

    delete[] tmp; //メモリの解放

}


void merge_sort_sub(status n[], int left, int right)  
{
    if (right - left <= 1) return;

    int mid = left + (right - left) / 2;	//中央値を決める
    merge_sort_sub(n, left, mid);		//中央から左側の処理
    merge_sort_sub(n, mid, right);		//中央から右側の処理
    merge(n, left, mid, right);			//マージする

}


void merge_sort(status n[], int len)//マージ開始
{
    merge_sort_sub(n, 0, len);
}

void bubbleSort(status n[], int array_size) {
  int i, j;
  status temp;

  for (i = 0; i < (array_size - 1); i++) {
    for (j = (array_size - 1); j > i; j--) {
        int dsub = strcmp(n[j].department,n[j-1].department);
        int nsub = n[j].number - n[j-1].number;
      if (dsub < 0 || (dsub == 0 && nsub < 0)) { //j-1のほうが小さければ入れ替え
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

//	merge_sort(student,N);
//	bubbleSort(student,N);
  	qsort4(student, 0, N - 1);              // qsort4はisort3とセットで使用してください
        isort3(student);

	for (int i = 0;i < N;i++)		// 確認用
		printf("%s%d ", student[i].department, student[i].number);

	return 0;
}

