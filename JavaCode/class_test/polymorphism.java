class School {
    public void demo() {
        System.out.println("School");
    }
}
class Department extends School {
    public void demo() {
        System.out.println("Department");
    }
}

class Bank {
    int balance = 10000;
}
class FirstBank extends Bank {
    int balance = 50000;
}

public class polymorphism {
    public static void main(String[] args) {
        School A = new School();
        School B = new Department();
        A.demo();
        B.demo();
        System.out.println("--------------------------------");

        Bank c = new FirstBank();
        System.out.println(c.balance);
    }
}
