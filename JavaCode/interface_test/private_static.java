interface LearnJava {
    abstract void method1();
    default void method2() {
        method4();
        method5();
        System.out.println("This is default method");
    }
    public static void method3() {
        method5();
        System.out.println("This is static method.");
    }
    private void method4() {
        System.out.println("This is private method");
    }
    private static void method5() {
        System.out.println("This is private static method.");
    }
}
class Learning implements LearnJava {
    public void method1() {
        System.out.println("This is abstract method.");
    }
}

public class private_static {
    public static void main(String[] args) {
        LearnJava obj = new Learning();
        obj.method1();
        obj.method2();
        LearnJava.method3();
    }
}
