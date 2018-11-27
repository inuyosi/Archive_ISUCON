import java.io.*;
import java.security.*;
import java.security.spec.*;
import javax.crypto.*;
import javax.crypto.spec.*;

public class SKdecrypt implements Serializable{
 public static void main(String args[]){
  	try{
	FileInputStream inFile = new FileInputStream(args[0]); 			//平文読込み
	FileInputStream keyFile = new FileInputStream(args[1]); 		//共通鍵読込み
	ObjectInputStream skeyFile = new ObjectInputStream(keyFile);	
	SecretKey skey = (SecretKey) skeyFile.readObject();				
	String algorithm = skey.getAlgorithm();							//アルゴリズム取得
	IvParameterSpec iv;
	byte[] buf = new byte[8];
	byte[] gbuf = new byte[2048];
	int len;
	FileInputStream paramFile = new FileInputStream(args[4]);		
	length = paramFile.read(buf);
	iv = new IvParameterSpec(buf,0,length);
	//cipher生成
	Cipher cipher = Cipher.getInstance(algorithm+"/"+args[3]+"/PKCS5Padding");	
	//cipher初期化
	cipher.init(Cipher.DECRYPT_MODE,skey,iv);
	FileOutputStream encrypted = new FileOutputStream(args[2]);
	while(( len = inFile.read(buf)) != -1){
		gbuf = cipher.update(buf,0,len);
		encrypted.write(gbuf);
	}
	gbuf = cipher.doFinal();
	inFile.close();
	keyFile.close();
	encrypted.close();
	}
	catch (Exception e){
		System.err.println(e.getMessage());
		}
 }
}
