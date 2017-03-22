import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.concurrent.ThreadLocalRandom;
public class JavaStrInstantiation {

	public static void main(String[] args) {
		try{
			if(args.length==0){
				int[] ints0=ThreadLocalRandom.current().ints(9999999,1,0xd7ff).toArray();//no surrogate?
				String strfromcwo = new String(ints0,0,ints0.length);
				int[] ints1=ThreadLocalRandom.current().ints(9999999,1,0x10ffff).toArray();//with surrogates?
				String strfromc = new String(ints0,0,ints0.length);

				long t0=System.currentTimeMillis();
				byte[] utf16le=strfromcwo.getBytes("UTF-16LE");
				long t1=System.currentTimeMillis();
				byte[] utf8=strfromcwo.getBytes("UTF-8");
				long t2=System.currentTimeMillis();
				byte[] utf16be=strfromcwo.getBytes("UTF-16BE");
				long t3=System.currentTimeMillis();
				System.out.println(t1-t0);
				System.out.println(t2-t1);
				System.out.println(t3-t2);
				t0=System.currentTimeMillis();
				String asutf16le=new String(utf16le,"UTF-16LE");
				t1=System.currentTimeMillis();
				String asutf8=new String(utf8,"UTF-8");
				t2=System.currentTimeMillis();
				String asutf16be=new String(utf16be,"UTF-16BE");
				t3=System.currentTimeMillis();
				System.out.println(t1-t0);
				System.out.println(t2-t1);
				System.out.println(t3-t2);

				t0=System.currentTimeMillis();
				utf16le=strfromc.getBytes("UTF-16LE");
				t1=System.currentTimeMillis();
				utf8=strfromc.getBytes("UTF-8");
				t2=System.currentTimeMillis();
				utf16be=strfromc.getBytes("UTF-16BE");
				t3=System.currentTimeMillis();
				System.out.println(t1-t0);
				System.out.println(t2-t1);
				System.out.println(t3-t2);
				t0=System.currentTimeMillis();
				asutf16le=new String(utf16le,"UTF-16LE");
				t1=System.currentTimeMillis();
				asutf8=new String(utf8,"UTF-8");
				t2=System.currentTimeMillis();
				asutf16be=new String(utf16be,"UTF-16BE");
				t3=System.currentTimeMillis();
				System.out.println(t1-t0);
				System.out.println(t2-t1);
				System.out.println(t3-t2);
			}else{
				byte[] bytes=Files.readAllBytes(Paths.get(args[0]));
				long t0=System.currentTimeMillis();
				String asutf16le=new String(bytes,"UTF-16LE");
				long t1=System.currentTimeMillis();
				String asutf8=new String(bytes,"UTF-8");
				long t2=System.currentTimeMillis();
				String asutf16be=new String(bytes,"UTF-16BE");
				long t3=System.currentTimeMillis();
				System.out.println(t1-t0);
				System.out.println(t2-t1);
				System.out.println(t3-t2);
			}
		}catch(Exception e){
			System.out.println(e);
		}
	}

}
