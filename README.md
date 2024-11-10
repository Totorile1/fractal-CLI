# Fractal-CLI

**Fractal-CLI** is a fast and highly customizable command-line interface tool for exploring and rendering fractals, written in C. It supports a variety of fractal types, rendering modes, and interactive controls.

## Features
- **Mandelbrot and Julia Sets**: Explore two classic fractals with ease.
- **Interactive Controls**: Pan, zoom, and adjust iterations in real time.
- **Configurable Output**: Adjust colors, viewport, resolution, and more.
- **Fast Performance**: Optimized for speed using `-Ofast` for quick rendering.

## Installation

### Quick Start
```bash
git clone https://github.com/Totorile1/fractal-CLI.git
cd fractal-CLI
gcc mandelbrot.c -Ofast -lm -o fractal
```

### Detailed Installation
1. **Clone the repository**: Download the source code from GitHub.
2. **Compile the code**: Use a C compiler (e.g., `gcc`). Optimizing with `-Ofast` is recommended for best performance.
   - Example with `gcc`:
     ```bash
     gcc mandelbrot.c -Ofast -lm -o fractal
     ```
3. **Dependencies**: Ensure you link against the math library (`-lm`).

## Usage

```bash
fractal [OPTIONS]
```

Fractal-CLI generates and renders fractal images based on the selected options. By default, it generates the Mandelbrot set.

### Options

| Option            | Description                                                                                         |
|-------------------|-----------------------------------------------------------------------------------------------------|
| `-j <real> <imaginary>` | Set Julia set mode with the specified complex number (e.g., `-j -0.55268 0.959456`).        |
| `-xmin <value>`   | Set the minimum x-coordinate for the fractal viewport.                                              |
| `-xmax <value>`   | Set the maximum x-coordinate for the fractal viewport.                                              |
| `-ymin <value>`   | Set the minimum y-coordinate for the fractal viewport.                                              |
| `-ymax <value>`   | Set the maximum y-coordinate for the fractal viewport.                                              |
| `-c`              | Clear the screen before rendering each frame.                                                       |
| `-s <scale>`      | Set the scale multiplier for image resolution (default: 10).                                        |
| `-p <string>`     | Set the character used for fractal points (default: `█`).                                           |
| `-cs <value>`     | Set color shift value to adjust fractal colors.                                                     |
| `-f`              | Render a single frame and exit.                                                                     |
| `-i <value>`      | Set the number of iterations for fractal calculation.                                               |
| `-m <mode>`       | Set rendering mode. Options include: `color` (default), `number`, `red`, `green`, `blue`, `gray`.   |
| `-h`, `--help`    | Display help message and exit.                                                                      |

### Controls (for interactive mode)
When `-f` is not specified, the following keyboard controls are available for exploring the fractal interactively:

- **Movement**: `w` (up), `s` (down), `a` (left), `d` (right)
- **Zoom**: `r` (zoom in), `f` (zoom out)
- **Adjust Iterations**: `q` (decrease by 100), `e` (increase by 100)
- **Exit**: `x`

### Examples
Render a Julia set with custom viewport and high resolution:
```bash
./fractal -j -0.55268 0.959456 -xmin -2.1 -xmax 0.7 -ymin -1.5 -ymax 1.5 -s 20 -m color
```

Render the Mandelbrot set with red color mode:
```bash
./fractal -c -p '#' -m red
```
Render a big and detailled Mandelbrot set:
```bash
./fractal -c -s 20 -i 1000
```
