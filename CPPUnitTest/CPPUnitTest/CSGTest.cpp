#include "CSGTest.h"
#include "Object.h"

using namespace std;

CSGTest::CSGTest(void) {}


CSGTest::~CSGTest(void) {

}

void CSGTest::IntersectionTest() {
	_LoadPairObjects("input/cube_pyramid_1.txt", "output/outputI.txt", INTERSECTION);
}

void CSGTest::UnioinTest() {
	_LoadPairObjects("input/cube_pyramid_1.txt", "output/outputU.txt", UNION);
}

void CSGTest::DifferenceTest() {
	_LoadPairObjects("input/cube_pyramid_1.txt", "output/outputD.txt", DIFFERENCE);
}

void CSGTest::DetectIntersection() {
	_LoadPairObjects("input/cubes.txt", "output/no_intersections.txt", INTERSECTION);
}

void CSGTest::ToleranceTest() {
	_LoadPairObjects("input/beam_cone_vertex_touch.txt", "output/outputToleranceU.txt", UNION);
	_LoadPairObjects("input/beam_cone_vertex_touch.txt", "output/outputToleranceD.txt", DIFFERENCE);
	_LoadPairObjects("input/beam_cone_vertex_touch.txt", "output/outputToleranceI.txt", INTERSECTION);
}

void CSGTest::SplitTest() {
	_LoadPairObjects("input/cube_pyramid_1.txt", "output/outputSplit1.txt", SPLIT_FIRST);
	_LoadPairObjects("input/cube_pyramid_1.txt", "output/outputSplit2.txt", SPLIT_SECOND);
}

void CSGTest::SubdivideTest() {
	_LoadPairObjects("input/cube_pyramid_1.txt", "output/outputSubdivide1.txt", SUBDIVIDE_FIRST);
	_LoadPairObjects("input/cube_pyramid_1.txt", "output/outputSubdivide2.txt", SUBDIVIDE_SECOND);
}

void CSGTest() {

}

void CSGTest::_LoadObject(const string & input, const string& output) {
	vector<enterprise_manager::Object<Odouble>*> objects;
	parser.ReadTestFile(input, objects);
	if (objects.size() != 1)
		return;

	parser.WriteTestFile(objects, output);
	parser.ClearObjects(objects);
}

void CSGTest::_LoadPairObjects(const string& input, const string& output, Operation operation) {
	vector<enterprise_manager::Object<Odouble>*> objects;
	parser.ReadTestFile(input, objects);

	if (objects.size() != 2) return;

	switch (operation) {
	case UNION:
		enterprise_manager::Object<Odouble>::CreateUnion(*objects[0], *objects[1]);
		break;
	case DIFFERENCE:
		enterprise_manager::Object<Odouble>::CreateDifference(*objects[0], *objects[1]);
		break;
	case INTERSECTION:
		enterprise_manager::Object<Odouble>::CreateIntersection(*objects[0], *objects[1]);
		break;
	case SPLIT_FIRST:
		objects[0]->SplitBy(*objects[1]);
		break;
	case SPLIT_SECOND:
		objects[1]->SplitBy(*objects[0]);
		std::swap(objects[0], objects[1]);
		break;
	case SUBDIVIDE_FIRST:
		enterprise_manager::Object<Odouble>::SubdivideObjects(*objects[0], *objects[1]);
		break;
	case SUBDIVIDE_SECOND:
		enterprise_manager::Object<Odouble>::SubdivideObjects(*objects[0], *objects[1]);
		std::swap(objects[0], objects[1]);
		break;
	}

	delete objects[1];
	objects.erase(objects.begin() + 1);

	parser.WriteTestFile(objects, output);
	parser.ClearObjects(objects);
}

