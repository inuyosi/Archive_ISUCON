import java.io.*;
import java.security.*;
import java.security.spec.*;
import javax.crypto.*;
import javax.crypto.spec.*;

public class KeyGen {
 public static void main(String args[]){
  	try{
	KeyGenerator kg = KeyGenerator.getInstance(args[0]);
	kg.init(Integer.parseInt(args[1]));
	SecretKey skey = kg.generateKey();
	FileOutputStream outFile = new FileOutputStream(args[2]);
	ObjectOutputStream ooFile = new ObjectOutputStream(outFile);
	ooFile.writeObject(skey);
	ooFile.close();
	}
	catch (NoSuchAlgorithmException e){
		System.err.println(e.getMessage());
		}
	catch (IOException e){
		System.err.println(e.getMessage());
		}
 }
}
