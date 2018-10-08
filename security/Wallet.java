import java.io.*;
public class Wallet implements Serializable{
private String holder;
private int amount;
public Wallet(String holder, int amount) {
this.holder = holder; // this.holderやthis.lamountはフィールド
this.amount = amount;
}
public void show() {
System.out.println("財布の持ち主："+holder);
System.out.println("財布の中身："+amount+"円");
}
public void rename(String holder) {
this.holder = holder;
}
public void pay(int money) {
amount = amount-money;
}
public void save(int money) {
amount = amount+money;
}
}
