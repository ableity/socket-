import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JPasswordField;
import javax.swing.JTextField;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.*;
import java.net.*;

public class SwingUI {

    private static JLabel strText;
    private static JLabel fileText;
    private static JTextField dirText;


    private static ServerSocket serverSocket;
    private static ServerSocket serverSocket2;
    private static ServerSocket serverSocket3;
    public String FLAG;
    String IMG = "image";
    String STR = "string";
    private static String filePath;

    public static void main(String[] args) throws IOException {
        setUi();

        serverSocket=new ServerSocket(18893);
        serverSocket2=new ServerSocket(18895);
        serverSocket3=new ServerSocket(18892);
        Accept_img accept;
        Thread thread;
        accept=new Accept_img(serverSocket,serverSocket3,dirText,fileText);
        thread=new Thread(accept);
        thread.start();

        Accept_and_send accept_str;
        Thread thread_str;
        accept_str= new Accept_and_send(serverSocket2,strText);
        thread_str=new Thread(accept_str);
        thread_str.start();
    }

    private static void setUi()
    {
        // 创建 JFrame 实例
        JFrame frame = new JFrame("文件传输");
        // Setting the width and height of frame
        frame.setSize(330, 180);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        /* 创建面板，这个类似于 HTML 的 div 标签
         * 我们可以创建多个面板并在 JFrame 中指定位置
         * 面板中我们可以添加文本字段，按钮及其他组件。
         */
        JPanel panel = new JPanel();
        // 添加面板
        frame.add(panel);
        /*
         * 调用用户定义的方法并添加组件到面板
         */
        placeComponents(panel);
        // 设置界面可见
        frame.setVisible(true);
    }

    private static void placeComponents(JPanel panel) {

        /* 布局部分我们这边不多做介绍
         * 这边设置布局为 null
         */
        panel.setLayout(null);

        // 创建 JLabel

        /* 这个方法定义了组件的位置。
         * setBounds(x, y, width, height)
         * x 和 y 指定左上角的新位置，由 width 和 height 指定新的大小。
         */

        JLabel userLabel = new JLabel("接收的字符串:");
        userLabel.setBounds(10,20,80,25);
        panel.add(userLabel);

        strText = new JLabel("");
        strText.setBounds(100,20,165,25);
        panel.add(strText);



        JLabel fileLabel = new JLabel("接收文件:");
        fileLabel.setBounds(10,50,80,25);
        panel.add(fileLabel);

        fileText = new JLabel("");
        fileText.setBounds(100,50,165,25);
        panel.add(fileText);



        JLabel dirLabel = new JLabel("设置目录:");
        dirLabel.setBounds(10,80,80,25);
        panel.add(dirLabel);

        dirText = new JTextField(20);
        dirText.setText("D:\\data");
        dirText.setBounds(100,80,165,25);
        panel.add(dirText);



        // 创建登录按钮
//        loginButton = new JButton("目录确认");
//        loginButton.setBounds(200, 160, 100, 25);
//        panel.add(loginButton);

//        JLabel portLabel = new JLabel("port(file):18893");
//        portLabel.setBounds(10,110,80,25);
//        portLabel.setFont(new Font("Times new Roman",Font.BOLD, 10));
//        panel.add(portLabel);
//        JLabel portLabel2 = new JLabel("port(name):18892");
//        portLabel2.setBounds(10,135,80,25);
//        portLabel2.setFont(new Font("Times new Roman",Font.BOLD, 10));
//        panel.add(portLabel2);
//        JLabel portLabel3 = new JLabel("port(str):18895");
//        portLabel3.setBounds(10,160,80,25);
//        portLabel3.setFont(new Font("Times new Roman",Font.BOLD, 10));
//        panel.add(portLabel3);

    }


}


class Accept_img implements Runnable{
    //接收文件，原版没修改
    ServerSocket serverSocket=null;
    ServerSocket serverSocket_name = null;
    private String FILE_NAME = null;
    JTextField dirText;
    JLabel LED;


    public Accept_img(ServerSocket serverSocket_root,ServerSocket serverSocket_name_,JTextField dirtext, JLabel Led)
    {
        serverSocket  = serverSocket_root;
        serverSocket_name = serverSocket_name_;
        dirText = dirtext;
        LED = Led;
    }

    private String getpath()
    {
        String file_path = dirText.getText();
        String temp = file_path.substring(file_path.length()-1);
        if(temp.equals("/"))
        {
        }
        else
        {
            file_path = file_path+"\\";
        }
        return file_path;
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
        DataInputStream inputStream;


        byte[] inputByte = null;
        int length = 0;
        DataInputStream dis = null;
        FileOutputStream fos = null;
        Socket socket=null;

        try {
            try {
                while(true)
                {
                    socket_name=serverSocket_name.accept();
                    //System.out.println("socket="+socket.toString());
                    inputStream=new DataInputStream(socket_name.getInputStream());
                    FILE_NAME=inputStream.readUTF();

                    socket=serverSocket.accept();
                    String dir = getpath();
                    dis = new DataInputStream(socket.getInputStream());
                    fos = new FileOutputStream(new File(dir+FILE_NAME));
                    inputByte = new byte[1024];
                    System.out.println("开始接收文件:"+FILE_NAME+"至:"+dir+FILE_NAME);
                    LED.setText(FILE_NAME+"正在传输");
                    System.out.println(dir);


                    while ((length = dis.read(inputByte, 0, inputByte.length)) > 0) {
                        fos.write(inputByte, 0, length);
                        fos.flush();
                    }
                    System.out.println("完成接收");
                    LED.setText(FILE_NAME+"完成传输");
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
    JLabel strLabel;
    public Accept_and_send(ServerSocket serverSocket_root,JLabel strlabel){
        serverSocket=serverSocket_root;
        strLabel = strlabel;
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
                strLabel.setText(get);
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