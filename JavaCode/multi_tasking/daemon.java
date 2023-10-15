class XDaemon extends Thread {
    public void run() {
        if (Thread.currentThread().isDaemon()) {
            System.out.println("Daemon starting...");
            try {
                sleep(5000);
            }
            catch (InterruptedException e) {
                System.out.println(e);
            }
            System.out.println("Daemon exiting...");
        }
        else {
            System.out.println("Non-Daemon start...");
            System.out.println("Non-Daemon exiting...");
        }
    }
}

public class daemon {
    public static void main(String[] args) {
        XDaemon d = new XDaemon();
        XDaemon nd = new XDaemon();
        d.setDaemon(true);
        d.start();
        nd.start();
    }
}
