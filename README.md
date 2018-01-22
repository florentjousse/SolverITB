# CSP Solver

This project is a constraint satisfaction problem solver written in C++11.
The solution is found using a backtrack algorithm combined with a filtering algorithm (AC-3)
More precisely, the algorithm is called forward checking : when we assign a value to a variable we filter from this variable. 

There is an example of the N-queen = 6 problem in the "main.cpp" file.

It's recommended to compile with -O2 optimizations because the backtrack algorithm is written reccursively with a terminal call.

  
 In propagation.cpp :
 uncomment this portion of code to print the solution
 ```c++
		std::cout << "\nsolution trouvee";
		for (auto i : labelled) {
			std::cout << "\nvar[" << i.getIndice()+1 << "]=" << i.getLabel();
		}
 ```

    
In propagation.cpp :
This return statement allow us to abort the recursive stack: without the return statement the solver will return all the solutions :
```cpp
	return 1;
```

Benchmarks where we can see the improvement of AC-3 to solve N-Queen :

![alt text](https://github.com/cryckx/SolverITB/blob/master/bench.png)

A significant way to improve the performance of the solver might be to add some algorithm to solve global constraint such that "alldifferent". Indeed, there are polynomial algorithms to solve an alldifferent constraint ( problem equivalent to strongly connected components) and N-Queen problem can ben express with 3 allDifferent constraints:

