import java.io.*;
import java.security.*;
import java.security.spec.*;
import javax.crypto.*;
import javax.crypto.spec.*;

public class RSAverify implements Serializable{
 public static void main(String args[]){
  	try{
	FileInputStream inFile = new FileInputStream(args[0]);
	FileInputStream keyFile = new FileInputStream(args[2]);
	ObjectInputStream skeyFile = new ObjectInputStream(keyFile);
	PublicKey skey = (PublicKey) skeyFile.readObject();
	FileInputStream signed = new FileInputStream(args[1]);
	byte[] buf = new byte[128];
	byte[] digitalsign = new byte[128];
	byte[] gbuf = new byte[128];
	int len;
	Signature sha = Signature.getInstance("SHA1withRSA");
	sha.initVerify(skey);
	while(( len = inFile.read(digitalsign)) != -1){
		sha.update(digitalsign,0,len);
	}
	ByteArrayOutputStream outbyte = new ByteArrayOutputStream();
	while(( len = signed.read(gbuf)) != -1){
		outbyte.write(gbuf,0,len);
        }
	buf = outbyte.toByteArray();
	boolean verifies = sha.verify(buf,0,buf.length);
	System.out.println("署名検証結果 "+ verifies);
	keyFile.close();
	signed.close();
	inFile.close();
	}
	catch (Exception e){
		System.err.println(e.getMessage());
		}
 }
}
