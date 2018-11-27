import java.io.*;
import java.security.*;
import java.security.spec.*;
import javax.crypto.*;
import javax.crypto.spec.*;

public class RSAdecrypt implements Serializable{
 public static void main(String args[]){
  	try{
	FileInputStream inFile = new FileInputStream(args[0]);
	FileInputStream keyFile = new FileInputStream(args[1]);
	ObjectInputStream skeyFile = new ObjectInputStream(keyFile);
	PrivateKey skey = (PrivateKey) skeyFile.readObject();
	byte[] buf = new byte[2048];
	byte[] gbuf;
	byte[] tbuf = new byte[8];
	int len;
	keyFile.close();
	Cipher cipher = Cipher.getInstance("RSA");
	cipher.init(Cipher.DECRYPT_MODE,skey);
    FileOutputStream decrypted = new FileOutputStream(args[2]);
	while(( len = inFile.read(tbuf)) != -1){
		gbuf = cipher.update(tbuf,0,len);
		decrypted.write(gbuf);
	}
	gbuf = cipher.doFinal();
	if(gbuf != null){
		decrypted.write(gbuf);
	}
	inFile.close();
	decrypted.close();
	}
	catch (Exception e){
		System.err.println(e.getMessage());
		}
 }
}
