class XPriority extends Thread {
    XPriority(String name) {
        super(name);
    }
    public void run() {
        for (int i = 1; i <= 10; i++) {
            System.out.println(getName() + " is running : " + i);
        }
    }
}

public class thread_priority {
    public static void main(String[] args) {
        XPriority rabbit = new XPriority("Rabbit.");
        rabbit.setPriority(Thread.MAX_PRIORITY);
    }
}
