import java.io.*;
public class FileCopy {
	public static void main(String args[]){
		try{
		FileInputStream inFile = new FileInputStream(args[0]);
		byte[] buf = new byte[inFile.available()];
		char[] cbuf = new char[inFile.available()];
		FileOutputStream outFile = new FileOutputStream(args[1]);
		System.out.println("入力文:");
		FileReader filereader = new FileReader(args[0]);
		filereader.read(cbuf,0,cbuf.length);
		System.out.println(cbuf);
		filereader.close();
		outFile.write(buf,0,buf.length);
		System.out.println("ファイルサイズ:"+buf.length);
		inFile.close();
		outFile.close();
		}
		catch (IOException e){
		System.err.println(e.getMessage());
		}
	}
}
