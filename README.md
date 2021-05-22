# WebServer
A simple webserver using the knowledge of 《高性能服务器编程》by 游双

-主线程使用epoll进行IO处理。
-子线程处理逻辑
-使用状态机进行HTTP报文的解析，解析GET和POST两种请求。
-访问服务器数据库实现注册登录功能，可以请求服务器的图片和视频。
-使用定时器定期清理超时的连接
-实现日志模块



