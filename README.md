# Generate_Unpredictable_Random_Number


Author: Alessandro Conti - [AlessandroConti11](https://github.com/AlessandroConti11)

License: [MIT license](LICENSE).

Tags: `#/dev/random`, `#C`, `#computer_engineering`, `#computer_security`, `#Linux`,  `#random_number`.


## Specification

The project aims to generate unpredictable random numbers using the *Linux Kernel*'s special device */dev/random*.


## How to run

To ensure that the project works properly, you must compile it and run it in a Unix environment from the terminal by following these steps:

0. install gcc
    ```bash
    sudo apt-get install gcc 
    ```
1. compile the project
    ```bash
    gcc -Wall -Werror -O2 -g3 main.c -o EXECUTABLE 
    ```
2. run the project
    - with entering the arguments from the command line
      ```bash
      ./EXECUTABLE MIN MAX
      ```
    - without entering the arguments from the command line
      ```bash
      ./EXECUTABLE
      # at the beginning you will be asked to enter the minimum and maximum value
      ```
    

<br>

The Makefile in the repository can also be used to compile the code.
- this option allows you to compile with the following tags: *-Wall -Werror -O2 -g3*
    ```bash
    make compile
    ```
- if you want to specify different tags, you can set them
   ```bash
   make compile CFLAGS=YOUR_FLAGS
   ```
- if you want to use Address SANitizer
    ```bash
    make asan
    ```


## Final consideration

Random number generation functions, such as the *rand* function of the standard C library, produce pseudo-random numbers. 
These numbers, although satisfying many of the desired properties of randomness, can be reproduced if the initial seed of the generated sequence is known. 
This reproducibility can pose a risk, especially in sensitive contexts such as cryptography, where a predictable sequence can compromise security.


To obtain truly random numbers, it is necessary to draw on external sources of randomness. 
The *Linux Kernel* relies on user input as a source of randomness. 
Special devices such as **/dev/random** and **/dev/urandom** exploit the delay between user actions, such as typing and mouse movements, to generate random numbers.


Linux offers two ways to access randomness. 
With **/dev/random**, if an attempt is made to read a large amount of data without further input from the user, the read operation is blocked, as the kernel has no further data from which to continue the random sequence. 
On the other hand, with **/dev/urandom**, the kernel uses a cryptographic algorithm to continue generating random numbers even in the absence of new input, ensuring that the read operation is not blocked. 
However, it is important to note that in this case the numbers generated can be considered pseudo-random, since they are derived from a previous sequence.
