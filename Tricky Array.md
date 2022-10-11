#### [1. Number of Students Unable to Eat Lunch](https://leetcode.com/problems/number-of-students-unable-to-eat-lunch/description/)  
The school cafeteria offers circular and square sandwiches at lunch break, referred to by numbers 0 and 1 respectively. All students stand in a queue. Each student either prefers square or circular sandwiches.

The number of sandwiches in the cafeteria is equal to the number of students. The sandwiches are placed in a stack. At each step:

If the student at the front of the queue prefers the sandwich on the top of the stack, they will take it and leave the queue.
Otherwise, they will leave it and go to the queue's end.
This continues until none of the queue students want to take the top sandwich and are thus unable to eat.

You are given two integer arrays students and sandwiches where sandwiches[i] is the type of the `ith` sandwich in the stack (i = 0 is the top of the stack) and students[j] is the preference of the `jth` student in the initial queue (j = 0 is the front of the queue). Return the number of students that are unable to eat.

**Approach: T:O(N) S:O(1)**
1. The thing to understand is the request is not satisfied whenever the sandwhich at current pos say has no buyer among the students. Otherwise they will always buy by rotating themselves.
2. So just maintain two variables as count for the two sandwich requirement by the students.
3. Now iterate through the sandwich array if the count of that sandwich is > 0 then decrement it and inc the `count` representing number of students whose request is acceptable.
4. If the count of sandwich is zero for the current sandwich then it means no more student need that sandwich hence we cant move forward.

```
int a=0,b=0;
        for(int i=0; i<stud.size(); i++){
            if(stud[i]==0) a++;
            else b++;
        }
        int count=0;
        for(int i=0; i<ord.size(); i++){
            if((ord[i]==0 && a==0 )||(ord[i]==1 && b==0)) break;
            else{
                count++;
                if(ord[i]==0) a--;
                else b--;
            }
        }
        return stud.size() - count;
```
