#pragma once
#include "FileManager.h"

class CSGTest {
public:
	CSGTest(void);
	~CSGTest(void);

	void IntersectionTest();

	void UnioinTest();

	void DifferenceTest();

	void DetectIntersection();

	void ToleranceTest();

	void SplitTest();

	void SubdivideTest();

private:
	enum Operation { UNION, DIFFERENCE, INTERSECTION, SPLIT_FIRST, SPLIT_SECOND, SUBDIVIDE_FIRST, SUBDIVIDE_SECOND, NONE };
	FileManager parser;
	void _LoadObject(const string& input, const string& output);
	void _LoadPairObjects(const string& input, const string& output, Operation operation);
};

