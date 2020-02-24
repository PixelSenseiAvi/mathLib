#include "vec2.h"
#include "matrix.h"

int main()
{
	vec2<float> v1(1.0f, 2.0f);

	vec2<float> v2(1.0f, 2.0f);

	std::cout << v1 / .5;
	
	std::array<std::array<float, 5>, 3> matOne;
	for (size_t i = 0; i < 3; ++i)
	{
		std::array<float, 5> arr;
		for (size_t j = 0; j < 5; ++j)
		{
			arr[j] = i * j;
		}
		matOne[i] = arr;
	}
	matrix<float, 5, 3> matrixOne(matOne);

	matrix<float, 5, 3> matrixTwo;
	for (size_t i = 0; i < 3; ++i)
	{
		std::array<float, 5> arr;
		for (size_t j = 0; j < 5; ++j)
		{
			arr[j] = i + j;
		}
		matrixTwo.mat[i] = arr;
	}

	matrix<float, 5, 3> matrixThree;
	matrixThree = matrixTwo / 2;

	std::cout << "Matrix One: "<<matrixOne << std::endl;
	std::cout << "Matrix Two: "<<matrixTwo << std::endl;
	std::cout <<  "Result: "<< matrixThree << std::endl;

	std::cin.get();
	return 0;

}