#include <stdio.h>
#include <math.h>

// define the limits of the integeral [a,b] such that they can be globally accessed and easilly understood
#define a 0 
#define b M_PI

int return_dp();
double f(double theta, double x, int m);
double CTR(double x, int m, int N);
void file_formater(double x, int m, int max_m, int max_x, int dp, int N, FILE *fp);
void header_underline(int max_m, int pad, int dp, FILE *fp);
void convergence_estimator(int max_x, int dp, int N);

int main() {

    // vary paramaters based on desired output
    int dp, max_m = 2, max_x = 20, num_intervals = 100, N = 10000;
    double step_size = (double) max_x / num_intervals; // data type double to better handle potential future changes to solve at irrational intervals 
    char filename[] = "25590_Bessel_output.txt"; // change filename accordingly, maintaining '.txt' suffix

    printf("\nThis program will approximate the Bessel function solutions for 0 <= x <= %i, and 0 <= m <= %i using the composite trapezium rule at N = %i \n", max_x, max_m, N);
    
    // determine the users desired level of precision for the Bessel function solutions
    dp = return_dp();

    FILE *fp;
    fp = fopen(filename, "w");
    // check if the file opened successfully
    if (fp == NULL) {
        printf("Error opening file - please try again \n");
        return 1;
    }

    // loop through the range of x and m values and save the calcuated Bessel function solutions to the file 
    // as both x and m are non-negative for Bessel solutions, the initial iterated value of each loop is set <= 0 to format the header titles (x<=0) and x column (m<=0)
    for (double x = 0 - step_size; x <= max_x; x += step_size) { 
        for (int m = -1; m <= max_m; m++) {
            file_formater(x, m, max_m, max_x, dp, N, fp);
        }
    }

    printf("The Bessel function solutions, to %i dp, have successfully been saved to a file named '%s' \n", dp, filename);
    fclose(fp);

    // estimate the convergence of the Bessel function solutions at the given value of N
    // one may wish to disable this function once they have settled upon a suitable value of N based off their desired precision 
    convergence_estimator(max_x, dp, N); 

    return 0;

}


// function to return the users desired level of precision of the Bessel function solutions while checking for invalid input
int return_dp() {
    
    int dp, assigned, loop;
    
    do {
        loop = 0;
        printf("How many decimal places would you like Bessel function solutions to display to: \n");
        assigned = scanf("%i", &dp); // 'assigned' is the number of successfully read values - 1 if the user enters an integer, else 0
        while (getchar() != '\n'); // clears the input buffer, ensuring any additional characters like newline characters are discarded --> prevents an infinite loop

        if (assigned != 1 || dp < 0) { // checks if the user input is not an integer or is negative
            printf("Invalid input - please enter a positive integer \n");
            loop = 1;
        } else if (dp > 14) {
            printf("Invalid input - the precision requested is greater than the data type double can support\n");
            loop = 1;
        }
    }
    while (loop != 0); // loop until the user enters a valid input

    return dp;
}


// Bessel integrand function 
double f(double theta, double x, int m) {

    double func = (1/M_PI) * cos(m*theta - x*sin(theta));

    return func; 

}


// composite trapezium rule function --> \int_{a}^{b} f(x) dx ~ h/2 * \sum_{n=1}^{N-1} f(a + nh) + f(a + (n+1)h)
// computationally ~2x as fast to calcuate h * ( (f(a) + f(b)) / 2  * \sum_{n=1}^{N-2} f(a + nh) ) 
double CTR(double x, int m, int N) {

	double total = 0;
    double h = (b - a) / (N-1); // calcuate h - width of trapeziums 

    // add the first and last terms to the total and divide by 2 
    total += (f(a, x, m) + f(b, x, m)) / 2;

    // sum over the interiior terms without the half factor, having already calcuated f(a + h*0) and f(a + h*(N-1))
	for (int n = 1; n < N-1; n++) {

		total += f(a + h*n, x, m);
	}   

    total *= h; // multiply the total by h to complete the trapezium rule

	return total;

}


// function to format the output of the Bessel function solutions to the text file
void file_formater(double x, int m, int max_m, int max_x, int dp, int N, FILE *fp) {

    int pad = 3; // padding (number of blank spaces) either side of the outputed value in the file
    int head_diff = dp - 2; // head_diff = len(Bessel output = +0.dp) - len('J_{m}') = (dp + 3) - 5 --> ensures header spacing matches outputed value column width 

    // if x or m <= 0 then the respective title header or x column is outputted else the Bessel function solutions are outputted
    if (x < 0) { 
        if (m < 0) { // if x, m < 0 the header underline is outputted followed by the x column title 
            header_underline(max_m, pad, dp, fp);
            fprintf(fp, "|%*s%s%*s|", pad + 2, "", "x", pad + 2, ""); // len(x output = 00.00) - len('x') = 5 - 1 = 4 so padding = pad +4/2 extra on each side
        } else { // if x < 0, m >= 0 then the Bessel function header is outputted
            fprintf(fp, "|%*sJ_{%d}%*s|", pad + (head_diff - head_diff/2), "", m, pad + head_diff/2, ""); // if head_diff is odd then the extra space is added to the left of the header
        }
    } else {
        if (m < 0) { // if x >= 0, m < 0 then the x value is outputted
            fprintf(fp, "|%*s%05.2f%*s|", pad, "", x, pad, "");
        } else { // if x, m >= 0 then the Bessel function solutions are outputted
            fprintf(fp, "|%*s%+.*f%*s|", pad, "", dp, CTR(x, m, N), pad, "");
        }
    }

    if (m == max_m) { // if m = max_m then the row is complete and a new line is started
        fprintf(fp, "\n"); 
        if (x < 0 || x > max_x - 1e-7) { // if x <= 0 or x >= max_x then the header underline is outputted
            header_underline(max_m, pad, dp, fp);
        } 
    }

}


// function to format the header underline, |-----|, of the file for any given max_m
void header_underline(int max_m, int pad, int dp, FILE *fp) {

    for (int i = 0; i <= max_m + 1; i++) {

        fprintf(fp, "|");
        if (i == 0) { // if i = 0 then the x column is being underlined
            for (int j = 0; j < 5 + 2*pad; j++) { // x col has width of len(x output = 00.00) + 2 * padding on either side = 5 + 2*pad
            fprintf(fp, "-");
            }
        } else { // else the J_{m} columns are being underlined
            for (int j = 0; j < 3 + dp + 2*pad; j++) { // J_{m} col has width of len(Bessel output = +0.dp) + 2 * padding on either side = (dp + 3) + 2*pad
            fprintf(fp, "-");
            }
        }
        fprintf(fp, "|");
    }

    fprintf(fp, "\n");

}

// function to estimate the rough convergence of the Bessel function solutions at the given value of N and N - N_diff
// future renditions may be improved by importing a random module to randomly select the values of x and m to test the convergence of the solutions at 
void convergence_estimator(int max_x, int dp, int N) {

    // declare trial m value and difference in N value to compare the Bessel function solutions at
    int m_trial = 1, x_step = 1, N_diff = 10; // solving for a particualr m should give a good indication of the global convergence while saving computational time
    double difference = 0, avg_difference;

    // loop through a reasonbly disperse range of x values to gauge an average difference between solutions at N and N-N_diff
    for (int x = 1; x <= max_x; x += x_step) { // J_m(x = 0) is a trivial solution of 1 or 0 that even a very low N returns accurately --> skip

        difference += fabs(CTR(x, m_trial, N) - CTR(x, m_trial, N-N_diff));
    }

    avg_difference = difference / max_x;
    int round_int_diff = round(avg_difference * pow(10, dp)); // shift the value of avg_difference dp places to the left and round to the nearest integer

    printf("Convergence: a sampled estimate of the average difference between the Bessel function solutions at N=%i and N-%i, ", N, N_diff); 
    printf("at your desired level of precision of %idp, is %.*f \n", dp, dp, avg_difference);

    printf("Based off this estimation you may wish to consider ");
    if (round_int_diff == 0) { // if the average difference is 0 then the solutions are identical for that level of precision
        printf("decresing the value of N to reduce computational time \n\n");
    } else { // if non zero then the solutions may still be visibly converging at the desired level of precision at the current N value
        printf("increasing the value of N to improve the accuracy of the Bessel function solutions \n\n");
    }

}


