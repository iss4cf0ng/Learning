class HorseRacing extends Thread {
    private String name;
    HorseRacing(String name) {
        super(name);
    }
    public void run() {
        for (int i = 1; i <= 5; i++) {
            try {
                sleep(500);
            }
            catch(InterruptedException e) {
                System.out.println(e);
            }
            System.out.println(getName() + " in " + i + " round.");
        }
    }
}

public class thread_sleep {
    public static void main(String[] args) {
        HorseRacing t1 = new HorseRacing("Horse1");
        HorseRacing t2 = new HorseRacing("Horse2");
        t1.start();
        t2.start();
    }
}
