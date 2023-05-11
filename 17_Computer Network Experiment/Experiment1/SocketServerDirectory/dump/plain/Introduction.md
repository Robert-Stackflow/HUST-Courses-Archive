# Socket Server Dump

您好，这里是Socket Server Dump，一个使用Winsock实现的TCP服务端

## 功能介绍

- 您可以向这里发送文件请求，当这个文件可以在服务端上找到时，服务端将会把文件传输给您
- 当这个文件在服务端上找不到时，服务端将会返回给你404页面
- 当您输入的路径不合法时，服务端将会返回给你400页面
- 如果这个文件是简单的文本类型，浏览器将可以显示这个文件的内容
- 如果这个文件是图片类型，客户端也将会将它显示出来，除非文件传输错误

## 服务端文件列表

- 首页
  - [index.html](/index.html)、[favicon.ico](/favicon.ico)
- 文本文件(目录为plain)
  - [Introduction.md](/plain/Introduction.md)、[Helloworld.java](/plain/Helloworld.java)、[movie.txt](/plain/movie.txt)
- 图片文件(目录为picture)
  - [network.png](/picture/network.png)
- 二进制文件(目录为binary)
  - [SocketServer.exe](/binary/SocketServer.exe)