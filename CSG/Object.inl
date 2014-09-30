namespace enterprise_manager {

#define MAX_POLYGONS 50000


template <class T>
T Object<T>::MaxDistance() {
	CalculateExtents();
	Vec3<T> vMaxA = extent().max();
	T d = max(fabs(vMaxA[0]), fabs(vMaxA[1]));
	d = max(d, fabs(vMaxA[2]));
	return d;
}

template <class T>
/*static*/ void
Object<T>::SetTolerance(Object& objectA, Object& objectB) {
	T d = max(objectA.MaxDistance(), objectB.MaxDistance());
	Ofloat alfa = 1.e9;

	Vertex<T>::tolerance = d * alfa * Vertex<T>::epsilonValue;
	Vertex<T>::unitTolerance = alfa * Vertex<T>::epsilonValue;
}

template <class T>
inline const std::vector<Polygon<T>*>&
Object<T>::polygon() const {
	return _polygon;
}

template <class T>
inline const std::vector<Vertex<T>*>&
Object<T>::vertex() const {
	return _vertex;
}

template <class T>
inline const Extent<T>&
Object<T>::extent() const {
	return _extent;
}

template <class T>
Object<T>::Object() {
	this->failed = false;
}

template <class T>
/* virtual */
Object<T>::~Object() {
	while (!_vertex.empty()) {
		delete _vertex.back();
		_vertex.pop_back();
	}
	while (!_polygon.empty()) {
		delete _polygon.back();
		_polygon.pop_back();
	}
}

template <class T>
void
Object<T>::CalculateExtents() {
	Vec3<T> max(0, 0, 0);
	Vec3<T> min(0, 0, 0);
	if (!_vertex.empty()) {
		max = _vertex[0]->point();
		min = _vertex[0]->point();
		for (Ouint i = 1; i < _vertex.size(); i++) {
			max.MaxComp(_vertex[i]->point());
			min.MinComp(_vertex[i]->point());
		}
	}
	_extent.setMin(min);
	_extent.setMax(max);
}


//ivan 07.10.2011 - dealing with collinear triangles (i.e. all points of triangle on same line) 
//Artem 11.03.2014 NOT WORKING NEED TO REMOVE OR FIX (see SVN)
template <class T>
void
Object<T>::RemoveCollinearPolygons() {
	return;
}

//Artem 11.03.2014 NOT WORKING NEED TO REMOVE OR FIX (see SVN)
template <class T>
void
Object<T>::MakeValid() {
	//remove collinear triangles, and change collinear point in other polygons to new coordinates
}

//Artem 11.03.2014 NOT WORKING NEED TO REMOVE OR FIX (see SVN)
template <class T>
Obool
Object<T>::IsValid(Obool operandCheck = true) const {
	return true;
}

template <class T>
Obool
Object<T>::HasValidTopology() {
return true;
std::map<std::pair<Oint, Oint>, Oint> edgeMap = GetEdgeMap();

std::vector<std::pair<Oint, Oint>> invalid_edges;
std::map<std::pair<Oint, Oint>, Oint>::const_iterator it;
T local_tolerance = Vertex<T>::tolerance;// * 2;
for (it = edgeMap.begin(); it != edgeMap.end(); ++it) {
	if (it->second % 2 != 0) {
		Obool same = false;
		for (Ouint i = 0; i < invalid_edges.size(); i++) {
			std::pair<Oint, Oint> inv_edge = invalid_edges[i];
			//check if edges are actually same
			if (inv_edge.first == it->first.first && _vertex[inv_edge.second]->point().Equal(_vertex[it->first.second]->point(), local_tolerance) ||
				inv_edge.second == it->first.second && _vertex[inv_edge.first]->point().Equal(_vertex[it->first.first]->point(), local_tolerance) ||
				inv_edge.first == it->first.second && _vertex[inv_edge.second]->point().Equal(_vertex[it->first.first]->point(), local_tolerance) ||
				inv_edge.second == it->first.first && _vertex[inv_edge.first]->point().Equal(_vertex[it->first.second]->point(), local_tolerance)) {
				same = true;
				invalid_edges.erase(invalid_edges.begin() + i);
				break;
			}
		}
		if (!same)
			invalid_edges.push_back(it->first);
	}
}
return invalid_edges.size() == 0 || CheckInvalidEdges(invalid_edges);
}

template <class T>
Obool
Object<T>::CheckInvalidEdges(std::vector<std::pair<Oint, Oint>> invalid_edges) {
	//invalid egdes can be valid actually
	for (Ouint i = 0; i < invalid_edges.size(); i++) {
		if (invalid_edges[i].first != -1) {

#ifdef DEBUG
			stringstream ss;
#endif
			std::set<Oint> vertexes;
			vertexes.insert(invalid_edges[i].first);
			vertexes.insert(invalid_edges[i].second);
#ifdef DEBUG
			ss << "\nInvalid topology, edge indexes = " << invalid_edges[i].first << "," << invalid_edges[i].second;
#endif
			invalid_edges[i].first = -1;
			invalid_edges[i].second = -1;
			for (Ouint j = i + 1; j < invalid_edges.size(); j++)
			if (invalid_edges[j].first != -1)
			if (vertexes.find(invalid_edges[j].first) != vertexes.end()) {
#ifdef DEBUG
				ss << "\nInvalid topology, edge indexes = " << invalid_edges[j].first << "," << invalid_edges[j].second;
#endif
				vertexes.insert(invalid_edges[j].second);
				invalid_edges[j].first = -1;
				invalid_edges[j].second = -1;
			}
			//now we have vertexes that are in same graph
			Ouint counter = 0;
			std::set<Oint>::iterator it2;
			Oint v0 = NULL, v1 = NULL, v00 = NULL, v01 = NULL;
			for (it2 = vertexes.begin(); it2 != vertexes.end(); it2++) {
				if (!v00) {
					v00 = *it2;
				}
				else {
					if (!v01)
						v01 = *it2;

					if (!v0) {
						v0 = *it2;
					}
					else {
						if (!v1) {
							v1 = *it2;
						}
						else {
							Oint v2 = *it2;
							if (counter == (Ouint)vertexes.size() - 2) {
								if (!Vertex<T>::Collinear(_vertex[v1], _vertex[v2], _vertex[v00])) {
#ifdef DEBUG
									cout << ss.str();
									/*std::vector<Vertex<T>*> vertexes;
									vertexes.push_back(_vertex[v1]);
									vertexes.push_back(_vertex[v2]);
									vertexes.push_back(_vertex[v00]);

									Polygon<T>* poligon = new Polygon<T>(vertexes, counter);
									string fPuth = "C:\\octaga_tmp\\logs\\BadColliniarVertex.csv";
									poligon->PrintToFileCSV(fPuth.c_str(),"000");
									delete poligon;*/
#endif
									return false;
								}
							}
							else if (counter == vertexes.size() - 1) {
								if (!Vertex<T>::Collinear(_vertex[v2], _vertex[v00], _vertex[v01])) {
#ifdef DEBUG								
									cout << ss.str();
#endif
									return false;
								}
							}
							else {
								if (!Vertex<T>::Collinear(_vertex[v0], _vertex[v1], _vertex[v2])) {
#ifdef DEBUG								
									cout << ss.str();
#endif
									return false;
								}
							}
							v0 = v1;
							v1 = v2;
						}
					}
					counter++;
				}
			}
		}
	}
	return true;
}

template <class T>
/* static */  void
Object<T>::CreateUnion(Object& objectA, Object& objectB) {
	T savedTolerance = Vertex<Odouble>::tolerance;
	T savedUnitTolerance = Vertex<Odouble>::unitTolerance;

	SetTolerance(objectA, objectB);
	//all validations of operands SHOULD BE done in calling method - ivan 30.03.2012
	SubdivideObjects(objectA, objectB);
	DeletePolygons(objectA, (INSIDE | OPPOSITE), objectB, (INSIDE | SAME | OPPOSITE));
	objectA.DeleteUnusedVertices();
	objectA.Merge(objectB);
	//objectA.RemoveCollinearPolygons();

	//CLEAN UP OBJECT
	for (Ouint i = 0; i < objectA._vertex.size(); ++i) {
		objectA._vertex[i]->setStatus(UNKNOWN);
		objectA._vertex[i]->ClearAdjacencyInfo();
	}
	for (Ouint i = 0; i < objectA._polygon.size(); ++i) {
		objectA._polygon[i]->CalculatePlaneEquation();
		objectA._polygon[i]->CalculateExtents();
	}
	objectA.Simplify();
	objectA.CalculateExtents();

	//restore tolerance 
	Vertex<Odouble>::tolerance = savedTolerance;
	Vertex<Odouble>::unitTolerance = savedUnitTolerance;
}

template <class T>
/* static */  void
Object<T>::CreateIntersection(Object& objectA, Object& objectB) {
	T savedTolerance = Vertex<Odouble>::tolerance;
	T savedUnitTolerance = Vertex<Odouble>::unitTolerance;
	SetTolerance(objectA, objectB);
	//all validations of operands SHOULD BE done in calling method - ivan 30.03.2012
	SubdivideObjects(objectA, objectB);
	DeletePolygons(objectA, (OUTSIDE | OPPOSITE), objectB, (OUTSIDE | SAME | OPPOSITE));
	objectA.DeleteUnusedVertices();

	objectA.Merge(objectB);
	//objectA.RemoveCollinearPolygons();
	//CLEAN UP OBJECT
	for (Ouint i = 0; i < objectA._vertex.size(); ++i) {
		objectA._vertex[i]->setStatus(UNKNOWN);
		objectA._vertex[i]->ClearAdjacencyInfo();
	}
	for (Ouint i = 0; i < objectA._polygon.size(); ++i) {
		objectA._polygon[i]->CalculatePlaneEquation();
		objectA._polygon[i]->CalculateExtents();
	}
	objectA.Simplify();
	objectA.CalculateExtents();

	Vertex<Odouble>::tolerance = savedTolerance;
	Vertex<Odouble>::unitTolerance = savedUnitTolerance;
}

template <class T>
/* static */  void
Object<T>::CreateDifference(Object& objectA, Object& objectB) {
	T savedTolerance = Vertex<Odouble>::tolerance;
	T savedUnitTolerance = Vertex<Odouble>::unitTolerance;
	SetTolerance(objectA, objectB);
	SubdivideObjects(objectA, objectB);
	DeletePolygons(objectA, (INSIDE | SAME), objectB, (OUTSIDE | SAME | OPPOSITE));
	objectA.MergeReversed(objectB);
	objectA.CalculateExtents();
	Vertex<Odouble>::tolerance = savedTolerance;
	Vertex<Odouble>::unitTolerance = savedUnitTolerance;
}

template <class T>
void
Object<T>::GetFaceSetIndexes(std::vector<Oint>& coordIndex) const {
	coordIndex.clear();
	std::map<Vertex<T>*, Ouint> vertexMap;

	for (Ouint i = 0; i < _vertex.size(); ++i) {
		if (_vertex[i])
			vertexMap[_vertex[i]] = i;
	}
	for (Ouint i = 0; i < _polygon.size(); ++i) {
		Polygon<T>* polygon = _polygon[i];
		if (polygon) {
			for (Ouint j = 0; j < polygon->vertex().size(); ++j) {
				// ave. What will happens in the case of missing polygon->vertex()[j] in the map ?
				// need fix it
				coordIndex.push_back(vertexMap[polygon->vertex()[j]]);
			}
			coordIndex.push_back(-1);
		}
	}
}

template <class T>
void
Object<T>::GetCoords(std::vector<Vec3<CSGReal> >& coord) const {
	coord.clear();
	for (Ouint i = 0; i < _vertex.size(); ++i) {
		coord.push_back(_vertex[i]->point());
	}
}

template <class T>
void
Object<T>::Transform(const Matrix4<T>& matrix) {
	for (Ouint i = 0; i < _vertex.size(); ++i) {
		Vec3<T> point(_vertex[i]->_point[0], _vertex[i]->_point[1], _vertex[i]->_point[2]);
		point *= matrix;
		_vertex[i]->_point = Vec3<T>(point[0], point[1], point[2]);
	}
	for (Ouint i = 0; i < _polygon.size(); ++i) {
		_polygon[i]->CalculatePlaneEquation();
		_polygon[i]->CalculateExtents();
	}
	CalculateExtents();
}

template <class T>
/* static */ Object<T>*
Object<T>::CreateFromIndexedFaceSet(const std::vector<Vec3<T> >& coord, const std::vector<Oint>& coordIndex, Obool /* ccw */, Obool /* convex */) {
	Object<T>* object = new Object<T>;

	if (coord.empty())
		return object;

	// Populate the vertex array and calculate extent.
	Vec3<T> max(coord[0][0], coord[0][1], coord[0][2]);
	Vec3<T> min(coord[0][0], coord[0][1], coord[0][2]);
	for (Ouint i = 0; i < coord.size(); ++i) {
		Vec3<T> v = Vec3<T>(coord[i][0], coord[i][1], coord[i][2]);
		//if (object->GetExistingVertex(v) != NULL) {
		//  delete object;
		//  return new Object<T>;
		//}
		//assert(object->GetExistingVertex(v) == NULL);
		object->_vertex.push_back(new Vertex<T>(v));
#ifdef DEBUG
		object->_vertex[object->_vertex.size() - 1]->id = i;
#endif
		max.MaxComp(v);
		min.MinComp(v);
	}
	object->_extent.setMin(min);
	object->_extent.setMax(max);

	// Populate the polygon array and join adjacent vertices.
	std::vector<Vertex<T>*> polygonVertices;
	for (Ouint i = 0; i < coordIndex.size(); ++i) {
		if (coordIndex[i] != -1) {
			polygonVertices.push_back(object->_vertex[coordIndex[i]]);
		}
		else {
			object->_polygon.push_back(new Polygon<T>(polygonVertices, object->_polygon.size()));
			polygonVertices.clear();
		}
	}

	return object;
}

template <class T>
Object<T>*
Object<T>::CreateFromVertices(vector<Vertex<T>*> vertices) {
	Object<T>* object = new Object<T>;

	// Populate the vertex array and calculate extent.
	Vec3<T> max(vertices[0]->point());
	Vec3<T> min(vertices[0]->point());
	for (Ouint i = 0; i < vertices.size(); ++i) {
		Vec3<T> v = vertices[i]->point();
		object->_vertex.push_back(new Vertex<T>(v));
#ifdef DEBUG
		object->_vertex[object->_vertex.size() - 1]->id = i;
#endif
		max.MaxComp(v);
		min.MinComp(v);
	}
	object->_extent.setMin(min);
	object->_extent.setMax(max);

	object->_polygon.push_back(new Polygon<T>(vertices, object->_polygon.size()));

	return object;
}

template <class T>
void
Object<T>::Merge(const Object<T>& objectB) {
	for (Ouint i = 0; i < objectB.polygon().size(); ++i) {
		Polygon<T>* polygonB = objectB.polygon()[i];
		std::vector<Vertex<T>*> polygonVertices;
		for (Ouint j = 0; j < polygonB->vertex().size(); ++j) {
			const Vec3<T>& pointB = polygonB->vertex()[j]->point();
			// Get or create vertex corresponding to the new point.
			polygonVertices.push_back(GetCreateVertex(pointB));
		}
		_polygon.push_back(new Polygon<T>(polygonVertices, _polygon.size()));
	}
}

template <class T>
void
Object<T>::MergeReversed(const Object& objectB) {
	for (Ouint i = 0; i < objectB.polygon().size(); ++i) {
		Polygon<T>* polygonB = objectB.polygon()[i];
		std::vector<Vertex<T>*> polygonVertices;
		for (Ouint j = 0; j < polygonB->vertex().size(); ++j) {
			const Vec3<T>& pointB = polygonB->vertex()[polygonB->vertex().size() - 1 - j]->point();
			// Get or create vertex corresponding to the new point.
			polygonVertices.push_back(GetCreateVertex(pointB));
		}
		_polygon.push_back(new Polygon<T>(polygonVertices, _polygon.size()));
	}
}

template <class T>
std::vector<Oint>
Object<T>::CreateDeleteList(Ouint deleteMask, const Object& objectB) const {
	std::vector<Oint> deleteList;
	// For each polygonA in objectA 
	for (Ouint i = 0; i < _polygon.size(); ++i) {
		Polygon<T>* polygonA = _polygon[i];
		// For each vertexA in polygonA
		RELPOS_STATUS polyStatus = UNKNOWN;
		for (Ouint j = 0; j < polygonA->vertex().size(); ++j) {
			Vertex<T>* vertexA = polygonA->vertex()[j];
			// If the status of vertexA is not BOUNDARY
			// the status of the polygonA is the status of vertexA.
			if (vertexA->status() == INSIDE || vertexA->status() == OUTSIDE) {
				polyStatus = vertexA->status();
				break;
			}
		}
		// If no status for polygonA, was found
		// determine status of polygonA using the polygon classification routine
		if (polyStatus == UNKNOWN) {
			polyStatus = objectB.FindRelativePosition(*polygonA);
		}

		// If polygons of this status should be deleted for this operation
		// delete polygonA from objectA


		if (polyStatus & deleteMask) {
#ifdef DEBUG

			//_polygon[i]->PrintToFileCSV("C:\\octaga_tmp\\logs\\deletedpoligons.csv", "000");
			//continue;			
#endif

			deleteList.push_back(i);
		}

	}
	return deleteList;
}

template <class T>
void
Object<T>::DeletePolygons(const std::vector<Oint> deleteList) {
	//delete
	for (Ouint i = 0; i < deleteList.size(); ++i) {
#if DEBUG
		_polygon[deleteList[i]]->PrintToFileCSV("C:\\octaga_tmp\\logs\\ValidDeletedPolygons.csv", "deleted");
#endif
		delete _polygon[deleteList[i]];
		_polygon[deleteList[i]] = NULL;
	}

	// Clean up
	CleanPolygonList();
}


template <class T>
void
Object<T>::DeletePolygons(Object& objectA, Ouint deleteMaskA, Object& objectB, Ouint deleteMaskB) {
	std::vector<Oint> deleteListA = objectA.CreateDeleteList(deleteMaskA, objectB);
	std::vector<Oint> deleteListB = objectB.CreateDeleteList(deleteMaskB, objectA);

	objectA.DeletePolygons(deleteListA);
	objectB.DeletePolygons(deleteListB);
}

template <class T>
void
Object<T>::DeleteUnusedVertices() {
	std::map<Vertex<T>*, Ouint> vertexMap;
	for (Ouint i = 0; i < _vertex.size(); ++i) {
		vertexMap[_vertex[i]] = i;
	}
	std::vector<Obool> vertexUsed(_vertex.size(), false);

	for (Ouint i = 0; i < _polygon.size(); ++i) {
		Polygon<T>* polygonA = _polygon[i];
		for (Ouint j = 0; j < polygonA->vertex().size(); ++j) {
			vertexUsed[vertexMap[polygonA->vertex()[j]]] = true;
		}
	}

	std::vector<Vertex<T>*>  newVertexList;

	for (Ouint i = 0; i < _vertex.size(); ++i) {
		if (vertexUsed[i] == false) {
			delete _vertex[i];
			_vertex[i] = false;
		}
		else {
			newVertexList.push_back(_vertex[i]);
		}
	}
	_vertex = newVertexList;
}

template <class T>
/* static */  void
Object<T>::MarkVertices(Object& objectB) {
	return;
}


template <class T>
void
Object<T>::BuildVertexAdjacencyInfo() {
	// Clear
	for (Ouint i = 0; i < _vertex.size(); ++i) {
		_vertex[i]->ClearAdjacencyInfo();
	}
	for (Ouint i = 0; i < _polygon.size(); ++i) {
		_polygon[i]->BuildVertexAdjacencyInfo();
	}
}

template <class T>
/* static */  void
Object<T>::SubdivideObjects(Object<T>& objectA, Object<T>& objectB) {
	objectB.MakeCcw();
	//1: Split the first object so that it doesn't intersect the second object
	objectA.SplitBy(objectB);
	//2: Split the second object so that it doesn't intersect the first object
	objectB.SplitBy(objectA);
	//3: Split the first object again, resolving newly introduced intersections
	objectA.SplitBy(objectB);

	objectA.MakeCcw();
}

template <class T>
void
Object<T>::SplitBy(const Object& objectB) {
	/*Ivan:
	I don't really understand what's going on in this method (yet),
	but the issue looks like additional member is being added to _polygon and deleted on next iteration.
	Workaround is build on this fact.
	Also added max limit of polygons in object, to be safe from endless loops.
	*/
	int count = 0;
	// Splitting ObjectA by ObjectB
	// If extent of objectA overlaps extent of objeetB
	if (Extent<T>::Overlap(_extent, objectB.extent())) {
		// For each polygonA in objectA
		// Do not process newly added Polygons at the end of the vector _polygon
		for (Ouint i = 0; i < _polygon.size(); ++i) {
			if (_polygon.size() > MAX_POLYGONS) {
				printf("The amount of polygons (%d) extended the limit MAX_POLYGONS (%d)\n", _polygon.size(), MAX_POLYGONS);
				//cout << "\nObjectA: MAX_POLYGONS limit reached.";
				while (!_vertex.empty()) {
					delete _vertex.back();
					_vertex.pop_back();
				}
				while (!_polygon.empty()) {
					delete _polygon.back();
					_polygon.pop_back();
				}
				failed = true;
				break;
			}
			Polygon<T>& polygonA = *_polygon[i];
			// If the extent of polygonA overlaps the extent of objectB
			if (Extent<T>::Overlap(polygonA.extent(), objectB.extent())) {
				// For each polygonB in objectB
				for (Ouint j = 0; j < objectB.polygon().size(); ++j) {
					Polygon<T>& polygonB = *objectB.polygon()[j];
					// If the extents of polygonA and polygonB overlap
					if (Extent<T>::Overlap(polygonA.extent(), polygonB.extent())) {
						// Analyze them as in "5. Do Two Polygons Intersect?"
						Segment<T> segmentA, segmentB;
						INTERSECT_TYPE intersection = Polygon<T>::Intersect(polygonA, polygonB, segmentA, segmentB);
						// If they are not COPLANAR and do INTERSECT
						if (intersection == INTERSECT) {
							// Subdivide polygonA as in "6. Subdividing Non-Coplanar Polygons"
							Subdivide(polygonA, polygonB, segmentA, segmentB);
							if (_polygon[i] == NULL) {
								if (i == _polygon.size() - 2)
									count++;
								else
									count = 0;
								//break;
							}
						}
						else {
							// Else if they do NOT-INTERSECT or if they are COPLANAR
							//(do nothing)
						}
					}
				}
			}
			if (count > 10) {
				cout << "\nObject<T>::SplitBy(): count > 10.";
				break;
			}
		}
		// Clean up
		CleanPolygonList();
	}
}


template <class T>
void
Object<T>::Subdivide(Polygon<T>& polygonA, const Polygon<T>& polygonB, Segment<T>& segmentA, Segment<T>& segmentB) {

	Ray<T> intersectionLine;

	Polygon<T>::CalcLineOfIntersection(polygonA, polygonB, intersectionLine);

	segmentA.FindIntersection(segmentB, polygonA);

	Oint si = segmentA.startIndex();
	Oint ei = segmentA.endIndex();

#ifdef DEBUG
	Obool printit = false;
	if (segmentA.IntersectionType() != Segment<T>::VERTEX_VERTEX_VERTEX
		&& segmentA.IntersectionType() != Segment<T>::VERTEX_EDGE_VERTEX
		&& segmentA.IntersectionType() != Segment<T>::EDGE_EDGE_VERTEX
		&& printit) {
		_polygonsDivided.clear();
		stringstream typess;
		typess << "0, intersection " << Segment<T>::IntersectionType(segmentA.IntersectionType());
		//polygonA.PrintToFileCSV(typess.str());
		polygonA.AppendToFileCSV(typess.str());
		polygonB.AppendToFileCSV("1");
	}
#endif

	switch (segmentA.IntersectionType()) {
	case Segment<T>::VERTEX_VERTEX_VERTEX:
	{
												//Mark as boundary
												polygonA.vertex()[si]->setStatus(BOUNDARY);
	}
		break;
	case Segment<T>::VERTEX_EDGE_VERTEX:
	{
											//Mark as boundary
											polygonA.vertex()[si]->setStatus(BOUNDARY);
											polygonA.vertex()[ei]->setStatus(BOUNDARY);
	}
		break;
	case Segment<T>::VERTEX_EDGE_EDGE:
	{
											//create new vertex
											Vertex<T>* newVertexN = CreateEdgeVertex(intersectionLine, ei, segmentA.endDistance(), polygonA);

											//Mark as boundary
											polygonA.vertex()[si]->setStatus(BOUNDARY);
											newVertexN->setStatus(BOUNDARY);

											//create 2 new polygons 
											Obool removePolygon = true;
											Polygon<T>* newPoly1 = NULL;
											Polygon<T>* newPoly2 = NULL;
											if (si == ei) {
												removePolygon &= CreateSubPolygon(polygonA, polygonA.NextIndex(si), polygonA.PrevIndex(si), newVertexN);
												removePolygon &= CreateSubPolygon(polygonA, polygonA.PrevIndex(si), si, newVertexN);
											}
											else {
												removePolygon &= CreateSubPolygon(polygonA, si, polygonA.PrevIndex(ei), newVertexN);
												removePolygon &= CreateSubPolygon(polygonA, polygonA.PrevIndex(ei), ei, newVertexN);
											}


											if (removePolygon) {
												RemovePolygon(&polygonA);
											}
	}
		break;
	case Segment<T>::VERTEX_FACE_VERTEX:
	{
											//Mark as boundary
											polygonA.vertex()[si]->setStatus(BOUNDARY);
											polygonA.vertex()[ei]->setStatus(BOUNDARY);

											//create 2 new polygons
											Obool removePolygon = true;
											removePolygon &= CreateSubPolygon(polygonA, ei, si);
											removePolygon &= CreateSubPolygon(polygonA, si, ei);
											if (removePolygon) {
												RemovePolygon(&polygonA);
											}
	}
		break;
	case Segment<T>::VERTEX_FACE_EDGE:
	{
											Vertex<T>* newVertexN = CreateEdgeVertex(intersectionLine, ei, segmentA.endDistance(), polygonA);

											//Mark as boundary
											polygonA.vertex()[si]->setStatus(BOUNDARY);
											newVertexN->setStatus(BOUNDARY);

											//create 2 new polygons
											Obool removePolygon = true;
											removePolygon &= CreateSubPolygon(polygonA, polygonA.NextIndex(ei), si, newVertexN);
											removePolygon &= CreateSubPolygon(polygonA, si, ei, newVertexN);

											if (removePolygon) {
												RemovePolygon(&polygonA);
											}
	}
		break;
	case Segment<T>::VERTEX_FACE_FACE:
	{
											//create one new vertex
											Vertex<T>* newVertex = CreateFaceVertex(intersectionLine, segmentA.endDistance(), polygonA);

											//Mark as boundary
											polygonA.vertex()[si]->setStatus(BOUNDARY);
											newVertex->setStatus(BOUNDARY);

											Obool collinear = Vertex<T>::Collinear(newVertex, polygonA.vertex()[si], polygonA.vertex()[ei]);
											//two cases
											Obool removePolygon = true;
											if (collinear) {
												//create 4 new polygons
												removePolygon &= CreateSubPolygon(polygonA, polygonA.NextIndex(ei), si, newVertex);
												removePolygon &= CreateSubPolygon(polygonA, ei, polygonA.NextIndex(ei), newVertex);
												removePolygon &= CreateSubPolygon(polygonA, polygonA.PrevIndex(ei), ei, newVertex);
												removePolygon &= CreateSubPolygon(polygonA, si, polygonA.PrevIndex(ei), newVertex);
											}
											else {
												//create 3 new polygons
												removePolygon &= CreateSubPolygon(polygonA, polygonA.NextIndex(ei), si, newVertex);
												removePolygon &= CreateSubPolygon(polygonA, ei, polygonA.NextIndex(ei), newVertex);
												removePolygon &= CreateSubPolygon(polygonA, si, ei, newVertex);
											}
											if (removePolygon) {
												RemovePolygon(&polygonA);
											}
	}
		break;
	case Segment<T>::EDGE_EDGE_VERTEX:
	{
											Vertex<T>* newVertexN = CreateEdgeVertex(intersectionLine, si, segmentA.startDistance(), polygonA);

											//Mark as boundary
											polygonA.vertex()[ei]->setStatus(BOUNDARY);
											newVertexN->setStatus(BOUNDARY);

											//create 2 new polygons 
											Obool removePolygon = true;

											if (si == ei) {
												removePolygon &= CreateSubPolygon(polygonA, polygonA.NextIndex(ei), polygonA.PrevIndex(ei), newVertexN);
												removePolygon &= CreateSubPolygon(polygonA, polygonA.PrevIndex(ei), ei, newVertexN);
											}
											else {
												removePolygon &= CreateSubPolygon(polygonA, ei, polygonA.PrevIndex(si), newVertexN);
												removePolygon &= CreateSubPolygon(polygonA, polygonA.PrevIndex(si), si, newVertexN);
											}

											if (removePolygon) {
												RemovePolygon(&polygonA);
											}
	}
		break;
	case Segment<T>::EDGE_EDGE_EDGE:
	{

#ifdef ASSERT_CSG
										assert (si == ei); //both should point to same edge
#endif /*ASSERT_CSG*/

										Obool onePoint = (Equal(segmentA.startDistance(), segmentA.endDistance()));
										if (onePoint) {
											Vertex<T>* newVertexN = CreateEdgeVertex(intersectionLine, si, segmentA.startDistance(), polygonA);

											//Mark as boundary
											newVertexN->setStatus(BOUNDARY);

											//create 2 new polygons
											Obool removePolygon = true;
											removePolygon &= CreateSubPolygon(polygonA, polygonA.NextIndex(si), polygonA.PrevIndex(si), newVertexN);
											removePolygon &= CreateSubPolygon(polygonA, polygonA.PrevIndex(si), si, newVertexN);
											if (removePolygon) {
												RemovePolygon(&polygonA);
											}
										}
										else {
											Vertex<T>* newVertexN = CreateEdgeVertex(intersectionLine, si, segmentA.startDistance(), polygonA);
											Vertex<T>* newVertexM = CreateEdgeVertex(intersectionLine, ei, segmentA.endDistance(), polygonA);

											//Mark as boundary
											newVertexN->setStatus(BOUNDARY);
											newVertexM->setStatus(BOUNDARY);

											//assure newVertexN is nearest to si (B)
											Vec3<T> nVec = newVertexN->point() - polygonA.vertex()[si]->point();
											Vec3<T> mVec = newVertexM->point() - polygonA.vertex()[si]->point();
											Obool mNearest = ((mVec*mVec) < (nVec*nVec));
											if (mNearest) {
												Vertex<T>* tmp = newVertexN;
												newVertexN = newVertexM;
												newVertexM = tmp;
											}

											//create 3 new polygons
											Obool removePolygon = true;
											removePolygon &= CreateSubPolygon(polygonA, polygonA.NextIndex(si), polygonA.PrevIndex(si), newVertexM);
											removePolygon &= CreateSubPolygon(polygonA, polygonA.PrevIndex(si), polygonA.PrevIndex(si), newVertexN, newVertexM);
											removePolygon &= CreateSubPolygon(polygonA, polygonA.PrevIndex(si), si, newVertexN);
											if (removePolygon) {
												RemovePolygon(&polygonA);
											}
										}
	}
		break;
	case Segment<T>::EDGE_FACE_VERTEX:
	{
											Vertex<T>* newVertexN = CreateEdgeVertex(intersectionLine, si, segmentA.startDistance(), polygonA);

											//Mark as boundary
											polygonA.vertex()[ei]->setStatus(BOUNDARY);
											newVertexN->setStatus(BOUNDARY);

											//create 2 new polygons
											Obool removePolygon = true;
											removePolygon &= CreateSubPolygon(polygonA, polygonA.NextIndex(si), ei, newVertexN);
											removePolygon &= CreateSubPolygon(polygonA, ei, si, newVertexN);
											if (removePolygon) {
												RemovePolygon(&polygonA);
											}
	}
		break;
	case Segment<T>::EDGE_FACE_EDGE:
	{
										Vertex<T>* newVertexN = CreateEdgeVertex(intersectionLine, si, segmentA.startDistance(), polygonA);
										Vertex<T>* newVertexM = CreateEdgeVertex(intersectionLine, ei, segmentA.endDistance(), polygonA);

										//Mark as boundary
										newVertexN->setStatus(BOUNDARY);
										newVertexM->setStatus(BOUNDARY);

										if (newVertexN == newVertexM)
											newVertexM = NULL;

										//create two new polygons
										Obool removePolygon = true;
										removePolygon &= CreateSubPolygon(polygonA, polygonA.NextIndex(ei), si, newVertexN, newVertexM);
										removePolygon &= CreateSubPolygon(polygonA, polygonA.NextIndex(si), ei, newVertexM, newVertexN);
										if (removePolygon) {
											RemovePolygon(&polygonA);
										}
	}
		break;
	case Segment<T>::EDGE_FACE_FACE:
	{
										Vertex<T>* newVertexN = CreateEdgeVertex(intersectionLine, si, segmentA.startDistance(), polygonA);
										Vertex<T>* newVertexM = CreateFaceVertex(intersectionLine, segmentA.endDistance(), polygonA);

										//Mark as boundary
										newVertexN->setStatus(BOUNDARY);
										newVertexM->setStatus(BOUNDARY);

										Obool removePolygon = true;

										//Obool collinear = Vertex<T>::Collinear(newVertexN, newVertexM, polygonA.vertex()[ei]);
										Obool collinear = Vertex<T>::Collinear(newVertexN, newVertexM, polygonA.vertex()[ei]);
										if (collinear) {
											//create 4 new polygons
											removePolygon &= CreateSubPolygon(polygonA, polygonA.NextIndex(si), polygonA.PrevIndex(ei), newVertexM, newVertexN);
											removePolygon &= CreateSubPolygon(polygonA, polygonA.NextIndex(ei), si, newVertexN, newVertexM);
											removePolygon &= CreateSubPolygon(polygonA, polygonA.PrevIndex(ei), ei, newVertexM);
											removePolygon &= CreateSubPolygon(polygonA, ei, polygonA.NextIndex(ei), newVertexM);
										}
										else {
											//create 3 new polygons
											removePolygon &= CreateSubPolygon(polygonA, polygonA.NextIndex(si), ei, newVertexM, newVertexN);
											removePolygon &= CreateSubPolygon(polygonA, polygonA.NextIndex(ei), si, newVertexN, newVertexM);
											removePolygon &= CreateSubPolygon(polygonA, ei, polygonA.NextIndex(ei), newVertexM);
										}
										if (removePolygon) {
											RemovePolygon(&polygonA);
										}
	}
		break;
	case Segment<T>::FACE_FACE_VERTEX:
	{
											//create one new vertex
											Vertex<T>* newVertex = CreateFaceVertex(intersectionLine, segmentA.startDistance(), polygonA);

											//Mark as boundary
											polygonA.vertex()[ei]->setStatus(BOUNDARY);
											newVertex->setStatus(BOUNDARY);

											Obool removePolygon = true;

											Obool collinear = Vertex<T>::Collinear(newVertex, polygonA.vertex()[si], polygonA.vertex()[ei]);
											//two cases
											if (collinear) {
												//create 4 new polygons
												removePolygon &= CreateSubPolygon(polygonA, polygonA.NextIndex(si), ei, newVertex);
												removePolygon &= CreateSubPolygon(polygonA, si, polygonA.NextIndex(si), newVertex);
												removePolygon &= CreateSubPolygon(polygonA, polygonA.PrevIndex(si), si, newVertex);
												removePolygon &= CreateSubPolygon(polygonA, ei, polygonA.PrevIndex(si), newVertex);
											}
											else {
												//create 3 new polygons
												removePolygon &= CreateSubPolygon(polygonA, polygonA.NextIndex(si), ei, newVertex);
												removePolygon &= CreateSubPolygon(polygonA, si, polygonA.NextIndex(si), newVertex);
												removePolygon &= CreateSubPolygon(polygonA, ei, si, newVertex);
											}
											if (removePolygon) {
												RemovePolygon(&polygonA);
											}
	}
		break;
	case Segment<T>::FACE_FACE_EDGE:
	{
										Vertex<T>* newVertexN = CreateEdgeVertex(intersectionLine, ei, segmentA.endDistance(), polygonA);
										Vertex<T>* newVertexM = CreateFaceVertex(intersectionLine, segmentA.startDistance(), polygonA);

										//Mark as boundary
										newVertexN->setStatus(BOUNDARY);
										newVertexM->setStatus(BOUNDARY);

										Obool removePolygon = true;

										Obool collinear = Vertex<T>::Collinear(newVertexN, newVertexM, polygonA.vertex()[si]);
										if (collinear) {
											//create 4 new polygons
											removePolygon &= CreateSubPolygon(polygonA, polygonA.NextIndex(ei), polygonA.PrevIndex(si), newVertexM, newVertexN);
											removePolygon &= CreateSubPolygon(polygonA, polygonA.NextIndex(si), ei, newVertexN, newVertexM);
											removePolygon &= CreateSubPolygon(polygonA, polygonA.PrevIndex(si), si, newVertexM);
											removePolygon &= CreateSubPolygon(polygonA, si, polygonA.NextIndex(si), newVertexM);
										}
										else {
											//create 3 new polygons
											removePolygon &= CreateSubPolygon(polygonA, polygonA.NextIndex(ei), si, newVertexM, newVertexN);
											removePolygon &= CreateSubPolygon(polygonA, polygonA.NextIndex(si), ei, newVertexN, newVertexM);
											removePolygon &= CreateSubPolygon(polygonA, si, polygonA.NextIndex(si), newVertexM);
										}
										if (removePolygon) {
											RemovePolygon(&polygonA);
										}
	}
		break;
	case Segment<T>::FACE_FACE_FACE:
	{
										Obool removePolygon = true;
										Obool onePoint = (Equal(segmentA.startDistance(), segmentA.endDistance()));
										Obool startOnIntersectionLine = polygonA.vertex()[si]->OnLine(intersectionLine.dir, intersectionLine.point);
										Obool endOnIntersectionLine = polygonA.vertex()[ei]->OnLine(intersectionLine.dir, intersectionLine.point);
										if (onePoint) {
											Vertex<T>* newVertexN = CreateFaceVertex(intersectionLine, segmentA.startDistance(), polygonA);

											//Mark as boundary
											newVertexN->setStatus(BOUNDARY);

											if (startOnIntersectionLine && endOnIntersectionLine) {
												//create 6 new polygons
												removePolygon &= CreateSubPolygon(polygonA, polygonA.NextIndex(ei), polygonA.PrevIndex(si), newVertexN);
												removePolygon &= CreateSubPolygon(polygonA, polygonA.PrevIndex(si), si, newVertexN);
												removePolygon &= CreateSubPolygon(polygonA, si, polygonA.NextIndex(si), newVertexN);
												removePolygon &= CreateSubPolygon(polygonA, polygonA.NextIndex(si), polygonA.PrevIndex(ei), newVertexN);
												removePolygon &= CreateSubPolygon(polygonA, polygonA.PrevIndex(ei), ei, newVertexN);
												removePolygon &= CreateSubPolygon(polygonA, ei, polygonA.NextIndex(ei), newVertexN);
											}
											else if (startOnIntersectionLine) {
												//create 5 new polygons
												removePolygon &= CreateSubPolygon(polygonA, polygonA.NextIndex(ei), polygonA.PrevIndex(si), newVertexN);
												removePolygon &= CreateSubPolygon(polygonA, polygonA.PrevIndex(si), si, newVertexN);
												removePolygon &= CreateSubPolygon(polygonA, si, polygonA.NextIndex(si), newVertexN);
												removePolygon &= CreateSubPolygon(polygonA, polygonA.NextIndex(si), ei, newVertexN);
												removePolygon &= CreateSubPolygon(polygonA, ei, polygonA.NextIndex(ei), newVertexN);
											}
											else if (endOnIntersectionLine) {
												//create 5 new polygons
												removePolygon &= CreateSubPolygon(polygonA, polygonA.NextIndex(ei), si, newVertexN);
												removePolygon &= CreateSubPolygon(polygonA, si, polygonA.NextIndex(si), newVertexN);
												removePolygon &= CreateSubPolygon(polygonA, polygonA.NextIndex(si), polygonA.PrevIndex(ei), newVertexN);
												removePolygon &= CreateSubPolygon(polygonA, polygonA.PrevIndex(ei), ei, newVertexN);
												removePolygon &= CreateSubPolygon(polygonA, ei, polygonA.NextIndex(ei), newVertexN);
											}
											else {
												//create 4 new polygons
												removePolygon &= CreateSubPolygon(polygonA, polygonA.NextIndex(ei), si, newVertexN);
												removePolygon &= CreateSubPolygon(polygonA, si, polygonA.NextIndex(si), newVertexN);
												removePolygon &= CreateSubPolygon(polygonA, polygonA.NextIndex(si), ei, newVertexN);
												removePolygon &= CreateSubPolygon(polygonA, ei, polygonA.NextIndex(ei), newVertexN);
											}
										}
										else {
											Vertex<T>* newVertexN = CreateFaceVertex(intersectionLine, segmentA.startDistance(), polygonA);
											Vertex<T>* newVertexM = CreateFaceVertex(intersectionLine, segmentA.endDistance(), polygonA);

											//Mark as boundary
											newVertexN->setStatus(BOUNDARY);
											newVertexM->setStatus(BOUNDARY);
											if (startOnIntersectionLine && endOnIntersectionLine) {
												//create 6 new polygons
												removePolygon &= CreateSubPolygon(polygonA, polygonA.NextIndex(ei), polygonA.PrevIndex(si), newVertexN, newVertexM);
												removePolygon &= CreateSubPolygon(polygonA, polygonA.PrevIndex(si), si, newVertexN);
												removePolygon &= CreateSubPolygon(polygonA, si, polygonA.NextIndex(si), newVertexN);
												removePolygon &= CreateSubPolygon(polygonA, polygonA.NextIndex(si), polygonA.PrevIndex(ei), newVertexM, newVertexN);
												removePolygon &= CreateSubPolygon(polygonA, polygonA.PrevIndex(ei), ei, newVertexM);
												removePolygon &= CreateSubPolygon(polygonA, ei, polygonA.NextIndex(ei), newVertexM);
											}
											else if (startOnIntersectionLine) {
												//create 5 new polygons
												removePolygon &= CreateSubPolygon(polygonA, polygonA.NextIndex(ei), polygonA.PrevIndex(si), newVertexN, newVertexM);
												removePolygon &= CreateSubPolygon(polygonA, polygonA.PrevIndex(si), si, newVertexN);
												removePolygon &= CreateSubPolygon(polygonA, si, polygonA.NextIndex(si), newVertexN);
												removePolygon &= CreateSubPolygon(polygonA, polygonA.NextIndex(si), ei, newVertexM, newVertexN);
												removePolygon &= CreateSubPolygon(polygonA, ei, polygonA.NextIndex(ei), newVertexM);
											}
											else if (endOnIntersectionLine) {
												//create 5 new polygons
												removePolygon &= CreateSubPolygon(polygonA, polygonA.NextIndex(ei), si, newVertexN, newVertexM);
												removePolygon &= CreateSubPolygon(polygonA, si, polygonA.NextIndex(si), newVertexN);
												removePolygon &= CreateSubPolygon(polygonA, polygonA.NextIndex(si), polygonA.PrevIndex(ei), newVertexM, newVertexN);
												removePolygon &= CreateSubPolygon(polygonA, polygonA.PrevIndex(ei), ei, newVertexM);
												removePolygon &= CreateSubPolygon(polygonA, ei, polygonA.NextIndex(ei), newVertexM);
											}
											else {
												//create 4 new polygons
												removePolygon &= CreateSubPolygon(polygonA, polygonA.NextIndex(ei), si, newVertexN, newVertexM);
												removePolygon &= CreateSubPolygon(polygonA, si, polygonA.NextIndex(si), newVertexN);
												removePolygon &= CreateSubPolygon(polygonA, polygonA.NextIndex(si), ei, newVertexM, newVertexN);
												removePolygon &= CreateSubPolygon(polygonA, ei, polygonA.NextIndex(ei), newVertexM);
											}
										}
										if (removePolygon) {
											RemovePolygon(&polygonA);
										}
	}
		break;
	default:
		//error: unhandeled intersection type
		assert(0);
	}

#ifdef DEBUG
	if (segmentA.IntersectionType() == Segment<T>::VERTEX_VERTEX_VERTEX
		|| segmentA.IntersectionType() == Segment<T>::VERTEX_EDGE_VERTEX
		|| segmentA.IntersectionType() == Segment<T>::EDGE_EDGE_VERTEX
		|| !printit)
		return;

	if (_polygonsDivided.size() == 0) {
		Polygon<T>::PrintCSV("\nNo subdivision results");
		return;
	}

	//first polygon in list could be deleted by that time 8(
	for (Ouint i = 0; i < _polygonsDivided.size(); ++i) {
		stringstream ss;
		ss << i + 2;
		_polygonsDivided[i]->AppendToFileCSV(ss.str());
	}
#endif

}

template <class T>
Vertex<T>*
Object<T>::CreateEdgeVertex(const Ray<T>& line, Oint index, T distance, Polygon<T>& polygon) {
	Vec3<T> newPoint = line.point + line.dir*distance;

	//project onto edge
	Ouint index2 = polygon.NextIndex(index);
	const Vec3<T>& v1 = polygon.vertex()[index]->point();
	const Vec3<T>& v2 = polygon.vertex()[index2]->point();
	Vec3<T> edgeDir = (v2 - v1);
	edgeDir.Normalize();

	newPoint = v1 + ((newPoint - v1)*edgeDir)*edgeDir;

	//clamp on edge
	T newDist = (newPoint - v1)*edgeDir;
	if (newDist < 0) {
		newPoint = v1;
	}
	else if (newDist >(v2 - v1)*edgeDir) {
		newPoint = v2;
	}

	//get or create vertex corresponding to the new point
	return GetCreateVertex(newPoint);
}

template <class T>
Vertex<T>*
Object<T>::CreateFaceVertex(const Ray<T>& line, T distance, Polygon<T>& polygon) {
	Vec3<T> newPoint = line.point + line.dir*distance;

	//project onto poly
	T dist = polygon.normal()*newPoint + polygon.d();
	newPoint -= polygon.normal()*dist;

	//get or create vertex corresponding to the new point
	return GetCreateVertex(newPoint);
}

template <class T>
Vertex<T>*
Object<T>::GetCreateVertex(const Vec3<T>& point) {
	Vertex<T>* newVertex = GetExistingVertex(point);
	if (!newVertex) {
		newVertex = new Vertex<T>(point);
		_vertex.push_back(newVertex);
#ifdef DEBUG
		_vertex[_vertex.size() - 1]->id = _vertex.size() - 1;
#endif
	}
	return newVertex;
}

template <class T>
Vertex<T>*
Object<T>::GetExistingVertex(const Vec3<T>& point) {
	//test if point already exists in Object
	for (Ouint i = 0; i < _vertex.size(); ++i) {
		if (_vertex[i]->point().Equal(point, Vertex<T>::tolerance)) {
			return _vertex[i];
		}
	}
	return NULL;
}

template <class T>
Obool
Object<T>::AddSubPolygon(Polygon<T>& oldPolygon, Polygon<T>* subPolygon) {
	if (!subPolygon)
		return true; //WTF? We did not add any polygon, so why does the result of operation equal true?

	if (subPolygon->IsEqual(oldPolygon)) {
		delete subPolygon;
		subPolygon = NULL;
#ifdef DEBUG
		//_polygonsDivided.push_back(_polygon[oldPolygon._index]);
		_polygonsDivided.push_back(&oldPolygon);
#endif
		return false;
	}
	subPolygon->setIndex(_polygon.size());
	_polygon.push_back(subPolygon);
#ifdef DEBUG
	_polygonsDivided.push_back(subPolygon);
#endif
	return true;
}

template <class T>
bool
Object<T>::CreateSubPolygon(
Polygon<T>& oldPolygon,
Ouint startIndex,
Ouint endIndex,
Vertex<T>* newVertex1,
Vertex<T>* newVertex2) {
	std::vector<Vertex<T>*> vertex;
	Ouint i = startIndex;
	while (i != endIndex) {
		vertex.push_back(oldPolygon.vertex()[i]);
		i = oldPolygon.NextIndex(i);
	}

	//add the end vertex
	vertex.push_back(oldPolygon.vertex()[endIndex]);
	//add the new vertices if specified
	if (newVertex1)
		vertex.push_back(newVertex1);
	if (newVertex2)
		vertex.push_back(newVertex2);

	if (vertex.size() > 2) {
		Polygon<T>* newPolygon = new Polygon<T>(vertex, 0);
		return AddSubPolygon(oldPolygon, newPolygon);
#if DEBUG
		newPolygon->PrintToFileCSV("C:\\octaga_tmp\\logs\\noValidAndNoAllocPoligon.csv", "222");
#endif
		delete newPolygon;
	}
	return false;
}

template <class T>
void
Object<T>::RemovePolygon(Polygon<T>* polygon) {
	Ouint polygonIndex = polygon->index();
	if ((polygonIndex < _polygon.size()) && (polygonIndex >= 0)) {
		Polygon<T>* polyAtIndex = _polygon[polygonIndex];
		if (polyAtIndex == polygon) { // verify polygon is the same
			delete polyAtIndex;
			_polygon[polygonIndex] = NULL;
			return;
		}
	}

	//if not found by index, search by element
	std::vector<Polygon<T>*>::iterator it = std::find(_polygon.begin(), _polygon.end(), polygon);
	if (it != _polygon.end()) {
		delete *it;
		(*it) = NULL;
	}
}

template <class T>
void
Object<T>::CleanPolygonList() {
	//clean up
	Ouint i = 0;
	while (i < _polygon.size()) {
		if (_polygon[i] == NULL) {
			_polygon[i] = _polygon.back();
			_polygon.pop_back();
		}
		else {
			++i;
		}
	}
}


//This algorithm looks for  for closest intersected polygon
//if we got several polygon as result - this means we hit the boundary of adjacent polygons.
//If their normals point in one direction choose any polygon. Otherwise we need to check distance to their barycenter and take closest one.
template <class T>
RELPOS_STATUS
Object<T>::FindRelativePosition(const Polygon<T>& polygonA) const {
	Vec3<T> barycenter = polygonA.CalcBarycenter();
	Vec3<T> normalA(polygonA.normal());
	Vec3<T> rayFromA(normalA);

	T shortestIntersectionDistance;
	Obool initialized = false; //since we can not assign min or max for type T we will use this flag

	vector<Polygon<T>*> closestPolygons;

	Obool polygonAMeaning = polygonA.IsMeaning();

	for (Oint i = 0; i < _polygon.size(); ++i) {
		Polygon<T>& polygonB = *_polygon[i];
		T distance = Polygon<T>::PlaneToPointDistance(polygonB, barycenter);

		Obool orderOfTolerance = !polygonB.IsMeaning() || !polygonAMeaning;

		//If no polygon is meaning (i.e. both polygons greater than order of tolerance than compare as always otherwise use epsilon as tolerance
		if ((!orderOfTolerance && EQ(distance, T(0), Vertex<T>::tolerance)) ||
			(orderOfTolerance && EQ(distance, T(0), Vertex<T>::epsilonValue))) { //polygons are the same or lay in one plane (cannot intersect!)
			RELPOS_STATUS relPosB = polygonB.FindRelativePosition(barycenter);
			if (relPosB == INSIDE || relPosB == BOUNDARY) {
				//find the DOT PRODUCT of RAY direction with the normal of polygonB
				T dotProduct = rayFromA*polygonB.normal();
				// according to the algorithm 
				if (GE(dotProduct, T(0), Vertex<T>::tolerance)) {
					return SAME;
				}
				else if (LT(dotProduct, T(0), Vertex<T>::tolerance)) {
					return OPPOSITE;
				}
			}
		}
		else {
			//find intersection dist of ray with plane of polygonB
			T intDist = polygonB.IntersectRayWithPlane(barycenter, rayFromA);

			T dotProduct = rayFromA * polygonB.normal();
			Obool isDotZero = EQ(dotProduct, T(0), Vertex<T>::tolerance);
			Obool isDistancePositive = GT(distance, T(0), Vertex<T>::tolerance);

			if (LT(intDist, T(0), Vertex<T>::tolerance) || (isDotZero && isDistancePositive)) {
				continue;//parallel or behind the polygonA
			}

			Vec3<T> intersection = barycenter + rayFromA*intDist;
			RELPOS_STATUS pos = polygonB.FindRelativePosition(intersection);
			if (pos == OUTSIDE)
				continue;

			if (!initialized) {
				shortestIntersectionDistance = intDist;
				initialized = true;
				closestPolygons.push_back(_polygon[i]);
			}

			if (LT(intDist, shortestIntersectionDistance)) {
				shortestIntersectionDistance = intDist;
				closestPolygons.clear();
				closestPolygons.push_back(_polygon[i]);
			}

			if (EQ(intDist, shortestIntersectionDistance)) {
				closestPolygons.push_back(_polygon[i]);
			}
		}
	}


	Ouint selectedPolygon = _ChooseClosestPolygon(initialized, closestPolygons, barycenter);

	if (selectedPolygon == -1) {
		return OUTSIDE;
	}

	T dotProduct = rayFromA*closestPolygons[selectedPolygon]->normal();
	// according to the algorithm 
	if (GT(dotProduct, T(0), Vertex<T>::tolerance)) {
		return INSIDE;
	}
	else if (LT(dotProduct, T(0), Vertex<T>::tolerance)) {
		return OUTSIDE;
	}
}


template<class T>
Ouint
Object<T>::_ChooseClosestPolygon(Obool &initialized, vector<Polygon<T>*> &polygons, Vec3<T> &barycenter) const {
	T shortestDistance, distanceA, distanceB;
	initialized = false;
	Ouint selectedPolygon = 0;

	if (polygons.size() == 0)
		return -1;

	if (polygons.size() == 1)
		return selectedPolygon;

	for (int i = 1; i < polygons.size(); ++i) {

		Vec3<T> normA = polygons[i - 1]->normal();
		Vec3<T> normB = polygons[i]->normal();

		if (normA*normB > 0) { //if their normal points in one direction choose any of them
			Vec3<T> barycenterB = polygons[i]->CalcBarycenter();
			distanceB = barycenter.Distance(barycenterB);
			if (!initialized || LE(shortestDistance, distanceB)) {
				shortestDistance = distanceB;
				selectedPolygon = i;
			}
		}
		else { //otherwise choose closest one
			Vec3<T> barycenterA = polygons[selectedPolygon]->CalcBarycenter();
			Vec3<T> barycenterB = polygons[i]->CalcBarycenter();

			distanceA = barycenter.Distance(barycenterA);
			distanceB = barycenter.Distance(barycenterB);

			T min = LE(distanceA, distanceB) ? distanceA : distanceB;

			if (!initialized || LE(shortestDistance, min)) {
				shortestDistance = min;
				selectedPolygon = i - 1;
			}
		}
	}

	return selectedPolygon;
}


template <class T>
void
Object<T>::MakeCcwEx() {
	if (_polygon.size() == 0)
		return;
	Vec3<T> randVec(0, 0, 0);
	Oint counter = 0;
	RELPOS_STATUS pos_status = UNKNOWN;
	for (int p = 0; p < _polygon.size(); p++) {
		Polygon<T>& polygonA = *_polygon[p];
		_MakeCcw(polygonA);
	}
}

template <class T>
void
Object<T>::MakeCcw() {
	if (_polygon.size() == 0)
		return;
	Oint counter = 0;
	const Polygon<T>& polygonA = *_polygon[0];
	_MakeCcw(polygonA);
}

template <class T>
void
Object<T>::_MakeCcw(const Polygon<T>& polygonA) {
	if (_polygon.size() == 0)
		return;
	Oint counter = 0;
	Vec3<T> barycenter = polygonA.CalcBarycenter();
	Vec3<T> rayFromA(polygonA.normal());
	RELPOS_STATUS pos_status = UNKNOWN;
	std::map<Ouint, vector<Polygon<T>*>> adjacentPolygons;
	Ouint adjacentGroup = 0;
	for (Ouint i = 1; i < _polygon.size(); i++) {
		const Polygon<T>& polygonB = *_polygon[i];
		T distance = Polygon<T>::PlaneToPointDistance(polygonB, barycenter);
		if (EQ(distance, T(0), Vertex<T>::tolerance)) {
			continue;
		}
		T intDist = polygonB.IntersectRayWithPlane(barycenter, rayFromA);
		if (LE(intDist, T(0), Vertex<T>::tolerance)) {
			continue;
		}
		Vec3<T> intersection = barycenter + rayFromA*intDist;
		pos_status = polygonB.FindRelativePosition(intersection);
		if (pos_status == BOUNDARY) {
			//Look for appropriate adjacent group
			Obool isNewAdjacentGroup = true;
			for (map<Ouint, vector<Polygon<T>*>>::iterator it = adjacentPolygons.begin(); it != adjacentPolygons.end() && isNewAdjacentGroup; ++it) {
				for (int j = 0; j < it->second.size(); ++j) {
					if (polygonB.IsAdjacent(*(it->second[j]))) {
						it->second.push_back(_polygon[i]);
						isNewAdjacentGroup = false;
						break;
					}
				}
			}

			if (isNewAdjacentGroup) {
				++adjacentGroup;
				adjacentPolygons[adjacentGroup] = vector<Polygon<T>*>();
				adjacentPolygons[adjacentGroup].push_back(_polygon[i]);
			}
		}
		else if (pos_status == INSIDE) {
			counter++;
		}
	}

	for (map<Ouint, vector<Polygon<T>*>>::iterator it = adjacentPolygons.begin(); it != adjacentPolygons.end(); ++it) {
		T dotProductSign = 1;
		for (int j = 0; j < it->second.size(); ++j) {
			Polygon<T>* current = it->second[j];
			Polygon<T>* next = (j + 1 == it->second.size())
				? it->second[0]
				: it->second[j + 1];

			T dotProduct = current->normal() * next->normal();
			if (dotProductSign != 0)
				dotProductSign *= dotProduct;
		}

		if (dotProductSign > 0)
			++counter;
	}

	if (counter % 2 != 0) {
		for (Ouint j = 0; j < _polygon.size(); j++) {
			_polygon[j]->Reverse();
			_polygon[j]->CalculatePlaneEquation();
		}
	}
}

//Find outer perimeters and inner perimeters of facet and re-triangulate it, replacing current polygons **NOT WORKING NEED TO REMOVE OR FIX** (see SVN)
template <class T>
void
Object<T>::Simplify(T multiplierUnion) {
	return;
}

template <class T>
std::vector<std::pair<std::vector<Oint>, Obool>>
Object<T>::GetPerimeters(std::map<Vertex<T>*, Oint> vertexMap, std::map<Oint, Vertex<T>*> indexMap, std::vector<Polygon<T>*> polygons) {

	Vec3<T> normal = polygons[0]->_normal;
	//check polygons
	for (Ouint i = 0; i < polygons.size() - 1; i++) {
		Polygon<T>* pi = polygons[i];
		for (Ouint j = i + 1; j < polygons.size(); j++) {
			Polygon<T>* pj = polygons[j];
			pi->AddVertices(pj);
			pj->AddVertices(polygons[i]);
			polygons[i] = pi;
			polygons[j] = pj;
		}

	}

	//find "lonely" edges (will be marked as "true")
	std::map<std::pair<Oint, Oint>, Obool> edges;
	for (Ouint j = 0; j < polygons.size(); j++) {
		Polygon<T>* poly = polygons[j];
		Oint p0 = vertexMap[poly->_vertex[poly->_vertex.size() - 1]];
		for (Ouint k = 0; k < poly->_vertex.size(); k++) {
			Oint p1 = vertexMap[poly->_vertex[k]];
			std::pair<Oint, Oint> key = std::pair<Oint, Oint>(p1, p0);
			if (edges.find(key) != edges.end()) {
				edges[key] = false;
			}
			else {
				key = std::pair<Oint, Oint>(p0, p1);
				edges[key] = true;
			}
			p0 = p1;
		}
	}

	//make perimeter(s) using those edges
	std::vector<std::pair<std::vector<Oint>, Obool>> perimeters;
	_MakePerimeters(edges, perimeters);

	_ClearCollinearPoints(perimeters, indexMap);

	return perimeters;
}

template<class T>
void
Object<T>::_MakePerimeters(std::map<std::pair<Oint, Oint>, Obool> &edges, std::vector<std::pair<std::vector<Oint>, Obool>> &perimeters) {
	Obool changed = true;
	Oint curIndex = -1;
	std::vector<Oint> perimeter;
	while (changed) {
		changed = false;
		std::map<std::pair<Oint, Oint>, Obool>::iterator it = edges.begin();
		while (it != edges.end()) {
			if (it->second) {
				if (curIndex == -1) {
					if (perimeter.size() > 0) {
						perimeters.push_back(std::pair<std::vector<Oint>, Obool>(perimeter, true));
					}
					perimeter.clear();
					it->second = false;
					curIndex = it->first.second;
					perimeter.push_back(it->first.first);
#if DEBUG
					Oint ind = it->first.first;
#endif

					changed = true;
				}
				else {
					if (it->first.first == curIndex) {
						it->second = false;
						curIndex = it->first.second;
						perimeter.push_back(it->first.first);
						changed = true;
					}
				}
			}
			*it++;
		}
		if (!changed && curIndex != -1) {
			changed = true;
			curIndex = -1;
		}
	}
	if (perimeter.size() > 0) {
		perimeters.push_back(std::pair<std::vector<Oint>, Obool>(perimeter, true));
	}
}

template <class T>
void Object<T>::_ClearCollinearPoints(std::vector<std::pair<std::vector<Oint>, Obool>> &perimeters, std::map<Oint, Vertex<T>*> &indexMap) {
	//remove collinear points and decide outer/inner perimeters
	std::vector<Oint> perimeter;

	for (Ouint i = 0; i < perimeters.size(); i++) {
		perimeter = perimeters[i].first;
		if (perimeter.size() < 3)
			continue;
		Oint i0 = perimeter[1];
		Oint i1 = perimeter[0];
		Oint i2;
		Oint removeIndex = 0;
		//Vec3<T>* pn = NULL;
		for (Oint j = perimeter.size() - 1; j >= 0; j--) {
			i2 = perimeter[j];
			if (Vertex<T>::Collinear(indexMap[i0], indexMap[i1], indexMap[i2])) {
				perimeter.erase(perimeter.begin() + removeIndex);
				if (removeIndex < j)
					j--;
			}
			else {
				i0 = i1;
			}
			removeIndex = j;
			i1 = i2;
		}
		//check first point just in case
		if (perimeter.size() > 3 && Vertex<T>::Collinear(indexMap[perimeter[1]], indexMap[perimeter[0]], indexMap[perimeter[perimeter.size() - 1]]))
			perimeter.erase(perimeter.begin() + removeIndex);

		//check ccw
		T angle = 0;
		Oint size = (Oint)perimeter.size();
		if (size > 2) {
			Oint j = size - 1;
			Oint k = size - 2;
			for (Oint i = 0; i < size; ++i) {
				Vec3<T> v0 = indexMap[perimeter[j]]->point() - indexMap[perimeter[k]]->point();
				Vec3<T> v1 = indexMap[perimeter[i]]->point() - indexMap[perimeter[j]]->point();
				T tmp = v0.CosAngle(v1);
				if (tmp > 1.0)
					tmp = 0.0;
				else if (tmp < -1.0)
					tmp = PI;
				else
					tmp = acos(tmp);
				if (v0.Cross(v1)*normal < 0)
					tmp *= -1.0f;
				angle += tmp;
				k = j;
				j = i;
			}
		}

		//perimeters[i].second = pn->Equal(normal, Vertex<T>::unitTolerance);
		perimeters[i].second = angle >= 0;
		perimeter.push_back(-1);
		perimeters[i].first = perimeter;
	}
}


template <class T>
std::map<std::pair<Oint, Oint>, Oint>
Object<T>::GetEdgeMap() {
	std::vector<Oint> coordIndex;
	GetFaceSetIndexes(coordIndex);

	std::map<std::pair<Oint, Oint>, Oint> edgeMap;
	Ouint startIndex = 0;
	std::pair<Oint, Oint> edge;
	for (Ouint i = 0; i < coordIndex.size(); ++i) {
		while (i < coordIndex.size() && coordIndex[i] != -1) { // ave. bad style ! - need fix it
			++i;
		}
		for (Ouint j = startIndex + 1; j < i; ++j) {
			if (coordIndex[j] < coordIndex[j - 1])
				edge = std::pair<Oint, Oint>(coordIndex[j], coordIndex[j - 1]);
			else
				edge = std::pair<Oint, Oint>(coordIndex[j - 1], coordIndex[j]);
			if (edgeMap.find(edge) == edgeMap.end())
				edgeMap[edge] = 1;
			else
				edgeMap[edge] = edgeMap[edge] + 1;
		}
		if (coordIndex[i - 1] < coordIndex[startIndex])
			edge = std::pair<Oint, Oint>(coordIndex[i - 1], coordIndex[startIndex]);
		else
			edge = std::pair<Oint, Oint>(coordIndex[startIndex], coordIndex[i - 1]);
		if (edgeMap.find(edge) == edgeMap.end())
			edgeMap[edge] = 1;
		else
			edgeMap[edge] = edgeMap[edge] + 1;
		startIndex = i + 1;
	}
	return edgeMap;
}

template <class T>
Obool
Object<T>::UnionWithNeighborPolygon(Polygon<T> &polygonA) const {
	Obool result = false;
	for (Ouint i = 0; i < _polygon.size(); i++) {
		const Polygon<T>& polygonB = *_polygon[i];
		if (polygonA.IsEqual(polygonB))
			continue;
		if (!polygonA.IsCoplanar(&polygonB))
			continue;
		//Find maximum side of polygonA
		std::pair<Vertex<T>, Vertex<T>> segmentMaxA = polygonA.FindMaxSegment();
		if (polygonB.isHasVertex(segmentMaxA.first) ||
			polygonB.isHasVertex(segmentMaxA.second)) {
			//neighbor polygon found
			polygonA.AddVertices(&polygonB);
			result = true;
		}
	}
	return result;
}

#ifdef DEBUG
template <class T>
void
Object<T>::AddPolygon(vector<Vertex<T>*> vertices) {
	for (Ouint i = 0; i < vertices.size(); ++i) {
		Vec3<T> v = vertices[i]->point();
		_vertex.push_back(new Vertex<T>(v));
	}
	_polygon.push_back(new Polygon<T>(vertices, _polygon.size()));
	CalculateExtents();
}
#endif
} // namespace enterprise_manager
