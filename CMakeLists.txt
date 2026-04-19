cmake_minimum_required(VERSION 3.20)
project(MathLib_main)

set(CMAKE_CXX_STANDARD 17)

add_executable(MathLib_main
        glad/src/glad.c
        main/init.cpp

        main/math/calculus/Derivation.cpp
        main/math/calculus/Integration.cpp
        main/math/curves/BezierCurve.cpp
        main/math/curves/Curve.cpp
        main/math/vectors/2DVector.cpp
        main/math/vectors/3DVector.cpp
        main/math/MathUtils.cpp
        main/physics/AbstractPhysicsInstance.cpp
        main/rendering/screen/AbstractScreen.cpp
        main/rendering/screen/Screen2D.cpp
        main/rendering/screen/Screen3D.cpp
        main/rendering/RenderingUtils.cpp
        main/math/transformations/LinearTransformation.h
)

target_include_directories(MathLib_main PRIVATE
        include
        main
)

target_include_directories(MathLib_main PRIVATE
        C:/msys64/mingw64/include
)

target_link_libraries(MathLib_main PRIVATE
        C:/msys64/mingw64/lib/libglfw3.a
        opengl32
        gdi32
)
