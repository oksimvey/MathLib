
public class CIntegrationJ {
    
     static {
        System.loadLibrary("native");
    }

    public native long add(int a, int b);

    static CIntegrationJ integration = new CIntegrationJ();

   public static void main(String[] args) {


    long result = 0;

        long t0 = System.nanoTime();

       result = integration.add(0,0);

      

        long t1 = System.nanoTime();

        System.out.println(result);

        System.out.println((t1 - t0) / 1000000 + "ms");
    }
}