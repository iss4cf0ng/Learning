interface MyMath {
    default int addEven(int... nums) {
        return add(true, nums);
    }
    default int addOdd(int... nums) {
        return add(false, nums);
    }
    private int add(boolean flag, int... nums) {
        int sum_odd, sum_even;
        sum_odd = sum_even = 0;
        for (int num:nums) {
            if (num % 2 == 1)
                sum_odd += num;
            else
                sum_even += num;
        }
        if (flag)
            return sum_even;
        else
            return sum_odd;
    }
}

public class private_static_2 implements MyMath {
    public static void main(String[] args) {
        MyMath obj = new private_static_2();
        int even_sum = obj.addEven(1,2,3,4,5,6,7,8,9);
        int odd_sum = obj.addOdd(1,2,3,4,5,6,7,8,9);
        System.out.println("Even sum : " + even_sum);
        System.out.println("Odd sum : " + odd_sum);
    }
}
