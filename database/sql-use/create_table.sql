# create table Book, Read, Borrow

# create Book table
create table book(
id				char(8),
name 			varchar(10),
author    varchar(10),
price			float,
status		int,
constraint primary key (id)
);

create table reader(
id 				char(8),
name 			varchar(10),
age 			int,
address		varchar(20),
constraint primary key (id)
);

create table borrow(
book_id					char(8),
reader_id				char(8),
borrow_date			date,
return_date			date,
constraint primary key (book_id, reader_id),
constraint bookkey foreign key (book_id) references book(id),
constraint readerkey foreign key (reader_id) references reader(id)
);