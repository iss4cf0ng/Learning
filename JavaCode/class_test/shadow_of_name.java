class ShadowingTest {
    int x = 10;
    void printInfo(int x) {
        System.out.println("Local variable : " + x);
        System.out.println("Member property : " + this.x);
    }
}

public class shadow_of_name {
    public static void main(String[] args) {
        ShadowingTest A = new ShadowingTest();
        A.printInfo(20);
    }
}
