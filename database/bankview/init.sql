/*==============================================================*/
/* DBMS name:      MySQL 5.0                                    */
/* Created on:     2018/5/16 10:16:04                           */
/*==============================================================*/

drop table if exists 储蓄账户;

drop table if exists 员工;

drop table if exists 客户;

drop table if exists 开户;

drop table if exists 支付;

drop table if exists 支票账户;

drop table if exists 支行;

drop table if exists 账户;

drop table if exists 贷款;

drop table if exists 部门;

/*==============================================================*/
/* Table: 支行                                                    */
/*==============================================================*/
create table 支行
(
   支行名                  varchar(20) not null,
   所在城市                 varchar(20),
   primary key (支行名)
);

/*==============================================================*/
/* Table: 部门                                                    */
/*==============================================================*/
create table 部门
(
   部门名                  varchar(30),
   部门类型                 varchar(30),
   部门经理身份证              varchar(30),
   部门号                  numeric(8,0) not null,
   支行名                  varchar(20),
   primary key (部门号)
);

/*==============================================================*/
/* Table: 员工                                                    */
/*==============================================================*/
create table 员工
(
   身份证                  varchar(30) not null,
   部门号                  numeric(8,0),
   姓名                   varchar(20),
   家庭地址                 varchar(30),
   电话号码                 numeric(8,0),
   开始工作日期              date,
   primary key (身份证)
);

/*==============================================================*/
/* Table: 客户                                                    */
/*==============================================================*/
create table 客户
(
    身份证             varchar(30) not null,
    员工_身份证		    varchar(30) not null,
    姓名               varchar(20),
    家庭地址            varchar(30),
    电话号码            numeric(8,0),
    联系人姓名          varchar(30),
    联系人手机          varchar(30),
    联系人邮箱          varchar(30),
    联系人关系          varchar(30),
    primary key (身份证)
);

/*==============================================================*/
/* Table: 账户                                                    */
/*==============================================================*/
create table 账户
(
   账户号                  numeric(20,0) not null,
   余额                   int,
   开户日期                date,
   最近访问日期             date,
   primary key (账户号)
);

/*==============================================================*/
/* Table: 开户                                                    */
/*==============================================================*/
create table 开户
(
   身份证                  varchar(30) not null,
   账户号                  numeric(20,0) not null,
   开户行                  varchar(30),
   账户类型                 varchar(30),
   primary key (身份证, 账户号),
   unique key AK_Key_2 (身份证, 开户行, 账户类型)
);

/*==============================================================*/
/* Table: 储蓄账户                                                  */
/*==============================================================*/
create table 储蓄账户
(
   账户号                  numeric(20,0) not null,
   余额                    int,
   开户日期                 date,
   最近访问日期              date,
   利率                   double,
   货币类型                 varchar(20),
   primary key (账户号)
);

/*==============================================================*/
/* Table: 支票账户                                                  */
/*==============================================================*/
create table 支票账户
(
   账户号                 numeric(20,0) not null,
   余额                   int,
   开户日期                date,
   最近访问日期             date,
   透支额                  double,
   primary key (账户号)
);

/*==============================================================*/
/* Table: 贷款                                                    */
/*==============================================================*/
create table 贷款
(
   贷款号                  numeric(8,0) not null,
   支行名                  varchar(20) not null,
   贷款金额                 double,
   总共支付次数               int,
   primary key (贷款号)
);

/*==============================================================*/
/* Table: 支付                                                    */
/*==============================================================*/
create table 支付
(
   支付序号                 decimal not null,
   贷款号                  numeric(8,0),
   身份证                  varchar(30),
   支付金额                 double,
   primary key (支付序号, 贷款号)
);


alter table 储蓄账户 add constraint FK_储蓄继承 foreign key (账户号)
      references 账户 (账户号) on delete restrict on update restrict;

alter table 员工 add constraint FK_雇佣 foreign key (部门号)
      references 部门 (部门号) on delete restrict on update restrict;

alter table 客户 add constraint FK_受理 foreign key (员工_身份证)
      references 员工 (身份证) on delete restrict on update restrict;

alter table 开户 add constraint FK_开户 foreign key (身份证)
      references 客户 (身份证) on delete restrict on update restrict;

alter table 开户 add constraint FK_开户2 foreign key (账户号)
      references 账户 (账户号) on delete restrict on update restrict;

alter table 支付 add constraint FK_支付情况 foreign key (贷款号)
      references 贷款 (贷款号) on delete restrict on update restrict;

alter table 支付 add constraint FK_贷款支付 foreign key (身份证)
      references 客户 (身份证) on delete restrict on update restrict;

alter table 支票账户 add constraint FK_支票继承 foreign key (账户号)
      references 账户 (账户号) on delete restrict on update restrict;

alter table 贷款 add constraint FK_贷款项目 foreign key (支行名)
      references 支行 (支行名) on delete restrict on update restrict;

alter table 部门 add constraint FK_拥有部门 foreign key (支行名)
      references 支行 (支行名) on delete restrict on update restrict;