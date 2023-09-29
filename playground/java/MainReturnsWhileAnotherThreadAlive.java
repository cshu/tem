

//Unlike c++/golang, main return does not terminate program (provided there is other non-daemon thread still running)

public class MainReturnsWhileAnotherThreadAlive{
	public static void main(String[] args) throws Exception {
		System.out.println("begin");
		new Thread(() -> {
			try{
				System.out.println("new thread");
				try{
					Thread.sleep(5000);
				} catch (Exception e){
					System.out.println("unreachable");
				}
				System.out.println(Thread.interrupted());//this prints false
				System.out.println("after sleep");
			}finally{
				System.out.println("block of finally");
			}
		}).start();
		Thread.sleep(100);
		System.out.println("end");
	}
}
