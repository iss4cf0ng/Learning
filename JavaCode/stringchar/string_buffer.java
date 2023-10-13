public class string_buffer {
    public static void main(String[] args) {
        String str = "ISSAC";
        StringBuffer sb = new StringBuffer(str);
        System.out.println("StringBuffer object content : " + sb);
        System.out.println("StringBuffer object length : " + sb.length());
        System.out.println("StringBuffer object capacity : " + sb.capacity());

        //Modify capacity
        sb.ensureCapacity(10); //Less then original capacity -> unchange
        System.out.println("StringBuffer object capacity : " + sb.capacity());
        sb.ensureCapacity(30);
        System.out.println("StringBuffer object capacity : " + sb.capacity());
        sb.ensureCapacity(100);
        System.out.println("StringBuffer object capacity : " + sb.capacity());

        //Modify length
        sb.setLength(10);
        System.out.println("StringBuffer object content : " + sb);
        System.out.println("StringBuffer object length : " + sb.length());
        sb.setLength(3);
        System.out.println("StringBuffer object content : " + sb);
        System.out.println("StringBuffer object length : " + sb.length());
    }
}