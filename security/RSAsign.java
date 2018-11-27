import java.io.*;
import java.security.*;
import java.security.spec.*;
import javax.crypto.*;
import javax.crypto.spec.*;

public class RSAsign implements Serializable{
 public static void main(String args[]){
  	try{
	FileInputStream inFile = new FileInputStream(args[0]);
	FileInputStream keyFile = new FileInputStream(args[1]);
	ObjectInputStream skeyFile = new ObjectInputStream(keyFile);
	PrivateKey skey = (PrivateKey) skeyFile.readObject();
	byte[] buf = new byte[2048];
	byte[] gbuf;
	byte[] tbuf = new byte[128];
	int len;
	keyFile.close();
	Signature sha = Signature.getInstance("SHA1withRSA");
	sha.initSign(skey);
	FileOutputStream signed = new FileOutputStream(args[2]);
	while(( len = inFile.read(tbuf)) != -1){
		sha.update(tbuf,0,len);
	}
	byte[] digitalsign = sha.sign();
	signed.write(digitalsign);
	inFile.close();
	signed.close();
	}
	catch (Exception e){
		System.err.println(e.getMessage());
		}
 }
}
