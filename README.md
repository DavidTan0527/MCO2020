# MCO2020
Solutions with explanations of Malaysian Computing Olympiad (MCO) 2020

I only included solutions for the first three problems as these were the only ones I was able to solve out of the five.
I will still include the problem statements of the last two problems in this repo and might one day come back to solving them.

# Problems
- [Increasing-increment](https://github.com/DavidTan0527/MCO2020#increasing-increment)
- [Reversi](https://github.com/DavidTan0527/MCO2020#reversi)
- [Friends](https://github.com/DavidTan0527/MCO2020#friends)

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
Normally, when given a problem related to diagonals on a grid, it is useful to recall that cells with column *c* and row *r* sharing the same diagonal with positive gradient, i.e. /, has a common value of *r-c* (or *c-r*), whereas cells sharing the same diagonal with negative gradient, i.e. \, has a common value of *r+c*.

It is also important to note that we do not need to account for every possible diagonal as the total number of diagonals is 4\*10<sup>9</sup> - 2, which will exceed the memory limit. Thus, we only need to account for diagonals that have at least one white piece on it, which has a maximum number of 2\*N.

Keeping this in mind, it is obvious to see that we can treat white pieces as edges that connect a diagonal of positive gradient with another diagonal of negative gradient. Since the question states that every white piece flipped triggers a chain reaction for all the subsequent diagonals of all its connected white pieces, this can be understood as grouping all these diagonals into one group by using a **DSU** (Disjoint Set Union). 

Finally, we only need to calculate the number of independent groups.

> The time complexity of this solution is estimated to be ***O(N\*logN)***

# Friends
At first, this might seem quite impossible as even floating point numbers are allowed to be distributed (for example, time of 5 can be splitted into 1.5, 3.5, 0).

There's a very important concept to note: *the optimum way of a person to distribute their time is to use all its time on one friend*

This can be proven roughly:
```
When N=3:
A - B - C
A and C will only have the choice to contribute all their time
Let x be the time spent by B on A
Total happiness = x*A + (B-x)*C = B*C + x(A-C)
if A > C, it is optimal to choose the maximum value for x, which is B
else, x should be 0

By looking at more cases where several neighbours are considered, you can work out that devoting all your time to one friend is the best choice
```

Thus, we have concluded that a person uses all its time onto one edge only, which means we can think of choosing edges on the tree where all edges do not share a vertex. This is a classic tree dp problem where we need to find the maximum happiness of a subtree.
We can define:
```
dp[i][j] = maximum happiness of subtree of i given its state j
i = node on tree
j = 0: i is connected to none of its children, 1: i is connected to one of its children
```

Then we can use a dfs to recursively resolve the dp values from children to parent.

When u is not connected to its children, each children has the freedom to choose whether to connect with their children or not to maximise the happiness.
```
dp[u][0] = ∑ max(dp[v][0], dp[v][1]) for v in children of u
```

When u is connected to one of the children, we need to find the maximum happiness across all happiness obtained by connecting to each children subsequently. As we loop through children of u, we calculate the happiness when u is connected to the current child.
```
for v in children of u:
  dp[u][1] = max(dp[u][1], happy[u]*happy[v] + dp[u][0] - max(dp[v][0], dp[v][1]) + dp[v][0])

Note that dp[u][0] - max(dp[v][0], dp[v][1]) + dp[v][0] clears the happiness given by maximum of both states of v and later fixed to taking the happiness when v is not connected to its children, this is because we are assuming u is connected to v already.
```
Then we only need to output max(dp[0][0], dp[0][1])

Since we only traversed to each node and looked at its children, we are basically looping through the *N* nodes.

> The time complexity of this solution is ***O(N)***