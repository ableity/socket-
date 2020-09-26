import java.io.*;
import java.net.*;
import java.nio.channels.FileLockInterruptionException;

public class SocketServer{

    private static ServerSocket serverSocket;
    private static ServerSocket serverSocket2;
    private static ServerSocket serverSocket3;
    public String FLAG;
    String IMG = "image";
    String STR = "string";

    //启动服务器
    public static void main(String[] args) throws IOException {

        serverSocket=new ServerSocket(18893);
        serverSocket2=new ServerSocket(18895);
        serverSocket3=new ServerSocket(18892);
        Accept_img accept;
        Thread thread;
        accept=new Accept_img(serverSocket,serverSocket3);
        thread=new Thread(accept);
        thread.start();

        Accept_and_send accept_str;
        Thread thread_str;
        accept_str= new Accept_and_send(serverSocket2);
        thread_str=new Thread(accept_str);
        thread_str.start();

        }

}




class Showip implements Runnable{
    //展示IP地址（但是展示的不太对，去网络属性里看对应的IPV4地址）
    @Override
    public void run() {
        InetAddress address = null;
            //while(true){
        try {
            address = InetAddress.getLocalHost();
            System.out.println("IP: " + address.getHostAddress());
        } catch (UnknownHostException e) {
            e.printStackTrace();
        }

                //Thread.sleep(30000);
            //}
    }
}

class Accept_img implements Runnable{
    //接收文件，原版没修改
    ServerSocket serverSocket=null;
    ServerSocket serverSocket_name = null;
    private String FILE_NAME = null;
    public Accept_img(ServerSocket serverSocket_root,ServerSocket serverSocket_name_)
    {
        serverSocket  = serverSocket_root;
        serverSocket_name = serverSocket_name_;
    }
    @Override
    public void run() {
        System.out.println("文件等待传输");
        try {
            receiveFile();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    public void receiveFile() throws IOException {

        Socket socket_name=null;
        socket_name=serverSocket_name.accept();
        //System.out.println("socket="+socket.toString());
        DataInputStream inputStream=new DataInputStream(socket_name.getInputStream());
        FILE_NAME=inputStream.readUTF();
        inputStream.close();
        socket_name.close();


        byte[] inputByte = null;
        int length = 0;
        DataInputStream dis = null;
        FileOutputStream fos = null;
        Socket socket=null;

        try {
            try {
                while(true)
                {
                    socket=serverSocket.accept();
                    dis = new DataInputStream(socket.getInputStream());
                    fos = new FileOutputStream(new File("D:/"+FILE_NAME));
                    inputByte = new byte[1024];
                    System.out.println("开始接收文件:"+FILE_NAME+"至:"+"D:/"+FILE_NAME);


                    while ((length = dis.read(inputByte, 0, inputByte.length)) > 0) {
                        fos.write(inputByte, 0, length);
                        fos.flush();
                    }
                    System.out.println("完成接收");
                }

            } finally {
                if (fos != null)
                    fos.close();
                if (dis != null)
                    dis.close();
                if (socket != null)
                    socket.close();
            }
        } catch (Exception e) {

        }

    }
}



class Accept implements Runnable{
    //接收字符串
    ServerSocket serverSocket=null;
    public Accept(ServerSocket serverSocket_root){
        serverSocket=serverSocket_root;
    }
    @Override
    public void run() {
        // TODO Auto-generated method stub
        Socket socket=null;
        try {
                System.out.println("字符串等待传输");
                while(true)
                {
                    socket=serverSocket.accept();
                    //System.out.println("socket="+socket.toString());
                    DataInputStream inputStream=new DataInputStream(socket.getInputStream());
                    String get=inputStream.readUTF();
                    System.out.println("传输结果："+get);
                    inputStream.close();
                }

        }catch (IOException e) {
            // TODO: handle exception
            System.out.println("fatal reason= "+e.getMessage());
        }finally {
            if(socket!=null) {
                try {
                    socket.close();
                } catch (IOException e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
                }
            }
        }
    }
}

class Accept_and_send implements Runnable{
    //接收字符串
    ServerSocket serverSocket=null;
    public Accept_and_send(ServerSocket serverSocket_root){
        serverSocket=serverSocket_root;
    }
    @Override
    public void run() {
        // TODO Auto-generated method stub
        Socket socket=null;
        try {
            System.out.println("字符串等待传输");
            while(true)
            {
                socket=serverSocket.accept();
                //System.out.println("socket="+socket.toString());
                DataInputStream inputStream=new DataInputStream(socket.getInputStream());
                String get=inputStream.readUTF();
                System.out.println("传输结果："+get);
                DataOutputStream outputStream =new DataOutputStream(socket.getOutputStream());
                outputStream.writeUTF("传回数据");
                outputStream.close();
                inputStream.close();
            }

        }catch (IOException e) {
            // TODO: handle exception
            System.out.println("fatal reason= "+e.getMessage());
        }finally {
            if(socket!=null) {
                try {
                    socket.close();
                } catch (IOException e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
                }
            }
        }
    }
}
//class Accept_flag implements Runnable{
//    //接收flag并判断
//    //第一位为固定的“begin”
//    //第二位为文件类型，分为“file”和“string”
//    //第三位为文件后缀名
//    private String FLAG = null;
//    private String FILE_TYPE = null;
//    private Socket socket=null;
//    private boolean ISNEXT = false;
//    private ServerSocket serverSocket=null;
//    Accept_flag(ServerSocket serverSocket_root){
//        serverSocket=serverSocket_root;
//    }
//
//    @Override
//    public void run() {
//        // TODO Auto-generated method stub
//            String begin_flag = getstr();
//            System.out.println(begin_flag);
//            FLAG = getstr();
//            System.out.println(FLAG);
//            FILE_TYPE = getstr();
//            ISNEXT = true;
//            System.out.println("校验完毕，开始传输");
//
//
//        Accept_flag accept_flag;
//        Accept accept_string;
//        Accept_img accept_file;
//        Thread thread;
//        Thread thread2;
//        Thread thread3;
//        System.out.println(getFLAG());
//
//        if (getISNEXT() == true)
//        {
//            System.out.println("文件种类"+getFLAG());
//            if(getFLAG().equals("string"))
//            {
//                accept_string = new Accept(serverSocket);
//                thread2 = new Thread(accept_string);
//                thread2.start();
//            }
//            else if(getFLAG().equals("file"))
//            {
//                accept_file = new Accept_img(serverSocket,getFILE_TYPE());
//                thread3 = new Thread(accept_file);
//                thread3.start();
//            }
//        }
//            destroy();
//    }
//
//    public String getFLAG()
//    {
//        return FLAG;
//    }
//
//    public String getFILE_TYPE()
//    {
//        return FILE_TYPE;
//    }
//
//    public boolean getISNEXT()
//    {
//        return ISNEXT;
//    }
//
//    public void setISNEXT_false()
//    {
//        ISNEXT = false;
//    }
//
//    private String getstr()
//    {
//        String get = null;
//        try {
//                socket=serverSocket.accept();
//                DataInputStream inputStream=new DataInputStream(socket.getInputStream());
//                get=inputStream.readUTF();
//                inputStream.close();
//        }catch (IOException e) {
//            // TODO: handle exception
//            System.out.println("fatal reason= "+e.getMessage());
//        }
//        return get;
//    }
//
//    private void destroy()
//    {
//        if(socket!=null) {
//            try {
//                socket.close();
//            } catch (IOException e) {
//                // TODO Auto-generated catch block
//                e.printStackTrace();
//            }
//        }
//    }
//}
