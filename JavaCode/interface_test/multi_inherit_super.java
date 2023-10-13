interface Dog {
    void who();
    default void running() {
        System.out.println("Dog is running.");
    }
}
interface Cat {
    void who();
    default void running() {
        System.out.println("Cat is running.");
    }
}
class Horse {
    public void running() {
        System.out.println("Horse is running.");
    }
}
class Pet extends Horse implements Dog, Cat {
    public void who() {
        Dog.super.running();
        Cat.super.running();
    }

}

public class multi_inherit_super {
    public static void main(String[] args) {
        Pet obj = new Pet();
        obj.running();
        obj.who();
    }
}