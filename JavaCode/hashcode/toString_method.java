class Animal {
    String name = "Dog";
    int age = 5;
}
class NewAnimal {
    String name = "Dog";
    int age = 5;

    @Override
    public String toString() {
        return this.name + "|" + this.age;
    }
}

public class toString_method {
    public static void main(String[] args) {
        Animal animal = new Animal();
        System.out.println("Print object : " + animal);

        NewAnimal new_animal = new NewAnimal();
        System.out.println("Print object : " + new_animal);
    }
}
