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
