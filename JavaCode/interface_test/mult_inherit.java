interface Bird {
    void flying();
}
interface Airplane {
    void flying();
}
interface Fly extends Bird, Airplane {
    
}
class InfoFly implements Fly {
    public void flying() {
        System.out.println("Is flying.");
    }
}

interface Dog {
    default void running() {
        System.out.println("Dog is running.");
    }
}
interface Cat {
    default void running() {
        System.out.println("Cat is running.");
    }
}
class Pet implements Dog, Cat {
    public void running() {
        System.out.println("Pet is running.");
    }
}

//Multiple inheritance
public class mult_inherit {
    public static void main(String[] args) {
        Pet obj = new Pet();
        obj.running();

        
    }
}
