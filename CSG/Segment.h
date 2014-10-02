#ifndef CSG_SEGMENT_H
#define CSG_SEGMENT_H

#include <vector>

namespace enterprise_manager {

	template <class T> class Object;
	template <class T> class Polygon;

	/** The class Segment represents a line segment for use when intersection Polygons
	  Algorithms taken from "Constructive Solid Geometry for Polyhedral Objects"
	  by Laidlaw, Trumbore and Hughes
	  */
	template <class T> class Segment {
		friend class Object<T>;
		friend class Polygon<T>;

	public:
		static std::string IntersectionType(Oint it);


		// Constructor.
		Segment();
		/// Destructor.
		virtual               ~Segment();

	protected:

		enum POINT_DESCRIPTOR {
			VERTEX = 0,
			EDGE = 1,
			FACE = 2
		};

		enum INTERSECTION_TYPE {
			VERTEX_VERTEX_VERTEX = 0,                     //1   0
			VERTEX_EDGE_VERTEX = EDGE << 2,                 //2   4
			VERTEX_EDGE_EDGE = (EDGE << 2) + EDGE,            //3   5
			VERTEX_FACE_VERTEX = FACE << 2,                 //4   8
			VERTEX_FACE_EDGE = (FACE << 2) + EDGE,            //5   9
			VERTEX_FACE_FACE = (FACE << 2) + FACE,            //6   10
			EDGE_EDGE_VERTEX = (EDGE << 4) + (EDGE << 2),       //S   20
			EDGE_EDGE_EDGE = (EDGE << 4) + (EDGE << 2) + EDGE,    //7   21
			EDGE_FACE_VERTEX = (EDGE << 4) + (FACE << 2),       //S   24
			EDGE_FACE_EDGE = (EDGE << 4) + (FACE << 2) + EDGE,    //8   25
			EDGE_FACE_FACE = (EDGE << 4) + (FACE << 2) + FACE,    //9   26
			FACE_FACE_VERTEX = (FACE << 4) + (FACE << 2),       //S   40
			FACE_FACE_EDGE = (FACE << 4) + (FACE << 2) + EDGE,    //S   41
			FACE_FACE_FACE = (FACE << 4) + (FACE << 2) + FACE,    //10  42
		};


		//specify that the start or end intersection is of vertex type with the given index and distance
		//start intersection is set unless it has already been specified 
		void                  SetVertexIntersection(Ouint index, T distance);

		//specify that the start or end intersection is of edge type with the given index and distance
		//start intersection is set unless it has already been specified 
		void                  SetEdgeIntersection(Ouint index, T distance);

		//set the midpoint intersection type based on the start and end intersection types
		//max index specifies the index of the last vertex in the assosiated polygon
		void                  SetIntersectionMidpoint(Ouint maxIndex);

		//check if an intersection has been found (and set)
		bool                  IntersectionFound();

		//test if two segments overlap
		static Obool          Overlap(const Segment& segmentA, const Segment& segmentB);

		//modify this segment to become the intersection of this segment and segmentB
		void                  FindIntersection(const Segment& segmentB, const Polygon<T>& polygonA);

		//get the intersection type based on start-, mid- and endpoint types
		Oint                  IntersectionType();

		//accessors / mutators
		inline Ouint          startIndex() const;
		inline Ouint          endIndex() const;
		inline T              startDistance() const;
		inline T              endDistance() const;

		inline POINT_DESCRIPTOR
			midpointType() const;

	private:

		//distance of start of segment from P on the line of intersection
		T                     _startDistance;

		//distance of end of segment from P on the line of intersection
		T                     _endDistance;

		//descriptors for starting, middle, and ending points
		POINT_DESCRIPTOR      _startpointType;
		POINT_DESCRIPTOR      _midpointType;
		POINT_DESCRIPTOR      _endpointType;

		//index of polygon vertex near start point
		Ouint                 _startIndex;

		//index of polygon vertex near end point
		Ouint                 _endIndex;

	};

} // namespace enterprise_manager

#include "Segment.inl"

#endif // CSG_SEGMENT_H
