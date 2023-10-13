class Animal {
    String name = "Dog";
    int age = 5;
}

public class equals_method {
    public static void main(String[] args) {
        Animal A = new Animal();
        Animal B = new Animal();
        Animal C = B;
        System.out.println("A=B : " + A.equals(B));
        System.out.println("B=C : " + B.equals(C));
    }
}
