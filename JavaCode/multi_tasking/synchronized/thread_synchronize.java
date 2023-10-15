class Demo {
    public synchronized void printDemo(int n) {
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
    Demo PD;
    JobThread1(Demo pd) {
        this.PD = pd;
    }
    public void run() {
        PD.printDemo(10);
    }
}
class JobThread2 extends Thread {
    Demo PD;
    JobThread2(Demo pd) {
        this.PD = pd;
    }
    public void run() {
        PD.printDemo(100);
    }
}

public class thread_synchronize {
    public static void main(String[] args) {
        Demo obj = new Demo();
        JobThread1 t1 = new JobThread1(obj);
        JobThread2 t2 = new JobThread2(obj);
        t1.start();
        t2.start();
    }
}
