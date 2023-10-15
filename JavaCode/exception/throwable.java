public class throwable {
    public static String myDiv(int x, int y) {
        try {
            return Integer.toString(x / y);
        } catch (ArithmeticException e) {
            System.out.println(e);
            System.out.println(e.toString());
            System.out.println(e.getMessage());
            e.printStackTrace();
            return "Div 0";
        }
    }
    public static void myMethod(int x1, int x2) throws ArithmeticException {
        System.out.println("Division : " + (x1 / x2));
    }

    public static void main(String[] args) {
        System.out.println(myDiv(6, 2));
        System.out.println(myDiv(6, 0));

        int[][] x = {{10, 2}, {10, 0}, {10, 5}};
        for (int i = 0; i < x.length; i++) {
            try {
                myMethod(x[i][0], x[i][1]);
            }
            catch (ArithmeticException e) {
                System.out.println("Div 0 exception : " + e);
            }
        }
    }
}
