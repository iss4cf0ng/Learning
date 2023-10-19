public class value_of {
    public static void main(String[] args) {
        Integer x = Integer.valueOf(10);
        Integer y = Integer.valueOf("101");
        Integer b2 = Integer.valueOf("10111", 2);
        Integer b8 = Integer.valueOf("15", 8);
        Integer b16 = Integer.valueOf("18a", 16);

        System.out.println(x);
        System.out.println(y);
        System.out.println(b2);
        System.out.println(b8);
        System.out.println(b16);
    }
}
