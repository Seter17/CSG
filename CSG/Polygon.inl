#include <iostream>
#include <fstream>

using namespace std;


namespace enterprise_manager {

    template <class T>
    Obool
        Polygon<T>::IsEqual(const Polygon<T>& other) const {
            if (_vertex.size() != other._vertex.size())
                return false;

            Ouint offset = 0;
            for (Ouint i = 0; i < _vertex.size(); ++i) {
                if (_vertex[0] == other._vertex[i]) {
                    offset = i;
                    break;
                }
            }
            for (Ouint i = 0; i < _vertex.size(); ++i) {
                if (_vertex[i] != other._vertex[(i + offset) % _vertex.size()]) {
                    if (!_vertex[i]->_point.Equal(other._vertex[(i + offset) % _vertex.size()]->_point, _vertex[i]->unitTolerance)) {
                        return false;
                    }
                }
            }
            return true;
        }

    template <class T>
    inline Ouint
        Polygon<T>::PrevIndex(Ouint index) const {
            if (index == 0)
                return (Ouint)_vertex.size() - 1;
            return (index - 1);
        }

    template <class T>
    inline Ouint
        Polygon<T>::NextIndex(Ouint index) const {
            if (index == _vertex.size() - 1)
                return 0;
            return (index + 1);
        }

    template <class T>
    inline const std::vector<Vertex<T>*>&
        Polygon<T>::vertex() const {
            return _vertex;
        }

    template <class T>
    inline const Extent<T>&
        Polygon<T>::extent() const {
            return _extent;
        }

    template <class T>
    inline const Vec3<T>&
        Polygon<T>::normal() const {
            return _normal;
        }

    template <class T>
    inline const T
        Polygon<T>::d() const {
            return _d;
        }

    template <class T>
    inline void
        Polygon<T>::setIndex(Oint index) {
            _index = index;
        }

    template <class T>
    Polygon<T>::Polygon(const std::vector<Vertex<T>*>& vertices, Oint index)
        : _vertex(vertices) {
#ifdef ASSERT_CSG
        assert(vertices.size() > 2);
#endif /*ASSERT_CSG*/

        _index = index;

        CalculateExtents();
        CalculatePlaneEquation();
    }

    template <class T>
    Polygon<T>::Polygon(const std::vector<Vertex<T>*>& vertices, Oint index, const Polygon<T>& original)
        : _vertex(vertices) {
#ifdef ASSERT_CSG
        assert(vertices.size() > 2);
#endif /*ASSERT_CSG*/

        _index = index;

        CalculateExtents();
        _normal = original._normal;
        _d = original._d;
    }

    template <class T>
    /* virtual */
    Polygon<T>::~Polygon() {}

    template <class T>
    const int
        Polygon<T>::index() const {
            return _index;
        }

    template <class T>
    void
        Polygon<T>::CalculatePlaneEquation() {
            if (_vertex.size() == 3) {
                CalculatePlaneEquation3();
                return;
            }

            Ouint v0 = 0;
            Ouint v1 = NULL;
            Ouint v2 = NULL;

            T distance = 0;
            for (Ouint i = 1; i < _vertex.size(); i++) {
                T alt = _vertex[v0]->_point.DistanceSqr(_vertex[i]->_point);
                if (alt > distance) {
                    distance = alt;
                    v1 = i;
                }
            }

            distance = 0;
            Vec3<T> lineDirection = (_vertex[v1]->_point - _vertex[v0]->_point);
            lineDirection.Normalize();
            for (Ouint i = 1; i < _vertex.size(); i++) {
                if (i == v1)
                    continue;

                //Vec3<T> projected_v2 = _vertex[v0]->_point + ((_vertex[i]->_point-_vertex[v0]->_point)*lineDirection)*lineDirection;
                //T alt = static_cast<T>(projected_v2.DistanceSqr(_vertex[i]));
                T alt = static_cast<T>(_vertex[i]->_point.DistanceSqr(_vertex[v0]->_point + ((_vertex[i]->_point - _vertex[v0]->_point)*lineDirection)*lineDirection));
                if (alt > distance) {
                    distance = alt;
                    v2 = i;
                }
            }

            if (v2 < v1) {
                Oint tmp = v1;
                v1 = v2;

                v2 = tmp;
            }


            Vec3<T> vv1 = (_vertex[v1]->point() - _vertex[v0]->point());
            Vec3<T> vv2 = (_vertex[v2]->point() - _vertex[v1]->point());
            _normal = vv1.Cross(vv2);
            _normal.Normalize();
            _d = -(_vertex[v0]->point()*_normal);
            //_d = (-(_vertex[v0]->point()*_normal) - (_vertex[v1]->point()*_normal) - (_vertex[v2]->point()*_normal))/3;
            RefilCache();
        }

    template <class T>
    void
        Polygon<T>::CalculatePlaneEquation3() {
            Vec3<T> v1 = (_vertex[1]->point() - _vertex[0]->point());
            Vec3<T> v2 = (_vertex[2]->point() - _vertex[1]->point());
            _normal = v1.Cross(v2);
            _normal.Normalize();
            _d = -(_vertex[0]->point()*_normal);
            RefilCache();
        }

    template <class T>
    void
        Polygon<T>::CalculateExtents() {
            Vec3<T> max = _vertex[0]->point();
            Vec3<T> min = _vertex[0]->point();
            for (Ouint i = 0; i < _vertex.size(); ++i) {
                max.MaxComp(_vertex[i]->point());
                min.MinComp(_vertex[i]->point());
            }
            _extent.setMin(min);
            _extent.setMax(max);
            RefilCache();
        }

    template <class T>
    Obool
        Polygon<T>::IsPlanar() const {
            for (Ouint i = 0; i < _vertex.size(); ++i) {
                //if (!enterprise_manager::Equal(_vertex[i]->point()*_normal + _d,T(0))) {
                if (!enterprise_manager::EQ(_vertex[i]->point()*_normal + _d, T(0), Vertex<T>::tolerance)) {// * 5)) {
                    return false;
                }
            }
            return true;
        }

    template <class T>
    Obool
        Polygon<T>::IsConvex() const {
            /*
            Checking for convexity may be implemented by the analyzing signs of vector products of adjacent edges.
            If the vector product is zero, then adjacent edges are collinear.
            If the vector products for the vertices have different signs, then polygon is not convex.
            If all the signs are positive, the polygon is convex, and bypass vertexes implemented counterclockwise.
            */
            Vec3<T> v0, v1, n;
            Obool allPositive = true;
            Obool allNegative = true;

            v0 = v1 = (_vertex[0]->point() - _vertex[_vertex.size() - 1]->point());
            v0.Normalize(); v1.Normalize();
            for (Ouint i = 1; i < _vertex.size(); ++i) {
                Vec3<T> v2 = (_vertex[i]->point() - _vertex[i - 1]->point());
                v2.Normalize();
                n = v1.Cross(v2);
                n.Normalize();
                //if (n*_normal < 0)
                if (n*_normal < 0) //TODO: validate!
                    //return false;
                    allPositive = false;
                else if (n*_normal > 0)
                    allNegative = false;
                else
                    return false;
                v1 = v2;
            }
            n = v1.Cross(v0);
            n.Normalize();
            if (n*_normal < 0)
                //return false;
                allPositive = false;
            else if (n*_normal > 0)
                allNegative = false;
            else
                return false;
            if ((allPositive  && !allNegative) ||
                (!allPositive && allNegative))
                return true;
            return false;
        }

    template <class T>
    void
        Polygon<T>::RemoveVertex(Oint index) {
            std::vector<Vertex<T>*> vertex_tmp;
            for (Oint j = _vertex.size() - 1; j > index; j--) {
                vertex_tmp.push_back(_vertex[j]);
                _vertex.pop_back();
            }
            _vertex.pop_back();
            for (Oint j = vertex_tmp.size() - 1; j >= 0; j--) {
                _vertex.push_back(vertex_tmp[j]);
            }
            RefilCache();
        }

    template <class T>
    void
        Polygon<T>::RemoveCollinearVertex(const Oint indexVrtexA, const Oint indexVrtexB, const Oint indexVrtexC) {
            switch (Object<T>::MaxSectionAtVertex(_vertex[indexVrtexA], _vertex[indexVrtexB], _vertex[indexVrtexC])) {
                case AB:
                    RemoveVertex(indexVrtexC);
                    break;
                case AC:
                    RemoveVertex(indexVrtexB);
                    break;
                case BC:
                default:
                    RemoveVertex(indexVrtexA);
                    break;
            }
            RefilCache();
        }

    template <class T>
    /*static*/ INTERSECT_TYPE
        Polygon<T>::Intersect(const Polygon<T>& polygonA, const Polygon<T>& polygonB, Segment<T>& segmentA, Segment<T>& segmentB) {
            T intersection_tolerance = Vertex<T>::tolerance; // / 2;
            //check each vertex in polygonA against the plane of polygonB

            std::vector<T> distancesA(polygonA.vertex().size());
            INTERSECT_TYPE intersection = polygonA.DistancesFromVerticesToPolygonPlane(polygonB, distancesA, intersection_tolerance);

            if (intersection != INTERSECT)
                return intersection;

            std::vector<T> distancesB(polygonB.vertex().size());
            intersection = polygonB.DistancesFromVerticesToPolygonPlane(polygonA, distancesB, intersection_tolerance);

            if (intersection != INTERSECT)
                return intersection;
            //  If the preceding tests are inconclusive then we calculate the
            //line off interseetion of the two planes. The line of intersection L is
            //determined by a point P and a direction D. Some segment of this
            //line is interior to or on the perimeter of polygonA, and some segment
            //is interior to or on the perimeter of polygonB

            //calculate the line of intersection (L) between the two polygons
            //L is defined by a point and a direction
            Ray<T> intesectionLine;
            CalcLineOfIntersection(polygonA, polygonB, intesectionLine);

            //T local_tolerance = Vertex<T>::unitTolerance;
            T distance_tolerance = Vertex<T>::tolerance;// / 1.5;

            polygonA.SegmentWithIntesectionLine(distancesA, intesectionLine, segmentA, distance_tolerance);
            polygonB.SegmentWithIntesectionLine(distancesB, intesectionLine, segmentB, distance_tolerance);

            // check if the intersection segments are overlapped
            if (Segment<T>::Overlap(segmentA, segmentB))
                return INTERSECT;

            return NOT_INTERSECT;
        }

    template <class T>
    enterprise_manager::INTERSECT_TYPE
        Polygon<T>::DistancesFromVerticesToPolygonPlane(const Polygon<T>& polygon, std::vector<T>& distances, T intersection_tolerance) const {
            Obool coplanar = true;
            Obool hasPositiveDistances = false;
            Obool hasNegativeDistances = false;
            // calculate distances from A vertexes to plane of B and check if A is intersected by plane of B
            for (Ouint i = 0; i < vertex().size(); ++i) {
                const Vertex<T>& vertexA = *vertex()[i];
                distances[i] = PlaneToPointDistance(polygon, vertexA.point());
                if (!Equal(distances[i], T(0), intersection_tolerance)) {
                    // A vertex is not on the plane B
                    coplanar = false;
                    if (Greater(distances[i], T(0), intersection_tolerance))
                        hasPositiveDistances = true;
                    else
                        hasNegativeDistances = true;
                }
                else {
                    // A vertex is on the plane B
                    hasPositiveDistances = true;
                    hasNegativeDistances = true;
                }
            }
            if (coplanar)
                return COPLANAR;

            if (!hasPositiveDistances || !hasNegativeDistances)
                return NOT_INTERSECT;

            return INTERSECT;
        }

    template <class T>
    /*static*/ T
        Polygon<T>::PlaneToPointDistance(const Polygon<T>& polygonA, const Vec3<T>& pointB) {
            return (polygonA._normal * pointB + polygonA._d);

            /*T A = polygonA.normal()[X];
            T B = polygonA.normal()[Y];
            T C = polygonA.normal()[Z];
            return (A*pointB[X] + B*pointB[X] + C*pointB[Z] + polygonA.d()) / sqrt(A*A+B*B+C*C);*/
        }

    template <class T>
    /*static*/ void
        Polygon<T>::CalcLineOfIntersection(const Polygon<T>& polygonA, const Polygon<T>& polygonB, Ray<T>& ray) {
            const Vec3<T>& nA = polygonA._normal;
            const Vec3<T>& nB = polygonB._normal;
            T dA = polygonA._d;
            T dB = polygonB._d;

            ray.dir = nA.Cross(nB);

            //choose the axis u,v,w so that w is the largest axis of dir
            Oint u = X;
            Oint v = Y;
            Oint w = Z;
            if (fabs(ray.dir[Y]) > fabs(ray.dir[w])) {
                v = w;
                w = Y;
            }
            if (fabs(ray.dir[X]) > fabs(ray.dir[w])) {
                u = w;
                w = X;
            }

            //solve nA*p+dA = 0, nB*p+dB = 0, by setting p[w] = 0;
            //point[u] = (nA[v]*dB - nB[v]*dA) / dir[w];
            //point[v] = (nB[u]*dA - nA[u]*dB) / dir[w];
            ray.point[u] = (dA*nB[v] - dB*nA[v]) / (nA[v] * nB[u] - nA[u] * nB[v]);
            ray.point[v] = (dA*nB[u] - dB*nA[u]) / (nA[u] * nB[v] - nA[v] * nB[u]);
            ray.point[w] = 0;

            ray.dir.Normalize();
        }

    template <class T>
    void
        Polygon<T>::SegmentWithIntesectionLine(std::vector<T> &distancesFromVerticesToPlane, Ray<T>& intesectionRay, Segment<T> &segment, T distance_tolerance) const {
            // define segment of L where polygon A is intersected by B-plane 
            for (Ouint i = 0; i < distancesFromVerticesToPlane.size(); ++i) {
                if (Equal(distancesFromVerticesToPlane[i], T(0), distance_tolerance)) {
                    // intersected in the vertex
                    T distance = intesectionRay.CalcVertexDistanceToPoint(*vertex()[i]);
                    segment.SetVertexIntersection(i, distance);
                }
                else if (i > 0 && !Equal(distancesFromVerticesToPlane[i - 1], T(0), distance_tolerance) && ((distancesFromVerticesToPlane[i] > 0) != (distancesFromVerticesToPlane[i - 1] > 0))) {
                    // intersected on edge [i-1]-[i]
                    T distance = intesectionRay.CalcVertexIntersectionDistanceToPoint(distancesFromVerticesToPlane[i - 1], distancesFromVerticesToPlane[i], *vertex()[i - 1], *vertex()[i]);
                    segment.SetEdgeIntersection(i - 1, distance);
                }
            }
            //check edge [last]-[0]
            Ouint last = (Ouint)distancesFromVerticesToPlane.size() - 1;
            if (!Equal(distancesFromVerticesToPlane[0], T(0), distance_tolerance) && !Equal(distancesFromVerticesToPlane[last], T(0), distance_tolerance) && (distancesFromVerticesToPlane[0] > 0) != (distancesFromVerticesToPlane[last] > 0)) {
                // intersected on edge [last]-[0]
                T distance = intesectionRay.CalcVertexIntersectionDistanceToPoint(distancesFromVerticesToPlane[last], distancesFromVerticesToPlane[0], *vertex()[last], *vertex()[0]);
                segment.SetEdgeIntersection(last, distance);
            }
            if (!segment.IntersectionFound()) {
                //search for vertex A closest to the L
                T minDist = fabs(distancesFromVerticesToPlane[0]);
                int minIndex = 0;
                for (Ouint i = 1; i < distancesFromVerticesToPlane.size(); ++i) {
                    if (fabs(distancesFromVerticesToPlane[i]) < minDist) {
                        minDist = fabs(distancesFromVerticesToPlane[i]);
                        minIndex = i;
                    }
                }
                T distance = intesectionRay.CalcVertexDistanceToPoint(*vertex()[minIndex]);
                segment.SetVertexIntersection(minIndex, distance);
            }
            // define type of intersection (v-v-v; v-e-v; v-f-v; v-f-e; e-f-v; e-f-e)
            segment.SetIntersectionMidpoint(last);
        }

    template <class T>
    Vec3<T>
        Polygon<T>::CalcBarycenter() const {
            Vec3<T> result(0, 0, 0);
            for (Ouint i = 0; i < _vertex.size(); ++i) {
                result += _vertex[i]->point();
            }
            result /= (T)_vertex.size();
            return result;
        }

    template <class T>
    T
        Polygon<T>::IntersectRayWithPlane(const Vec3<T>& rayOrigin, const Vec3<T>& rayDir) const {
            //(rayOrigin + rayDir*t)*normal+d = 0
            return -(rayOrigin * _normal + _d) / (rayDir * _normal);
        }

    template <class T>
    Vec3<T>
        Polygon<T>::CalcShiftBaryCenter(const Vec3<T>& v2, const Vec3<T>& v1, const Vec3<T>& point, const Vec3<T>& baryCenter) const {
            Vec3<T> vecToV1(0, 0, 0);
            vecToV1 = v1 - v2;
            Vec3<T> shiftBaryCenter(0, 0, 0);
            if (shiftBaryCenter.Equal((point - baryCenter), T(0)))
                shiftBaryCenter = vecToV1.Cross(_normal);
            else
                shiftBaryCenter = vecToV1.Cross(point - baryCenter);
            shiftBaryCenter.Normalize();
            //Shift must be not very small, because shift will not have effect and also shift not must be very large, 
            //because new barycenter after shifting may be out of range. Two tolerance is optimal value.
            return shiftBaryCenter * (Vertex<T>::tolerance * 2);
        }

    template <class T>
    RELPOS_STATUS
        Polygon<T>::FindRelativePosition(const Vec3<T>& point) const {
            //find a segment that contains a point 
            if (EQ(point.DistanceToSegment(_vertex[0]->point(), _vertex[_vertex.size() - 1]->point()), T(0))) {
                return BOUNDARY;
            }
            Ochar ix, iy;
            FindProjectionAxes(_normal, ix, iy);

            return _RelativePosition(point, ix, iy);
        }

    template <class T>
    inline void
        Polygon<T>::FindProjectionAxes(const Vec3<T>& normal, Ochar& ix, Ochar& iy) const {
            //find the two major axis for projection  
            Ochar big = (fabs(normal[X]) > fabs(normal[Y])) ?
                ((fabs(normal[X]) > fabs(normal[Z])) ? 0 : 2) :
                ((fabs(normal[Y]) > fabs(normal[Z])) ? 1 : 2);

            switch (big) {
                case 0:
                    ix = 1;
                    iy = 2;
                    break;
                case 1:
                    ix = 0;
                    iy = 2;
                    break;
                case 2:
                    ix = 0;
                    iy = 1;
                    break;
            }
        }

    template <class T>
    RELPOS_STATUS
        Polygon<T>::_RelativePosition(const Vec3<T> &point, Ochar ix, Ochar iy) const {
            Vertex<T>* firstIntersectedA = NULL;
            Vertex<T>* lastIntersectedB = NULL;
            Vertex<T>* A = NULL;
            Vertex<T>* B = NULL;

            Obool c = false;
            Obool vertexHit = false;

            for (Ouint i = 1; i <= _vertex.size(); ++i) {

                Ouint previous = i - 1;
                Ouint current = (i == _vertex.size()) ? 0 : i;

                if (EQ(point.DistanceToSegment(_vertex[previous]->point(), _vertex[current]->point()), T(0))) {
                    return BOUNDARY;
                }

                if (_vertex[previous]->point()[iy] == _vertex[current]->point()[iy])
                    continue;

                if (vertexHit && (A->point()[iy] > point[iy] == _vertex[current]->point()[iy] > point[iy])) {
                    //Common vertex B was hit. And previous segment and new segment are on the one side of the ray so roll back counter (we proved that it was not an intersection)
                    c = !c;
                    vertexHit = false;
                }

                A = _vertex[previous];
                B = _vertex[current];

                bool isBetweenWithRespectToY = (B->point()[iy] > point[iy] != A->point()[iy] > point[iy]);
                bool notFullyOnThRightSide = !(point[ix] > A->point()[ix] && point[ix] > B->point()[ix]);

                if (isBetweenWithRespectToY && notFullyOnThRightSide) {
                    T k = A->point()[ix] + (point[iy] - A->point()[iy])*(B->point()[ix] - A->point()[ix]) / (B->point()[iy] - A->point()[iy]);

                    bool isRayIntersect = point[ix] + Vertex<T>::tolerance < k;

                    if (!isRayIntersect) continue;

                    c = !c; //count as intersection until we proved otherwise
                    if (B->point()[iy] == point[iy]) {
                        vertexHit = true;
                        lastIntersectedB = B;
                    }
                    if (A->point()[iy] == point[iy] && firstIntersectedA == NULL) {
                        firstIntersectedA = A;
                    }
                }
            }

            // if the last meaning edge was hit at the vertex B we need to compare it with first edge that was hit at vertex A
            // This case works when we have a lot of 'skipped'(i.e. parallel to ray) edges between last edge that was in B and first edged that was hit in A
            if (vertexHit && firstIntersectedA && lastIntersectedB && (firstIntersectedA->point()[iy] > point[iy] == lastIntersectedB->point()[iy] > point[iy])) {
                c = !c;
            }

            if (c)
                return INSIDE;
            else
                return OUTSIDE;
        }



    //Check performed with barycentric coordinate system use
    template <class T>
    inline Obool
        Polygon<T>::IsInsideTriangle(const Vec3<T>& requiredPoint,
        const Vec3<T>& firstVertex,
        const Vec3<T>& secondVertex,
        const Vec3<T>& thirdVertex,
        Ochar indexAxisX,
        Ochar indexAxisY) const {
            T distToHit[2];
            distToHit[0] = requiredPoint[indexAxisX] - firstVertex[indexAxisX];
            distToHit[1] = requiredPoint[indexAxisY] - firstVertex[indexAxisY];

            T distToSecond[2];
            distToSecond[0] = secondVertex[indexAxisX] - firstVertex[indexAxisX];
            distToSecond[1] = secondVertex[indexAxisY] - firstVertex[indexAxisY];

            T distToThird[2];
            distToThird[0] = thirdVertex[indexAxisX] - firstVertex[indexAxisX];
            distToThird[1] = thirdVertex[indexAxisY] - firstVertex[indexAxisY];

            T alpha = 1.0f;
            T beta;
            if (fabs(distToSecond[0]) < fabs(distToSecond[1])) {
                beta = (distToHit[0] * distToSecond[1] - distToSecond[0] * distToHit[1]) / (distToThird[0] * distToSecond[1] - distToThird[1] * distToSecond[0]);
                if ((beta >= 0.0f) && (beta <= 1.0f))
                    alpha = (distToHit[1] - beta * distToThird[1]) / distToSecond[1];
            }
            else {
                beta = (distToHit[1] * distToSecond[0] - distToHit[0] * distToSecond[1]) / (distToThird[1] * distToSecond[0] - distToThird[0] * distToSecond[1]);
                if ((beta >= 0.0f) && (beta <= 1.0f))
                    alpha = (distToHit[0] - beta * distToThird[0]) / distToSecond[0];
            }
            return ((alpha >= 0) && (beta >= 0) && ((alpha + beta) <= 1.0f));
        }

    template <class T>
    Obool
        Polygon<T>::HasUnmarkedVertices() const {
            for (Ouint i = 0; i < _vertex.size(); ++i) {
                if (_vertex[i]->status() == UNKNOWN)
                    return true;
            }

            return false;
        }

    template <class T>
    void
        Polygon<T>::BuildVertexAdjacencyInfo() {
            for (Ouint i = 1; i < _vertex.size(); ++i) {
                Vertex<T>::Join(_vertex[i], _vertex[i - 1]);
            }
            Vertex<T>::Join(_vertex[0], _vertex[_vertex.size() - 1]);
        }

    template <class T>
    void
        Polygon<T>::CheckCollinear() { //remove collinear sequential points 
            if (_vertex.size() > 3) {
                T tolerance2 = Vertex<T>::tolerance * Vertex<T>::tolerance;
                Vertex<T> *v0, *v1;
                int index1 = _vertex.size() - 1;
                v1 = _vertex[index1];
                v0 = _vertex[_vertex.size() - 2];
                for (Ouint i = 0; i < _vertex.size(); ++i) {
                    Vertex<T>* v2 = _vertex[i];

                    Vec3<T> lineDirection = (v2->point() - v0->point());
                    lineDirection.Normalize();
                    Vec3<T> projected_v1 = v0->point() + ((v1->point() - v0->point())*lineDirection)*lineDirection;
                    T distance = static_cast<T>(projected_v1.DistanceSqr(v1->point()));
                    if (distance < tolerance2) {
                        //need to remove v1
                        std::vector<Vertex<T>*> vertex_tmp;
                        for (Oint j = _vertex.size() - 1; j > index1; j--) {
                            vertex_tmp.push_back(_vertex[j]);
                            _vertex.pop_back();
                        }
                        _vertex.pop_back();
                        for (Oint j = 0; j < vertex_tmp.size(); j++) {
                            _vertex.push_back(vertex_tmp[j]);
                        }
                        if (_vertex.size() < 4) {
                            break;
                        }
                        v1 = v2;
                    }
                    else {
                        v0 = v1;
                        v1 = v2;
                    }
                    index1 = i;
                }
            }
        }

    template <class T>
    Obool
        Polygon<T>::IsCCW(const Vec3<CSGReal>& direction) {
            Obool isCcw = true;
            CSGReal angle = 0.0f;
            Oint size = (Oint)_vertex.size();
            if (size > 2) {
                Oint j = size - 1;
                Oint k = size - 2;
                for (Oint i = 0; i < size; ++i) {
                    Vec3<T> v0 = _vertex[j]->point() - _vertex[k]->point();
                    Vec3<T> v1 = _vertex[i]->point() - _vertex[j]->point();
                    CSGReal tmp = v0.CosAngle(v1);
                    if (tmp > 1.0)
                        tmp = 0.0;
                    else if (tmp < -1.0)
                        tmp = PI;
                    else
                        tmp = acos(tmp);
                    if (v0.Cross(v1)*direction < 0)
                        tmp *= -1.0f;
                    angle += tmp;
                    k = j;
                    j = i;
                }
                if (angle < 0)
                    isCcw = false;
            }

            return isCcw;
        }

    template <class T>
    void
        Polygon<T>::Reverse() {
            std::reverse(_vertex.begin(), _vertex.end());
            RefilCache();
        }

    template <class T>
    Obool
        Polygon<T>::IsCoplanar(const Polygon<T>* other) {
            if (!enterprise_manager::EQ(this->_d, other->_d, Vertex<T>::tolerance))// * 5))
                return false;

            if (!this->_normal.Equal(other->_normal, Vertex<T>::tolerance))
                return false;

            return true;
        }

    template <class T>
    std::string
        Polygon<T>::toString() const {
            stringstream ss;
            ss.precision(16);
            ss << " " << _index;
            for (Ouint i = 0; i < _vertex.size(); ++i) {
                ss << "\n" << _vertex[i]->point()[X] << ";" << _vertex[i]->point()[Y] << ";" << _vertex[i]->point()[Z];
#ifdef DEBUG
                ss << ";" << _vertex[i]->id;
                ss << ";";
                for (Ouint j = 0; j < _vertex[i]->parents.size(); j++) {
                    ss << _vertex[i]->parents[j] << " ";
                }
#endif
            }
            ss << "\n" << _vertex[0]->point()[X] << ";" << _vertex[0]->point()[Y] << ";" << _vertex[0]->point()[Z];
#ifdef DEBUG
            ss << ";" << _vertex[0]->id;
            ss << ";";
            for (Ouint j = 0; j < _vertex[0]->parents.size(); j++) {
                ss << _vertex[0]->parents[j] << " ";
            }
#endif
            return ss.str();
        }

    template <class T>
    void
        Polygon<T>::AddVertices(const Polygon<T>* poly) {
            Vertex<T>* v0 = _vertex[_vertex.size() - 1];
            for (Ouint i = 0; i < _vertex.size(); i++) {
                Vertex<T>* v1 = _vertex[i];
                for (Ouint j = 0; j < poly->_vertex.size(); j++) {
                    Vertex<T>* v = poly->_vertex[j];
                    if (v->_point.Equal(v0->_point, Vertex<T>::tolerance) || v->_point.Equal(v1->_point, Vertex<T>::tolerance))
                        continue;
                    if (EQ(v->_point.DistanceToSegment(v0->_point, v1->_point), T(0))) {
                        _vertex.insert(_vertex.begin() + i, v);
                        v1 = v;
                    }
                }
                v0 = v1;
            }

            RefilCache();
        }


    template <class T>
    Obool
        Polygon<T>::PointInsidePolygon(const Vec3<T>& point) const {
            if (FindRelativePosition(point) == INSIDE)
                return true;
            return false;
        }

    template <class T>
    Vec3<T>
        Polygon<T>::CenterForExtendedPolygon(const Vec3<T> *oldBaryCenter) const {
            Vec3<T> barycenter(0, 0, 0);
            Vec3<T> halfMinSide(0, 0, 0);
            Vec3<T> min = _vertex[0]->point() - _vertex[_vertex.size() - 1]->point();
            if (oldBaryCenter == NULL)
                barycenter = CalcBarycenter() - _vertex[_vertex.size() - 1]->point();
            else
                barycenter = *oldBaryCenter - _vertex[_vertex.size() - 1]->point();
            for (Ouint i = 1; i < _vertex.size(); ++i) {
                if (min.Length() >(_vertex[i]->point() - _vertex[i - 1]->point()).Length()) {
                    min = _vertex[i]->point() - _vertex[i - 1]->point();
                    if (oldBaryCenter == NULL)
                        barycenter = CalcBarycenter() - _vertex[i - 1]->point();
                    else
                        barycenter = *oldBaryCenter - _vertex[i - 1]->point();

                }
            }
            T lengthMinSide = min.Length();
            halfMinSide = min.Normalize() * (lengthMinSide / T(2));
            Vec3<T> shiftToMidle(0, 0, 0);
            shiftToMidle = halfMinSide - barycenter;
            T lengthMindle = shiftToMidle.Length();
            //shift to boundary of minimum side
            //if ((Vertex<T>::tolerance*2) < (lengthMindle / 2))
            return (shiftToMidle.Normalize() * (lengthMindle - Vertex<T>::tolerance * 2));
            //return shiftToMidle.Normalize() * Vertex<T>::tolerance*2;
        }

    //Shift barycenter on shiftForBaryCenter.
    //If new value of barycenter out of range polygon (it is possible in case extended polygon) 
    //try to shift barycenter to minimum side of polygon and try again shift barycenter on shiftForBaryCenter.
    //Return true if shift barycenter succeed, otherwise return false.  
    template <class T>
    Obool
        Polygon<T>::GetNewCenter(Vec3<T> &barycenter, const Vec3<T>	&shiftForBaryCenter) const {
            while (true) {
                barycenter += shiftForBaryCenter;
                //check barycenter out of range of polygonA
                if (PointInsidePolygon(barycenter))
                    return true;
                //restore barycenter inside polygonA, shift backward 
                barycenter -= shiftForBaryCenter;
                if (!ShiftBaryCenterToMinSide(barycenter)) {
                    return false;
                }
            }
        }

    //Find min side of polygon and do shift barycenter to this way.
    //If barycenter shifted and still  be inside this polygon - return true.
    //If barycenter out of range this polygon - return false and barycenter don't changed 
    template <class T>
    Obool
        Polygon<T>::ShiftBaryCenterToMinSide(Vec3<T> &barycenter) const {
            Vec3<T> shiftForBaryCenter(0, 0, 0);
            shiftForBaryCenter = CenterForExtendedPolygon(&barycenter);
            barycenter += shiftForBaryCenter;
            if (!PointInsidePolygon(barycenter)) {
                //Restore barycenter
                barycenter -= shiftForBaryCenter;
                return false;
            }
            return true;
        }

    template <class T>
    std::pair<Vertex<T>, Vertex<T>>
        Polygon<T>::FindMaxSegment() const {
            std::pair<Vertex<T>, Vertex<T>> maxSegment(_vertex[0]->point(), _vertex[_vertex.size() - 1]->point());
            Vec3<T> max = _vertex[0]->point() - _vertex[_vertex.size() - 1]->point();
            for (Ouint i = 1; i < _vertex.size(); ++i) {
                if (max.Length() >(_vertex[i]->point() - _vertex[i - 1]->point()).Length()) {
                    max = _vertex[i]->point() - _vertex[i - 1]->point();
                    maxSegment = std::make_pair(_vertex[i]->point(), _vertex[i - 1]->point());
                }
            }
            return maxSegment;
        }

    template <class T>
    Obool
        Polygon<T>::isHasVertex(const Vertex<T> &vertexB, Ouint *indexEqualVertex) const {
            for (Ouint i = 0; i < _vertex.size(); ++i) {
                if (_vertex[i]->point().Equal(vertexB.point(), Vertex<T>::tolerance)) {
                    if (indexEqualVertex)
                        *indexEqualVertex = i;
                    return true;
                }
            }
            return false;
        }

    template <class T>
    Obool
        Polygon<T>::IsMeaning() const {
            T val = abs(Area());
            T eps = Vertex<T>::epsilonValue;
            if (val - Vertex<T>::tolerance <= Vertex<T>::epsilonValue)
                return false;
            return true;
        }

    template <class T>
    T
        Polygon<T>::Area() const {
            if (_isAreaCached)
                return _area;

            _area = T(0);
            Vec3<T> sum(0, 0, 0);
            for (int i = 0; i < _vertex.size(); ++i) {
                int current = i;
                int next = (i + 1 == _vertex.size())
                    ? 0
                    : i + 1;

                sum += _vertex[current]->point().Cross(_vertex[next]->point());
            }
            _area = normal() * sum / 2;
            _isAreaCached = true;

            return _area;
        }

    template <class T>
    void
        Polygon<T>::RefilCache() {
            _isAreaCached = false;
        }

    template <class T>
    Obool
        Polygon<T>::IsAdjacent(const Polygon<T>& polygonB) const {
            //look for a common vertex
            for (int i = 0; i < _vertex.size(); ++i) {
                for (int j = 0; j < polygonB.vertex().size(); ++j) {
                    if (_vertex[i]->point() == polygonB.vertex()[j]->point())
                        return true;
                }
            }
            return false;
        }

} // namespace enterprise_manager

