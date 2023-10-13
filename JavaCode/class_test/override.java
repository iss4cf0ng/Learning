class Animal {
    public void moving() {
        System.out.println("Animal moving.");
    }
}
class Cat extends Animal {
    @Override
    public void moving() {
        super.moving();
        System.out.println("Cat moving and jumping");
    }
}

public class override {
    public static void main(String[] args) {
        Cat c = new Cat();
        c.moving();
    }
}
