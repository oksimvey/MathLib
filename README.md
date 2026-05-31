<div align="center">

```

    ███╗   ███╗ █████╗ ████████╗██╗  ██╗██╗     ██╗██████╗
    ████╗ ████║██╔══██╗╚══██╔══╝██║  ██║██║     ██║██╔══██╗
    ██╔████╔██║███████║   ██║   ███████║██║     ██║██████╔╝
    ██║╚██╔╝██║██╔══██║   ██║   ██╔══██║██║     ██║██╔══██╗
    ██║ ╚═╝ ██║██║  ██║   ██║   ██║  ██║███████╗██║██████╔╝
    ╚═╝     ╚═╝╚═╝  ╚═╝   ╚═╝   ╚═╝  ╚═╝╚══════╝╚═╝╚═════╝
```

A Mathematics & Physics Library written in QuantC, C, and C++.  
Bindings for **Java**, **Python**, and **JavaScript (WebAssembly)**.

[![Language](https://img.shields.io/badge/Core-QuantC%20%2F%20C%20%2F%20C%2B%2B-blue?style=flat-square)](/)
[![Bindings](https://img.shields.io/badge/Bindings-Java%20%7C%20Python%20%7C%20JS%20(WASM)-green?style=flat-square)](/)
[![License](https://img.shields.io/badge/License-MIT-purple?style=flat-square)](/)

</div>

---

## Overview

MathLib is a general-purpose math and physics library focused on being easy to use without sacrificing correctness or performance. It covers everything from symbolic algebra to rigid body dynamics, and can be called from Java, Python, or JavaScript — no C++ knowledge required.

---

## Features

### 🧮 Computer Algebra System (CAS)
- Symbolic differentiation and integration
- Expression simplification, expansion, factoring
- Taylor series and limit evaluation
- LaTeX and string output

```quantc
expr f = x^3 + 2*x^2 - x + 5;
expr df = diff(f, x);                    // 3x² + 4x - 1
expr area = integrate(f, x, 0, 1);      // exact result
```

### 📐 Linear Algebra
- Vectors (`Vec2`, `Vec3`, `Vec4`, `VecN`) and Matrices (`Mat2`–`Mat4`, `MatNxM`)
- Quaternions and 3D transformations (TRS, affine, projective)
- Decompositions: LU, QR, SVD, Cholesky, Eigendecomposition
- Vector fields: gradient, divergence, curl, Laplacian
- Sparse matrix support

### 🔢 Numerical Methods
- **Equation solving** — Newton-Raphson, Brent, bisection, nonlinear systems
- **Integration** — Gaussian quadrature, adaptive Simpson, Monte Carlo
- **Differentiation** — automatic diff (forward & reverse), finite differences, Jacobians
- **ODEs** — RK4, RK45 (adaptive), Verlet, Leapfrog

### 📊 Statistics
- Descriptive stats, probability distributions, hypothesis testing
- Linear, polynomial, and logistic regression
- FFT and power spectrum analysis

### ⚡ Physics
- **Collision** — AABB and OBB (SAT-based), broad phase with BVH
- **Rigid body dynamics** — impulse solver, joints, friction, restitution
- **Fluids** — SPH and Eulerian (Navier-Stokes) solvers
- **Motion** — kinematics, inverse kinematics (FABRIK), spring-damper systems

### 📈 Functions & Curves
- Special functions: Gamma, Beta, Bessel, Legendre
- Interpolation: cubic spline, Hermite, Catmull-Rom, B-spline, NURBS
- Curve fitting and piecewise function definitions

---

## Language Bindings

### Java
```java
Matrix A = Matrix.of(new double[][]{{2, 1}, {5, 3}});
Matrix inv = A.inverse();
```

### Python
```python
import mathlib as ml

field = ml.VectorField(lambda x, y, z: (y, -x, 0))
curl = field.curl(at=(1, 2, 0))  # (0, 0, -2)
```

### JavaScript (WebAssembly)
```js
import MathLib from 'mathlib-wasm';

const lib = await MathLib.init();
const q = lib.Quaternion.fromAxisAngle([0, 1, 0], Math.PI / 2);
```

### QuantC (native)
```quantc
matrix A = [[1, 2], [3, 4]];
vector b = [5, 6];
vector x = solve(A, b);
```

---

## Building

**Requirements:** C++17 compiler, CMake ≥ 3.20, QuantC compiler (`qcc`, included in `tools/`)

```bash
git clone https://github.com/yourname/mathlib.git
cd mathlib
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel
./build/tests/run_all
```

**WebAssembly:**
```bash
emcmake cmake -B build-wasm -DMATHLIB_TARGET=WASM
cmake --build build-wasm
```

**Python bindings:**
```bash
cd bindings/python && pip install .
```

---

## License

MIT — see [`LICENSE`](./LICENSE).
