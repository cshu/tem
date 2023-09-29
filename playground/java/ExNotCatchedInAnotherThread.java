

//Unlike c++/golang, Java uncaught exception terminate only one thread, not necessarily the entire program

public class ExNotCatchedInAnotherThread{
	public static void main(String[] args) throws Exception {
		System.out.println("begin");
		new Thread(() -> {
			System.out.println("new thread");
			try{
				Thread.sleep(500);
			} catch (Exception e){
				System.out.println("unreachable");
			}
			int x = 1/0;
		}).start();
		Thread.sleep(2000);
		System.out.println("end");
	}
}
