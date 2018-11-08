import java.io.*;
import java.security.*;
import java.security.spec.*;
import javax.crypto.*;
import javax.crypto.spec.*;

public class SKdecrypt implements Serializable{
 public static void main(String args[]){
  	try{
	FileInputStream inFile = new FileInputStream(args[0]);
	FileInputStream keyFile = new FileInputStream(args[1]);
	ObjectInputStream skeyFile = new ObjectInputStream(keyFile);
	SecretKey skey = (SecretKey) skeyFile.readObject();
	String algorithm = skey.getAlgorithm();
	byte[] buf = new byte[2048];
	byte[] gbuf = new byte[2048];
	int len;
	Cipher cipher = Cipher.getInstance(algorithm+"/"+args[3]+"/PKCS5Padding");
	cipher.init(Cipher.DECRYPT_MODE,skey);
	FileOutputStream outFile = new FileOutputStream(args[2]);
	ObjectOutputStream encrypted = new ObjectOutputStream(outFile);

	while(( len = inFile.read(buf)) != -1){
		gbuf = cipher.update(buf,0,len);
		encrypted.write(gbuf);
	}
	gbuf = cipher.doFinal();
	inFile.close();
	keyFile.close();
	encrypted.close();
	}
	catch (ClassNotFoundException e){
		System.err.println(e.getMessage());
		}
	catch (NoSuchAlgorithmException e){
		System.err.println(e.getMessage());
		}
	catch (IOException e){
		System.err.println(e.getMessage());
		}
	catch (NoSuchPaddingException e){
		System.err.println(e.getMessage());
		}
	catch (InvalidKeyException e){
		System.err.println(e.getMessage());
		}
	catch (IllegalBlockSizeException e){
		System.err.println(e.getMessage());
		}
	catch (BadPaddingException e) {
		System.err.println(e.getMessage());
		}
 }
}
