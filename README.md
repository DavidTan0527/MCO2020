# MCO2020
Solutions with explanations of Malaysian Computing Olympiad (MCO) 2020

I only included solutions for the first three problems as these were the only ones I was able to solve out of the five.
I will still include the problem statements of the last two problems in this repo and might one day come back to solving them.

# Problems
- [Increasing-increment](https://github.com/DavidTan0527/MCO2020#increasing-increment)
- [Reversi](https://github.com/DavidTan0527/MCO2020#reversi)

---

# Increasing-increment
WLOG, we will start by first considering all the *X* and *Y* values separately. 

Since *X* is a simple range increment over *[L, R]*, a simple solution to efficiently do this is to use the +1/-1 technique.
Suppose we have an array, base, of length *N* where each element is default to 0. For every *X* over *[L, R]*, we set *base\[L\] += X* and *base\[R+1\] -= X*.
```
Example:
Let's say we have 9 castles
1. +3 over [2, 5]
2. +1 over [3, 7]
3. +3 over [1, 8]

By applying the rule stated above, base is now { 0, 3, 3, 1, 0, 0, -3, 0, -1 }
Notice that since the length of the array is 9, the third condition where we should do base[9] -= 3 can be ignored as it exceeds the array length

Thus the damage dealt on the castles can be calculated by recording the current damage baseumulated.
Formally, the current damage dealt on castle i is calculated by taking the prefix sum of base from 0 to i;
```

*Y* can become more complicated as the amount of damage by which a castle takes increases repeatedly over the interval. There are many ways of solving it and my method is honestly very messy. My idea is to keep track of the accumulated damage and the amount to increment that damage by for every castle. Because my method does not account for terminating this accumulating increment, I cancel this effect by keeping track of the accumulated value to deduct from the damage and the amount by which this value increments by.

Using this we can easily calculate the damage for a given castle *i* where the *X* damage = ∑ base[0...i], *Y* damage = accumulated damage - accumulated deduction.

> The time complexity of this solution is ***O(N)***

# Reversi
## Problem Statement
