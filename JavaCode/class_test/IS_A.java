class Animal {

}
class Fish extends Animal {

}
class Bird extends Animal {

}
class Eagle extends Bird {

}

public class IS_A {
    public static void main(String[] args) {
        Animal animal = new Animal();
        Fish fish = new Fish();
        Bird bird = new Bird();
        Eagle eagle = new Eagle();

        System.out.println("Fish is Animal : " + (fish instanceof Animal));
        System.out.println("Bird is Animal : " + (bird instanceof Animal));
        System.out.println("Eagle is Bird : " + (eagle instanceof Bird));
        System.out.println("Eagle is Animal : " + (eagle instanceof Animal));
        System.out.println("Bird is Bird : " + (bird instanceof Bird));
    }
}
