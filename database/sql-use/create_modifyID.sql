drop procedure if exists modifyBookID;

delimiter $$
create procedure modifyBookID(in oldID char(8), in newID char(8))
begin
	-- remove borrow foreign key constraint
	alter table borrow drop foreign key bookkey;
	-- update book.id
	update book
	set id = newID
	where id = oldID;
	-- update borrow.book_id
	update borrow
	set book_id = newID
	where book_id = oldID;
	-- recover constraints
	alter table borrow add constraint bookkey foreign key (book_id) references book(id);
end$$
delimiter ;