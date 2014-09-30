#ifndef CSG_OBJECT_H
#define CSG_OBJECT_H

#include "Vertex.h"
#include "Polygon.h"
#include "Segment.h"
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include "TriangulatedSurface.h"

namespace enterprise_manager {

// The class Object represents an object for use in CSG operations. Algorithms
// taken from "Constructive Solid Geometry for Polyhedral Objects" by Laidlaw,
// Trumbore and Hughes.
template <class T> class Object
{
public:

	Object();

	virtual                     ~Object();

	bool                        failed;

	void                        RemoveCollinearPolygons();

	static void                 SetTolerance(Object& objectA, Object& objectB);

	// Test if the object is valid.
	Obool                       IsValid(Obool operandCheck = true) const;

	Obool                       HasValidTopology();

	void                        MakeValid();

	static Object*              CreateFromIndexedFaceSet(const std::vector<Vec3<T> >& coord, const std::vector<Oint>& coordIndex, Obool ccw, Obool convex);

	//for tesing purposes
	static Object*              CreateFromVertices(vector<Vertex<T>*> vertices);

	// Create the union of two objects. After the operation objectA will contain
	// the union (A U B), objectB will be an invalid object.
	static void                 CreateUnion(Object& objectA, Object& objectB);

	// Create the intersection of two objects. After the operation objectA will
	// contain the intersection (A ^ B), objectB will be an invalid object.
	static void                 CreateIntersection(Object& objectA, Object& objectB);

	// Create the difference of two objects. After the operation objectA will
	// contain the difference (A - B), objectB will be an invalid object.
	static void                 CreateDifference(Object& objectA, Object& objectB);

	void                        GetFaceSetIndexes(std::vector<Oint>& coordIndex) const;

	void                        GetCoords(std::vector<Vec3<CSGReal> >& coord) const;

	void                        Transform(const Matrix4<T>& matrix);

	inline const Extent<T>&  
		extent() const;
	// Split this object by ObjectB.
	void                        SplitBy(const Object& objectB);

	// Split ObjectA and ObjectB
	static  void                SubdivideObjects(Object& objectA, Object& objectB);
    
	// Make sure that polygons of object are oriented counter-clockwise. 
	// Call it for IfcManifoldSolidBrep subtypes and IfcShellBasedSurfaceModel if they are participating in CSG operations.
	void                        MakeCcw();

	// Make sure that polygons of object are oriented counter-clockwise. Unlike MakeCcw function, 
	// this function is check each polygons in object
	void                        MakeCcwEx();

	// Make object geometry simpler, e.g. unite triangles, etc.
	void                        Simplify(T multiplierUnion = 100);    

	Obool						UnionWithNeighborPolygon(Polygon<T> &polygonA) const;

#ifdef DEBUG
	void                        AddPolygon(vector<Vertex<T>*> vertices);
#endif


	inline const std::vector<Polygon<T>*>&   
		polygon() const;
private:

	void                        CalculateExtents();

	// Merge the polygons og objectB into this object.
	void                        Merge(const Object& objectB);

	// Merge adjacency vertexes in each polygon if distance between vertexes less or equal distanseMerge
	// Function is calculating average point between adjacent vertexes and remove average vertexes on this point (vertex) if
	// adjacency vertexes have equal status   
	//void						MergeAdjacencyVertexs(const T distanseMerge);

	// Merge the polygons og objectB into this object, reversing them in the
	// process.
	void                        MergeReversed(const Object& objectB);  

	inline const std::vector<Vertex<T>*>&
		vertex() const;

	std::vector<Oint>           CreateDeleteList(Ouint deleteMask, const Object& objectB) const;

	// Delete polygons and vertices based on the specified delete mask (bitwise
	// combinations of RELPOS_STATUS).
	static void                 DeletePolygons(Object& objectA, Ouint deleteMaskA, Object& objectB, Ouint deleteMaskB);
	void                        DeletePolygons(const std::vector<Oint> deleteList);

	void                        DeleteUnusedVertices();

	// Mark un-marked vertices according to their status relative to objectB
	// (INSIDE or OUTSIDE).
	void                        MarkVertices(Object& objectB);

	// Build adjacency info for all the vertices in the object.
	void                        BuildVertexAdjacencyInfo();

	// Subdivide polygonA so that it does not intersect B.
	// segmentA and segmentB are results of the intersection routine.
	void                        Subdivide(Polygon<T>& polygonA, const Polygon<T>& polygonB, Segment<T>& segmentA, Segment<T>& segmentB);

	// Find the position of polygonA relative to the object (INSIDE, OUTSIDE, SAME or OPPOSITE)
	RELPOS_STATUS               FindRelativePosition(const Polygon<T>& polygonA) const;

	// Create a vertex on an edge of the polygon and add it to the object if it does not exist.
	Vertex<T>*                  CreateEdgeVertex(const Ray<T>& line, Oint index, T distance, Polygon<T>& polygon); 

	// Create a vertex in the face of the polygon and add it to the object if it does not exist.
	Vertex<T>*                  CreateFaceVertex(const Ray<T>& line, T distance, Polygon<T>& polygon); 

	// Add a sub polygon
	Obool                       AddSubPolygon(Polygon<T>& oldPolygon, Polygon<T>* subPolygon);
	Obool                       CreateSubPolygon(Polygon<T>& oldPolygon, Ouint startIndex, Ouint endIndex, Vertex<T>* newVertex1 = NULL, Vertex<T>* newVertex2 = NULL);

	// Remove a polygon from the object by setting the polygon element to NULL.
	// Must clean up afterwards by calling CleanPolygons
	void                        RemovePolygon(Polygon<T>* polygon);

	// Clean up the polygon list removing NULL entries
	void                        CleanPolygonList();

	// Check if a vertex exists at the specified point. If it does not exists it
	// is created, added to the object and returned. Otherwise the existing
	// vertex is returned.
	Vertex<T>*                  GetCreateVertex(const Vec3<T>& point);

	Vertex<T>*                  GetExistingVertex(const Vec3<T>& point);

	T							MaxDistance();

private:
	std::vector<Vertex<T>*>     _vertex;
	std::vector<Polygon<T>*>    _polygon;
	Extent<T>                   _extent;    

	std::map<std::pair<Oint, Oint>, Oint>
		GetEdgeMap();

	void                        PrepareSimplifyData(Polygon<T>* firstPolygon, Oint firstIndex, std::map<Vertex<T>*, Oint> vertexMap, std::vector<Polygon<T>*>& polygons, std::map<Oint, std::vector<Oint>>& nextIndexMap);
	T                           AngleCriteria(T c, T s, T x, T y);
	std::vector<std::pair<std::vector<Oint>, Obool>>
		GetPerimeters(std::map<Vertex<T>*, Oint> vertexMap, std::map<Oint, Vertex<T>*> indexMap, std::vector<Polygon<T>*> polygons);
	//std::vector<Oint>           GetPerimeters(std::vector<Polygon<T>*>& polygons, std::set<Oint>& usedVertices, std::map<Vertex<T>*, Oint> vertexMap, std::map<Oint, Vertex<T>*> indexMap, std::map<Oint, std::vector<Oint>> nextIndexMap, Obool ccw);

#ifdef DEBUG
	std::vector<Polygon<T>*>    _polygonsDivided;
#endif

	Obool                       CheckInvalidEdges(std::vector<std::pair<Oint, Oint>> invalid_edges);

	Ouint                       _ChooseClosestPolygon(Obool &initialized, vector<Polygon<T>*> &closestPolygons, Vec3<T> &barycenter) const;

	void                        _MakeCcw(const Polygon<T>& polygonA);
	void                        _MakePerimeters(std::map<std::pair<Oint, Oint>, Obool> &edges, std::vector<std::pair<std::vector<Oint>, Obool>> &perimeters);
	void                        _ClearCollinearPoints(std::vector<std::pair<std::vector<Oint>, Obool>> &perimeters, std::map<Oint, Vertex<T>*> &indexMap);

};

} // namespace enterprise_manager

#include "Object.inl"

#endif // CSG_OBJECT_H
