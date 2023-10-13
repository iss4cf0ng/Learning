interface Fly {
    void flying();
}
class Bird implements Fly {
    public void flying() {
        System.out.println("Bird is flying.");
    }
}
class Airplane implements Fly {
    public void flying() {

    }
}

public class test {
    public static void main(String[] args)    {
        Fly bird = new Bird();
        bird.flying();
    }
}