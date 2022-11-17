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

