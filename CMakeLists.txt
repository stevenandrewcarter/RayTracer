cmake_minimum_required(VERSION 3.6)
project(RayTracer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        main.cpp
        Camera.h
        IntersectTests.h
        Light.h
        LightConstants.h
        Matrix4.h
        Matrix4Operations.h
        PriorityQueue.h
        Ray.h
        Shapes/Shape.h
        Image/Bitmap.h
        Image/Bitmap.cpp
        Maths/Vector.h Shapes/Sphere.cpp Shapes/Sphere.h Shapes/Triangle.cpp Shapes/Triangle.h Shapes/Plane.cpp Shapes/Plane.h Maths/Vector.cpp IntersectTest.cpp)
add_executable(RayTracer ${SOURCE_FILES})