class Animal {
    private String name;
    Animal(String name) {
        this.name = name;
    }
    public void eat() {
        System.out.println(name + " is Eating");
    }
    public void sleep() {
        System.out.println(name + " is Sleeping");
    }
}
class Dog extends Animal {
    Dog(String name) {
        super(name);
    }
    public void barking() {
        System.out.println("Is barking");
    }
}

public class private_super {
    public static void main(String[] args) {
        Dog dog = new Dog("Hally");
        dog.eat();
        dog.sleep();
        dog.barking();
    }
}