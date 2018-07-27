select book.name as book_name, borrow_date
from book, reader, borrow
where book.id = borrow.book_id and reader.id = borrow.reader_id
			and reader.name = 'Rose';