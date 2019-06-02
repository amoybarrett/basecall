
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



public class imageRequestor
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
			 System.out.println("Usage:\n\t--java imageRequestor [server_ip:localhost] [server_port:2001] [local_port:2002] [path_file]\n");
			 return ;
		 }
         try {
            InetAddress acceptorHost=InetAddress.getByName(args[0]);
            int acceptorPort=Integer.parseInt(args[1]);
            int myPort=Integer.parseInt(args[2]);
            String filename=args[3];
            System.out.println("Send File:" + filename);
            MyDatagramSocket ms=new MyDatagramSocket(myPort);
            ms.sendMessage(acceptorHost,acceptorPort, filename);
            String result = ms.receiveMessage();
            ms.close();
///////////////////////////////////////////////////////////////////////
           ServerSocket connectionSocket=new ServerSocket(myPort);
           Socket dataSocket=connectionSocket.accept();
           OutputStream outStream=dataSocket.getOutputStream();
           File imageFile = new File(filename);
           FileInputStream in=new FileInputStream(imageFile);
           byte[] data = readInputStream(in);
           outStream.write(data);
           outStream.flush();
           dataSocket.close();
           connectionSocket.close();
           System.out.println(result);
			} //end
			catch (Exception ex) {
				ex.printStackTrace();
	        } //end catch
	} //end main
}  //end class
