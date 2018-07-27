create view readerborrow (readerid, readername, bookid, bookname, borrowdate)
as select reader.id as readerid, reader.name as readername,
					book.id as bookid, book.name as bookname, borrow.borrow_date as borrowdate
	 from reader, book, borrow
	 where reader.id = borrow.reader_id and book.id = borrow.book_id;