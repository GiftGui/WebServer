

TinyWebServer
===============
应用技术：Linux、C++、线程池、epoll。                
基于Linux的轻量级多线程Web服务器，应用层实现了一个简单的HTTP服务器，支持静态资源访问与动态消息回显。
1、使用状态机解析Http请求报文，支持解析GET和POST请求；
2、访问数据库实现用户注册、登录功能，请求图片和视频文件；
3、使用线程池+epoll+事件处理的并发模型；
4、实现同步/异步日志系统。

此项目来自于《Linux高性能服务器编程》游双著 书中知识的理解，
和对开源项目 https://github.com/qinguoyi/TinyWebServer 的学习。

快速运行
------------
* 服务器测试环境
	* Ubuntu版本16.04
	* MySQL版本5.7.29
* 浏览器测试环境
	* Windows、Linux均可
	* Chrome
	* FireFox
	* 其他浏览器暂无测试

* 测试前确认已安装MySQL数据库

    ```C++
    // 建立yourdb库
    create database yourdb;

    // 创建user表
    USE yourdb;
    CREATE TABLE user(
        username char(50) NULL,
        passwd char(50) NULL
    )ENGINE=InnoDB;

    // 添加数据
    INSERT INTO user(username, passwd) VALUES('name', 'passwd');
    ```

* 修改main.cpp中的数据库初始化信息

    ```C++
    //数据库登录名,密码,库名
    string user = "root";
    string passwd = "root";
    string databasename = "yourdb";
    ```

* build

    ```C++
    sh ./build.sh
    ```

* 启动server

    ```C++
    ./server
    ```

* 浏览器端

    ```C++
    ip:9190
    ```



