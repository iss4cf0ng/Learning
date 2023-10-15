class MyException extends Exception {
    String str;
    MyException(String msg) {
        str = msg;
    }
    public String toString() {
        return "Self define MyException occur " + str;
    }
}

public class my_exception {
    public static void main(String[] args) {
        try {
            System.out.println("try area.");
            throw new MyException("ERRORRRRRRR");
        }
        catch (MyException e) {
            System.out.println("catch area.");
            System.out.println("MyException : " + e);
            e.printStackTrace();
        }
    }
}
