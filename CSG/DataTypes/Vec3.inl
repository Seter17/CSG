namespace enterprise_manager {

	template <class T>
	inline
		Vec3<T>::Vec3() {
			_vec[0] = _vec[1] = _vec[2] = 0;
		}

	template <class T>
	inline
		Vec3<T>::Vec3(const T& x, const T& y, const T& z) {
			_vec[0] = x;
			_vec[1] = y;
			_vec[2] = z;
		}

	template <class T>
	inline
		Vec3<T>::Vec3(const Vec2<T>& vec, const T& z) {
			_vec[0] = vec._vec[0];
			_vec[1] = vec._vec[1];
			_vec[2] = z;
		}

	template <class T>
	inline
		Vec3<T>::Vec3(const Vec3<T>& vec) {
			_vec[0] = vec._vec[0];
			_vec[1] = vec._vec[1];
			_vec[2] = vec._vec[2];
		}

	template <class T>
	inline
		Vec3<T>::~Vec3() {}

	template <class T>
	inline T
		Vec3<T>::operator*(const Vec3<T>& vec) const {
			return (_vec[0] * vec._vec[0] +
				_vec[1] * vec._vec[1] +
				_vec[2] * vec._vec[2]);
		}

	template <class T>
	inline Vec3<T>&
		Vec3<T>::operator*=(const T& value) {
			_vec[0] *= value;
			_vec[1] *= value;
			_vec[2] *= value;
			return *this;
		}

	template <class T>
	inline Vec3<T>&
		Vec3<T>::operator/=(const Vec3<T>& vec) {
			_vec[0] /= vec._vec[0];
			_vec[1] /= vec._vec[1];
			_vec[2] /= vec._vec[2];
			return *this;
		}

	template <class T>
	inline Vec3<T>&
		Vec3<T>::operator/=(const T& value) {
			_vec[0] /= value;
			_vec[1] /= value;
			_vec[2] /= value;
			return *this;
		}

	template <class T>
	inline Vec3<T>&
		Vec3<T>::operator+=(const Vec3<T>& vec) {
			_vec[0] += vec._vec[0];
			_vec[1] += vec._vec[1];
			_vec[2] += vec._vec[2];
			return *this;
		}

	template <class T>
	inline Vec3<T>
		Vec3<T>::operator-() const {
			return Vec3<T>(-_vec[0], -_vec[1], -_vec[2]);
		}

	template <class T>
	inline Vec3<T>&
		Vec3<T>::operator-=(const Vec3<T>& vec) {
			_vec[0] -= vec._vec[0];
			_vec[1] -= vec._vec[1];
			_vec[2] -= vec._vec[2];
			return *this;
		}

	template <class T>
	inline Obool
		Vec3<T>::operator==(const Vec3<T>& vec) const {
			return (_vec[0] == vec._vec[0] &&
				_vec[1] == vec._vec[1] &&
				_vec[2] == vec._vec[2]);
		}

	template <class T>
	inline Obool
		Vec3<T>::operator==(const T& value) const {
			return (_vec[0] == value &&
				_vec[1] == value &&
				_vec[2] == value);
		}

	template <class T>
	inline Obool
		Vec3<T>::Equal(const Vec3<T>& vec, const T& tolerance) const {
			return (DistanceSqr(vec) <= tolerance*tolerance);
		}

	template <class T>
	inline Obool
		Vec3<T>::Equal(const T& value, const T& tolerance) const {
			return ((fabs(_vec[0] - value) <= tolerance) &&
				(fabs(_vec[1] - value) <= tolerance) &&
				(fabs(_vec[2] - value) <= tolerance));
		}

	template <class T>
	inline Obool
		Vec3<T>::operator!=(const Vec3<T>& vec) const {
			return (_vec[0] != vec._vec[0] ||
				_vec[1] != vec._vec[1] ||
				_vec[2] != vec._vec[2]);
		}

	template <class T>
	inline Obool
		Vec3<T>::operator!=(const T& value) const {
			return (_vec[0] != value ||
				_vec[1] != value ||
				_vec[2] != value);
		}

	template <class T>
	inline Vec3<T>&
		Vec3<T>::operator=(const Vec3<T>& vec) {
			_vec[0] = vec._vec[0];
			_vec[1] = vec._vec[1];
			_vec[2] = vec._vec[2];
			return *this;
		}

	template <class T>
	inline T&
		Vec3<T>::operator[](const Oint i) {
			return _vec[i];
		}

	template <class T>
	inline T
		Vec3<T>::operator[](const Oint i) const {
			return _vec[i];
		}

	template <class T>
	inline T
		Vec3<T>::Length() const {
			return static_cast<T>(sqrt(_vec[0] * _vec[0] + _vec[1] * _vec[1] + _vec[2] * _vec[2]));
		}

	template <class T>
	inline T
		Vec3<T>::LengthSqr() const {
			return (_vec[0] * _vec[0] + _vec[1] * _vec[1] + _vec[2] * _vec[2]);
		}

	template <class T>
	inline Vec3<T>&
		Vec3<T>::Normalize() {
			T length = sqrt(_vec[0] * _vec[0] + _vec[1] * _vec[1] + _vec[2] * _vec[2]);
			if (length != 0) {
				T length_1 = 1 / length;
				_vec[0] *= length_1;
				_vec[1] *= length_1;
				_vec[2] *= length_1;
			}
			return *this;
		}

	template <class T>
	inline T
		Vec3<T>::Distance(const Vec3<T>& vec) const {
			T sqr_x(_vec[X] - vec._vec[X]);
			T sqr_y(_vec[Y] - vec._vec[Y]);
			T sqr_z(_vec[Z] - vec._vec[Z]);

			sqr_x *= sqr_x;
			sqr_y *= sqr_y;
			sqr_z *= sqr_z;

			return T(sqrt(sqr_x + sqr_y + sqr_z));
		}

	template <class T>
	inline T
		Vec3<T>::DistanceSqr(const Vec3<T>& vec) const {
			T sqr_x(_vec[X] - vec._vec[X]);
			T sqr_y(_vec[Y] - vec._vec[Y]);
			T sqr_z(_vec[Z] - vec._vec[Z]);

			sqr_x *= sqr_x;
			sqr_y *= sqr_y;
			sqr_z *= sqr_z;

			return sqr_x + sqr_y + sqr_z;
		}

	template <class T>
	inline T
		Vec3<T>::DistanceToSegment(Vec3<T> s0, Vec3<T> s1) const {
			Vec3<T> v = s1 - s0;
			Vec3<T> w = *this - s0;

			T c1 = w * v;
			if (c1 <= 0)
				return sqrt(w * w);

			T c2 = v * v;
			if (c2 <= c1) {
				Vec3<T> ww = *this - s1;
				return sqrt(ww * ww);
			}

			T b = c1 / c2;
			Vec3<T> pb = s0 + b * v;
			Vec3<T> res = *this - pb;
			return sqrt(res * res);
		}

	template <class T>
	inline T
		Vec3<T>::CosAngle(const Vec3<T>& vec) const {
			T lengthSq = (_vec[X] * _vec[X] + _vec[Y] * _vec[Y] + _vec[Z] * _vec[Z])  *
				(vec._vec[X] * vec._vec[X] + vec._vec[Y] * vec._vec[Y] + vec._vec[Z] * vec._vec[Z]);
			if (lengthSq != 0)
				return  ((_vec[X] * vec._vec[X] +     //dot product
				_vec[Y] * vec._vec[Y] +
				_vec[Z] * vec._vec[Z]) /
				sqrtf((Ofloat)lengthSq));
			return 0;
		}

	template <class T>
	inline T
		Vec3<T>::AngleToAxis(Oint axis, Obool normalised) const {
			/** Calculate dot product. This is just 1 x the component of the vector
			parallel to the specified axis.
			*/
			Odouble angle;
			T dot_product = _vec[axis];

			// Normalise if necessary
			if (!normalised) {
				dot_product /= Length();
			}

			// Check if orthogonal
			if (fabs(dot_product) < TOLERANCE) {
				// Vec3<T> is orthogonal to axis
				angle = PI * 0.5;
			}
			else if (fabs(dot_product - 1.0f) < TOLERANCE) {
				// Vec3<T> is parallel to axis
				angle = 0.0f;
			}
			else {
				// Otherwise calculate angle by arcosine
				assert((dot_product >= -1.0f) && (dot_product <= 1.0f));

				// Take the arcosine
				angle = ::acos(dot_product);

				// Check if the angle is bigger than 180 deg, if so make it a negative angle
				if (angle >= PI) {
					angle = -1 * ((2 * PI) - angle);
				}
			}
			return static_cast<T>(angle);
		}

	template <class T>
	inline Vec3<T>
		Vec3<T>::Cross(const Vec3<T> &vec) const {
			return Vec3<T>(_vec[Y] * vec._vec[Z] - _vec[Z] * vec._vec[Y],
				_vec[Z] * vec._vec[X] - _vec[X] * vec._vec[Z],
				_vec[X] * vec._vec[Y] - _vec[Y] * vec._vec[X]);
		}

	template <class T>
	inline Vec3<T>
		Vec3<T>::MultiplyComp(const Vec3<T> &vec) const {
			return Vec3<T>(_vec[X] * vec._vec[X], _vec[Y] * vec._vec[Y], _vec[Z] * vec._vec[Z]);
		}

	template <class T>
	inline void
		Vec3<T>::MaxComp(const Vec3<T> &vec) {
			if (vec._vec[X] > _vec[X])
				_vec[X] = vec._vec[X];
			if (vec._vec[Y] > _vec[Y])
				_vec[Y] = vec._vec[Y];
			if (vec._vec[Z] > _vec[Z])
				_vec[Z] = vec._vec[Z];
		}


	template <class T>
	inline void
		Vec3<T>::MinComp(const Vec3<T> &vec) {
			if (vec._vec[X] < _vec[X])
				_vec[X] = vec._vec[X];
			if (vec._vec[Y] < _vec[Y])
				_vec[Y] = vec._vec[Y];
			if (vec._vec[Z] < _vec[Z])
				_vec[Z] = vec._vec[Z];
		}

	template <class T>
	inline const T*
		Vec3<T>::Ptr() const {
			return _vec;
		}

	template <class T>
	inline Vec3<T>&
		Vec3<T>::FastMultiply(const Matrix4<T>& mat) {
			T tmp1 = _vec[X] * mat._elements[Matrix4<T>::a00] +
				_vec[Y] * mat._elements[Matrix4<T>::a10] +
				_vec[Z] * mat._elements[Matrix4<T>::a20] + mat._elements[Matrix4<T>::a30];

			T tmp2 = _vec[X] * mat._elements[Matrix4<T>::a01] +
				_vec[Y] * mat._elements[Matrix4<T>::a11] +
				_vec[Z] * mat._elements[Matrix4<T>::a21] + mat._elements[Matrix4<T>::a31];

			_vec[Z] = _vec[X] * mat._elements[Matrix4<T>::a02] +
				_vec[Y] * mat._elements[Matrix4<T>::a12] +
				_vec[Z] * mat._elements[Matrix4<T>::a22] + mat._elements[Matrix4<T>::a32];

			_vec[X] = tmp1;
			_vec[Y] = tmp2;

			return *this;
		}

	template <class T>
	Vec3<T>&
		Vec3<T>::operator*=(const Matrix4<T>& mat) {
			T tmp1 = _vec[X] * mat._elements[Matrix4<T>::a00] +
				_vec[Y] * mat._elements[Matrix4<T>::a10] +
				_vec[Z] * mat._elements[Matrix4<T>::a20] + mat._elements[Matrix4<T>::a30];

			T tmp2 = _vec[X] * mat._elements[Matrix4<T>::a01] +
				_vec[Y] * mat._elements[Matrix4<T>::a11] +
				_vec[Z] * mat._elements[Matrix4<T>::a21] + mat._elements[Matrix4<T>::a31];

			T tmp3 = _vec[X] * mat._elements[Matrix4<T>::a02] +
				_vec[Y] * mat._elements[Matrix4<T>::a12] +
				_vec[Z] * mat._elements[Matrix4<T>::a22] + mat._elements[Matrix4<T>::a32];

			T tmp4 = _vec[X] * mat._elements[Matrix4<T>::a03] +
				_vec[Y] * mat._elements[Matrix4<T>::a13] +
				_vec[Z] * mat._elements[Matrix4<T>::a23] + mat._elements[Matrix4<T>::a33];

			_vec[X] = tmp1;
			_vec[Y] = tmp2;
			_vec[Z] = tmp3;

			if (tmp4 != 1.0f) {
				tmp4 = 1.0f / tmp4;
				_vec[X] *= tmp4;
				_vec[Y] *= tmp4;
				_vec[Z] *= tmp4;
			}
			return *this;
		}

	template <class T>
	Vec3<T>&
		Vec3<T>::operator*=(const Matrix3<T>& mat) {
			T tmp1 = _vec[X] * mat._elements[Matrix3<T>::a00] +
				_vec[Y] * mat._elements[Matrix3<T>::a10] +
				_vec[Z] * mat._elements[Matrix3<T>::a20];

			T tmp2 = _vec[X] * mat._elements[Matrix3<T>::a01] +
				_vec[Y] * mat._elements[Matrix3<T>::a11] +
				_vec[Z] * mat._elements[Matrix3<T>::a21];

			_vec[Z] = _vec[X] * mat._elements[Matrix3<T>::a02] +
				_vec[Y] * mat._elements[Matrix3<T>::a12] +
				_vec[Z] * mat._elements[Matrix3<T>::a22];

			_vec[X] = tmp1;
			_vec[Y] = tmp2;

			return *this;
		}

	template <class T>
	Vec3<T>&
		Vec3<T>::operator*=(const Quaternion<T>& q) {
			// calculate coefficients
			T x2 = q._vec[X] + q._vec[X];
			T y2 = q._vec[Y] + q._vec[Y];
			T z2 = q._vec[Z] + q._vec[Z];
			T xx2 = q._vec[X] * x2;
			T xy2 = q._vec[X] * y2;
			T xz2 = q._vec[X] * z2;
			T yy2 = q._vec[Y] * y2;
			T yz2 = q._vec[Y] * z2;
			T zz2 = q._vec[Z] * z2;
			T wx2 = q._vec[R] * x2;
			T wy2 = q._vec[R] * y2;
			T wz2 = q._vec[R] * z2;

			T tmp1 = _vec[X] * (1.0f - (yy2 + zz2)) +
				_vec[Y] * (xy2 - wz2) +
				_vec[Z] * (xz2 + wy2);

			T tmp2 = _vec[X] * (xy2 + wz2) +
				_vec[Y] * (1.0f - (xx2 + zz2)) +
				_vec[Z] * (yz2 - wx2);

			_vec[Z] = _vec[X] * (xz2 - wy2) +
				_vec[Y] * (yz2 + wx2) +
				_vec[Z] * (1.0f - (xx2 + yy2));

			_vec[X] = tmp1;
			_vec[Y] = tmp2;

			return *this;
		}

	template <class T>
	Vec3<T>&
		Vec3<T>::Rotate(const Matrix4<T>& mat) {
			T tmp1 = _vec[X] * mat._elements[Matrix4<T>::a00] +
				_vec[Y] * mat._elements[Matrix4<T>::a10] +
				_vec[Z] * mat._elements[Matrix4<T>::a20];

			T tmp2 = _vec[X] * mat._elements[Matrix4<T>::a01] +
				_vec[Y] * mat._elements[Matrix4<T>::a11] +
				_vec[Z] * mat._elements[Matrix4<T>::a21];

			_vec[Z] = _vec[X] * mat._elements[Matrix4<T>::a02] +
				_vec[Y] * mat._elements[Matrix4<T>::a12] +
				_vec[Z] * mat._elements[Matrix4<T>::a22];

			_vec[X] = tmp1;
			_vec[Y] = tmp2;

			return *this;
		}

	template <class T>
	/* static */ Obool
		Vec3<T>::IsInteriorPoint(const Vec3<T>& testPoint, const Vec3<T>& u, const Vec3<T>& v, const Vec3<T>& w, Ochar ix, Ochar iy, Obool isCcw, Ofloat& alpha, Ofloat& beta, T tolerance) {
			//check if point is inside polygon
			Ofloat U[2], V[2], W[2];
			U[0] = testPoint[ix] - u[ix];
			U[1] = testPoint[iy] - u[iy];
			if (isCcw) {
				V[0] = v[ix] - u[ix];
				V[1] = v[iy] - u[iy];
				W[0] = w[ix] - u[ix];
				W[1] = w[iy] - u[iy];
			}
			else {
				W[0] = v[ix] - u[ix];
				W[1] = v[iy] - u[iy];
				V[0] = w[ix] - u[ix];
				V[1] = w[iy] - u[iy];
			}

			if (V[0] == 0) {
				beta = U[0] / W[0];
				if ((beta >= 0.0f) && (beta <= 1.0f))
					alpha = (U[1] - beta*W[1]) / V[1];
			}
			else {
				beta = (U[1] * V[0] - U[0] * V[1]) / (W[1] * V[0] - W[0] * V[1]);
				if ((beta >= 0.0f) && (beta <= 1.0f))
					alpha = (U[0] - beta*W[0]) / V[0];
			}
			return (alpha >= -tolerance && beta >= -tolerance && (alpha + beta) <= 1 - tolerance);
		}

	template <class T>
	/* static */ void
		Vec3<T>::FindProjectionAxes(const Vec3<T>& normal, Ochar& ix, Ochar& iy) {
			//find the two major axis for projection
			Oint big = (fabs(normal[X]) > fabs(normal[Y])) ?
				((fabs(normal[X]) > fabs(normal[Z])) ? 0 : 2) :
				((fabs(normal[Y]) > fabs(normal[Z])) ? 1 : 2);
			if (normal[big] < 0.0f) {
				ix = (big + 2) % 3;
				iy = (big + 1) % 3;
			}
			else {
				ix = (big + 1) % 3;
				iy = (big + 2) % 3;
			}
		}

	template <class T>
	/* static */ Obool
		Vec3<T>::FindPlane2VectorIntersection(const Vec3<T>& normal, const Vec3<T>& vector, const Vec3<T>& refPoint, const Vec3<T>& origin, Vec3<T>& intersection, T tolerance) {
			//intersection with plane (t=normal(p0 - origin)/(normal*vector)
			T denom = normal*vector;
			if (denom != 0) {
				T t = normal*(refPoint - origin) / denom;
				intersection = origin + t*vector;
				return true;
			}
			return false;
		}

	template <class T>
	/* static */ T
		Vec3<T>::FindSignedDistanceToPlane(const Vec3<T>& normal, T P0, const Vec3<T>& testPoint) {
			return normal*testPoint + P0;
		}

	template <class T>
	inline Obool
		Vec3<T>::operator<(const Vec3<T>& vec) const {
			return std::lexicographical_compare(_vec, _vec + 3, vec._vec, vec._vec + 3);
		}

} // namespace enterprise_manager

