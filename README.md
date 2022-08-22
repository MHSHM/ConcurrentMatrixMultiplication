# ConcurrentMatrixMultiplication
Multi-threaded matrix multiplication solution using C++14 and the standard library thread header. The solution was first impleneted sequentially in "Multiply".
For the Concurrent version of the solution i first implemented a Task class which is basically a wrapper around any callable type,
Then implemented a Thread Pool which is just a collection of threads listining to a queue of tasks. Each time the main thread schedules a task a sleeping thread from the thread pool would be
awakened to handle it. The Execution time of the Concurrent version of the solution was two times faster than the Sequential in some extreme cases with matrix size 700x700 and 800x800. 
For a Comaprison between the sequential solution and the Concurrent solution check out the Performance section. If you'd like to try the code make sure you initialize the matrices with "InitializeWithRandom"
this function will initialize the matrix with random values in the range 1-10, it's currently the only way to initialize the matrix and the main reason is that i'm too lazy to implement another way.

# Performance
The test was run on Ryzen 5 3100 with 4 CPU Cores and 8 Threads in a Debug mode.

| Size        | Concurrent           | Sequential  |
| ------------- |:-------------:| -----:|
| 100x100      | 0.05s     | 0.03s |
| 200x200      | 0.23s     |   0.22s |
| 300x300      | 0.56s      |    0.69s |
| 400x400      | 1.11s      |    1.62s |
| 500x500      | 1.90s      |    3.14s |
| 600x600      | 3.00s      |    5.34s |
| 700x700      | 4.56s      |    8.33s |
| 800x800      | 6.69s      |    12.47s |
| 900x900      | 9.60s      |    17.87s |
| 1000x1000      | 13.25s      |    24.02s |

![Performance Graph](https://i.imgur.com/uxbW0Ej.png)
