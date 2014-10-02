#include "CSGTest.h"

int main() {
	CSGTest test;
	test.DetectIntersection();
	test.IntersectionTest();
	test.UnioinTest();
	test.DifferenceTest();
	test.ToleranceTest();
	test.SplitTest();
	test.SubdivideTest();
	std::cin.get();

	return 0;
}