# Thread Syncronisation App- LFX
- This solution demonstrates thread synchronization using mutexes within shared memory, graceful signal handling for SIGINT, and automated control through a bash script.

## C application design decisions

### outline
This application spawns two threads to share data through a shared memory segment. Processes the SIGINT signal to terminate the application cleanly.

### Shared memory management

- Use `shm_open` to create a shared memory object, and `ftruncate` to set the memory size.
- Use `mmap` to map shared memory.
- Implement inter-thread synchronization using `pthread_mutex`.

### Thread synchronization

- The two threads take turns increasing the counter value in shared memory.
- Use `pthread_mutex_lock` and `pthread_mutex_unlock` to maintain data consistency.

### Signal processing

- Use the `signal` function to handle the SIGINT signal.
- When the SIGINT signal is received, the shared memory is freed, the mutex is destroyed, and the application is terminated.

### Bash script

- The script runs the application in the background and sends a SIGINT signal after a specified amount of time.
- Check whether the application terminates cleanly through the SIGINT signal.


## Build Instructions:
- Ensure you have GCC installed on your Linux distribution.
- Compile the C application using "make".
- Use the bash script to launch the application: ./launch_app.sh <duration>.

  ## Detailed Instructions:

  #### one must grant execution permission to launch_app.sh.
  - chmod +x  launch_app.sh

  #### To compile the C application
  - make

  #### To run the c application
  - ./main &

  #### To send SIGINT Signal 
  - ctrl + c

  #### To run control script
  - ./launch_app.sh &  

  ##### (Run this in terminal where "&" represent the duration till we want to run.)


## Assumptions:
- The environment is a Linux system with support for gcc, pthread, and standard POSIX libraries.
- The application and the script are executed with sufficient permissions, especially for allocating shared memory.
- The duration provided to the bash script is a positive integer.
