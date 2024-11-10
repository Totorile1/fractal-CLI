#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

/*
 ------------------- Default opions ---------------------
                                                        */
bool fix = false; // renders only one frame and then exit the program
bool julia = false; // renders a Julia set
long double JuliaZ[2]; // 
int IterNum = 100; // number of iterations
int resolution[2]; // resolution
long double xmin = -2.1; // xmin
long double xmax = 0.7; // xmax
long double ymin = -1.5; // ymin
long double ymax = 1.5; // ymax
int scaler = 10; // scales the resolution 
long double delta = 0.2; // Movement 
char pixel[3] = "█"; // pixel
int ColorShift = 0; // Shifts all the color. 0 <= ColorShift < 40.
bool clear = false; // Clears the terminal after each frame
double long sqrt2 = sqrtl(2);
char RenderMode[50] = "color"; // can be color, number, red, blue, green or gray
/*
 ------------------- Code --------------------------------
                                                         */

// Calculates the resolution in function of xmin, xmax, ymin, ymax and scaler
void ResCalc() {
    resolution[0] = round((ymax-ymin)*2*scaler);
    resolution[1] = round((xmax-xmin)*5*scaler); // the 2/5 is the ration of █ 
}
// Each complex number is an array of long double.
// Re(z) is z[0]
// Im(z) is z[1]

// Adds two complex numbers and return a pointer
long double* addc(long double z1[2], long double z2[2]) {
    long double* zptr;
    zptr = (long double*)malloc(2*sizeof(long double));
    zptr[0] = z1[0] + z2[0];
    zptr[1] = z1[1] + z2[1];
    return zptr; // z1 + z2
}

// Multiplies two complex numbers and return a pointer
long double* multc(long double z1[2], long double z2[2]) {
    long double* zptr;
    zptr = (long double*)malloc(2*sizeof(long double));
    // (a + bi)(c + di) = ac + adi + bci - bd = (ac - bd) + (ad + bc)i
    zptr[0] = z1[0]*z2[0] - z1[1]*z2[1];
    zptr[1] = z1[0]*z2[1] + z1[1]*z2[0];
    return zptr; // z1 x z2
}

// Return the absolute value of the complex number
long double absc(long double z[2]) {
    long double temp = z[0]*z[0] + z[1]*z[1];
    return sqrt(temp); // |z|
}

// For Julia's and Mandelbrot's sets calculates the number of iterations needed such that |z| > 2.
int iteration(long double z[2]) {
/*  For Mandelbrot's set and Julia's sets:
 *  Each pixel represents a point on the complex plane. For each pixel, we apply a function f() many times (a maximum of IterNum times) until the absolute value is more than 2. We stop and return this value (0 if we reach IterNum).
 *  f() = z² + c
 *  where c is in Mandelbrot's sets the original value of the pixel and in Julia's sets a fixed complex number. 
 */
    long double start[2];
    if (julia) {
        start[0] = JuliaZ[0];
        start[1] = JuliaZ[1];
    } else {
        start[0] = z[0];
        start[1] = z[1];
    }
    for (int i = 1; i <= IterNum; i++) {
        long double* temp;
        // z² + c
        temp = multc(z,z);
        z = addc(temp, start);
        free(temp);
        if (absc(z) > 2) {
            return i;
        }
    }
    return 0;
}
// prints the helping information
void print_help() {
    printf("Usage: fractal [OPTIONS]\n");
    printf("Generate and render fractal images with configurable parameters.\n\n");
    printf("Default fractal is the Mandelbrot's set.\n");
    printf("Currently supported fractals are Mandelbrot's set and Julia's sets.\n\n");

    printf("Options:\n");
    printf("  -j <real> <imaginary>    Set Julia set mode with the specified complex number (e.g., -0.55268 0.959456).\n");
    printf("  -xmin <value>            Set the minimum x-coordinate for the fractal viewport.\n");
    printf("  -xmax <value>            Set the maximum x-coordinate for the fractal viewport.\n");
    printf("  -ymin <value>            Set the minimum y-coordinate for the fractal viewport.\n");
    printf("  -ymax <value>            Set the maximum y-coordinate for the fractal viewport.\n");
    printf("  -c                       Clear the screen before rendering each frame.\n");
    printf("  -s <scale>               Set the scale multiplier for image resolution (default is 10).\n");
    printf("  -p <string>              Set the string to represent fractal points (default is \"█\").\n");
    printf("  -cs <value>              Set the color shift value to alter colors in the render.\n");
    printf("  -f                       Render only one fixed frame and exit the program.\n");
    printf("  -i <value>               Set the number of iterations.\n");
    printf("  -m <mode>                Set the render mode. Options:\n");
    printf("                             'color' (default), 'number', 'red', 'green', 'blue', 'gray'.\n");
    printf("  -h, --help               Display this help message and exit.\n\n");
    printf("Controls (if not using -f):\n");
    printf("  w, s, a, d               Pan the viewport up, down, left, and right.\n");
    printf("  q, e                     Decrease or increase the iteration count by 100.\n");
    printf("  r                        Zoom in on the fractal.\n");
    printf("  f                        Zoom out of the fractal.\n");
    printf("  x                        Exit the program.\n");
    printf("\nExamples:\n");
    printf("  ./fractal -j -0.55268 0.959456 -xmin -2.1 -xmax 0.7 -ymin -1.5 -ymax 1.5 -s 20 -m color\n");
    printf("  ./fractal -c -p '#' -m red -cs 10\n");
    printf("\nNote:\n");
    printf("  Ensure arguments following options are provided. Invalid or missing arguments\n");
    printf("  may lead to undefined behavior or program errors.\n");
}
void render(int array[resolution[0]][resolution[1]]) {
    if (clear) {
    system("clear");
    }
    if (strcmp(RenderMode, "number") == 0) {
        for (int yi = 0; yi < resolution[0]; yi++) {
            for (int xi = 0; xi < resolution[1]; xi++) {
                printf("%d ", array[yi][xi]);
            }
            printf("\n");
        }
    } else if (strcmp(RenderMode, "color") == 0 || strcmp(RenderMode, "colour") == 0) {
        // All 40 rgb values used for the colors. Generated with https://colordesigner.io/color-wheel.
        int color[40][3] = {
            {255, 69, 56},
            {255, 99, 56},
            {255, 129, 56},
            {255, 159, 56},
            {255, 188, 56},
            {255, 218, 56},
            {255, 248, 56},
            {232, 255, 56},
            {202, 255, 56},
            {172, 255, 56},
            {143, 255, 56},
            {113, 255, 56},
            {83, 255, 56},
            {56, 255, 59},
            {56, 255, 89},
            {56, 255, 119},
            {56, 255, 149},
            {56, 255, 178},
            {56, 255, 208},
            {56, 255, 238},
            {56, 242, 255},
            {56, 212, 255},
            {56, 182, 255},
            {56, 152, 255},
            {56, 123, 255},
            {56, 93, 255},
            {56, 63, 255},
            {79, 56, 255},
            {109, 56, 255},
            {139, 56, 255},
            {168, 56, 255},
            {198, 56, 255},
            {228, 56, 255},
            {255, 56, 252},
            {255, 56, 222},
            {255, 56, 192},
            {255, 56, 162},
            {255, 56, 133},
            {255, 56, 103},
            {255, 56, 73}
        };
        for (int yi = 0; yi < resolution[0]; yi++) {
            for (int xi = 0; xi < resolution[1]; xi++) {
                if (array[yi][xi] == 0) {
                    printf(" ");
                } else {
                    printf("\033[38;2;%d;%d;%dm%s", color[(array[yi][xi] + ColorShift) % 40][0], color[(array[yi][xi] + ColorShift) % 40][1], color[(array[yi][xi] + ColorShift) % 40][2], pixel);
                    // \033[38;2;R;G;Bm is the ascii escape code for coloring the text with an RGB values.
                }
            }
            printf("\n");
        }
    } else if (strcmp(RenderMode, "red") == 0) {
        int max = 0;
        for (int yi = 0; yi < resolution[0]; yi++) {
            for (int xi = 0; xi < resolution[1]; xi++) {
                if (array[yi][xi] > max) {
                 max = array[yi][xi];
                 //printf("%d\n",max);
                }
            }
        }
        for (int yi = 0; yi < resolution[0]; yi++) {
            for (int xi = 0; xi < resolution[1]; xi++) {
                array[yi][xi] = round(array[yi][xi]*255/max);
            }
        }
        for (int yi = 0; yi < resolution[0]; yi++) {
            for (int xi = 0; xi < resolution[1]; xi++) {
                if (array[yi][xi] == 0) {
                    printf(" ");
                } else {
                    printf("\033[38;2;%d;0;0m%s", array[yi][xi], pixel);
                }
            }
            printf("\n");
        }
    } else if (strcmp(RenderMode, "green") == 0) {
        int max = 0;
        for (int yi = 0; yi < resolution[0]; yi++) {
            for (int xi = 0; xi < resolution[1]; xi++) {
                if (array[yi][xi] > max) {
                 max = array[yi][xi];
                }
            }
        }
        for (int yi = 0; yi < resolution[0]; yi++) {
            for (int xi = 0; xi < resolution[1]; xi++) {
                array[yi][xi] = array[yi][xi]*255/max;
            }
        }
        for (int yi = 0; yi < resolution[0]; yi++) {
            for (int xi = 0; xi < resolution[1]; xi++) {
                if (array[yi][xi] == 0) {
                    printf(" ");
                } else {
                    printf("\033[38;2;0;%d;0m%s", array[yi][xi], pixel);
                }
            }
            printf("\n");
        }
    } else if (strcmp(RenderMode, "blue") == 0) {
        int max = 0;
        for (int yi = 0; yi < resolution[0]; yi++) {
            for (int xi = 0; xi < resolution[1]; xi++) {
                if (array[yi][xi] > max) {
                 max = array[yi][xi];
                }
            }
        }
        for (int yi = 0; yi < resolution[0]; yi++) {
            for (int xi = 0; xi < resolution[1]; xi++) {
                array[yi][xi] = array[yi][xi]*255/max;
            }
        }
        for (int yi = 0; yi < resolution[0]; yi++) {
            for (int xi = 0; xi < resolution[1]; xi++) {
                if (array[yi][xi] == 0) {
                    printf(" ");
                } else {
                    printf("\033[38;2;0;0;%dm%s", array[yi][xi], pixel);
                }
            }
            printf("\n");
        }
    } else if (strcmp(RenderMode, "grey") == 0 || strcmp(RenderMode, "gray") == 0) {
        int max = 0;
        for (int yi = 0; yi < resolution[0]; yi++) {
            for (int xi = 0; xi < resolution[1]; xi++) {
                if (array[yi][xi] > max) {
                 max = array[yi][xi];
                }
            }
        }
        for (int yi = 0; yi < resolution[0]; yi++) {
            for (int xi = 0; xi < resolution[1]; xi++) {
                array[yi][xi] = array[yi][xi]*255/max;
            }
        }
        for (int yi = 0; yi < resolution[0]; yi++) {
            for (int xi = 0; xi < resolution[1]; xi++) {
                if (array[yi][xi] == 0) {
                    printf(" ");
                } else {
                    printf("\033[38;2;%d;%d;%dm%s", array[yi][xi], array[yi][xi], array[yi][xi], pixel);
                }
            }
        printf("\n");
        }
    } else {
        printf("%s is an invalid render mode!\n", RenderMode);
    }
    printf("\033[0m\n");
    }
// main function
int main(int argc, char** argv) {
    // Processes all the arguments when executing the code
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-j") == 0) {
            julia = true;
            JuliaZ[0] = atof(argv[i+1]);
            JuliaZ[1] = atof(argv[i+2]);
        } else if (strcmp(argv[i], "-xmin") == 0) {
            xmin = atof(argv[i+1]);
        } else if (strcmp(argv[i], "-xmax") == 0) {
            xmax = atof(argv[i+1]);        
        } else if (strcmp(argv[i], "-ymin") == 0) {
            ymin = atof(argv[i+1]);
        } else if (strcmp(argv[i], "-ymax") == 0) {
            ymax = atof(argv[i+1]);
        } else if (strcmp(argv[i], "-c") == 0) {
            clear = true;
        } else if (strcmp(argv[i], "-s") == 0) {
            scaler = atoi(argv[i+1]);
        } else if (strcmp(argv[i], "-p") == 0) {
            strcpy(pixel, argv[i+1]);
        } else if (strcmp(argv[i], "-cs") == 0) {
            ColorShift = atoi(argv[i+1]);
        } else if (strcmp(argv[i], "-f") == 0) {
            fix = true;
        } else if (strcmp(argv[i], "-m") == 0) {
            strcpy(RenderMode, argv[i+1]);
        } else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            print_help();
            exit(0);
        } else if (strcmp(argv[i], "-i") == 0) {
            IterNum = atoi(argv[i+1]);
        } 
    }
    bool first = true; // is it the first time a frame is rendered?
    bool NeedRender = true; // does it needs rendering? 
    ResCalc();
    while (first || !fix) { // if fix == true, it will render only one time because first is allways true at the start
    if (!first) {
        char input[255];
        scanf("%s", input);
        for (int i = 0; input[i] != '\0'; i++) {
            // Movements
            if (input[i] == 'w') {
                NeedRender=true;
                ymin -= delta;
                ymax -= delta;
            } else if (input[i] == 's') {
                NeedRender=true;
                ymin += delta;
                ymax += delta;
            } else if (input[i] == 'a') {
                NeedRender=true;
                xmin -= delta;
                xmax -= delta;
            } else if (input[i] == 'd') {
                NeedRender=true;
                xmin += delta;
                xmax += delta;
            // Quit
            } else if (input[i] == 'x') {
                return 0;
            // Changes the number of iterations
            } else if (input[i] == 'q') {
                IterNum -= 100;
                NeedRender = true;
            } else if (input[i] == 'e') {
                IterNum += 100;
                NeedRender = true;
            // Zoom in
            } else if (input[i] == 'r') {
                long double xdist = (xmax - xmin)/(2*sqrt2);
                long double xcenter = (xmax + xmin)/2;
                xmin = xcenter - xdist;
                xmax = xcenter + xdist;

                long double ydist = (ymax - ymin)/(2*sqrt2);
                long double ycenter = (ymax + ymin)/2;
                ymin = ycenter - ydist;
                ymax = ycenter + ydist;

                delta /= sqrt2;
                NeedRender = true;
            // Zoom out
            } else if (input[i] == 'f') {
                long double xdist = sqrt2*(xmax-xmin)/2;
                long double xcenter = (xmax + xmin)/2;
                xmin = xcenter - xdist;
                xmax = xcenter + xdist;

                long double ydist = sqrt2*(ymax-ymin)/2;
                long double ycenter = (ymax + ymin)/2;
                ymin = ycenter - ydist;
                ymax = ycenter + ydist;

                delta *= sqrt2;
                NeedRender = true;
            }
        }
    }
    if (NeedRender) {
    int grid[resolution[0]][resolution[1]];
    long double deltax = (xmax - xmin)/resolution[1]; 
    long double deltay = (ymax - ymin)/resolution[0];
    long double y = ymin;
    long double x = xmin;
    // Computes everything
    for (int yi = 0; yi < resolution[0]; yi++) {
        for (int xi = 0; xi < resolution[1]; xi++) {
            long double xyi[2];
            xyi[0] = x;
            xyi[1] = y;
            grid[yi][xi] = iteration(xyi);
            x +=  deltax;
        }
    y += deltay;
    x = xmin;
    first = false;
    }
    // And then renders it
    render(grid); 
    NeedRender = false;
    }
    }
    return 0;
}
