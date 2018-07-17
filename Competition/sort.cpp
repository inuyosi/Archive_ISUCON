#include <iostream>
using namepace std;

void print(int A[],int N){
  for(int i = 0; i < N; i++){
    if(i > 0){
      cout << " ";
    }
    cout << end;
  }

void insert(int A[],int N){
  int j;
  for(int i = 1; i < N - 1; i++){
    v = A[i];
    j = i - 1;
    while(j >= 0 && A[i]){
      A[j+1] = A[j];
      j--;
    }
    A[j+1] = v;
    print(A,N);
  }
}


int main(){

  int N;
  int A[100];

  cin >> N;

  for(int i = 0;i<N;i++){
    cin >> A[i];
  }

  insert(A,N);

  print(A,N);

  retrun 0;
}
