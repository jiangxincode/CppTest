public class testdll{
	static {
		System.loadLibrary("testdll");
		}
	public native static int get();
	public native static void set(int i);
	public static void main(String[] args) {
		testdll test = new testdll();
		test.set(10);
		System.out.println(test.get());
		}
	}