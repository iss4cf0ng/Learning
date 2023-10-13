class Animal {
    public void moving() {
        System.out.println("Animal moving.");
    }
}
class Cat extends Animal {
    public void moving(String msg) {
        System.out.println(msg);
    }
}

public class overload {
    public static void main(String[] args) {
        Cat c = new Cat();
        c.moving();
        c.moving("Cat moving");
    }
}
