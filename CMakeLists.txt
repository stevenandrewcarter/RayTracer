cmake_minimum_required(VERSION 3.6)
project(RayTracer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        src/main.cpp
        src/Camera.h
        src/Shapes/Light.h
        src/Shapes/LightConstants.h
        src/Maths/Matrix4.h
        src/Maths/Matrix4Operations.h
        src/PriorityQueue.h
        src/Maths/Ray.h
        src/Shapes/Shape.h
        src/Image/Bitmap.h
        src/Image/Bitmap.cpp
        src/Maths/Vector.h
        src/Shapes/Sphere.cpp
        src/Shapes/Sphere.h
        src/Shapes/Triangle.cpp
        src/Shapes/Triangle.h
        src/Shapes/Plane.cpp
        src/Shapes/Plane.h
        src/Maths/Vector.cpp
        src/Shapes/World.cpp
        src/Shapes/World.h
        src/Shapes/Light.cpp
        src/Camera.cpp)
add_executable(RayTracer ${SOURCE_FILES})