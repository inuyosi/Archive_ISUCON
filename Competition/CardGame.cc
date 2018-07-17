#include <iostream>
using namespace std;

int main(){

int a,b,i,aa,ba;

scanf(" %d",&a);
aa = ba = 0;

for(i=0;i<a;i++){
scanf("%d %d",&a,&b);
if(a==b){
        aa += a;
        ba += b;
        }else if(a<b){
        ba += a+b;
        }else{
        aa += a+b;
        }
}

printf("%d %d",aa,ba);

return 0;
}
