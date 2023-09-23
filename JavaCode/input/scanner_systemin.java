package JavaCode.input;
import java.util.Scanner;

public class scanner_systemin {
    public static void main(String[] args) {
        int x1, x2;
        String x;

        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter 2 integer(Split with space)");
        x1 = scanner.nextInt();
        x2 = scanner.nextInt();
        System.out.println("First integer : " + x1);
        System.out.println("Second integer : " + x2);
        System.out.println("Sum : " + (x1 + x2));

        System.out.print("Enter 2 integer(Split with space)");
        x1 = scanner.nextInt();
        x2 = scanner.nextInt();
        System.out.println("First integer : " + x1);
        System.out.println("Second integer : " + x2);
        System.out.println("Sum : " + (x1 + x2));

        System.out.print("Enter name : ");
        x = scanner.next();
        System.out.print("Your name : " + x);

        scanner.close();
    }
}
