interface Bird {
    void showMe();
    default void action() {
        System.out.println("I can fly.");
    }
}
class Eagle implements Bird {
    public void showMe() {
        System.out.println("I am bird.");
    }
}

//---------------------------------------------------------
interface Vehicle {
    String getBrand();
    String run();
    default String alarmOn() {
        return "Alarm on!";
    }
    default String alarmOff() {
        return "Alarm off!";
    }
    static int rpmUp(int rpm) {
        return rpm + 50;
    }
}
class Car implements Vehicle {
    private String brand;
    Car(String brand) {
        this.brand = brand;
    }
    public String getBrand() {
        return brand;
    }
    public String run() {
        return "Safety driving.";
    }
}

public class default_method {
    public static void main(String[] args) {
        Eagle eagle = new Eagle();
        eagle.showMe();
        eagle.action();

        Vehicle car = new Car("TOYOTA");
        System.out.println(car.getBrand());
        System.out.println(car.run());
        System.out.println(car.alarmOn());
        System.out.println(car.alarmOff());
        System.out.println(Vehicle.rpmUp(3000));
    }
}
