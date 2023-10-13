class MyMath {
    protected int square(int x) {
        return x * x;
    }
}

class Circle {
    protected MyMath obj;
    public double get_area(int radius) {
        obj = new MyMath();
        int r_square = obj.square(radius);
        return Math.PI * r_square;
    }
}

public class HAS_A {
    public static void main(String[] args) {
        Circle circle = new Circle();
        double area = circle.get_area(10);
        System.out.printf("Area : %6.2f\n", area);
    }
}
