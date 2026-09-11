# Codexion

A concurrent C project where coders compete for shared dongles while avoiding burnout.

## Features

* Multithreading with `pthread`
* FIFO and EDF scheduling
* Min-heap priority queue
* Mutexes and condition variables
* Dongle cooldown management
* Burnout monitoring
* Thread-safe logging

## Usage

```bash
make
./codexion 5 3000 200 200 200 10 400 fifo
```

### Arguments

```text
number_of_coders
time_to_burnout
time_to_compile
time_to_debug
time_to_refactor
number_of_compiles_required
dongle_cooldown
scheduler
```

### Schedulers

* `fifo` — First In, First Out
* `edf` — Earliest Deadline First

## Cooldown

After a dongle is released, it cannot be taken again until the configured cooldown time has passed.

Example with a `400 ms` cooldown:

```text
Released:  200 ms
Next take: 600 ms

600 - 200 = 400 ms ✓
```

## Build

```bash
make
make clean
make fclean
make re
```

### Some Theory of thread

> that should be enough to start just make you have a idea of what happen that what you need

![some theory of thread](images/codexion_tra.png)
