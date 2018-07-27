insert into book
values ('B#001', 'Oracle', 'Ullman', '10', '1');
insert into book
values ('B#002', 'SQL', 'zhiqilin', '100', '0');
insert into book
values ('B#003', 'GoOut', 'Ullman', '50', '0');
insert into book
values ('B#004', 'book4', 'author1', '11', '0');
insert into book
values ('B#005', 'book5', 'author2', '12', '1');
insert into book
values ('B#006', 'book6', 'author3', '13', '0');
insert into book
values ('B#007', 'book7', 'author4', '14', '1');
insert into book
values ('B#008', 'Oracle123', 'Ullman', '10', '0');
insert into book
values ('B#009', '123Oracle', 'Ullman', '0.2', '1');
insert into book
values ('B#010', '23Oracle32', 'Ullman', '10.3', '1');

insert into reader
values ('R#001', 'Rose', '18', 'address1');
insert into reader
values ('R#002', '李林', '18', 'address2');
insert into reader
values ('R#003', 'author3', '19', 'address1');
insert into reader
values ('R#004', 'author4', '19', 'address1');
insert into reader
values ('R#005', 'author5', '19', 'address1');		# not borrow books

insert into borrow
values ('B#001', 'R#001', str_to_date('12/08/2017', '%d/%m/%Y'), NULL);
insert into borrow
values ('B#002', 'R#002', str_to_date('11/08/2017', '%d/%m/%Y'), str_to_date('13/09/2017','%d/%m/%Y'));
insert into borrow
values ('B#003', 'R#001', str_to_date('11/08/2017', '%d/%m/%Y'), str_to_date('12/09/2017','%d/%m/%Y'));
insert into borrow
values ('B#004', 'R#003', str_to_date('11/08/2017', '%d/%m/%Y'), str_to_date('20/09/2017','%d/%m/%Y'));
insert into borrow
values ('B#005', 'R#002', str_to_date('11/08/2015', '%d/%m/%Y'), NULL);
insert into borrow
values ('B#005', 'R#003', str_to_date('11/08/2016', '%d/%m/%Y'), str_to_date('12/08/2017', '%d/%m/%Y'));
insert into borrow
values ('B#006', 'R#003', str_to_date('11/08/2014', '%d/%m/%Y'), str_to_date('19/09/2017','%d/%m/%Y'));
insert into borrow
values ('B#007', 'R#003', str_to_date('11/08/2017', '%d/%m/%Y'), NULL);
insert into borrow
values ('B#008', 'R#004', str_to_date('11/08/2017', '%d/%m/%Y'), str_to_date('18/09/2017','%d/%m/%Y'));
insert into borrow
values ('B#009', 'R#002', str_to_date('11/08/2012', '%d/%m/%Y'), NULL);
insert into borrow
values ('B#010', 'R#003', str_to_date('11/08/2017', '%d/%m/%Y'), NULL);