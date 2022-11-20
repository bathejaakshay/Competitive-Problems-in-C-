#### NOTES

Mysql is case sensitive, SQL server is case insensitive


#### LIMIT and offset

If you want to fetch n number of records from x to x+n then you should set offset to x-1 (this will ignore first x-1 rows) and limit = n (from offset we count n records).

Question : Write a query to fetch the Artists in rows 10 through 20

```
SELECT * FROM artists LIMIT 10 OFFSET 10;
```  

Question: Write a query to get 5th highest marks in students table

```
SELECT MARKS FROM STUDENTS ORDER BY MARKS DESC LIMIT 1 OFFSET 4; 
```

--- 

## Simple Min Max queries

Q: [Given a table FIREFIGHTERS, find the largest difference between the number of people saved by 2 firefighters](https://www.interviewbit.com/problems/largest-difference/).  

```
SELECT ( MAX(PeopleSaved) - MIN(PeopleSaved) ) as A from FIREFIGHTERS;
```

---

## IN operator framework

#### [Chess game](https://www.interviewbit.com/problems/chess-tournament/)
A chess tournament is being held which consists of several matches between a player and a computer. After every match one player is declared as the winner.  

You are given two tables, One table consists of the players that will be playing the tournament while the other table consists of the matches that will be played in the tournament and its Result. The Result would be 1 if the player won the match, 0 otherwise. You have to output the names of the players who have won atleast one match and lost atmost one match.  

```
Players : Id, Name
Matches: Id, Result
```

**Approach  1**
- find all the IDs that have atleast 1 win and all the ids that have atleast two losses
- now select those players that are in first table but  not in the second.

```
select Name from Players where Id IN (select f.Id from (select * from Matches where Result = 1) as f group by f.Id having count(f.Result) >=1)
and ID NOT IN
(select f2.Id from (select * from Matches where Result = 0) as f2 group by f2.Id having count(f2.Result) >1)
```

**Approach 2 : Single query**
- in matches group by id and find `sum of results >= 1` and `count(*) - sum(results) <= 1` the prior means atleast 1 win and latter means atmost 1 loss.

```
select Name from Players where Id in(select Id from Matches  group by Id having SUM(Result)>0 and count(*)-SUM(Result)<=1);

```

---

## Case-when operator

It is like an If-Then-Else statement.  
Syntax:
```
CASE
    WHEN condition1 THEN result1
    WHEN condition2 THEN result2
    WHEN conditionN THEN resultN
    ELSE result
END;
```

Question: #### [NULL Sorting](https://www.interviewbit.com/problems/null-sorting/)
You are given a table ‘Students’ which consists of the student information of every student along with the marks that they obtained in a test out of 100. However there were students who were Absent for the test, their marks section would contain ‘Absent’ word. Help the teacher arrange the students first based on their marks and second based on their first name.(You just have to output the names of the students).  

**Approach**
- One Approach is to update the marks attribute when marks='absent' and set it to -1. Now just sort by Marks desc and Name asc.
- Instead we can do this in one query. Firstly create another column which shows when Marks are absent as 0 and when they are not as 1.
- Now Simply first desc sort by this column then by Marks and then by Name.

```
select Name from(  
    select Id, Name, Marks, 
    case when Marks = 'Absent' then 0 else 1 end as is_absent from Students) as x order by x.is_absent desc, x.Marks desc, x.Name;
```

---


## Application of Case statement in sorting

```
SELECT CustomerName, City, Country
FROM Customers
ORDER BY
(CASE
    WHEN City IS NULL THEN Country
    ELSE City
END);
```

## Sorting with case statement
#### [I hate Vowels](https://www.interviewbit.com/problems/i-hate-vowels/)
You are given a ‘Students’ table consisting of Id,Name and marks of two tests namely Marks1 and Marks2. The teacher wants to sort the table based on their marks(in descending order). However the teacher has a particular hate towards students whose Names starts with a vowel. Therefore the teacher would take the maximum of the two tests for students whose name doesn’t start with a vowel while sorting, and would take the minimum of the two tests for the students whose name starts with a vowel while sorting.  

**Approach**
- Put case conditions of name and marks in order by

```
select Name  from Students order by case when ((Name like 'A%') or (Name like 'E%') or (Name like 'I%' )or (Name like 'O%') or (Name like 'U%')) then (
    case when Marks1 > Marks2 then Marks2 else Marks1 end
 ) else (
     case when Marks1 > Marks2 then Marks1 else Marks2 end
 ) end desc;

```

We can also check string starts with vowel using LEFT(string, number of chars) function

```
select Name  from Students order by case when (Left(Name,1) IN ('A','E','I','O','U')) then (
    case when Marks1 > Marks2 then Marks2 else Marks1 end
 ) else (
     case when Marks1 > Marks2 then Marks1 else Marks2 end
 ) end desc;
```
---

### Where to not use having clause

#### [Class Average](https://www.interviewbit.com/problems/class-average/)
You are given a table ‘Students’ which consists of the marks that students from different classes obtained in the final exam. Write an SQL query to find for each departments the number of students who managed to score above total average (average considering students of all classes) . The output should be sorted by ClassId .  

```
Students: Id,Name,Marks,Classid

```

**Approach**
- We cannot directly use group and having. i.e groupby classId having marks > avg(Total Marks of class). This doesnot make sense beacuse each classId has multiple students and we are filtering on classId i.e say there are two students having classid 101, one has marks > avg and the other has < avg.
- Then whichever record comes first in grouping statement will set if classId 101 should appear in the output or not and we cant count all of them in this way.
- Had it been, Output classIDs having enrolled students > 5 then we could have done group by classId having count(ID)>5. 
- Remember having condition must always have an aggregate.
- Instead we can do it simpy

```
select count(g.Id) as A from (select t.Id, t.Name, t.Marks, t.Classid from Students as t where t.Marks > (select AVG(s.Marks) from Students as s)) as g group by g.classid

```

---

#### NOTE: In Group By statement, if we want to project attributes other than those on which the table has been grouped upon then the other attributes must appear in an aggregate function. 
```
e.g Select Classid, count(Id) from Students group by Classid
```

#### NOTE2: Columns name can be more than 1 word just give it as a string
```
e.g select round(SUM(c.Result)/count(c.Result),4) as 'Percentage Wins' from (select m.PlayerId1, m.PlayerId2, m.Result, m.Date from Matches as m where m.PlayerId2 not in ( select p.Id from Team2 as p where p.Cheater = 1)) as c group by c.Date

```

#### NOTE3: String Length function

In Mysql: CHAR_LENGTH()
In SQL Server: LEN()

#### NOTE4: Case Insentitive sort

Way1 : order by lower(Name)
Way2 : order by Name COLLATE utf8_general_ci

---

#### JOINS
Joins are by default inner joins and `ON` keyword is necessary for specifying the joining attribute otherwise it will do a cartezian join.

#### [Job Offer]()
ou are given 3 tables namely ‘Students’ , ‘Departments’ and ‘Jobs’.  

Write an SQL query to find for each student their name and the date of the job offer. The output should be sorted by Department Names. Note that there might be students who did not receive a single offer, in such cases you should not include them in the output table.  

```
Students: Id, Name, DepartmentId
Departments: DepartmentId, DepartmentName
Jobs: Id, Date

```

**Approach**
- Inner join students with jobs first, it will only keep the students who got job.
- then join it with department and sort on department name.

```
select CONCAT(s.Name,',',j.Date) as Offers from  Students as s join Jobs as j on s.id = j.id join Departments as d on d.DepartmentId = s.DepartmentId order by d.DepartmentName
```

---

#### Full outer Join, only SQL server has full outer join

We are given a table with schema:

```
Children: CId, ParentId, Name, Gender
```

Now we need to print children name his male father name and his female mother null, if any of the above doesn't exist then print null

**Approach**
- Firstly join children with their fathers as t1 and children with their mothers as t2. Now join t1 and t2 as full outer join. (Keep in mind to handle null values)

```
select case when(t1.me IS NULL) then t2.me else t1.me end as Myself, t1.p1 as papa, t1.p1 as mumma from (select g1.CId, g1.Name as me, g2.Name as p1 from god as g1, god as g2 where g1.Parentid = g2.CId and g2.Gender = "male")as t1 full outer join (select g1.CId, g1.Name as me, g2.Name as p1 from god as g1, god as g2 where g1.Parentid = g2.CId and g2.Gender = "female")as t2 on t1.Cid = t2.Cid;

```
