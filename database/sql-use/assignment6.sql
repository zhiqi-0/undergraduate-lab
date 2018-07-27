select reader.name as name
from reader, borrow
where reader.id = borrow.reader_id
group by reader.id
having count(*) > 3