import java.net.*;
public class test {
    public static void main(String[] args) {
        try {
            int index = 0;
            int k=15;
                Socket sock = new Socket("127.0.0.1", 5050);
                //System.out.println("send content:  name=kingfish  "+"value="+(1+index));
                String mes = "lilasd aseasd asd asd a";
                byte[] temp = mes.getBytes();
                byte[] buf = new byte[28];
                System.arraycopy(temp, 0, buf, 0, temp.length);
                sock.getOutputStream().write(buf);
                sock.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
} // end 