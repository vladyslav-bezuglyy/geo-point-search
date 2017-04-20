# geo-point-search

Provides algorithms to find largest empty rectangle and 
smallest rectangle with specified fraction of points in 
the space of large number of random geo coordinates

**To build**: on Linux-type system with gcc and make: simpily run "make"

**To run**: "./sample X", where X is 0 or 1. 0 will run the algorithm for 
largest empty rectangle, and 1 will run the algorithm for smallest filled rectangle.
Any other value will run the largest empty rectangle algorithm.

**Description of the method**

Idea is to consider geo coordinates on a grid with desired precision. Grid itself is of size 180x360 (twice max latitude by twice max longitude).
When random points are generated, they are put on a grid, and we count the number of points in each cell of the grid. 
Next we apply "evolutionary" (or simply stochastic) algorithm to find a desired rectangle.

Stochastic algorithm starts with generating an initial population of rectangles. Each rectangle 
is specified by 2 points forming a diagonal and an angle alpha between diagonals. Other properties, 
such as 2 remaining points and area or perimeter may be deduced from these parameters. For each rectangle 
we can calculate area as 0.5*d^2*sin(alpha), where d is a diagonal. For the first algorithm, fitness function must be provided so that 
the algorithn maximizes the area and minimizes the number of points in the rectangle (or probablity that the points are in the rectangle). To maximize the area, 
we can minimize function f = (1 - area/max_area), where max_area = 180*360*4. Similarly, to minimize the area for the second algorithm, we can minimize funcion f = area/max_area. 
For the fitness function we must also account for constraints, i.e. there should be no point in the rectangle for the first case, and there should be 30% of points in the second case.
When generating random rectangles, we don't acount for periodicity of longitude, for the sake of the simpilicity. Otherwise, this must also be taken into account. 

When initial population is formed, we proceed to the next stage and decide which rectangle will go to the next generation. First we find the rectangle with the best fitness function 
value (i.e. minimal value) and put it to the next generation, so that we preserve the best rectangle. When we add the same element to the generation to allow it to be mutated with random probability. And finally we add a random rectangle to preserve some randomness in the populaton. The rest of the population is obtained using "tournament" approach: 
we take 2 rectangles from the population at random and compare their fitness function, the rectangle with better fitness function will go the next generation. 

After next generation is formed, we allow it to be mutated with some probability: we may change values of 2 points at random or change value of the angle with small perturbance. 
It is worth to mention that we don't use crossover operation in in this algorithms.

**File description**
EarthConstant.h - constant which determines size of the grid and size of the cell within grid
EarthGrid - keeps track of points in the grid
GeoObject - defines a rectangle and operation with it
ProjectDefines - project-specific defines, such as number of points, size of populatoin, number of generation, etc.
RandomPointGenerator - generates random geo locations.
Sample.cpp - main file which runs the algorithms

