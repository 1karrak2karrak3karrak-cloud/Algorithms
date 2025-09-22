Coin Change Problem - Dynamic Programming vs Greedy Approach

Overview
This C program implements two different algorithms for solving the coin change problem: dynamic programming and greedy approach. The problem involves finding the minimum number of coins needed to make a given amount, considering limited coin quantities.

Features
1. Dynamic Programming Solution
Optimal Solution: Guarantees minimum number of coins
- Time Complexity: O(kw) where k is number of coin denominations and w is the target amount
- Space Complexity: O(w) for DP table storage
- Handles Constraints: Respects limited coin quantities

2. Greedy Algorithm Solution
- Efficient but Suboptimal: May not always find the minimum coins
- Time Complexity: O(k) - much faster for large amounts
- Simple Implementation: Always selects largest possible coin first
- Works Best: When coin system is canonical (like standard currency)

Sources and References

"Introduction to Algorithms" by Cormen, Leiserson, Rivest, and Stein (CLRS)
- Chapter 16: Greedy Algorithms (coin change discussion)
- Chapter 15: Dynamic Programming (optimal substructure and DP formulation)

----------------------------------------------------------------------------------------
Matrix Multiplication Algorithms Comparison

Overview
This program implements and compares three different matrix multiplication algorithms: classical method, divide-and-conquer, and Strassen's algorithm. It measures performance for matrices of increasing sizes.

Features
1. Classical Matrix Multiplication
- Time Complexity: O(n³)
- Simple Implementation: Three nested loops
- Baseline Comparison: Standard approach for benchmarking
2. Divide-and-Conquer Method
- Time Complexity: O(n³) - same as classical but demonstrates recursive approach
- Recursive Structure: Divides matrices into quadrants
- Educational Value: Shows divide-and-conquer paradigm application
3. Strassen's Algorithm
- Time Complexity: O(n²·⁸¹) - theoretically faster for large matrices
- Advanced Technique: Uses 7 multiplications instead of 8 for subproblems
- Practical Limitations: Overhead makes it efficient only for large matrices

Sources and References

"Introduction to Algorithms" by Cormen, Leiserson, Rivest, and Stein (CLRS)
- Chapter 4: Divide-and-Conquer (matrix multiplication introduction)
- Section 28.2: Strassen's algorithm for matrix multiplication

----------------------------------------------------------------------------------------
 Diamond Collection - Dynamic Programming Pathfinding
 
Overview
This program solves a pathfinding problem using dynamic programming to maximize diamond collection in a grid. The agent can only move right or down to collect diamonds.

Problem Statement
Given an N×M grid where each cell may contain a diamond (1) or be empty (0), find the maximum number of diamonds that can be collected when moving from the top-left corner to the bottom-right corner, only moving right or down.

Sources and References

"Introduction to Algorithms" by Cormen, Leiserson, Rivest, and Stein (CLRS)
- Chapter 15: Dynamic Programming
- Section 15.4: Longest Common Subsequence (similar DP structure)
- Section 15.3: Elements of Dynamic Programming (optimal substructure, overlapping subproblems)
