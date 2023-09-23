public class datatype_auto_convert {
    public static void main(String[] args) {
        int x;
        double y;
        float z;
        long a;
        short x1 = 10;
        byte x2 = 5;

        y = (x = 10) + 3.3; //x -> double
        System.out.println("y = " + y);
        z = x + 5.5F; //x -> float
        System.out.println("z = " + z);
        a = x + 10L; //x -> long
        System.out.println("a = " + a);
        x = x1 + x2; //x1 & x2 -> int
        System.out.println("x = " + x);
    }
}
