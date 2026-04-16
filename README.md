A C++ console application that lets you create and interact with a circle object through a simple menu-driven interface. 
It demonstrates object-oriented composition concepts using two core classes: `Point` and `Circle`.

## Project Structure

| File | Description |
|------|-------------|
| `point.h` / `point.cpp` | Defines the `Point` class and supporting types |
| `circle.h` / `circle.cpp` | Defines the `Circle` class, built on top of `Point` |
| `main.cpp` | Handles the menu and user interaction |

## How It Works

On startup, the program creates a circle with radius `2` centered at `(3, 5)`.

The user is presented with a menu of 10 options:

| Option | Description |
|--------|-------------|
| 1 - Check position | Displays the `(x, y)` coordinates of the center |
| 2 - Check radius | Displays the current radius |
| 3 - Check perimeter | Calculates and displays `2 * PI * radius` |
| 4 - Check area | Calculates and displays `PI * radius²` |
| 5 - Check quadrant | Shows which Cartesian quadrant the center is in (`Q1`, `Q2`, `Q3`, or `Q4`) |
| 6 - Change position | Moves the circle by a given `(x, y)` displacement |
| 7 - Change radius | Resizes the circle using a multiplier (`zoom > 0`) |
| 8 - Distance between circles | Prompts for a second circle and reports the distance between their perimeters. Positive = separated, zero = touching, negative = overlapping |
| 9 - Point inside check | Reports whether a given `(x, y)` point lies inside the circle |
| 10 - Exit | Ends the program |

## Classes Overview

### `Point`
- Stores an `(x, y)` position
- Can compute the distance to another point, move by a displacement, and determine which Cartesian quadrant it sits in
- Provides a static `ORIGIN` constant at `(0, 0)`

### `Circle`
- Stores a center (`Point`) and a radius (`float`)
- Supports: `perimeter`, `area`, `move`, `resize`, `contains`, `perimetersDistance`, `position`, `size`, and `quadrant`

### Supporting types (defined in `point.h`)
- `FloatXY` — a simple struct holding `float x` and `float y` values
- `Quadrant` — an enum class with values `Q1`, `Q2`, `Q3`, `Q4`, and `NONE` (for points on an axis)

## Building

### Windows (Git Bash)
```bash
mingw32-make
```

### Linux/macOS
```bash
make
```

## Running

### Windows (Git Bash)
```bash
./circle-manager
```

### Linux/macOS
```bash
./circle-manager
```

## Notes

- Input validation is handled throughout. Invalid entries prompt the user to try again without crashing.
- Screen clearing is handled cross-platform (`cls` on Windows, `clear` on Linux/macOS).
