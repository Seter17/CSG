namespace enterprise_manager {

template <class T>
inline Ouint
    Segment<T>::startIndex() const
{
    return _startIndex;
}

template <class T>
inline Ouint
    Segment<T>::endIndex() const
{
    return _endIndex;
}

template <class T>
inline T
    Segment<T>::startDistance() const
{
    return _startDistance;
}

template <class T>
inline T
    Segment<T>::endDistance() const
{
    return _endDistance;
}

template <class T>
inline typename Segment<T>::POINT_DESCRIPTOR
    Segment<T>::midpointType() const
{
    return _midpointType;
}

template <class T> 
Segment<T>::Segment()
    : _startDistance(0),
    _endDistance(0),
    _startpointType(FACE), //init to invalid
    _midpointType(FACE), //init to invalid
    _endpointType(FACE), //init to invalid
    _startIndex(0),
    _endIndex(0)
{
}

template <class T> 
/* virtual */
Segment<T>::~Segment()
{
}

template <class T> 
void
    Segment<T>::SetVertexIntersection(Ouint index, T distance)
{
    if (_startpointType == FACE) {
        _startpointType = VERTEX;
        _startIndex = index;
        _startDistance = distance;
    } else {
        //assert(_endpointType == FACE);
        _endpointType = VERTEX;
        _endIndex = index;
        _endDistance = distance;
    }
}

template <class T> 
void
    Segment<T>::SetEdgeIntersection(Ouint index, T distance)
{
    if (_startpointType == FACE) {
        _startpointType = EDGE;
        _startIndex = index;
        _startDistance = distance;
    } else {
#ifdef ASSERT_CSG
        assert(_endpointType == FACE);
#endif /*ASSERT_CSG*/
        _endpointType = EDGE;
        _endIndex = index;
        _endDistance = distance;
    }
}

template <class T> 
bool
    Segment<T>::IntersectionFound()
{
    return (_startpointType != FACE);
}

template <class T> 
void
    Segment<T>::SetIntersectionMidpoint(Ouint maxIndex)
{
#ifdef ASSERT_CSG
    assert(_startpointType != FACE);
#endif /*ASSERT_CSG*/
    if (_startpointType == VERTEX && _endpointType == FACE) {
        //vertex-vertex-vertex
        _endpointType = VERTEX;
        _endIndex = _startIndex;
        _endDistance = _startDistance;

        _midpointType = VERTEX;
    } else {
#ifdef ASSERT_CSG
        assert(_endpointType != FACE);
#endif /*ASSERT_CSG*/
        if (_startpointType == VERTEX && _endpointType == VERTEX) {
#ifdef ASSERT_CSG
            assert(_startIndex <= _endIndex);
#endif /*ASSERT_CSG*/
            if ((_endIndex == _startIndex+1) || (_startIndex == 0 && _endIndex == maxIndex)) {
                //vertex-edge-vertex
                _midpointType = EDGE;
            } else {
                //vertex-face-vertex
                _midpointType = FACE;
            }
        } else {
            //any other (v-f-e, e-f-v or e-f-e)
            _midpointType = FACE;
        }
    }
}

template <class T> 
/*static*/ Obool
    Segment<T>::Overlap(const Segment& segmentA, const Segment& segmentB)
{
    T minA =  segmentA._startDistance;
    T maxA =  segmentA._endDistance;
    if (minA > maxA) {
        minA =  segmentA._endDistance;
        maxA =  segmentA._startDistance;
    }

    //test if one of segmentB points is inside segmentA
    if (Greater(segmentB._startDistance, minA) && Lesser(segmentB._startDistance, maxA))
        return true;
    if (Greater(segmentB._endDistance, minA) && Lesser(segmentB._endDistance, maxA))
        return true;

    T minB =  segmentB._startDistance;
    T maxB =  segmentB._endDistance;
    if (minB > maxB) {
        minB =  segmentB._endDistance;
        maxB =  segmentB._startDistance;
    }

    //test if one of segmentA points is inside segmentB
    if (Greater(segmentA._startDistance, minB) && Lesser(segmentA._startDistance, maxB))
        return true;
    if (Greater(segmentA._endDistance, minB) && Lesser(segmentA._endDistance, maxB))
        return true;

    //special case: one segment is a point, and lies on start/end of another
    if (Equal(minA, maxA)) {
        if (Equal(minA, minB) || Equal(minA, maxB))
            return false;
    }
    if (Equal(minB, maxB)) {
        if (Equal(minB, minA) || Equal(minB, maxA))
            return false;
    }

    //special case: equal segments 
    if (Equal(minA,minB) && Equal(maxA,maxB))
        return true;

    //no overlap
    return false;
}

template <class T> 
void
    Segment<T>::FindIntersection(const Segment& segmentB, const Polygon<T>& polygonA)
{
    T minB =  segmentB._startDistance;
    T maxB =  segmentB._endDistance;
    if (minB > maxB) {
        minB =  segmentB._endDistance;
        maxB =  segmentB._startDistance;
    }

    if (_startDistance < _endDistance) {
		if (Lesser(maxB, _endDistance, Vertex<T>::tolerance)) {// *2)) {
            _endDistance = maxB;
            _endpointType = _midpointType;
            if (_midpointType == EDGE && (_endIndex == polygonA.NextIndex(_startIndex)))
                _endIndex = _startIndex;
        }
		if (Greater(minB, _startDistance, Vertex<T>::tolerance)) {// *2)) {
            _startDistance = minB;
            _startpointType = _midpointType;
            if (_midpointType == EDGE && (_endIndex != polygonA.NextIndex(_startIndex)))
                _startIndex = _endIndex;
        }
    } else {
		if (Lesser(maxB, _startDistance, Vertex<T>::tolerance)) {// *2)) {
            _startDistance = maxB;
            _startpointType = _midpointType;
            if (_midpointType == EDGE && (_endIndex != polygonA.NextIndex(_startIndex)))
                _startIndex = _endIndex;
        }
		if (Greater(minB, _endDistance, Vertex<T>::tolerance)) {// *2)) {
            _endDistance = minB;
            _endpointType = _midpointType;
            if (_midpointType == EDGE && (_endIndex == polygonA.NextIndex(_startIndex)))
                _endIndex = _startIndex;
        }
    }
    //if _startpointType != EDGE
    // CreateEdgeVertex
    // if edge vertex == polygonA.vertex(si)
    //   _startpointType = VERTEX

    //samme for endPointType
}

template <class T> 
Oint
    Segment<T>::IntersectionType()
{
    return ((_startpointType << 4)+(_midpointType << 2)+_endpointType);
}

template <class T> 
std::string
    Segment<T>::IntersectionType(Oint it)
{
    switch (it)
    {
    case VERTEX_VERTEX_VERTEX : return "VERTEX_VERTEX_VERTEX";
    case VERTEX_EDGE_VERTEX : return "VERTEX_EDGE_VERTEX";
    case VERTEX_EDGE_EDGE : return "VERTEX_EDGE_EDGE";
    case VERTEX_FACE_VERTEX : return "VERTEX_FACE_VERTEX";
    case VERTEX_FACE_EDGE : return "VERTEX_FACE_EDGE";
    case VERTEX_FACE_FACE : return "VERTEX_FACE_FACE";
    case EDGE_EDGE_VERTEX : return "EDGE_EDGE_VERTEX";
    case EDGE_EDGE_EDGE : return "EDGE_EDGE_EDGE";
    case EDGE_FACE_VERTEX : return "EDGE_FACE_VERTEX";
    case EDGE_FACE_EDGE : return "EDGE_FACE_EDGE";
    case EDGE_FACE_FACE : return "EDGE_FACE_FACE";
    case FACE_FACE_VERTEX : return "FACE_FACE_VERTEX";
    case FACE_FACE_EDGE : return "FACE_FACE_EDGE";
    case FACE_FACE_FACE : return "FACE_FACE_FACE";
    default : return "UNKNOW";
    }
}
} // namespace enterprise_manager
