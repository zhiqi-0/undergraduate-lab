select readerid, count(distinct bookname) as borrownum
from readerborrow
where datediff(curdate(), borrowdate) <= 365
group by readerid