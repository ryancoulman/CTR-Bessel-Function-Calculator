# Bessel Function Calculator

This project aims to implicitly solve a simplified form of the Bessel function, 

$$
J_{m}(x) = \frac{1}{\pi}\int_{0}^{\pi} \text{cos}(m \theta - x \text{sin} \theta) \ d \theta,
$$

in C, using the composite trapezium rule (CTR) to approximate the integral. This demonstrates proficiency in mathematical computations, numerical methods, and efficient data handling. The calculator computes Bessel functions of the first kind for various orders and outputs the results in a neatly formated text file.
## Features

- **Bessel Function Computation:** Calculates Bessel functions of the first kind $J_{m}(x)$ for orders $m = 0$ to $m = 9$.
- **High-Precision Output:** Generates high-precision values suitable for scientific and engineering applications.
- **Tabular Data Output:** Outputs results in a tabular format for easy analysis and interpretation.

## Key Concepts Demonstrated

- **C Programming:** Utilises functional C programming for mathematical calculations.
- **Numerical Methods:** Implements the CTR to approximate the integral to a high degree of accuracy using $N = 10,000$ sub-intervals.
- **File Handling:** Efficiently manages output large dataset operations to a .txt file.
- **Algorithm Implementation:** Develops efficient algorithms to perform complex mathematical computations.
- **Efficiency Optimization:** Once calcuated, samples the Bessel function at varied m and x values using a smaller N to verify the precision to the number of decimal places rquested by the user, improving computational efficiency by reducing N when possible if the output is unchanged.


## Code Overview

### Main Program (`main.c`)

- Defines and initializes necessary variables and constants.
- Computes Bessel functions for orders $m = 0$ to $m = 9$.
- Outputs the results in a structured tabular format to `Bessel_Output.txt`.

### Output File (`Bessel_Output.txt`)

- Contains computed Bessel function values for $x$ ranging from 0 to 99.
- Organized in a table where each row corresponds to a different $x$ value, and each column corresponds to a Bessel function of a particular order.

## Quantifiable Results

- **Range of x:** 0 to 99
- **Orders Calculated:** 0 to 9
- **Precision:** Results calculated with user determined precision, suitable for detailed analysis.


