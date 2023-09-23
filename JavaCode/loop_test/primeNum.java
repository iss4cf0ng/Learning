import java.util.Scanner;

public class primeNum {
    public static void main(String[] args) {
        boolean prime = true;
        int num;
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter a number : ");
        num = scanner.nextInt();
        if (num < 2) {
            System.out.println("Must larger then 1");
            return;
        }
        if (num == 2) {
            System.out.println("2 is prime number.");
            return;
        } else {
            for (int i = 2; i < num; i++) {
                if (num % i == 0) {
                    System.out.printf("%d is not prime number.%n", num);
                    prime = false;
                    break;
                }
            }
        }

        if (prime) {
            System.out.printf("%d is prime number.%n", num);
        }
    }
}
