interface A {
    default void running() {
        System.out.println("I am A.");
    }
}
interface B extends A {
    default void running() {
        System.out.println("I am B.");
    }
}
interface C extends A {
    default void running() {
        System.out.println("I am C.");
    }
}
class D implements B, C {
    public void running() {
        System.out.println("I am D.");
    }
    public void who() {
        B.super.running();
        C.super.running();
    }
}

public class diamond_problem {
    public static void main(String[] args) {
        D obj = new D();
        obj.running();
        obj.who();
    }
}
