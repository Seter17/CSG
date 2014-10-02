namespace enterprise_manager {

	template <typename T>
	inline const Vec3<T>&
		Vertex<T>::point() const {
			return _point;
		}

	template <typename T>
	inline void
		Vertex<T>::setStatus(RELPOS_STATUS status) {
			_status = status;
		}

	template <typename T>
	inline RELPOS_STATUS
		Vertex<T>::status() const {
			return _status;
		}

	template <typename T>
	Vertex<T>::Vertex(const Vec3<T>& point)
		: _point(point),
		_adjacentVertex(),
		_status(UNKNOWN) {}

	template <typename T>
	/* virtual */
	Vertex<T>::~Vertex() {}

	template <typename T>
	/*static*/ void
		Vertex<T>::Join(Vertex* vertexA, Vertex* vertexB) {
			// Add if not already in array.
			if (std::find(vertexA->_adjacentVertex.begin(), vertexA->_adjacentVertex.end(), vertexB) == vertexA->_adjacentVertex.end()) {
				vertexA->_adjacentVertex.push_back(vertexB);
				vertexB->_adjacentVertex.push_back(vertexA);
#ifdef DEBUG
				vertexA->parents.push_back(vertexB->id);
				vertexB->parents.push_back(vertexA->id);
#endif
			}
		}

	template <typename T>
	Obool
		Vertex<T>::Collinear(Vertex* A, Vertex* B, Vertex* C) {
			switch (MaxSectionAtVertex(A, B, C)) {
			case AB:
				return IsAltCollinear(A, B, C);
			case AC:
				return IsAltCollinear(A, C, B);
			case BC:
			default:
				return IsAltCollinear(B, C, A);
			}
		}

	template <typename T>
	Obool
		Vertex<T>::OnLineOfIntersection(const Vec3<T>& dir, const Vec3<T>& point) const {
			Vec3<T> dir2 = _point - point;
			dir2.Normalize();
			return (UnitEqual(abs(dir*dir2), T(1)));
		}

	template <typename T>
	Obool
		Vertex<T>::OnLine(const Vec3<T>& dir, const Vec3<T>& point) const {
			Vec3<T> dir2 = _point - point;

			Vec3<T> v = ((dir * dir2) * dir) - dir2;
			return (v.LengthSqr() < Vertex<T>::tolerance * Vertex<T>::tolerance);
		}

	template <typename T>
	void
		Vertex<T>::MarkConnectedVertices(RELPOS_STATUS status) {
			_status = status;
			for (Ouint i = 0; i < _adjacentVertex.size(); ++i) {
				if (_adjacentVertex[i]->status() == UNKNOWN) {
					_adjacentVertex[i]->setStatus(status);
					_adjacentVertex[i]->MarkConnectedVertices(status);
				}
			}
		}

	template <typename T>
	void
		Vertex<T>::ClearAdjacencyInfo() {
			_adjacentVertex.clear();
		}


	template <class T>
	/* static */ SIDE_TRIANGLE
		Vertex<T>::MaxSectionAtVertex(const Vertex<T>* A, const Vertex<T>* B, const Vertex<T>* C) {
			Vec3<T> a_b = A->point() - B->point();
			Vec3<T> a_c = A->point() - C->point();
			Vec3<T> b_c = B->point() - C->point();
			T ab_length = a_b.Length();
			T ac_length = a_c.Length();
			T bc_length = b_c.Length();

			if (ab_length > ac_length &&
				ab_length > bc_length)
				return AB;
			if (ac_length > ab_length &&
				ac_length > bc_length)
				return AC;
			if (bc_length > ab_length &&
				bc_length > ac_length)
				return BC;
			return AB;
		}

	template <class T>
	/* static */ Obool
		Vertex<T>::IsAltCollinear(const Vertex<T>* A, const Vertex<T>* B, const Vertex<T>* C) {
			if (A->point().Equal(B->point(), Vertex<T>::tolerance) ||
				A->point().Equal(C->point(), Vertex<T>::tolerance) ||
				B->point().Equal(C->point(), Vertex<T>::tolerance))
				return true;
			Vec3<T> b_a = B->point() - A->point();
			b_a.Normalize();
			Vec3<T> c_a = C->point() - A->point();
			Vec3<T> c_height = c_a - (c_a * b_a) * b_a;
			return EQ(c_height * c_height, T(0), Vertex<T>::tolerance*Vertex<T>::tolerance);
		}

} // namespace enterprise_manager

