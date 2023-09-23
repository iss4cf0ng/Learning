import java.util.*;

public class recursive_factorial {
    public static void main(String[] args)    {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter integer : ");
        int input = scanner.nextInt();
        System.out.println("Result : " + factorial(input));
    }

    public static int factorial(int n) {
        if (n == 1)
            return n;
        else
            return n * factorial(n - 1);
    }
}