interface Shape {
    double PI = 3.14;
    double area();
}
class Rectangle implements Shape {
    protected double height, width;
    Rectangle(double height, double width) {
        this.height = height;
        this.width = width;
    }
    public double area() {
        return height * width;
    }
}
class Circle implements Shape {
    protected double r;
    Circle(double r) {
        this.r = r;
    }
    public double area() {
        return PI * r * r;
    }
}

public class variable {
    public static void main(String[] args) {
        Rectangle rectangle = new Rectangle(2, 3);
        Circle circle = new Circle(2);
        System.out.println("Rectangle area : " + rectangle.area());
        System.out.println("Circle area : " + circle.area());
        System.out.println("Rectangle PI : " + rectangle.PI);
        System.out.println("Circle PI : " + circle.PI);
    }
}
