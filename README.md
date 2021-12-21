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



  
