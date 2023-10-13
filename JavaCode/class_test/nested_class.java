class School {
    class Motto {
        public void printInfo() {
            System.out.println("Motto");
        }
    }
}

class Animal {
    public void moving() {
        System.out.println("Animal moving.");
    }
}

class MyCat {
    public void show_msg(Animal obj) {
        System.out.println("Anonymous class for parameter return : " + obj.toString());
    }
}

public class nested_class {
    public static void main(String[] args) {
        School sc = new School();
        School.Motto inner = sc.new Motto();
        inner.printInfo();

        Animal _inner = new Animal() {
            public void moving() {
                System.out.println("Cat moving.");
            }
        };
        _inner.moving();

        new Animal() {
            public void moving() {
                System.out.println("Cat moving.");
            }
        }.moving();
    }
}
