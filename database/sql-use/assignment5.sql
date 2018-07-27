select book.name
from book, reader, borrow
where borrow.book_id = book.id and borrow.reader_id = reader.id
			and reader.name = '李林' and return_date is NULL