import java.util.Scanner;

public class scanner_has {
    public static void main(String[] args) {
        int x1, x2;
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter 2 integer(Split space) : ");
        while (!scanner.hasNextInt()) {
            System.out.println("First data is wrong : ");
            scanner.next();
        }
        x1 = scanner.nextInt();
        while (!scanner.hasNextInt()) {
            System.out.println("Second data is wrong : ");
            scanner.next();
        }
        x2 = scanner.nextInt();
        System.out.println("First number : " + x1);
        System.out.println("Second number : " + x2);
        System.out.println("Total : " + (x1 + x2));

        scanner.close();
    }
}