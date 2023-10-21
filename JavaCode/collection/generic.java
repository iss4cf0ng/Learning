//Generic class
class MyData<T> {
    private T obj;
    void setobj(T obj) {
        this.obj = obj;
    }
    public T getobj() {
        return this.obj;
    }
}

public class generic {
    //Generic method
    public static <E> void outputArray(E[] elements) {
        for (E element:elements) {
            System.out.println(element);
        }
    }

    public static void main(String[] args) {
        MyData<Integer> m = new MyData<Integer>();
        m.setobj(10);
        System.out.println(m.getobj());
        MyData<Double> d = new MyData<Double>();
        d.setobj(20.3);
        System.out.println(d.getobj());
        MyData<String> s = new MyData<String>();
        s.setobj("Hello");
        System.out.println(s.getobj());

        Integer[] int_array = {5, 10, 30, 50, 20};
        Character[] char_array = {'J', 'A', 'V', 'A'};
        System.out.println("Integer array");
        outputArray(int_array);
        System.out.println("Character array");
        outputArray(char_array);
    }
}
