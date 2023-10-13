class Animal {
    public void walk() {
        System.out.println("Animal is walking.");
    }
}
class Dog extends Animal {
    public void walk() {
        System.out.println("Dog is walking.");
    }
    public void eat() {
        System.out.println("Dog is eating.");
    }
}
class Cat extends Animal {
    public void walk() {
        System.out.println("Cat is walking.");
    }
}

public class downcasting {
    public static void main(String[] args) {
        Animal animal = new Dog(); //Upcasting
        animal.walk();
        Dog dog = (Dog)animal; //Downcasting
        dog.walk();
        dog.eat();
    }
}
