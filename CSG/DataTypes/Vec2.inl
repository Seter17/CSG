namespace enterprise_manager {

	template <class T>
	inline
		Vec2<T>::Vec2() {
			_vec[0] = _vec[1] = 0;
		}

	template <class T>
	inline
		Vec2<T>::Vec2(T x, T y) {
			_vec[0] = x;
			_vec[1] = y;
		}

	template <class T>
	inline
		Vec2<T>::Vec2(const Vec2<T>& vec) {
			_vec[0] = vec._vec[0];
			_vec[1] = vec._vec[1];
		}

	template <class T>
	inline
		Vec2<T>::~Vec2() {}

	template <class T>
	inline T
		Vec2<T>::operator*(const Vec2<T>& vec) const {
			return (_vec[0] * vec._vec[0] +
				_vec[1] * vec._vec[1]);
		}

	template <class T>
	inline Vec2<T>&
		Vec2<T>::operator*=(const T& value) {
			_vec[0] *= value;
			_vec[1] *= value;
			return *this;
		}

	template <class T>
	inline Vec2<T>&
		Vec2<T>::operator/=(const Vec2<T>& vec) {
			_vec[0] /= vec._vec[0];
			_vec[1] /= vec._vec[1];
			return *this;
		}

	template <class T>
	inline Vec2<T>&
		Vec2<T>::operator/=(const T& value) {
			_vec[0] /= value;
			_vec[1] /= value;
			return *this;
		}

	template <class T>
	inline Vec2<T>&
		Vec2<T>::operator+=(const Vec2<T>& vec) {
			_vec[0] += vec._vec[0];
			_vec[1] += vec._vec[1];
			return *this;
		}

	template <class T>
	inline Vec2<T>
		Vec2<T>::operator-() const {
			return Vec2<T>(-_vec[0], -_vec[1]);
		}

	template <class T>
	inline Vec2<T>&
		Vec2<T>::operator-=(const Vec2<T>& vec) {
			_vec[0] -= vec._vec[0];
			_vec[1] -= vec._vec[1];
			return *this;
		}

	template <class T>
	inline Obool
		Vec2<T>::operator==(const Vec2<T>& vec) const {
			return (_vec[0] == vec._vec[0] && _vec[1] == vec._vec[1]);
		}

	template <class T>
	inline Obool
		Vec2<T>::operator==(const T& value) const {
			return (_vec[0] == value && _vec[1] == value);
		}

	template <class T>
	inline Obool
		Vec2<T>::Equal(const Vec2<T>& vec, const T& tolerance) const {
			return ((fabs(_vec[0] - vec._vec[0]) < tolerance) &&
				(fabs(_vec[1] - vec._vec[1]) < tolerance));
		}

	template <class T>
	inline Obool
		Vec2<T>::Equal(const T& value, const T& tolerance) const {
			return ((fabs(_vec[0] - value) < tolerance) &&
				(fabs(_vec[1] - value) < tolerance));
		}

	template <class T>
	inline Obool
		Vec2<T>::operator!=(const Vec2<T>& vec) const {
			return (_vec[0] != vec._vec[0] || _vec[1] != vec._vec[1]);
		}

	template <class T>
	inline Obool
		Vec2<T>::operator!=(const T& value) const {
			return (_vec[0] != value || _vec[1] != value);
		}

	template <class T>
	inline Vec2<T>&
		Vec2<T>::operator=(const Vec2<T>& vec) {
			_vec[0] = vec._vec[0];
			_vec[1] = vec._vec[1];
			return *this;
		}

	template <class T>
	inline T&
		Vec2<T>::operator[](const Oint i) {
			return _vec[i];
		}

	template <class T>
	inline T
		Vec2<T>::operator[](const Oint i) const {
			return _vec[i];
		}

	template <class T>
	inline T
		Vec2<T>::Length() const {
			return static_cast<T>(::sqrt(_vec[0] * _vec[0] + _vec[1] * _vec[1]));
		}

	template <class T>
	inline T
		Vec2<T>::LengthSqr() const {
			return (_vec[0] * _vec[0] +
				_vec[1] * _vec[1]);
		}

	template <class T>
	inline Vec2<T>&
		Vec2<T>::Normalize() {
			T length = sqrt(_vec[0] * _vec[0] + _vec[1] * _vec[1]);
			if (length != 0) {
				T length_1 = 1.0f / length;
				_vec[0] *= length_1;
				_vec[1] *= length_1;
			}
			return *this;
		}

	template <class T>
	inline T
		Vec2<T>::Distance(const Vec2<T>& vec) const {
			T sqr_x = _vec[X] - vec._vec[X];
			T sqr_y = _vec[Y] - vec._vec[Y];

			sqr_x *= sqr_x;
			sqr_y *= sqr_y;

			return T(sqrt(sqr_x + sqr_y));
		}

	template <class T>
	inline T
		Vec2<T>::DistanceSqr(const Vec2<T>& vec) const {
			T sqr_x(_vec[X] - vec._vec[X]);
			T sqr_y(_vec[Y] - vec._vec[Y]);

			sqr_x *= sqr_x;
			sqr_y *= sqr_y;

			return sqr_x + sqr_y;
		}

	template <class T>
	inline T
		Vec2<T>::CosAngle(const Vec2<T>& vec) const {
			T lengthSq = (_vec[X] * _vec[X] + _vec[Y] * _vec[Y])  *
				(vec._vec[X] * vec._vec[X] + vec._vec[Y] * vec._vec[Y]);
			if (lengthSq != 0)
				return  ((_vec[X] * vec._vec[X] + _vec[Y] * vec._vec[Y]) /
				sqrtf(lengthSq));
			return 0;
		}

	template <class T>
	inline T
		Vec2<T>::Cross(const Vec2<T> &vec) const {
			return _vec[X] * vec._vec[Y] - _vec[Y] * vec._vec[X];
		}

	template <class T>
	inline Vec2<T>
		Vec2<T>::MultiplyComp(const Vec2<T> &vec) const {
			return Vec2<T>(_vec[X] * vec._vec[X], _vec[Y] * vec._vec[Y]);
		}

	template <class T>
	inline void
		Vec2<T>::MaxComp(const Vec2<T> &vec) {
			if (vec._vec[X] > _vec[X])
				_vec[X] = vec._vec[X];
			if (vec._vec[Y] > _vec[Y])
				_vec[Y] = vec._vec[Y];
		}

	template <class T>
	inline void
		Vec2<T>::MinComp(const Vec2<T> &vec) {
			if (vec._vec[X] < _vec[X])
				_vec[X] = vec._vec[X];
			if (vec._vec[Y] < _vec[Y])
				_vec[Y] = vec._vec[Y];
		}

	template <class T>
	inline const T*
		Vec2<T>::Ptr() const {
			return _vec;
		}

	template <class T>
	Vec2<T>&
		Vec2<T>::operator*=(const Matrix3<T>& mat) {
			T tmp1 = _vec[X] * mat._elements[Matrix3<T>::a00] +
				_vec[Y] * mat._elements[Matrix3<T>::a10] +
				mat._elements[Matrix3<T>::a20];

			T tmp2 = _vec[X] * mat._elements[Matrix3<T>::a01] +
				_vec[Y] * mat._elements[Matrix3<T>::a11] +
				mat._elements[Matrix3<T>::a21];

			T tmp3 = _vec[X] * mat._elements[Matrix3<T>::a02] +
				_vec[Y] * mat._elements[Matrix3<T>::a12] +
				mat._elements[Matrix3<T>::a22];

			_vec[X] = tmp1;
			_vec[Y] = tmp2;

			if (tmp3 != 1.0f) {
				tmp3 = 1.0f / tmp3;
				_vec[X] *= tmp3;
				_vec[Y] *= tmp3;
			}
			return *this;
		}

} // namespace enterprise_manager

