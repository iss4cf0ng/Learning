class Animal {
    protected String name;
    Animal(String name) {
        this.name = name;
    }
    public void eat() {
        System.out.println(name + " is eating");
    }
}
class Mammal extends Animal {
    protected String favorite_food;
    Mammal(String name, String favorite_food) {
        super(name);
        this.favorite_food = favorite_food;
    }
    public void favoriteFood() {
        System.out.println(name + " like to eat " + favorite_food);
    }
}
class Cat extends Mammal {
    Cat(String name, String favorite_food) {
        super(name, favorite_food);
    }
    public void jumping() {
        System.out.println(name + " is jumping");
    }
}

public class multi_level_inherit {
    public static void main(String[] args) {
        Cat cat = new Cat("Lucky", "Fish");
        cat.eat();
        cat.favoriteFood();
        cat.jumping();
    }
}
