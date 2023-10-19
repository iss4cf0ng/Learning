import java.io.*;

public class console_pwd {
    public static void main(String[] args) {
        Console cs = System.console();
        cs.printf("Enter password : ");
        char[] ch = cs.readPassword();
        String pwd = String.valueOf(ch);
        cs.printf("Your password %s", pwd);
    }
}
