import myMath.CalAdd;
import myMath.subMath.*;
public class test {
    public static void main(String[] args) {
        CalAdd obj1 = new CalAdd();
        System.out.println(obj1.add(1, 5));

        CalSub obj2 = new CalSub();
        System.out.println(obj2.sub(5, 3));
    }
}
