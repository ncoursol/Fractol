# Fractol

## Introduction
This project is an introduction to graphical programming, complex numbers, and various optimization issues.

42 subject: [https://cdn.intra.42.fr/pdf/pdf/84885/en.subject.pdf](https://cdn.intra.42.fr/pdf/pdf/1823/fract_ol.fr.pdf)

The goal here is to create a small software application for exploring fractals on different sets of fractals such as Mandelbrot and Julia.

## Content
It is possible to display 4 different types of fractals:
  - Julia
  - Mandelbrot
  - Burning Ship
  - Multibrot (Mandelbrot variations)

> [!NOTE]
> Due to hardware constraints and increased complexity, the Multibrot set may be slower than the other available sets.

Here is the list of actions available during the rendering of the fractals:
  - The mouse wheel allows zooming in and out, and this can be done almost infinitely (limited by machine capabilities).
  - 'Q', 'E' - change the fractal set (see list above).
  - 'Z', 'X' - ...
  - 'R', 'G', 'B' - change the color of the fractals (red/green/blue).
  - 'UP', 'DOWN', 'LEFT', 'RIGHT' - move horizontally and vertically within the fractal.
  - 'W', 'S' - vary the color according to a gradient.
  - 'A', 'D' - change the coloring mode.
  - 'SPACE' - lock/unlock the variation of the set (Julia only).
  - '+', '-' - Increase or decrease the number of iterations/depth of the fractal (beyond a certain technical threshold, it affects performance).
  - 'ESC' - Quit the program.
  - 'Z', 'X' - (only for Mandelbrot) switch from Mandelbrot to its multi-branch variant (Multibrot). 'Z' and 'X' allow changing the number of branches.

## Run program
Compile using the Makefile:
`make` / `make re`

Usage : `./fractol [fractal_name]`
with fractale_name:
  - Mandelbrot
  - Julia
  - BurningShip

> [!NOTE]
> For the Multibrot set, you have to select Mandelbrot and change the number of branches with 'Z' and 'X'.

## Screenshots

![Picture 1](pic/screenshot_1.png)

![Picture 2](pic/screenshot_2.png)

![Picture 3](pic/screenshot_3.png)

![Picture 4](pic/screenshot_4.png)

![Picture 5](pic/screenshot_5.png)
