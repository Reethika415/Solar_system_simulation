# Solar System Simulation

A 2D solar system simulation built with OpenGL/GLUT in C++.

## Features
- 8 planets orbiting the Sun
- Earth with Moon and 3 satellites
- Saturn with rings
- Animated comet
- Background stars

## Controls
| Key | Action |
|-----|--------|
| `+` | Speed up |
| `-` | Slow down |
| `S` | Stop |
| `R` | Reset speed |
| `ESC` | Exit |

## Requirements
- C++ compiler
- OpenGL
- GLUT library

## How to Compile
```bash
g++ Solar_system_simulation.cpp -o simulation -lGL -lGLU -lglut
