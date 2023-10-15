class Xjoin extends Thread {
    Xjoin(String name) {
        super(name);
    }
    public void run() {
        for (int i = 1; i <= 5; i++) {
            try {
                sleep(500);
            }
            catch (InterruptedException e) {
                System.out.println(e);
            }
            System.out.println(getName() + " is running : " + i);
        }
    }
}

public class thread_join {
    public static void main(String[] args) {
        Xjoin job1 = new Xjoin("Job1");
        Xjoin job2 = new Xjoin("Job2");
        Xjoin job3 = new Xjoin("Job3");
        job1.start();
        try {
            job1.join();
        }
        catch (InterruptedException e) {
            System.out.println(e);
        }
        job2.start();
        job3.start();
    }
}
