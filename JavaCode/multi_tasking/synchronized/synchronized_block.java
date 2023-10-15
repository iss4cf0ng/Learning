class Demo {
    public void printDemo(int n) {
        synchronized(this) {
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

public class synchronized_block {
    public static void main(String[] args) {
        Demo obj = new Demo();
        new Thread() {
            public void run() {
                obj.printDemo(10);
            }
        }.start();
        new Thread() {
            public void run() {
                obj.printDemo(100);
            }
        }.start();
    }
}
