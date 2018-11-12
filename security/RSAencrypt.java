import java.io.*;
import java.security.*;
import java.security.spec.*;
import javax.crypto.*;
import javax.crypto.spec.*;

public class RSAencrypt implements Serializable{
 public static void main(String args[]){
  	try{
	FileInputStream inFile = new FileInputStream(args[0]);
	FileInputStream keyFile = new FileInputStream(args[1]);
	ObjectInputStream skeyFile = new ObjectInputStream(keyFile);
	PublicKey skey = (PublicKey) skeyFile.readObject();
	byte[] buf = new byte[2048];
	byte[] gbuf;
	byte[] tbuf = new byte[8];
	int len;
	keyFile.close();
	Cipher cipher = Cipher.getInstance("RSA");
	cipher.init(Cipher.ENCRYPT_MODE,skey);	
    FileOutputStream encrypted = new FileOutputStream(args[2]);
	while(( len = inFile.read(tbuf)) != -1){
		gbuf = cipher.update(tbuf,0,len);
		//encrypted.write(gbuf);
	}
	gbuf = cipher.doFinal();
	if(gbuf != null){
		encrypted.write(gbuf);
	}
	inFile.close();
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
