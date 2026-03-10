*This project has been created as part of the 42 curriculum by hbray*

# Philosophers

## Description
A number of philosophers sit around a table with a bowl of spaghetti. They alternately eat, sleep, and think. To eat, a philosopher needs two forks. If a philosopher doesn't eat within a given time, they die.

The goal is to implement a simulation where every philosopher stays alive as long as possible, using concurrent programming techniques. The mandatory part uses threads and mutexes.
Each philosopher is a thread sharing memory. Forks are individual mutexes. Deadlock is prevented by alternating fork pick-up order based on philosopher ID (even/odd). A central monitoring thread detects starvation.

## Instructions

### Compilation

The projet is managed via a Makefile. You can use the following commands:

```bash
make			# Compiles philo
make clean		# Removes object files
make fclean		# Removes all compiled files
make re			# Recompiles philo
```

### Execution

```bash
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep>
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> <number_of_times_each_philosophers_must_eat>
```

### Examples

```bash
./philo 4 410 200 200		# no philosopher should die
./philo 4 310 200 200		# one philosopher should die
./philo 5 610 200 200		# no philosopher should die
./philo 4 410 200 200 7		# stop after 7 meals
./philo 1 410 200 200		# 1 philosopher, will die
```

## Resources

### Reference

* **[thread_and_mutex(article fr)](https://www.codequoi.com/threads-mutex-et-programmation-concurrente-en-c/)** Deep dive into thread synchronization using mutex locks.
* **[mutex_lock_linux(article en)](https://www.geeksforgeeks.org/linux-unix/mutex-lock-for-linux-thread-synchronization/)** Deep dive into thread synchronization using mutex locks.

### AI Usage Disclosure

* **README Optimization :** Assistance with formatting and structuring this documentation.