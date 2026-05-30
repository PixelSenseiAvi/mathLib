#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "matrix.h"
#include "SceneGraph.h"

#include <iostream>

int main()
{
    // ----- vectors ------------------------------------------------------
    vec2<float> v1(1.0f, 2.0f);
    vec2<float> v2(3.0f, 4.0f);

    vec3<float> v3(1.0f, 2.0f, 1.5f);
    vec3<float> v4(2.0f, 0.0f, 3.0f);

    vec4<float> v5(1.0f, 2.0f, 1.5f, 5.0f);
    vec4<float> v6(1.0f, 2.0f, 1.5f, 5.0f);

    std::cout << "v1 / 0.5      = " << (v1 / 0.5f) << '\n';
    std::cout << "v1 + v2       = " << (v1 + v2) << '\n';
    std::cout << "v1 cross v2   = " << v1.cross(v2) << '\n';
    std::cout << "v3 + v4       = " << (v3 + v4) << '\n';
    std::cout << "v3 cross v4   = " << v3.cross(v4) << '\n';
    std::cout << "v3 . v4       = " << v3.dot(v4) << '\n';
    std::cout << "v3 length     = " << v3.length() << '\n';
    std::cout << "v3 normalized = " << v3.normalized() << '\n';
    std::cout << "2.0f * v3     = " << (2.0f * v3) << '\n';
    std::cout << "v5 . v6       = " << v5.dot(v6) << '\n';

    // ----- matrices -----------------------------------------------------
    matrix<float, 2, 3> a;
    for (std::size_t i = 0; i < a.rows(); ++i)
        for (std::size_t j = 0; j < a.cols(); ++j)
            a(i, j) = static_cast<float>(i + j);

    matrix<float, 3, 2> b;
    for (std::size_t i = 0; i < b.rows(); ++i)
        for (std::size_t j = 0; j < b.cols(); ++j)
            b(i, j) = static_cast<float>(i * j + 1);

    std::cout << "\nMatrix A (2x3):\n" << a;
    std::cout << "\nMatrix B (3x2):\n" << b;
    std::cout << "\nA * B (2x2):\n" << (a * b);
    std::cout << "\nTranspose of A (3x2):\n" << a.transpose();

    matrix<float, 3, 3> c;
    c(0, 0) = 6; c(0, 1) = 1; c(0, 2) = 1;
    c(1, 0) = 4; c(1, 1) = -2; c(1, 2) = 5;
    c(2, 0) = 2; c(2, 1) = 8; c(2, 2) = 7;
    std::cout << "\ndet(C) = " << c.det() << " (expected -306)\n";

    // ----- scene graph --------------------------------------------------
    SceneNode root;
    SceneNode* child = new SceneNode();
    child->SetTransform(Matrix4::identity());
    root.AddChild(child); // ownership transfers to root
    root.Update(0.0f);
    std::cout << "\nScene graph updated with " << 1 << " child node.\n";

    return 0;
}
