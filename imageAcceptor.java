import java.io.*;
import java.net.*;

class MyDatagramSocket extends DatagramSocket
{
   static final int MAX_LEN=100;
   MyDatagramSocket(int portNo) throws SocketException
   {
      super(portNo);
   }

   public void sendMessage(InetAddress receiverHost,int receiverPort,String message) throws IOException
   {
      byte[] sendBuffer=message.getBytes();
      DatagramPacket datagram=new DatagramPacket(sendBuffer, sendBuffer.length, receiverHost, receiverPort);
      this.send(datagram);
   }
   public String receiveMessage() throws IOException
   {
      byte[] receiverBuffer=new byte[MAX_LEN];
      DatagramPacket datagram=new DatagramPacket(receiverBuffer, MAX_LEN);
      this.receive(datagram);
      String message =new String(receiverBuffer);
      return message;
   }  //end receiveMessage
} //end class


public class imageAcceptor
{

   public static byte[] readInputStream(InputStream inStream) throws Exception{
   ByteArrayOutputStream outStream = new ByteArrayOutputStream();
   byte[] buffer = new byte[1024];
   int len = 0;
   while( (len=inStream.read(buffer)) != -1 ){
   outStream.write(buffer, 0, len);
   }
   inStream.close();
   return outStream.toByteArray();
}


   public static void main(String[] args)
   {
	     if(args.length < 4){
			 System.out.println("Usage:\n\t--java imageAcceptor [server_ip:localhost] [server_port:2002] [local_port:2001] [path]\n");
			 return ;
		 }

while(true){
	   try{
            InetAddress receiverHost=InetAddress.getByName(args[0]);
            int receiverPort=Integer.parseInt(args[1]);
            int myPort=Integer.parseInt(args[2]);
            String filepath=args[3];
            String fg = "\\";
            MyDatagramSocket ms=new MyDatagramSocket(myPort);
            String filename = ms.receiveMessage();
            filename = filename.substring(filename.lastIndexOf(fg) + 1, filename.length());
            System.out.println("Receive File:" + filename);
            filename = filepath + fg + filename;
            String res = "Success!";
            ms.sendMessage(receiverHost,receiverPort, res);
            ms.close();
///////////////////////////////////////////////////////////////////
			Socket mySocket=new Socket(receiverHost, receiverPort);
			InputStream is=mySocket.getInputStream();
            byte[] data = readInputStream(is);
            File imageFile = new File(filename);
            FileOutputStream outStream = new FileOutputStream(imageFile);
            outStream.write(data);
            outStream.flush();
			outStream.close();
			mySocket.close();
         }catch (Exception ex) {
            ex.printStackTrace();
         } //end catch
}
   } //end main
}  //end class
