interface Animal {
    void showMe();
}
interface Bird extends Animal {
    void flying();
}
class Eagle implements Bird {
    public void showMe() {
        System.out.println("I am animal.");
    }
    public void flying() {
        System.out.println("I am flying.");
    }
}

public class inherit {
    public static void main(String[] args) {
        Eagle eagle = new Eagle();
        eagle.showMe();
        eagle.flying();
    }
}
