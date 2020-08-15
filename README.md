云游戏平台项目

    第18届China joy在上海国博中心举行，除了Coser和showgirl外，最大的亮点就是云游戏展台。云游戏从14年的onlive拉开帷幕到19年谷歌的stadia平台发布，标志着进入到百家争鸣。
    目前国内发行较早的有上海的达龙云电脑，腾讯旗下也有好几款云游戏平台。

1.目录结构：

bin---可以运行的文件
captureServer-----远程云游戏服务器
client----android平台，windows平台，ios平台的客户端代码

2.技术介绍：

   a.虚拟化技术（我提供一种方案）
   
     1.采用citrix的技术方案,主要是vgpu能独立支持
     2.xenserver 做云主机的虚拟化
     3.采用maxwell架构，或者pascal架构的nvidia显卡来实现vgpu
     4.采用xencenter来管理vps
  如果说就是一台主机对一个用户的话，就不需要使用虚拟化技术。

 b.远程云主机端

  1.流媒体服务器，提供点播功能，rtsp协议
  2.流的源---桌面或者游戏主界面
  3.抓屏技术（nvidia capture sdk 、DXGI），采用后者，前者需要付费。
  4.视频编码技术 h264,h265  nvidia的 mediasdk
  5.音频获取(mmdeviceapi)
  6.音频编码
  7.封装rtsp协议
  8.push到网络
  9.提供操控信令接收服务
  10.hook技术，模拟外设指令操作游戏

c.用户端
 
  1.流媒体流的接收
  2.组包
  3.解封装
  4.解码
  5.渲染视频
  6.渲染音频
  7.捕获用户IO操作指令传输到云平台

3.相关模块及用到的开源代码：
 a.远程桌面端：
	 
	 1.rtsp流媒体服务器：MediaServerLib  参考：https://github.com/PHZ76/RtspServer

	2.desktop Capture 桌面抓屏：WinCaptureAndencodeLib 参考：https://github.com/diederickh/screen_capture

	3.video encode 视频编码：NEncoderLib  参考：NVIDIA官方demo Video_Codec_SDK_8.2.15 https://developer.download.nvidia.com/designworks/video-codec-sdk/secure/8.2/Video_Codec_SDK_8.2.15.zip?30lk3BXfcLRLrr8rEzpJaICqxnI2-lm9MCVk2MgnNjb1cMjkso-WJ7c83Jp0z8CoIukaGHcuC_RHCHamT42dFy0wWk3SskYG8WqIegT8Y5FuI9kjgetC9JBDBqV-gZrzV4woGfamR3z9MPQjeP2Fva3vPHWqhaY1EOebN3-SS7o

	4.日志：Log4cplus

	5.base64编码：Base64Codec

	6.音频采集和编码：mmdeviceapi 获取pcm ,  faac：pcm2aac(外加降采样)

	7.udp信令服务器：主要用来接收鼠标键盘的命令

	8.hook钩子：模拟鼠标键盘的操作

	9.主进程：CaptureStreamServer

	10.守护进程：CaptureServerManger
b.用户端：
	
	1.收流  live555模块改进

	2.解码  ffmpeg库

4.编译相关
	
	1.远程服务:  编译 vs2015 
	2.window客户端: vs2015
	3.android: android studio
	4.ios/mac: xcode

5.直接运行相关
	
	我们的远程桌面服务器需要Nvidia显卡的支持，无论是gtx系列的或者是tesla系列的，首先管理员权限cmd运行\bin\remote-server\NvFBCHWEnableAPI -enable 打开nvidia卡的加速功能。运行环境需要安装vc2015x86，虚拟机需要安装虚拟声卡VirtualAudioCable4.14.0.6871。
	其次远程桌面服务器需要关闭windows防火墙，允许客户端连接上来。如果是云服务器需要配置好策略，开放tcp和udp端口。
	1.远程服务器：\bin\remote-server\CaptureStreamServer.exe :远程桌面服务器支持win8.1以上系统或者同版本的windows server系统
	2.windows客户端：bin\windows-client\bin\RemoteDesktopClient.exe,输入远程桌面的IP,点连接。
	3.android客户端：输入远程桌面IP,点击左下角按钮开始远程控制。
	4.IOS和mac都是输入IP地址，点击连接。

6.我们的愿景
	
	互联网产品不断更新发展，我们一定需要去拥抱新的产品，思考它的价值，发现它的商业模式，动手打造自己的产品。同时也需要去思索和发掘市场和用户的需求，探索商业模式，动手实现商业项目。
	我们的名称是“IT奇兵”，我们在抖音、快手和B站里，会去详细讲解项目的历史背景，发展过程，技术框架，代码模块。
	我们一起来分享自己的劳动果实，一起创造新的奇迹。如果你也有相同的想法，请在各个平台关注“IT奇兵”，并私信我们，一群人才是一个团队，我们一起做有意义的事情。
	我们目前也发现了一些新的长尾市场的用户需求，商业模式也比较清晰，我们会逐步讲解和动手实践，欢迎你的参与！
	
7.开源协议

     无任何约束，想用就下载，但是对你的商业项目，本开源工程不会去承担任何法律责任，其中本工程用到的某些开源项目中的部分代码，请你仔细阅读它的相关开源协议。
     
     
Android代码、IOS和mac的代码正在整理中，后面会陆续上传，目前源码是服务端和windows client端。     
