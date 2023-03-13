

TinyWebServer
===============
A simple C++ Http server project.
Using state machine to parse Http quest message, support GET and POST request.
Using database to implement user log in, sign in and questing file and image function.
Building a thread pool and epoll based event process concurrency model.
Sync and Async log system.

------------
* Server test environment
	* Ubuntu 16.04
	* MySQL 5.7.29
* Web browser
	* Windows、Linux
	* Chrome
	* FireFox

* Install MySQL before testing

    ```C++
    // build yourdb library
    create database yourdb;

    // create user table
    USE yourdb;
    CREATE TABLE user(
        username char(50) NULL,
        passwd char(50) NULL
    )ENGINE=InnoDB;

    // add data
    INSERT INTO user(username, passwd) VALUES('name', 'passwd');
    ```

* Modify database initial message in main.cpp

    ```C++
    //database login name, password, databasename
    string user = "root";
    string passwd = "root";
    string databasename = "yourdb";
    ```

* Build

    ```C++
    sh ./build.sh
    ```

* Launch server

    ```C++
    ./server
    ```

* Web browser side

    ```C++
    ip:9190
    ```



