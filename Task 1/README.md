## Task 1

### Overview

The [Drake equation](https://en.wikipedia.org/wiki/Drake_equation) asserts to give an estimate of the number of intelligent civilisations, $`N`$, in our Milky Way galaxy. In its original form, the Drake equation calculates this estimate based on seven parameters. Your task is to write a program which calculates and prints $`N`$ for several different sets of parameters.

Your C source file for this task *must* be named `task1.c` and placed in the top-level directory of your git project for this coursework.

### Details

The original [Drake equation](https://en.wikipedia.org/wiki/Drake_equation) is:

```math
N = R_* \cdot f_p \cdot n_e \cdot f_l \cdot f_i \cdot f_c \cdot L
```

Where $`N`$ is the number of active, communicative extraterrestrial civilizations in the Milky Way galaxy, and the seven parameters are:

| Parameter | Description |
| :-----: | :--- |
| $`R_*`$ | the average rate of star formations in our galaxy |
| $`f_p`$ | the fraction of formed stars that have planets |
| $`n_e`$ | for stars that have planets, the average number of planets that can potentially support life |
| $`f_l`$ | the fraction of those planets that actually develop life |
| $`f_i`$ | the fraction of planets bearing life on which intelligent, civilized life, has developed |
| $`f_c`$ | the fraction of these civilizations that have developed communications |
| $`L`$   | the length of time over which such civilizations release detectable signals |

Your C source file should contain **two functions**: a `main` function and a function named `drake_equation`.

Your `drake_equation` function should calculate the Drake equation for a given set of parameters. The `drake_equation` function should take **seven arguments**, corresponding to the **seven parameters** in Drake's original equation, as described in the [Introduction](introduction-1) to this task. You should assume all arguments are double precision floating point numbers *except for* $`n_e`$ and $`L`$, which you should assume are integers. The `drake_equation` function should calculate and return the value of $`N`$ based on the values of the arguments passed to the function. $`N`$ should be returned as a non-negative integer.

Your `main` function should be defined correctly and should call the `drake_equation` function **four times** with the follow **four sets** of parameters:

|       | $`R_*`$ | $`f_p`$ | $`n_e`$ | $`f_l`$ | $`f_i`$ | $`f_c`$ | $`L`$ |
| :---: | :-----: | :-----: | :-----: | :-----: | :-----: | :-----: | :---: |
| Set 1 | 1.0     | 0.2     | 1       | 1.0     | 1.0     | 0.1     | 1000  |
| Set 2 | 1.0     | 0.5     | 5       | 1.0     | 1.0     | 0.2     | 1000000000  |
| Set 3 | 1.5     | 1.0     | 3       | 1.0     | 0.0001     | 0.001     | 304  |
| Set 4 | 3.0     | 1.0     | 5       | 1.0     | 1.0     | 0.1     | 10000000  |

*Set 1* and *Set 2* are Drake's original lower and upper estimates respectively for the parameters. *Set 3* and *Set 4* are possible lower and upper estimates respectively for the parameters based on current data.

After each call to `drake_equation`, your `main` function should print the value of $`N`$ calculated by the `drake_equation` function, along with the values of the seven parameters used in this calculation. You should print the results in the same order as above (*Set 1* first, then *Set 2*, then *Set 3*, then *Set 4*). Floating point numbers should be printed to **one decimal place**. Integers should be printed in standard (not scientific notation) form. The eight numbers should be printed together on a new line in the following format:

```
N=? R*=? fp=? ne=? fl=? fi=? fc=? L=?
```

where `?` is replaced by the values of each of the arguments the `drake_equation` function was called with and the value of $`N`$ calculated and returned by this function. So, the first output line of your program (*Set 1* above) will be:

```
N=20 R*=1.0 fp=0.2 ne=1 fl=1.0 fi=1.0 fc=0.1 L=1000
```

and so on for *Set 2*, *Set 3*, and *Set 4*.