#ifndef CSG_VERTEX_H
#define CSG_VERTEX_H

#include "config.h"
#include "DataTypes/Vec3.h"
#include <vector>
#include <limits>


namespace enterprise_manager {

	typedef enum {
		UNKNOWN = 0,
		INSIDE = 1,
		OUTSIDE = 2,
		BOUNDARY = 4,
		SAME = 8,
		OPPOSITE = 16,
	} RELPOS_STATUS;

	typedef enum {
		AB = 0,
		AC,
		BC
	} SIDE_TRIANGLE;

	template <typename T> class Object;
	template <typename T> class Polygon;

	// The class Segment represents a Vertex for use in CSG operations. Algorithms
	// taken from "Constructive Solid Geometry for Polyhedral Objects" by Laidlaw,
	// Trumbore and Hughes.
	template <typename T> class Vertex {
		friend class Object<T>;
		friend class Polygon<T>;

	public:
		inline const Vec3<T>&   point() const;

		// Static template variables to keep tolerances
		static T                tolerance;
		static T                unitTolerance;
		static T                epsilonValue;

		inline void             setStatus(RELPOS_STATUS status);
		inline RELPOS_STATUS    status() const;


		// Test if vertexB lies on vertexA-vertexC line
		static Obool            Collinear(Vertex* vertexA, Vertex* vertexB, Vertex* vertexC);

		Vertex(const Vec3<T>& point);
		virtual                 ~Vertex();

#ifdef DEBUG
		Ouint                   id;
		std::vector<Ouint>      parents;
#endif
	protected:


		// Join adjacent vertexes.
		static void             Join(Vertex* vertexA, Vertex* vertexB);

		// Clear all adjacency information.
		void                    ClearAdjacencyInfo();

		// Mark this vertex and all connected unmarked vertices as status.
		void                    MarkConnectedVertices(RELPOS_STATUS status);

		// Test if the vertex is on the "line of intersection" defined by dir and point.
		Obool                   OnLineOfIntersection(const Vec3<T>& dir, const Vec3<T>& point) const;

		Obool                   OnLine(const Vec3<T>& dir, const Vec3<T>& point) const;

	private:
		Vec3<T>                 _point;
		std::vector<Vertex<T>*> _adjacentVertex;
		RELPOS_STATUS           _status;

		static Obool            IsAltCollinear(const Vertex<T>* A, const Vertex<T>* B, const Vertex<T>* C);
		// Return max side triangle of passed vertexes 
		static SIDE_TRIANGLE    MaxSectionAtVertex(const Vertex<T>* A, const Vertex<T>* B, const Vertex<T>* C);
	};

	template <typename T> Obool Equal(T a, T b) { return (abs(a - b) < Vertex<T>::tolerance); };
	template <typename T> Obool Greater(T a, T b) { return (a > (b + Vertex<T>::tolerance)); };
	template <typename T> Obool Lesser(T a, T b) { return (a < (b - Vertex<T>::tolerance)); };

	template <typename T> Obool Equal(T a, T b, T tolerance) { return (abs(a - b) < tolerance); };
	template <typename T> Obool Greater(T a, T b, T tolerance) { return (a > (b + tolerance)); };
	template <typename T> Obool Lesser(T a, T b, T tolerance) { return (a < (b - tolerance)); };

	template <typename T> Obool UnitEqual(T a, T b) { return (abs(a - b) < Vertex<T>::unitTolerance); }
	template <typename T> Obool UnitGreater(T a, T b) { return (a > (b + Vertex<T>::unitTolerance)); };
	template <typename T> Obool UnitLesser(T a, T b) { return (a < (b - Vertex<T>::unitTolerance)); };

	template <typename T> Obool GT(T a, T b) { return (a >(b + Vertex<T>::tolerance)); };
	template <typename T> Obool GE(T a, T b) { return (a >= (b - Vertex<T>::tolerance)); };
	template <typename T> Obool EQ(T a, T b) { return (abs(a - b) <= Vertex<T>::tolerance); };
	template <typename T> Obool NQ(T a, T b) { return (abs(a - b) > Vertex<T>::tolerance); };
	template <typename T> Obool LE(T a, T b) { return (a <= (b + Vertex<T>::tolerance)); };
	template <typename T> Obool LT(T a, T b) { return (a < (b - Vertex<T>::tolerance)); };

	template <typename T> Obool GT(T a, T b, T tolerance) { return (a >(b + tolerance)); };
	template <typename T> Obool GE(T a, T b, T tolerance) { return (a > (b - tolerance)); };
	template <typename T> Obool EQ(T a, T b, T tolerance) { return (abs(a - b) <= tolerance); };
	template <typename T> Obool NQ(T a, T b, T tolerance) { return (abs(a - b) > tolerance); };
	template <typename T> Obool LE(T a, T b, T tolerance) { return (a < (b - tolerance)); };
	template <typename T> Obool LT(T a, T b, T tolerance) { return (a < (b + tolerance)); };

	template <>
	/*static*/ Odouble Vertex<Odouble>::tolerance = 0.1 / 1000;
	template <>
	/*static*/ Odouble Vertex<Odouble>::unitTolerance = 0.0001;
	template<>
	/*static*/ Odouble Vertex<Odouble>::epsilonValue = std::numeric_limits<Odouble>::epsilon();

	template <>
	/*static*/ Ofloat Vertex<Ofloat>::tolerance = 0.1f / 1000.0f;
	template <>
	/*static*/ Ofloat Vertex<Ofloat>::unitTolerance = 0.0001f;
	template<>
	/*static*/ Ofloat Vertex<Ofloat>::epsilonValue = std::numeric_limits<Ofloat>::epsilon();
} // namespace enterprise_manager

#include "Vertex.inl"


#endif // CSG_VERTEX_H
