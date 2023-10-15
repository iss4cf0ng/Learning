class A implements Runnable {
    public void run() {
        System.out.println("A is running.");
    }
}
class HorseRacing implements Runnable {
    private String name;
    HorseRacing(String name) {
        this.name = name;
    }
    public void run() {
        for (int i = 1; i <= 1000; i++)
            System.out.println(name + " in round : " + i);
    }
}

public class runnable {
    public static void main(String[] args) {
        A a = new A();
        Thread t = new Thread(a);
        t.start();

        HorseRacing hr1 = new HorseRacing("Horse1");
        HorseRacing hr2 = new HorseRacing("Horse2");
        Thread t1 = new Thread(hr1);
        Thread t2 = new Thread(hr2);
        t1.start();
        t2.start();
    }
}
