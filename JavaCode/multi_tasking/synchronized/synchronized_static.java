class Demo {
    synchronized static void printDemo(int n) {
        for (int i = 1; i <= 5; i++) {
            System.out.println("Output : " + i * n);
            try {
                Thread.sleep(500);
            }
            catch(Exception e) {
                System.out.println(e);
            }
        }
    }
}
class JobThread1 extends Thread {
    public void run() {
        Demo.printDemo(10);
    }
}
class JobThread2 extends Thread {
    public void run() {
        Demo.printDemo(100);
    }
}

public class synchronized_static {
    public static void main(String[] args) {
        JobThread1 t1 = new JobThread1();
        JobThread2 t2 = new JobThread2();
        t1.start();
        t2.start();
    }
}
