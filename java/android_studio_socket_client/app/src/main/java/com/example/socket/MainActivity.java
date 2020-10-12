package com.example.socket;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.provider.ContactsContract;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.net.Socket;

public class MainActivity extends AppCompatActivity {

    private Button button1;
    private Button button2;
    private EditText editip;
    private EditText editport;
    private EditText editport_file;
    private EditText file_name;
    String ipadress = null;
    int port = 0;
    int port_file = 0;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        //找到对应的控件
        editip = findViewById(R.id.ip);
        editport = findViewById(R.id.port);
        editport_file = findViewById(R.id.port_file);
        file_name = findViewById(R.id.img_name);



        button1 = (Button) findViewById(R.id.button);
        button1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                //当按下传送字符串时
                if (editport.getText().toString().equals("") || editip.getText().toString().equals(""))
                {
                    //判断端口号和IP地址是否为空
                    //Toast.makeText("你的端口号或IP地址填写错误");
                }
                else
                {
                    ipadress = editip.getText().toString();
                    port =Integer.parseInt(editport.getText().toString());
                    Log.d("上面的输入栏的端口:",String.valueOf(port));
                    Log.d("ip地址:",ipadress);
                }
                EditText edittext = findViewById(R.id.text);
                String text = edittext.getText().toString();
                Thread thread2 = new Thread(new SendStr(ipadress, port, text));
                thread2.start();
            }
        });

        button2 = (Button) findViewById(R.id.button2);
        button2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                if (editport_file.getText().toString().equals("") || editip.getText().toString().equals(""))
                {
                    return;
                }
                else
                {
                    ipadress = editip.getText().toString();
                    port_file =Integer.parseInt(editport_file.getText().toString());
                    Log.d("下面的输入栏的端口（传文件的端口），传文件名的端口为这个端口减一:",String.valueOf(port_file));
                    Log.d("ip地址:",ipadress);
                }
                //Thread thread2 = new Thread(new SendStr(ipadress, port_file-1, file_name.getText().toString()));
                //thread2.start();
                Thread thread3 = new Thread(new SendImg((EditText) findViewById(R.id.img_name)));
                thread3.start();
            }
        });
    }

    public class SendImg implements Runnable{
        private EditText ImgName;
        SendImg(EditText in)
        {
            ImgName = in;
        }
     @Override
     public void run() {
         int length = 0;
         byte[] sendBytes = null;
         Socket socket = null;
         DataOutputStream dos = null;
         FileInputStream fis = null;
         String imgname;
         if (ImgName.getText().toString().equals(""))
         {
             return;
         }
         else
         {
             imgname = ImgName.getText().toString();
         }

         try {
             try {
                 socket = new Socket();
                 socket.connect(new InetSocketAddress(ipadress, port_file),
                         10 * 1000);
                 dos = new DataOutputStream(socket.getOutputStream());
                 Log.d("外置目录",String.valueOf(getExternalCacheDir()));
                 File file = new File(getExternalCacheDir()+"/"+imgname);
                 fis = new FileInputStream(file);
                 sendBytes = new byte[1024];
                 while ((length = fis.read(sendBytes, 0, sendBytes.length)) > 0) {
                     dos.write(sendBytes, 0, length);
                     dos.flush();
                 }
             } finally {
                 if (dos != null)
                     dos.close();
                 if (fis != null)
                     fis.close();
                 if (socket != null)
                     socket.close();
             }
         } catch (Exception e) {
             e.printStackTrace();
         }
     }
    }


    public class SendImg_with_C implements Runnable{
        private EditText ImgName;
        SendImg_with_C(EditText in)
        {
            ImgName = in;
        }
        @Override
        public void run() {
            int length = 0;
            byte[] sendBytes = null;
            Socket socket = null;
            DataOutputStream dos = null;
            FileInputStream fis = null;
            String imgname;
            if (ImgName.getText().toString().equals(""))
            {
                return;
            }
            else
            {
                imgname = ImgName.getText().toString();
            }

            try {
                try {
                    socket = new Socket();
                    socket.connect(new InetSocketAddress(ipadress, port_file),
                            10 * 1000);
                    dos = new DataOutputStream(socket.getOutputStream());
                    Log.d("外置目录",String.valueOf(getExternalCacheDir()));
                    File file = new File(getExternalCacheDir()+"/"+imgname);
                    fis = new FileInputStream(file);
                    sendBytes = new byte[1024];
                    while ((length = fis.read(sendBytes, 0, sendBytes.length)) > 0) {
                        dos.write(sendBytes, 0, length);
                        dos.flush();
                    }
                } finally {
                    if (dos != null)
                        dos.close();
                    if (fis != null)
                        fis.close();
                    if (socket != null)
                        socket.close();
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }


    class SendStr implements Runnable {

        private String ipadress=null;
        private int port = 0;
        private String text = null;
        SendStr(String ip,int port_,String text_)
        {
            text = text_;
            ipadress = ip;
            port=port_;
        }
        @Override
        public void run() {
            Socket socket = null;
            Socket socket2 = null;

            if (text.equals("") || text == null) {
                return;
            } else {
                try {
                    Log.d("传送字符串的SendSte函数接收到的ip地址", ipadress);
                    Log.d("传送字符串的SendSte函数接收到的端口", String.valueOf(port));
                    socket = new Socket(ipadress, port);
                    DataOutputStream out = new DataOutputStream(socket.getOutputStream());
                    Log.d("SendStr函数里一个莫名其妙的输出", "out=" + out.toString() + " socket=" + socket.toString());
                    byte[] temp = text.getBytes();
                    out.write(temp);
                    out.flush();
                    //out.close();
                    Log.d("第一处标记", "-");
                    out.write(temp);
                    Log.d("第2处标记", "-");
                    out.flush();
                    out.close();

                    socket2 = new Socket(ipadress, port);
                    DataOutputStream out2 = new DataOutputStream(socket2.getOutputStream());
                    byte[] temp2 = text.getBytes();
                    out2.write(temp2);
                    //out.flush();
                    //out.close();
                    out2.flush();
                    out2.close();
                } catch (IOException e) {
                    Log.d("出现错误", "位于sendstr的try中：" + e.getMessage());
                } finally {
                    if (null != socket) {
                        try {
                            socket.close();
                            socket2.close();
                        } catch (IOException e) {
                            e.printStackTrace();
                        }
                    }
                }
            }
        }
    }

    class SendAndGetStr implements Runnable {

        private String ipadress=null;
        private int port = 0;
        private String text = null;
        SendAndGetStr(String ip,int port_,String text_)
        {
            text = text_;
            ipadress = ip;
            port=port_;
        }
        @Override
        public void run() {
            Socket socket = null;

            if (text.equals("") || text == null) {
                return;
            } else {
                try {
                    Log.d("传送字符串的SendSte函数接收到的ip地址", ipadress);
                    Log.d("传送字符串的SendSte函数接收到的端口", String.valueOf(port));
                    socket = new Socket(ipadress, port);
                    DataOutputStream out = new DataOutputStream(socket.getOutputStream());
                    Log.d("SendStr函数里一个莫名其妙的输出", "out=" + out.toString() + " socket=" + socket.toString());

                    //writeUTF在传输时会出现问题（c语言中没有找到合适的读取函数。）
                    byte[] temp = text.getBytes();
                    out.write(temp);

                    //out.writeUTF(text);
                    //socket.shutdownOutput();

                    Log.d("进度", "1");
                    DataInputStream inputStream = new DataInputStream(socket.getInputStream());
                    Log.d("进度", "2");
                    String input = inputStream.readUTF();
                    Log.d("进度", "3");
                    TextView textView = findViewById(R.id.strshow);
                    Log.d("进度", "4");
                    textView.setText(input);
                    Log.d("进度", "5");
                    out.flush();
                    out.close();
                } catch (IOException e) {
                    Log.d("发生错误", "无法获取IP:" + e.getMessage());
                } finally {
                    if (null != socket) {
                        try {
                            socket.close();
                        } catch (IOException e) {
                            e.printStackTrace();
                        }
                    }
                }
            }
        }
    }
//    class SendFlag implements Runnable {
//        //传送标志位，第一位为固定的“begin”
//        //第二位为文件类型，分为“file”和“string”
//        //第三位为文件后缀名
//        public String FLAG;
//        public String FILE_TYPE = "";
//        String FILE = "file";
//        String STR = "string";
//
//        public  SendFlag(String modeflag, String file_type)
//        {
//            FLAG = modeflag;
//            FILE_TYPE = file_type;
//        }
//
//        @Override
//        public void run() {
//            if(FLAG.equals(FILE) || FLAG.equals(STR))
//            {
//                sendflag("begin");
//                sendflag(FLAG);
//                sendflag(FILE_TYPE);
//            }
//        }
//
//
//        private void sendflag(String str)
//        {
//            Socket socket = null;
//
//            try {
//                Log.d("Tankai", "Thread=" + Thread.currentThread().getName());
//                socket = new Socket(ipadress, port);
//                DataOutputStream out = new DataOutputStream(socket.getOutputStream());
//                Log.d("Tankai", "out=" + out.toString() + " socket=" + socket.toString());
//                out.writeUTF(str);
//                out.flush();
//                out.close();
//
//            } catch (IOException e) {
//                Log.d("Tankai", "无法获取IP:" + e.getMessage());
//            } finally {
//                if (null != socket) {
//                    try {
//                        socket.close();
//                    } catch (IOException e) {
//                        e.printStackTrace();
//                    }
//                }
//            }
//        }
//    }
}