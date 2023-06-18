#include "vec2.h"
#include  "vec3.h"
#include "vec4.h"
#include "matrix.h"
#include <iostream>

int main()
{
    vec2<float> v1(1.0f, 2.0f);
    vec2<float> v2(1.0f, 2.0f);

	vec3<float> v3(1.0f, 2.0f, 1.5f);
    vec3<float> v4(1.0f, 2.0f, 1.5f);
	vec4<float> v6(1.0f, 2.0f, 1.5f, 5.0f);
    vec4<float> v5(1.0f, 2.0f, 1.5f, 5.0f);

    std::cout << "Vector v1 / 0.5: " << (v1 / 0.5) << std::endl;
    
	std::cout << "Vector v3 + v4: " << (v3 + v4) << std::endl; 

	std::cout << "Vector v5 . v6: " << (v5.dot(v6)) << std::endl; 


    matrix<float, 3, 5> matrixOne;
    for (size_t i = 0; i < 3; ++i)
    {
        for (size_t j = 0; j < 5; ++j)
        {
            matrixOne.mat[i][j] = i * j;
        }
    }

    matrix<float, 3, 5> matrixTwo;
    for (size_t i = 0; i < 3; ++i)
    {
        for (size_t j = 0; j < 5; ++j)
        {
            matrixTwo.mat[i][j] = i + j;
        }
    }

    std::cin.get();
    return 0;
}
