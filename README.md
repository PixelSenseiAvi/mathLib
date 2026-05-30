# mathLib

A small, header-only C++17 mathematics library for 2D/3D work: fixed-size
vectors, fixed-size matrices, and a simple scene graph. Everything has value
semantics and dimensions are encoded in the type, so size mismatches are caught
at compile time.

## Requirements

- A C++17 compiler (g++, clang++, or MSVC)
- No external dependencies (standard library only)

## Components

| Header         | Provides                                                        |
| -------------- | --------------------------------------------------------------- |
| `vec.h`        | `Vector<T, N>` — generic fixed-size vector (base class)         |
| `vec2.h`       | `vec2<T>` with `.x() / .y()` accessors and 2D `cross`           |
| `vec3.h`       | `vec3<T>` with `.x() / .y() / .z()` accessors and 3D `cross`    |
| `vec4.h`       | `vec4<T>` with `.x() / .y() / .z() / .w()` accessors            |
| `matrix.h`     | `matrix<T, M, N>` — fixed-size matrix                           |
| `SceneGraph.h` | `SceneNode` — hierarchical scene graph                          |
| `Mesh.h`       | Minimal `Mesh` / `OGLRenderer` stubs used by the scene graph    |

## Vectors

```cpp
#include "vec3.h"

vec3<float> a(1, 2, 3);
vec3<float> b(4, 5, 6);

auto sum   = a + b;          // component-wise add
auto diff  = a - b;          // component-wise subtract
auto had   = a * b;          // component-wise (Hadamard) product
auto scaled = a * 2.0f;      // scalar multiply (also 2.0f * a)
float d    = a.dot(b);       // dot product
auto c     = a.cross(b);     // cross product (vec3)
float len  = a.length();     // magnitude
auto unit  = a.normalized(); // unit-length copy
float xs   = a.x();          // named accessor
a[0] = 10;                   // indexed access
```

Also available: `operator+= -= *= /=`, unary `-`, `operator== / !=`,
`lengthSquared()`, and in-place `normalize()`. `vec2::cross` returns the scalar
signed area (z-component of the 3D cross product).

## Matrices

```cpp
#include "matrix.h"

matrix<float, 2, 3> a;
a(0, 0) = 1.0f;                 // (row, col) access

auto i  = matrix<float, 4, 4>::identity();
auto t  = a.transpose();        // 3x2
auto p  = a * b;                // (2x3)*(3x2) -> 2x2, checked at compile time
auto s  = 2.0f * a;             // scalar multiply
float dt = c.det();             // determinant (square matrices only)
```

Dimension mismatches (e.g. multiplying incompatible sizes, or taking the
determinant of a non-square matrix) are compile-time errors.

## Scene graph

```cpp
#include "SceneGraph.h"

SceneNode root;
SceneNode* child = new SceneNode();   // ownership transfers on AddChild
root.AddChild(child);
root.Update(0.0f);                    // propagates world transforms
```

A node's world transform is `parent.worldTransform * localTransform`. `Mesh.h`
provides placeholder `Mesh` / `OGLRenderer` types so the scene graph compiles
standalone; swap them for your real rendering backend.

## Building the demo

```sh
g++ -std=c++17 -Wall -Wextra Source.cpp -o mathlib_demo
./mathlib_demo
```

## License

See [LICENSE](LICENSE).
