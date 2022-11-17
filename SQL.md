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




