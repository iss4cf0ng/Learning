public class dead_lock {
    public static void main(String[] args) {
        String str1 = "Account";
        String str2 = "PwdWord";
        Thread t1 = new Thread() {
            public void run() {
                synchronized(str1) {
                    System.out.println("Thread 1 : Lock Account");
                    try {
                        Thread.sleep(300);
                    }
                    catch (Exception e) {
                        System.out.println(e);
                    }
                    synchronized(str2) {
                        System.out.println("Thread 1 : Lock PwdWord");
                    }
                }
            }
        };
        Thread t2 = new Thread() {
            public void run() {
                synchronized(str2) {
                    System.out.println("Thread 2 : Lock PwdWord");
                    try {
                        Thread.sleep(300);
                    }
                    catch (Exception e) {
                        System.out.println(e);
                    }
                    synchronized(str2) {
                        System.out.println("Thread 2 : Lock Account");
                    }
                }
            }
        };
        t1.start();
        t2.start();
    }
}
