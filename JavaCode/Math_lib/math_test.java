public class math_test {
    public static void main(String[] args) {
        double[] ran = new double[10];

        for (int i = 0; i < 10; i++) {
            ran[i] = Math.random() * (6 - 1 + 1) + 1;
            System.out.println((int)ran[i]);
        }
    }
}