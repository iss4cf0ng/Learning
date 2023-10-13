abstract class Shape {
    public void draw() {

    }
}
class Circle extends Shape {
    @Override
    public void draw() {
        System.out.println("Draw a circle.");
    }
}

abstract class MyMath {
    abstract int add(int n1, int n2);
    abstract int mul(int n1, int n2);
    void output() {
        System.out.println("MyMath");
    }
}
class MyTest extends MyMath {
    @Override
    public int add(int num1, int num2) {
        return num1 + num2;
    }
    public int mul(int num1, int num2) {
        return num1 * num2;
    }
}

public class test {
    public static void main(String[] args) {
        Circle circle = new Circle();
        circle.draw();

        MyMath obj = new MyTest();
        System.out.println(obj.add(3, 0));
        System.out.println(obj.mul(10, 2));
    }
}
