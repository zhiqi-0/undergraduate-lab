## Intro

### About

* This is a bank database client based on B/S framework

* Use NodeJs, Koa2.0 (MVC), Sequelize for development

* Use MySql for database

### How to Use

* First you should create mysql database use following command:
  
  ``` sql
  > create database bank;
  ```

* Execute init.sql to create tables

* Execute testdata.sql to import some basic test data

* Edit config.js to fit in your database account. Default is set by root and without any passwords

* Under this directory, run the command: (require internet)

  ``` js
  $ npm install
  ```

  This will fetch some node thidy-party packages in node_modules/

* Run the server:

  ```js
  $ npm start
  ```

  Then you will see the server running at 127.0.0.1:3000. You can visit it in your browser (Chrome is recommanded).

* Login account: zhiqilin

  Passwords: 123456

Enjoy this!