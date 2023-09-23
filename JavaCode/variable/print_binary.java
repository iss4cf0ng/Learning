public class print_binary {
    public static void main(String[] args) {
        int x1, x2;
        x1 = 17;
        x2 = -2;
        System.out.println("x1 binary : " + Integer.toBinaryString(x1));
        System.out.println("x2 binary : " + Integer.toBinaryString(x2));
        System.out.println("x2 octal : " + Integer.toOctalString(x1));
        System.out.println("x2 octal : " + Integer.toOctalString(x2));
        System.out.println("x1 heximal : " + Integer.toHexString(x1));
        System.out.println("x2 heximal : " + Integer.toHexString(x2));
    }
}
