class MultiThread extends Thread {
    MultiThread(String name) {
        super(name);
    }
    public void run() {
        System.out.println("Thread is running...");
    }
}
class HorseRacing extends Thread {
    private String name;
    HorseRacing(String name) {
        super(name);
    }
    public void run() {
        for (int i = 1; i <= 1000; i++)
            System.out.println(getName() + " in " + i + " round.");
    }
}

public class test {
    public static void main(String[] args) {
        /*
        MultiThread t = new MultiThread("Horse");
        t.start();
        System.out.println("Thread name : " + t.getName());
        */

        HorseRacing t1 = new HorseRacing("Horse1");
        HorseRacing t2 = new HorseRacing("Horse2");
        t1.start();
        t2.start();
    }
}
