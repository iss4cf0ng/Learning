import java.util.regex.*;
public class util_regex {
    public static void main(String[] args) {
        String str = "0952-001-001";
        String pattern = "\\d{4}(-\\d{3}){2}";

        Pattern p = Pattern.compile(pattern);
        Matcher m = p.matcher(str);

        System.out.println("Method 1 : " + m.matches());
        System.out.println("Method 2 : " + Pattern.matches(pattern, str));
    }
}
