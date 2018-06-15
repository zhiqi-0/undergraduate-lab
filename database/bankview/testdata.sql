insert into 支行
values('浙江支行1', '浙江');
insert into 支行
values('浙江支行2', '浙江');
insert into 支行
values('江西支行1', '江西');
insert into 支行
values('江西支行2', '江西');

insert into 部门
values('宣传部', '宣传', '1234', '1234', '浙江支行1');
insert into 部门
values('科技部', '科技', '2345', '2345', '浙江支行1');
insert into 部门
values('财务部', '财务', '3456', '3456', '江西支行1');
insert into 部门
values('科技部', '科技', '4567', '4567', '江西支行2');
insert into 部门
values('宣传部', '宣传', '5678', '5678', '浙江支行2');
insert into 部门
values('财务部', '科技', '6789', '6789', '浙江支行2');

insert into 员工
values ('1234', '1234', 'zhiqilin', 'USTC', '1875607', STR_TO_DATE('05/19/2018','%m/%d/%Y'));
insert into 员工
values ('2345', '1234', 'zzll', 'USTC', '1881111', STR_TO_DATE('05/19/2018','%m/%d/%Y'));
insert into 员工
values ('3456', '2345', 'a1', 'USTC', '1881112', STR_TO_DATE('05/19/2018','%m/%d/%Y'));
insert into 员工
values ('4567', '2345', 'a2', 'USTC', '1881113', STR_TO_DATE('05/19/2018','%m/%d/%Y'));
insert into 员工
values ('5678', '4567', 'a3', 'USTC', '1881114', STR_TO_DATE('05/19/2018','%m/%d/%Y'));
insert into 员工
values ('6789', '3456', 'a4', 'USTC', '1881115', STR_TO_DATE('05/19/2018','%m/%d/%Y'));
insert into 员工
values ('7890', '5678', 'a4', 'USTC', '1881116', STR_TO_DATE('05/19/2018','%m/%d/%Y'));

insert into 客户
values('1234', '2345', 'zhiqilin', 'USTC', '1875607', 'zzll', '1881111', 'zzll@163.com', 'Frends');
insert into 客户
values('2345', '1234', 'zzll', 'USTC', '1871111', 'zhiqilin', '1875607', 'lzq@163.com', 'Frends');
insert into 客户
values('5678', '1234', 'a3', 'USTC', '1871111', 'zhiqilin', '1875607', 'lzq@163.com', 'Frends');
insert into 客户
values('6789', '3456', 'a4', 'USTC', '1871111', 'a3', '1875607', 'a3@163.com', 'Frends');

insert into 账户
values('123456', '200000',  STR_TO_DATE('04/19/2018','%m/%d/%Y'), STR_TO_DATE('05/19/2018','%m/%d/%Y'));
insert into 账户
values('234567', '300000',  STR_TO_DATE('04/19/2018','%m/%d/%Y'), STR_TO_DATE('05/19/2018','%m/%d/%Y'));
insert into 账户
values('345678', '250000',  STR_TO_DATE('04/19/2018','%m/%d/%Y'), STR_TO_DATE('05/19/2018','%m/%d/%Y'));
insert into 账户
values('456789', '150000',  STR_TO_DATE('04/19/2018','%m/%d/%Y'), STR_TO_DATE('05/19/2018','%m/%d/%Y'));
insert into 账户
values('567890', '350000',  STR_TO_DATE('04/19/2018','%m/%d/%Y'), STR_TO_DATE('05/19/2018','%m/%d/%Y'));

insert into 储蓄账户
values('123456', '200000', STR_TO_DATE('04/19/2018','%m/%d/%Y'), STR_TO_DATE('05/19/2018','%m/%d/%Y'), '0.03', 'RMB');
insert into 储蓄账户
values('345678', '250000', STR_TO_DATE('04/19/2018','%m/%d/%Y'), STR_TO_DATE('05/19/2018','%m/%d/%Y'), '0.04', 'Dollar');
insert into 储蓄账户
values('456789', '150000', STR_TO_DATE('04/19/2018','%m/%d/%Y'), STR_TO_DATE('05/19/2018','%m/%d/%Y'), '0.05', 'RMB');
insert into 支票账户
values('234567', '300000', STR_TO_DATE('03/19/2018','%m/%d/%Y'), STR_TO_DATE('05/19/2018','%m/%d/%Y'),'30000');
insert into 支票账户
values('567890', '350000', STR_TO_DATE('02/19/2018','%m/%d/%Y'), STR_TO_DATE('05/19/2018','%m/%d/%Y'), '10000');

insert into 开户
values('1234', '123456', '浙江支行1', 'Saving');
insert into 开户
values('2345', '345678', '浙江支行1', 'Saving');
insert into 开户
values('5678', '456789', '江西支行1', 'Saving');
insert into 开户
values('1234', '234567', '浙江支行2', 'Credit');
insert into 开户
values('6789', '567890', '江西支行2', 'Credit');

insert into 贷款
values('1234', '浙江支行1', 300000, 6);
insert into 贷款
values('2345', '浙江支行2', 400000, 8);
insert into 贷款
values('5678', '江西支行1', 900000, 10);
insert into 贷款
values('6789', '江西支行2', 400000, 2);

insert into 支付
values(1, '6789', '1234', 200000);
insert into 支付
values(2, '6789', '1234', 200000);
insert into 支付
values(1, '1234', '2345', 80000);
insert into 支付
values(1, '2345', '5678', 20000);
insert into 支付
values(2, '2345', '5678', 100000);