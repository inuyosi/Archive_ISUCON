import java.io.*;
public class GetWallet {
 public static void main(String args[]){
  	try{
	FileInputStream inFile = new FileInputStream(args[0]);
	ObjectInputStream inStream = new ObjectInputStream(inFile);
	System.out.println("Walletインスタンスを読み込みました。");
	Wallet payWallet = (Wallet) inStream.readObject();
	payWallet.show();
	payWallet.pay(Integer.parseInt(args[1]));
	System.out.println(args[1] + "円を使いました");
	payWallet.show();
	inStream.close();
	System.out.println("");
	FileInputStream inputFile = new FileInputStream(args[0]);
	ObjectInputStream inputStream = new ObjectInputStream(inputFile);
	System.out.println("Walletインスタンスを読み込みました。");
	Wallet spendWallet = (Wallet) inputStream.readObject();
	spendWallet.show();
	spendWallet.save(Integer.parseInt(args[2]));
	System.out.println(args[2] + "円を補充しました。");
	spendWallet.show();
	inputStream.close();


	}
	catch (IOException e){
		System.err.println(e.getMessage());
		}
	catch (ClassNotFoundException e){
		System.err.println(e.getMessage());
		}
 }
}
