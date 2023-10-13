class Animal {
    public void eat() {
        System.out.println("Eating");
    }
    public void sleep() {
        System.out.println("Sleeping");
    }
}
class Dog extends Animal {
    public void barking() {
        System.out.println("Barking");
    }
}

class Father {
    protected int x = 50;
}
class Child extends Father {
    protected int x = 100;
    public void printInfo() {
        System.out.println("Print Father x : " + super.x);
        System.out.println("Print Chlid x : " + x);
    }
}

public class extends_class {
    public static void main(String[] args) {
        Dog dog = new Dog();
        dog.eat();
        dog.sleep();
        dog.barking();
        System.out.println("---------------------------------------------------");

        Father father = new Father();
        Child child = new Child();
        child.printInfo();
    }
}
