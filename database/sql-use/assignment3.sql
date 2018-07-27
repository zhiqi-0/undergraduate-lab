select reader.name as name
from reader
where not exists ( select reader.name from borrow where reader.id = borrow.reader_id );