class ArgException extends Exception {} // 例外クラスの定義
public class Except {
public static void main(String args[]){
try {
total(Integer.parseInt(args[0]));
}
catch (ArgException e) { // 例外処理
System.out.println("エラー： "+ e);
}
}
public static void total(int n) throws ArgException { // スロー宣言
int sum = 0;
if (n<0 || n>100) throw new ArgException(); // 例外のスロー
for (int i=1; i<=n; i++) {
sum += i;
}
System.out.println("合計=" + sum);
}
}
