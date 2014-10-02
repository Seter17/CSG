namespace enterprise_manager {

	template <class T>
	inline
		Vec4<T>::Vec4() {
			_vec[0] = _vec[1] = _vec[2] = _vec[3] = 0.0f;
		}

	template <class T>
	inline
		Vec4<T>::Vec4(const T& v0, const T& v1, const T& v2, const T& v3) {
			_vec[0] = v0;
			_vec[1] = v1;
			_vec[2] = v2;
			_vec[3] = v3;
		}

	template <class T>
	inline
		Vec4<T>::Vec4(const Vec4<T>& vec) {
			_vec[0] = vec._vec[0];
			_vec[1] = vec._vec[1];
			_vec[2] = vec._vec[2];
			_vec[3] = vec._vec[3];
		}

	template <class T>
	inline
		Vec4<T>::Vec4(const Vec2<T>& vector, const T& v2, const T& v3) {
			_vec[0] = vector._vec[0];
			_vec[1] = vector._vec[1];
			_vec[2] = v2;
			_vec[3] = v3;
		}

	template <class T>
	inline
		Vec4<T>::Vec4(const Vec2<T>& vector1, const Vec2<T>& vector2) {
			_vec[0] = vector1._vec[0];
			_vec[1] = vector1._vec[1];
			_vec[2] = vector2._vec[0];
			_vec[3] = vector2._vec[1];
		}

	template <class T>
	inline
		Vec4<T>::Vec4(const Vec3<T>& vector, const T& v3) {
			_vec[0] = vector._vec[0];
			_vec[1] = vector._vec[1];
			_vec[2] = vector._vec[2];
			_vec[3] = v3;
		}

	template <class T>
	inline
		Vec4<T>::~Vec4() {}

	template <class T>
	inline T
		Vec4<T>::operator*(const Vec4<T>& vec) const {
			return (_vec[0] * vec._vec[0] +
				_vec[1] * vec._vec[1] +
				_vec[2] * vec._vec[2] +
				_vec[3] * vec._vec[3]);
		}

	template <class T>
	inline Vec4<T>&
		Vec4<T>::operator*=(const T& value) {
			_vec[0] *= value;
			_vec[1] *= value;
			_vec[2] *= value;
			_vec[3] *= value;
			return *this;
		}

	template <class T>
	inline Vec4<T>&
		Vec4<T>::operator/=(const Vec4<T>& vec) {
			_vec[0] /= vec._vec[0];
			_vec[1] /= vec._vec[1];
			_vec[2] /= vec._vec[2];
			_vec[3] /= vec._vec[3];
			return *this;
		}

	template <class T>
	inline Vec4<T>&
		Vec4<T>::operator/=(const T& value) {
			_vec[0] /= value;
			_vec[1] /= value;
			_vec[2] /= value;
			_vec[3] /= value;
			return *this;
		}

	template <class T>
	inline Vec4<T>&
		Vec4<T>::operator+=(const Vec4<T>& vec) {
			_vec[0] += vec._vec[0];
			_vec[1] += vec._vec[1];
			_vec[2] += vec._vec[2];
			_vec[3] += vec._vec[3];
			return *this;
		}

	template <class T>
	inline Vec4<T>
		Vec4<T>::operator-() const {
			return Vec4<T>(-_vec[0], -_vec[1], -_vec[2], -_vec[3]);
		}

	template <class T>
	inline Vec4<T>&
		Vec4<T>::operator-=(const Vec4<T>& vec) {
			_vec[0] -= vec._vec[0];
			_vec[1] -= vec._vec[1];
			_vec[2] -= vec._vec[2];
			_vec[3] -= vec._vec[3];
			return *this;
		}

	template <class T>
	inline Obool
		Vec4<T>::operator==(const Vec4<T>& vec) const {
			return (_vec[0] == vec._vec[0] &&
				_vec[1] == vec._vec[1] &&
				_vec[2] == vec._vec[2] &&
				_vec[3] == vec._vec[3]);
		}

	template <class T>
	inline Obool
		Vec4<T>::operator==(const T& value) const {
			return (_vec[0] == value &&
				_vec[1] == value &&
				_vec[2] == value &&
				_vec[3] == value);
		}

	template <class T>
	inline Obool
		Vec4<T>::Equal(const Vec4<T>& vec, const T& tolerance) const {
			return ((fabs(_vec[0] - vec._vec[0]) < tolerance) &&
				(fabs(_vec[1] - vec._vec[1]) < tolerance) &&
				(fabs(_vec[2] - vec._vec[2]) < tolerance) &&
				(fabs(_vec[3] - vec._vec[3]) < tolerance));
		}

	template <class T>
	inline Obool
		Vec4<T>::Equal(const T& value, const T& tolerance) const {
			return ((fabs(_vec[0] - value) < tolerance) &&
				(fabs(_vec[1] - value) < tolerance) &&
				(fabs(_vec[2] - value) < tolerance) &&
				(fabs(_vec[3] - value) < tolerance));
		}

	template <class T>
	inline Obool
		Vec4<T>::operator!=(const Vec4<T>& vec) const {
			return (_vec[0] != vec._vec[0] ||
				_vec[1] != vec._vec[1] ||
				_vec[2] != vec._vec[2] ||
				_vec[3] != vec._vec[3]);
		}

	template <class T>
	inline Obool
		Vec4<T>::operator!=(const T& value) const {
			return (_vec[0] != value ||
				_vec[1] != value ||
				_vec[2] != value ||
				_vec[3] != value);
		}

	template <class T>
	inline Vec4<T>&
		Vec4<T>::operator=(const Vec4<T>& vec) {
			_vec[0] = vec._vec[0];
			_vec[1] = vec._vec[1];
			_vec[2] = vec._vec[2];
			_vec[3] = vec._vec[3];
			return *this;
		}

	template <class T>
	inline T&
		Vec4<T>::operator[](const Oint i) {
			return _vec[i];
		}

	template <class T>
	inline T
		Vec4<T>::operator[](const Oint i) const {
			return _vec[i];
		}

	template <class T>
	inline T
		Vec4<T>::Length() const {
			return ::sqrt(_vec[0] * _vec[0] +
				_vec[1] * _vec[1] +
				_vec[2] * _vec[2] +
				_vec[3] * _vec[3]);
		}

	template <class T>
	inline T
		Vec4<T>::LengthSqr() const {
			return (_vec[0] * _vec[0] +
				_vec[1] * _vec[1] +
				_vec[2] * _vec[2] +
				_vec[3] * _vec[3]);
		}

	template <class T>
	inline Vec4<T>&
		Vec4<T>::Normalize() {
			T length = sqrt(_vec[0] * _vec[0] + _vec[1] * _vec[1] + _vec[2] * _vec[2] + _vec[3] * _vec[3]);
			if (length != 0) {
				T length_1 = 1.0f / length;
				_vec[0] *= length_1;
				_vec[1] *= length_1;
				_vec[2] *= length_1;
				_vec[3] *= length_1;
			}
			return *this;
		}

	template <class T>
	inline T
		Vec4<T>::Distance(const Vec4<T>& vec) const {
			T sqr_0(_vec[0] - vec._vec[0]);
			T sqr_1(_vec[1] - vec._vec[1]);
			T sqr_2(_vec[2] - vec._vec[2]);
			T sqr_3(_vec[3] - vec._vec[3]);

			sqr_0 *= sqr_0;
			sqr_1 *= sqr_1;
			sqr_2 *= sqr_2;
			sqr_3 *= sqr_3;

			return T(sqrt(sqr_0 + sqr_1 + sqr_2 + sqr_3));
		}

	template <class T>
	inline T
		Vec4<T>::DistanceSqr(const Vec4<T>& vec) const {
			T sqr_0(_vec[0] - vec._vec[0]);
			T sqr_1(_vec[1] - vec._vec[1]);
			T sqr_2(_vec[2] - vec._vec[2]);
			T sqr_3(_vec[3] - vec._vec[3]);

			sqr_0 *= sqr_0;
			sqr_1 *= sqr_1;
			sqr_2 *= sqr_2;
			sqr_3 *= sqr_3;

			return sqr_0 + sqr_1 + sqr_2 + sqr_3;
		}

	template <class T>
	inline T
		Vec4<T>::CosAngle(const Vec4<T>& vec) const {
			T lengthSq = (_vec[0] * _vec[0] + _vec[1] * _vec[1] + _vec[2] * _vec[2] + _vec[3] * _vec[3])  *
				(vec._vec[0] * vec._vec[0] + vec._vec[1] * vec._vec[1] + vec._vec[2] * vec._vec[2] + vec._vec[3] * vec._vec[3]);
			if (lengthSq != 0)
				return  ((_vec[0] * vec._vec[0] +     //dot product
				_vec[1] * vec._vec[1] +
				_vec[2] * vec._vec[2] +
				_vec[3] * vec._vec[3]) / sqrtf(lengthSq));
			return 0;
		}

	template <class T>
	inline Vec4<T>
		Vec4<T>::MultiplyComp(const Vec4<T> &vec) const {
			return Vec4<T>(_vec[0] * vec._vec[0], _vec[1] * vec._vec[1], _vec[2] * vec._vec[2], _vec[3] * vec._vec[3]);
		}

	template <class T>
	inline const T*
		Vec4<T>::Ptr() const {
			return _vec;
		}

	template <class T>
	Vec4<T>&
		Vec4<T>::operator*=(const Matrix4<T>& mat) {
			T x = _vec[X] * mat.Get(0, 0) +
				_vec[Y] * mat.Get(1, 0) +
				_vec[Z] * mat.Get(2, 0) +
				_vec[3] * mat.Get(3, 0);

			T y = _vec[X] * mat.Get(0, 1) +
				_vec[Y] * mat.Get(1, 1) +
				_vec[Z] * mat.Get(2, 1) +
				_vec[3] * mat.Get(3, 1);

			T z = _vec[X] * mat.Get(0, 2) +
				_vec[Y] * mat.Get(1, 2) +
				_vec[Z] * mat.Get(2, 2) +
				_vec[3] * mat.Get(3, 2);

			_vec[3] = _vec[X] * mat.Get(0, 3) +
				_vec[Y] * mat.Get(1, 3) +
				_vec[Z] * mat.Get(2, 3) +
				_vec[3] * mat.Get(3, 3);

			_vec[X] = x;
			_vec[Y] = y;
			_vec[Z] = z;

			return *this;
		}

} // namespace enterprise_manager
