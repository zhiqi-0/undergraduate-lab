
select reader.name as name, reader.id
from reader
where not exists(
	select * from (select * from reader, borrow 
					where reader.id = borrow.reader_id and reader.name = '李林') rb
	where exists (
			select * from borrow
			where reader.id = borrow.reader_id and rb.book_id = borrow.book_id
			)
);