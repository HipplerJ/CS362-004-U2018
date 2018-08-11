# Final Project (Part B)
CS 362-400 (Summer 2018)  
Software Engineering II  
Due: Monday, August 13, 2018  

## Group Members
- Kyle Martinez (martink9)
- James Hippler (hipplerj)
- Caitlin Dudley (dudleyca)

You are provided a buggy version of URLValidator. You need to find out as many bugs as you can in this bad URLValidator. In the Part-A, I have provided the current test framework that Apache commons team had to test URLValidator. We need to assume that all those tests don’t exist. Your team is a testing company and client comes to you with URLValidator implementation and asks for your help to make it bug-free. You need to just concentrate on isValid method, the one that is tested in testIsValid() method. Your task is to find out two the bugs, find out failure causes and provide bug reports. You don’t need to fix any of the bugs. Developers will do it.

### CS362-004
You can use any methodology that you learn during the class to test it. To stay consistent let us do it this way:  
1. First, just do manual testing. Call the valid method of URLValidator with different possible valid/invalid inputs and see if you find a failure. (15 points)
2. Second, come up with good input partitioning. Try to provide a varying set of inputs that partition the overall input set well. Did you find any failures? You can call valid method once or more for each partition. (15 points)
3. Third, do programming based testing. Write few unit test cases. You can have some sort of loop in your unit test and test different URL with each instance of the loop. Something very similar to testIsValid() but your own logic and idea. Even a single test will be sufficient if you write it like testIsValid() method. Did you find any failures? (20 points)
