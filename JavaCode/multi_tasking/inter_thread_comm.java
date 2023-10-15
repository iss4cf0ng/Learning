class Bank {
    int balance = 10000;
    synchronized void withdraw(int amount) {
        System.out.println("Withdraw");
        while (balance < amount) {
            System.out.println("Insufficient balance");
            try {
                wait();
            }
            catch (Exception e) {
                System.out.println(e);
            }
        }
        balance -= amount;
        System.out.println("Withdraw finished");
    }
    synchronized void deposit(int amount) {
        System.out.println("Deposit.");
        balance += amount;
        System.out.println("Deposit finished");
        notify();
    }
}

public class inter_thread_comm {
    public static void main(String[] args) {
        Bank bank = new Bank();
        Thread t1 = new Thread() {
            public void run() {
                bank.withdraw(15000);
            }
        };
        t1.start();
        Thread t2 = new Thread() {
            public void run() {
                bank.deposit(10000);
            }
        };
        t2.start();
    }
}
