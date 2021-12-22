# Dining Philosophers Problem

## Project

This project implements a solution to [the dining philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem) using a limited set of **<pthread.h>** functions:
  - pthread_create
  - pthread_detach
  - pthread_join
  - pthread_mutex_init
  - pthread_mutex_destroy
  - pthread_mutex_lock
  - pthread_mutex_unlock

In a nutshell, we have a number _n_ of philosophers sitting around a table (a round table), each philosopher is sitting between two forks, _n_ forks in
total, each time a philosopher wants to eat, it needs to pick up two forks, meaning that the philosophers on its left and right are unable to eat
(they share some forks), after the philosopher finishes eating, it drops the forks, making the resources (forks) available again, now the other
philosophers can eat.  

 ![philosophers around table](https://camo.githubusercontent.com/77499a2b05beb38c534cba3fbb4ff85c6f59d43cfc8c7dd9807fc92b406bba56/68747470733a2f2f616469742e696f2f696d67732f64696e696e675f7068696c6f736f70686572732f61745f7468655f7461626c652e706e67)

## Main problems and Solutions
 
### Deadlock
  
  When trying to pick a fork, a philospher (thread) should first lock a [mutex](https://en.wikipedia.org/wiki/Lock_(computer_science)) to protect that fork
  (or its status) from being accessed by another thread (philosopher), if all the philosophers pick the forks in the same order; _left then right_ or _right then 
  left_, then a deadlock (**_similar to an infinite loop_**) will probably happen, since at a time, every philosopher will be waiting for the other philospher to 
  drop the second fork.  
  ![Visualization](https://cf2.ppt-online.org/files2/slide/i/IXmgTJMhE12oNPvnW40tYaRB5SkpsKH3rAL6ed/slide-38.jpg)  
  The fix is simple, one (or more) of the philosophers should switch the order by what the forks are picked!
  
### Starvation
 
 Mainly happens when we have an odd number of philosophers!
 Since the thread that gets executed when multiple threads (philosophers) are wating is chosen at random, their will come a time where a philosophers
 eats, sleeps, starts waiting for its turn again together with another philosopher that was waiting here before it, and gets to eat again, leaving the other 
 philosopher starving!
 example: 5 philosophers
 > 1. philo 1 and philo 3 eat ==> normal, they share no forks
 > 2. philo 2 and philo 4 eat ==> normal
 > 3. philo 5 and philo 3 eat ==> normal
 > 4. in this step, two things can happen since both 2 and 1 are waiting on the same fork: **philo 1 and philo 4** eat ***or*** **philo 2 and philo 4** eat, if  the latter happens, philo 1 will die, cause it has been a while since it ate.
  
Multiple solutions are available for this, This projects adds a _last-user_ variable to the forks, it stores the id of the last philosopher who used it! and
prevents it from eating two times in a row.
  
## Execution

From the command line run:

  - `make` to build the project
  - Launch the executable with the right parameters: `./philo 5 800 200 200`

## Arguments

First argument is the number of the philosophers sitting around the table.  
Second argument is how many milliseconds a philosopher can stay alive without eating.  
Third argument is how many milliseconds a philosophers needs to finish a meal.  
Fourth argument is how many milliseconds does a philosopher sleep for.  

## Resources

[Solving deadlock and starvation](http://web.eecs.utk.edu/~mbeck/classes/cs560/560/notes/Dphil/lecture.html)



  
