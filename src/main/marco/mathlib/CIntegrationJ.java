
public class CIntegrationJ {
    
     static {
        System.loadLibrary("native");
    }

    public native int add(int a, int b);

    public static void main(String[] args) {
        CIntegrationJ integration = new CIntegrationJ();

        int result = integration.add(5, 3);

        



        System.out.println(result);
    }
}
