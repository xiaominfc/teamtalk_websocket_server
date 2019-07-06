# teamtalk_websocket_server

让teamtalk支持websocket 从而实现web端的即时通讯

## 准备
一个编译好的teamtalk的工程(https://github.com/mogujie/TeamTalk)
打开一个终端切换到teamtalk的工程下的src(那些server的源码目录)

修改base下的imconn.h 中的Send函数 在前面加个virtual 
``````
	virtual  int Send(void* data, int len);

``````
重新编译一次base

在src路径下执行

###### clone 代码

``````
git clone https://github.com/xiaominfc/teamtalk_websocket_server.git
``````

###### 编译websocket库
``````
cd teamtalk_websocket_server/websocket
cmake .
make
cd ..
``````

###### 编译websocket_server
``````
cmake .
make
``````

这样就编译出来了

添加log使用的几个分享库以及配置文件 
以websocketserver.conf.example 为模版修改出一份websocketserver.conf
websocket_server 就能运行了

websocket的实现引用了(http://katzarsky.github.com/WebSocket)
感谢katzarsky

测试用的demo可以参考:https://github.com/xiaominfc/teamtalk_websocket_client

在线演示可以参考:http://im.xiaominfc.com



## SSL的支持 

1. 需要用我fork出来维护的Teamtalk的项目(https://github.com/xiaominfc/TeamTalk)
2. 对比server/src/base目录代码的差异也可以 主要是给服务端添加了ssl的支持
3. 打开websocket_server.cpp中的宏#define NEEDSSL 
4. 配置.conf文件中关于SSL的几个参数 SSLListenIP SSLListenPort SSLCertFile SSLKeyFile
