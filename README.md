# geo-point-search

Provides algorithms to find the largest empty rectangle and smallest rectangle with a specified fraction of points in 
the space of a large number of random geo coordinates

**To build**: on Linux-type system with gcc and make: simpily run "make"

**To run**: "./sample X", where X is 0 or 1. 0 will run the algorithm for 
largest empty rectangle, and 1 will run the algorithm for smallest filled rectangle.
Any other value will run the largest empty rectangle algorithm.

**Description of the method**

The idea is to consider geo coordinates on a grid with desired precision. The grid itself is of size 180x360 (twice max latitude by twice max longitude). When random points are generated, they are put on a grid, and we count the number of points in each cell of the grid. Next we apply "evolutionary" (or simply stochastic) algorithm to find a desired rectangle.

The stochastic algorithm starts with generating an initial population of rectangles. Each rectangle is specified by 2 points forming a diagonal and an angle alpha between diagonals. Other properties, such as 2 remaining points and area or perimeter, may be deduced from these parameters. For each rectangle we can calculate the area as 0.5\*d^2\*sin(alpha), where d is a diagonal. 

For the first algorithm, fitness function must be provided so that the algorithm maximizes the area and minimizes the number of points in the rectangle (or probability that the points are in the rectangle). To maximize the area, we can minimize function f = (1 - area/max\_area), where max\_area = 180\*360\*4. Similarly, to minimize the area for the second algorithm, we can minimize function f = area/max\_area.

For the fitness function we must also account for constraints, i.e. there should be no point in the rectangle in the first case, and there should be 30% of points in the second case. We consider the following fitness function for the first algorithm: f = (1 - area/max\_area) + k\*sum(points in the rectangle)/(total\_number\_of\_points), where k is an adjustable parameter which determines how important constraints are. Currently we use k = 1000, but it probably should depend on the grid size. 

For the second algorithm we consider the fitness function which is the sum of 2 parts: the first part is simply area/max\_area, whereas the second part depends on the count of points within the rectangle. We calculate the difference between actual fraction and the desired one, if the difference is larger than desired tolerance, add 10\*k to fitness, if it is smaller than the tolerance, add k\*(actual\_tolerance/required\_tolerance). Thus, if we require 30% of all points to be in a rectangle and tolerance of 2.5%, and there is 40% of the points in rectangle we add 10\*k to the fitness. If there is 32% of the points in the rectangle - we add 0.8\*k.

When initial population is formed, we proceed to the next stage and decide which rectangle will go to the next generation. First, we find the rectangle with the best fitness function value (i.e. minimal value) and put it to the next generation, so that we preserve the best rectangle. When we add the same element to the generation to allow it to be mutated with random probability. And finally we add a random rectangle to preserve some randomness in the population. The rest of the population is obtained using "tournament" approach: we take 2 rectangles from the population at random and compare their fitness function, the rectangle with better (smaller) fitness function will go to the next generation. 

After next generation is formed, we allow it to be mutated with some probability: we may change values of 2 points at random or change value of the angle with small perturbation.

It is worth to mention that we don't use crossover operation in in this algorithm. Also, note that when generating random rectangles, we don't account for periodicity of longitude, for the sake of the simplicity. Otherwise, this must also be taken into account. 

**File description**

EarthConstant.h - constant which determines the size of the grid and the size of the cell within the grid

EarthGrid - keeps track of points in the grid

GeoObject - defines a rectangle and operation with it

ProjectDefines - project-specific defines, such as number of points, size of population, number of generations, etc.

RandomPointGenerator - generates random geo locations.

Sample.cpp - main file which runs the algorithms

