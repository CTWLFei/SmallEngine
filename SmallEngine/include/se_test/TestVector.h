#include <se_math/Vector.h>

#include <iostream>

void PrintVector2(FVec2 a)
{
	printf("x = %f, y = %f \n", a[0], a[1]);
}

void PrintVector3(FVec3 a)
{
	printf("x = %f, y = %f, z = %f \n", a[0], a[1], a[2]);
}

void PrintVector4(FVec4 a)
{
	printf("x = %f, y = %f, z = %f \n", a[0], a[1], a[2]);
}

void TestVector()
{
	FVec2 vec2a, vec2b;
	vec2a[0] = 1;
	vec2a[1] = 3;
	vec2b[0] = 2;
	vec2b[1] = 4;
	PrintVector2(vec2a + vec2b);
	PrintVector2(vec2a - vec2b);
	PrintVector2(vec2a * vec2b);
	PrintVector2(vec2a / vec2b);
	PrintVector2(vec2a += vec2b);
	PrintVector2(vec2a -= vec2b);
	PrintVector2(vec2a *= vec2b);
	PrintVector2(vec2a /= vec2b);
}