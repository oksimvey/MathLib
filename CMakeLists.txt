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
        main/math/transformations/ITransformation.h
        main/math/quaternions/QuaternionF.h
        main/rendering/renderable/IRenderableInstance.h
        main/rendering/renderable/Renderable2DInstance.h
        main/rendering/screen/IScreen.h
        main/math/parameters/IColor.h
        main/math/parameters/ConstantColor.h
        main/math/parameters/IRenderParams.h
        main/math/parameters/ConstantRenderParams.h
        main/rendering/renderable/Renderable2DCurve.h
        main/rendering/renderable/Renderable2DFrag.h
        main/math/curves/ICurve.h
        main/math/curves/Static2DCurve.h
        main/math/curves/Dynamic2DCurve.h
        main/math/curves/Static3DCurve.h
        main/math/curves/Dynamic3DCurve.h
        main/math/surfaces/ISurface.h
        main/rendering/renderable/Renderable2DObject.h
        main/math/surfaces/Static2DSurface.h
        main/math/surfaces/Static3DSurface.h
        main/math/surfaces/Dynamic3DSurface.h
        main/math/surfaces/Dynamic2DSurface.h
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
