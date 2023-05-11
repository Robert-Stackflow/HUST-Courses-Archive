# Socket Server

您好，这里是Socket Server，一个使用Winsock实现的TCP服务端

## 功能介绍

- 您可以向这里发送文件请求，当这个文件可以在服务端上找到时，服务端将会把文件传输给您
- 当这个文件在服务端上找不到时，服务端将会返回给你404页面
- 当您输入的路径不合法时，服务端将会返回给你400页面
- 如果这个文件是简单的文本类型，浏览器将可以显示这个文件的内容
- 如果这个文件是图片类型，客户端也将会将它显示出来，除非文件传输错误
- 如果这个文件是文档类型，如Word、Excel、PowerPoint，您可以在下载目录里找到下载的文件并打开查看
- 您也可以尝试请求下面的文件列表中的其他文件

## 服务端文件列表

- 首页
  - [index.html](/index.html)、[favicon.ico](/favicon.ico)
- 文本文件(目录为text)
  - [Introduction.md](/text/Introduction.md)、[Helloworld.c](/text/Helloworld.c)、[Helloworld.cpp](/text/Helloworld.cpp)、[plants.xml](/text/plants.xml)
- 图片文件(目录为image)
  - [HUST.png](/image/HUST.png)、[CS.jpg](/image/CS.jpg)
- 文档文件(目录为document)
  - [Introduction.docx](/document/Introduction.docx)、[Introduction.pdf](/document/Introduction.pdf)、[hotkey.xlsx](/document/hotkey.xlsx)
- 媒体文件(目录为media)
  - [Lovers'Oath.mp3](/media/Lovers'Oath.mp3)