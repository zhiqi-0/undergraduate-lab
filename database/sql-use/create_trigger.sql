-- create trigger that when a book is borrowed,
-- book status will automatically change to 1;
-- when a book is returned,
-- book status will automatically change to 0.
drop trigger if exists borrowAndReturn;
delimiter $$

-- 0->1 trigger
create trigger onBorrow after insert 
on borrow for each row
begin
	update book
	set book.status = 1
	where book.id = new.book_id;
end$$

-- 1->0 trigger
create trigger onReturn after update
on borrow for each row
begin
	update book
	set book.status = 0
	where book.id = new.book_id and new.return_date is not NULL;
end$$

delimiter ;