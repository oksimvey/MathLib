cmake_minimum_required(VERSION 3.20)
project(MathLib_main)

set(CMAKE_CXX_STANDARD 17)

add_executable(MathLib_main
        glad/src/glad.c
        main/init.cpp

        main/math/MathUtils.cpp
        main/physics/AbstractPhysicsInstance.cpp
        main/rendering/RenderingUtils.cpp
        main/math/transformations/LinearTransformation.h
        main/rendering/screen/AbstractScreen.h
        main/rendering/screen/Screen2D.h
        main/rendering/Line.h
        main/math/calculus/Derivation.h
        main/math/parameters/TimeParameter.h
        main/math/easing/EasingStyle.h
        main/rendering/screen/Screen3D.h
        main/key/KeyInputHandler.h
        main/math/vectors/IVector.h
        main/math/vectors/Vector2D.h
        main/math/vectors/Vector3D.h
        main/math/transformations/Matrix3f.h
        main/math/transformations/ITransformation.h
        main/math/vectors/Vector4D.h
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
