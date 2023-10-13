class Animal {
    String name = "Dog";
    int age = 5;
}

public class hashcode {
    public static void main(String[] args) {
        String msg1 = "Hello";
        int hd1 = msg1.hashCode();
        System.out.println("HashCode of Hello : " + hd1);
        String msg2 = msg1;
        int hd2 = msg2.hashCode();
        System.out.println("HashCode of msg2 : " + hd2);

        StringBuilder sb = new StringBuilder(msg2);
        int hd3 = sb.hashCode();
        System.out.println("HashCode of sb : " + hd3);

        Animal animal = new Animal();
        int hd4 = animal.hashCode();
        System.out.println("HashCode of animal class : " + hd4);
    }
}
