import java.io.*;
public class StoreWallet {
  public static void main(String args[]){
  try{
	Wallet ver1 = new Wallet(args[0],Integer.parseInt(args[1]));
	System.out.println("Walletインスタンスを生成しました。");
	ver1.show();
	FileOutputStream outFile = new FileOutputStream(args[2]);
	ObjectOutputStream outStream = new ObjectOutputStream(outFile);
	outStream.writeObject(ver1);
	System.out.println("Walletインスタンスをファイル書き込みました。");
	outStream.close();
  }
  catch (IOException e){
                System.err.println(e.getMessage());
                }
  }
}
