public class print_format {
    public static void main(String[] args) {
        int x = 100;
        double y = 10.5;
        String s = "deep";
        System.out.printf("x=/%6d/\n", x);
        System.out.printf("y=/%6.2f/\n", y);
        System.out.printf("s=/%6s/\n", s);

        System.out.printf("x=/%-6d/\n", x);
        System.out.printf("y=/%-6.2f/\n", y);
        System.out.printf("s=/%-6s/\n", s);
    }
}