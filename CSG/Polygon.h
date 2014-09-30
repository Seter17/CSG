#ifndef CSG_POLYGON_H
#define CSG_POLYGON_H

#include "Vertex.h"
#include "Extent.h"
#include <vector>

namespace enterprise_manager {

template <class T> class Segment;

typedef enum {
    COPLANAR = 0,
    INTERSECT,
    NOT_INTERSECT
} INTERSECT_TYPE;

template <class T>
struct Ray
{
    Vec3<T> point;
    Vec3<T> dir;

    // Calculate the distance from v1 to point along dir
    T CalcVertexDistanceToPoint(const Vertex<T>& v1) {
        return (v1.point()-point)*dir;
    }

    // Calculate the distance from the intersection point between v1 and v2 at
    // distances d1 and d2 from the intersection point to a specified point.
    T CalcVertexIntersectionDistanceToPoint(T d1, T d2, const Vertex<T>& v1, const Vertex<T>& v2) {
            T ad1 = fabs(d1);
            T ad2 = fabs(d2);
            Vec3<T> intersection = v1.point()*(ad2/(ad1+ad2))+v2.point()*(ad1/(ad1+ad2));
            return (intersection-point)*dir;
    }
};

// The class Polygon represents a polygon for use in CSG operations. Algorithms
// taken from "Constructive Solid Geometry for Polyhedral Objects" by Laidlaw,
// Trumbore and Hughes.
template <class T> class Polygon
{
    friend class Object<T>;
    friend class Segment<T>;

public:
    Obool                   IsPlanar() const;
    Obool                   IsConvex() const;
    Obool                   IsCollinear();
	void					RemoveCollinearVertex(const Oint indexVrtexA, const Oint indexVrtexB, const Oint indexVrtexC);
    Obool                   IsCCW(const Vec3<CSGReal>& direction);
    void                    Reverse();
    void                    CheckCollinear();
    void                    AddVertices(const Polygon<T>* poly);
	
	//Find min side of polygon and do shift barycenter to this way.
	//If barycenter shifted and still  be inside this polygon - return true.
	//If barycenter out of range this polygon - return false and barycenter don't changed 
	Obool					ShiftBaryCenterToMinSide(Vec3<T> &barycenter) const;
	
	//!Shift barycenter on shiftForBaryCenter value.
	/*!
	\param barycenter the start point for shifting
	\param shiftForBaryCenter the value which adding to barycenter
	\return Return true if shift barycenter succeed, otherwise (if new barycenter out of range)return false and barycenter not modified.  
	/*! \brief 
	*	If new value of barycenter out of range polygon (it is possible in case extended polygon) 
	*	try to shift barycenter to minimum side of polygon and try again shift barycenter on shiftForBaryCenter.  
	*/
	Obool					GetNewCenter(Vec3<T> &barycenter, const Vec3<T>	&shiftForBaryCenter) const;
    
	std::pair<Vertex<T>,Vertex<T>>
							FindMaxSegment() const;

	Obool					isHasVertex(const Vertex<T> &vertexB, Ouint *indexEqualVertex = NULL) const;


    inline const std::vector<Vertex<T>*>&
        vertex() const;

    explicit                Polygon(const std::vector<Vertex<T>*>& vertices, Oint index);

    Obool                   IsCoplanar(const Polygon<T>* other);

    // Test if polygonA and polygonB intersects. If the routine returns
    // INTERSECT, the Segment structures are filled to be used for subdivision.
    static INTERSECT_TYPE   Intersect(const Polygon<T>& polygonA, const Polygon<T>& polygonB, Segment<T>& segmentA, Segment<T>& segmentB);

    INTERSECT_TYPE          DistancesFromVerticesToPolygonPlane(const Polygon<T>& polygon, std::vector<T>& distances, T intersection_tolerance) const;

    void                    SegmentWithIntesectionLine(std::vector<T> &distancesA, Ray<T>& intesectionLine, Segment<T> &segmentA, T distance_tolerance) const;

protected:  
    explicit                Polygon(const std::vector<Vertex<T>*>& vertices, Oint index, const Polygon<T>& original);
    virtual                 ~Polygon();

    Obool                   IsEqual(const Polygon<T>& other) const;

    // Calculates plane equation.
    void                    CalculatePlaneEquation();
    // Calculates plane equation by 3 first points.
    void                    CalculatePlaneEquation3();

    // Calculate polygon extents.
    void                    CalculateExtents();

    // Find the distance from pointB to the plane defined by polygonA.
    static T                PlaneToPointDistance(const Polygon<T>& polygonA, const Vec3<T>& pointB);

    // Calculate the line of intersection between the two polygons, defined by a
    // point and a direction.
    static void             CalcLineOfIntersection(const Polygon<T>& polygonA, const Polygon<T>& polygonB, Ray<T>& intesectionLine);

    // Calculate the barycenter of the polygon.
    Vec3<T>                 CalcBarycenter() const;
	
	// Calculate shift for barycenter. Needed so as to shift barycenter and for that would point does not belong to the boundary     
	// point - projection baryCenter on segment v1 (to the normal vector from the point (baryCenter) to the segment (v1))
	Vec3<T>					CalcShiftBaryCenter(const Vec3<T>& v2, const Vec3<T>& v1, const Vec3<T>& point, const Vec3<T>& baryCenter ) const;

	//Return new center for extended polygon. Find minimum side of polygon and shift barycenter at this direction
	Vec3<T>					CenterForExtendedPolygon(const Vec3<T> *oldBaryCenter=NULL) const;


    // Find the intersection distance between a ray with specified origin and
    // direction and the plane defined by the polygon.
    T                       IntersectRayWithPlane(const Vec3<T>& rayOrigin, const Vec3<T>& rayDir) const;

    // Find the position of a specified point relative to this polygon (INSIDE,
    // OUTSIDE or BOUNDARY).
    RELPOS_STATUS           FindRelativePosition(const Vec3<T>& point) const; 
    void                    FindProjectionAxes(const Vec3<T>& normal, Ochar& ix, Ochar& iy) const;
    RELPOS_STATUS           _RelativePosition(const Vec3<T> &point, Ochar iy, Ochar ix) const;

    Obool                   IsInsideTriangle(const Vec3<T>& requiredPoint,
                                             const Vec3<T>& firstVertex,
                                             const Vec3<T>& secondVertex, 
                                             const Vec3<T>& thirdVertex, 
                                             Ochar indexAxisX, 
                                             Ochar indexAxisY) const;

    // Test if the polygon contains unmarked vertices.
    Obool                   HasUnmarkedVertices() const;

    // Build adjacency info for all vertices in the polygon.
    void                    BuildVertexAdjacencyInfo();

    // Get the next index (returning 0 the index is the index of the last vertex
    // in the polygon).
    inline Ouint            PrevIndex(Ouint index) const;

    // Get the prev index (returning the index of the last vertex in the polygon
    // if index is zero).
    inline Ouint            NextIndex(Ouint index) const;

    inline const Extent<T>&  
                            extent() const;

    inline const Vec3<T>&   normal() const;

    inline const T          d() const;

    inline void             setIndex(Oint index);

    inline const int        index() const;

    //Return true if triangle not in order of tolerance
    inline Obool            IsMeaning() const;

    //Calculate signed area. Uses cache.
    inline T                Area() const;

    //Orders to re-fill cache data on demand
    void                    RefilCache();

    //Check if polygons touch each other (even vertex touch return true)
    Obool                   IsAdjacent(const Polygon<T> & polygon) const;

    //Determines whether a point belongs to the polygon  
    Obool					PointInsidePolygon(const Vec3<T>& point) const;
private:
    Polygon();
	
	std::vector<Vertex<T>*> _vertex;
    Extent<T>               _extent;

    // Plane equation ax+by+cz+d = 0 where (a,b,c) = normal
    Vec3<T>                 _normal;
    T                       _d;

    // the index of the Polygon into the associated array. Used to quickly remove it from the list.
    Oint                    _index; 
    
    mutable T               _area;
    mutable Obool           _isAreaCached;

	void                    RemoveVertex(Oint index);


	std::string             toString() const;

};

} // namespace enterprise_manager

#include "Polygon.inl"

#endif // CSG_POLYGON_H
