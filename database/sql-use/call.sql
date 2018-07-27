-- call procedure
-- call modifyBookID('B#001', 'B#011');

-- delete procedure
-- drop procedure if exists modifyBookID;

-- test trigger1
 insert into borrow
 values ('B#008', 'R#001', str_to_date('12/08/2017', '%d/%m/%Y'), NULL);
-- test trigger2
-- update borrow
-- set return_date = str_to_date('13/08/2017', '%d/%m/%Y')
-- where book_id = 'B#008' and reader_id = 'R#001';