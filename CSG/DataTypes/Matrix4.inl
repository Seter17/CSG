namespace enterprise_manager {

    template <class T>
    inline
        Matrix4<T>::Matrix4()
        : _flag(IDENTITY) {
            _elements[a10] = _elements[a20] = _elements[a30] = 0.0f;
            _elements[a01] = _elements[a21] = _elements[a31] = 0.0f;
            _elements[a02] = _elements[a12] = _elements[a32] = 0.0f;
            _elements[a03] = _elements[a13] = _elements[a23] = 0.0f;

            _elements[a00] = _elements[a11] = _elements[a22] = _elements[a33] = 1.0f;
        }

    template <class T>
    inline
        Matrix4<T>::Matrix4(const SpecialMatrix matrixType)
        : _flag(IDENTITY) {
            if (matrixType == IDENTITY) {
                _elements[a10] = _elements[a20] = _elements[a30] = 0.0f;
                _elements[a01] = _elements[a21] = _elements[a31] = 0.0f;
                _elements[a02] = _elements[a12] = _elements[a32] = 0.0f;
                _elements[a03] = _elements[a13] = _elements[a23] = 0.0f;

                _elements[a00] = _elements[a11] = _elements[a22] = _elements[a33] = 1.0f;

            }
            else {
                //WARNING("Trying to construct unknown matrix type");
                _flag = UNDEFINED;
            }
        }

    template <class T>
    inline
        Matrix4<T>::Matrix4(const ScaleType, T value)
        : _flag(0) {
            _elements[a10] = _elements[a20] = _elements[a30] = 0.0f;
            _elements[a01] = _elements[a21] = _elements[a31] = 0.0f;
            _elements[a02] = _elements[a12] = _elements[a32] = 0.0f;
            _elements[a03] = _elements[a13] = _elements[a23] = 0.0f;

            _elements[a00] = _elements[a11] = _elements[a22] = value;
            _elements[a33] = 1.0f;

        }

    template <class T>
    inline
        Matrix4<T>::Matrix4(const ScaleType, T x, T y, T z)
        : _flag(0) {
            _elements[a01] = _elements[a02] = _elements[a03] = 0.0f;
            _elements[a10] = _elements[a12] = _elements[a13] = 0.0f;
            _elements[a20] = _elements[a21] = _elements[a23] = 0.0f;
            _elements[a30] = _elements[a31] = _elements[a32] = 0.0f;
            _elements[a33] = 1.0f;
            _elements[a00] = x;
            _elements[a11] = y;
            _elements[a22] = z;
        }

    template <class T>
    inline
        Matrix4<T>::Matrix4(const ScaleType, const Vec3<T>& vec)
        : _flag(0) {
            _elements[a01] = _elements[a02] = _elements[a03] = 0.0f;
            _elements[a10] = _elements[a12] = _elements[a13] = 0.0f;
            _elements[a20] = _elements[a21] = _elements[a23] = 0.0f;
            _elements[a30] = _elements[a31] = _elements[a32] = 0.0f;
            _elements[a33] = 1.0f;
            _elements[a00] = vec[X];
            _elements[a11] = vec[Y];
            _elements[a22] = vec[Z];
        }

    template <class T>
    inline
        Matrix4<T>::Matrix4(const TranslateType, T x, T y, T z)
        : _flag(0) {
            _elements[a01] = _elements[a02] = _elements[a03] = 0.0f;
            _elements[a10] = _elements[a12] = _elements[a13] = 0.0f;
            _elements[a20] = _elements[a21] = _elements[a23] = 0.0f;
            _elements[a00] = _elements[a11] = _elements[a22] = _elements[a33] = 1.0f;
            _elements[a30] = x;
            _elements[a31] = y;
            _elements[a32] = z;
        }

    template <class T>
    inline
        Matrix4<T>::Matrix4(const TranslateType, const Vec3<T>& vec)
        : _flag(0) {
            _elements[a01] = _elements[a02] = _elements[a03] = 0.0f;
            _elements[a10] = _elements[a12] = _elements[a13] = 0.0f;
            _elements[a20] = _elements[a21] = _elements[a23] = 0.0f;
            _elements[a00] = _elements[a11] = _elements[a22] = _elements[a33] = 1.0f;
            _elements[a30] = vec[X];
            _elements[a31] = vec[Y];
            _elements[a32] = vec[Z];
        }

    template <class T>
    inline
        Matrix4<T>::Matrix4(const Matrix4<T>& X)
        : _flag(X._flag) {
            _elements[a00] = X._elements[a00];
            _elements[a01] = X._elements[a01];
            _elements[a02] = X._elements[a02];
            _elements[a03] = X._elements[a03];
            _elements[a10] = X._elements[a10];
            _elements[a11] = X._elements[a11];
            _elements[a12] = X._elements[a12];
            _elements[a13] = X._elements[a13];
            _elements[a20] = X._elements[a20];
            _elements[a21] = X._elements[a21];
            _elements[a22] = X._elements[a22];
            _elements[a23] = X._elements[a23];
            _elements[a30] = X._elements[a30];
            _elements[a31] = X._elements[a31];
            _elements[a32] = X._elements[a32];
            _elements[a33] = X._elements[a33];

        }

    template <class T>
    inline
        Matrix4<T>::Matrix4(const Matrix3<T>& X)
        : _flag(X._flag) {
            _elements[a00] = X._elements[Matrix3<T>::a00];
            _elements[a10] = X._elements[Matrix3<T>::a10];
            _elements[a20] = 0.0f;
            _elements[a30] = X._elements[Matrix3<T>::a20];
            _elements[a01] = X._elements[Matrix3<T>::a01];
            _elements[a11] = X._elements[Matrix3<T>::a11];
            _elements[a21] = 0.0f;
            _elements[a31] = X._elements[Matrix3<T>::a21];
            _elements[a02] = 0.0f;
            _elements[a12] = 0.0f;
            _elements[a22] = 1.0f;
            _elements[a32] = 0.0f;
            _elements[a03] = X._elements[Matrix3<T>::a02];
            _elements[a13] = X._elements[Matrix3<T>::a12];
            _elements[a23] = 0.0f;
            _elements[a33] = X._elements[Matrix3<T>::a22];
        }

    template <class T>
    inline Matrix4<T>&
        Matrix4<T>::operator=(const Matrix4<T>& X) {
            _flag = X._flag;
            _elements[a00] = X._elements[a00];
            _elements[a10] = X._elements[a10];
            _elements[a20] = X._elements[a20];
            _elements[a30] = X._elements[a30];
            _elements[a01] = X._elements[a01];
            _elements[a11] = X._elements[a11];
            _elements[a21] = X._elements[a21];
            _elements[a31] = X._elements[a31];
            _elements[a02] = X._elements[a02];
            _elements[a12] = X._elements[a12];
            _elements[a22] = X._elements[a22];
            _elements[a32] = X._elements[a32];
            _elements[a03] = X._elements[a03];
            _elements[a13] = X._elements[a13];
            _elements[a23] = X._elements[a23];
            _elements[a33] = X._elements[a33];

            return *this;
        }

    template <class T>
    inline
        Matrix4<T>::Matrix4(const T matrix[16])
        : _flag(0) {
            _elements[a00] = matrix[0];
            _elements[a01] = matrix[1];
            _elements[a02] = matrix[2];
            _elements[a03] = matrix[3];
            _elements[a10] = matrix[4];
            _elements[a11] = matrix[5];
            _elements[a12] = matrix[6];
            _elements[a13] = matrix[7];
            _elements[a20] = matrix[8];
            _elements[a21] = matrix[9];
            _elements[a22] = matrix[10];
            _elements[a23] = matrix[11];
            _elements[a30] = matrix[12];
            _elements[a31] = matrix[13];
            _elements[a32] = matrix[14];
            _elements[a33] = matrix[15];
        }

    template <class T>
    inline
        Matrix4<T>::Matrix4(const T matrix[4][4])
        : _flag(0) {
            _elements[a00] = matrix[0][0];
            _elements[a01] = matrix[0][1];
            _elements[a02] = matrix[0][2];
            _elements[a03] = matrix[0][3];
            _elements[a10] = matrix[1][0];
            _elements[a11] = matrix[1][1];
            _elements[a12] = matrix[1][2];
            _elements[a13] = matrix[1][3];
            _elements[a20] = matrix[2][0];
            _elements[a21] = matrix[2][1];
            _elements[a22] = matrix[2][2];
            _elements[a23] = matrix[2][3];
            _elements[a30] = matrix[3][0];
            _elements[a31] = matrix[3][1];
            _elements[a32] = matrix[3][2];
            _elements[a33] = matrix[3][3];

        }

    template <class T>
    inline
        Matrix4<T>::~Matrix4() {}

    template <class T>
    inline Obool
        Matrix4<T>::operator==(const Matrix4<T>& X) const {
            return (((_flag == X._flag) && _flag) ||
                    (_elements[a00] == X._elements[a00] &&
                    _elements[a01] == X._elements[a01] &&
                    _elements[a02] == X._elements[a02] &&
                    _elements[a03] == X._elements[a03] &&
                    _elements[a10] == X._elements[a10] &&
                    _elements[a11] == X._elements[a11] &&
                    _elements[a12] == X._elements[a12] &&
                    _elements[a13] == X._elements[a13] &&
                    _elements[a20] == X._elements[a20] &&
                    _elements[a21] == X._elements[a21] &&
                    _elements[a22] == X._elements[a22] &&
                    _elements[a23] == X._elements[a23] &&
                    _elements[a30] == X._elements[a30] &&
                    _elements[a31] == X._elements[a31] &&
                    _elements[a32] == X._elements[a32] &&
                    _elements[a33] == X._elements[a33]));
        }

    template <class T>
    inline Obool
        Matrix4<T>::operator!=(const Matrix4<T>& X) const {
            return (_elements[a00] != X._elements[a00] ||
                    _elements[a01] != X._elements[a01] ||
                    _elements[a02] != X._elements[a02] ||
                    _elements[a03] != X._elements[a03] ||
                    _elements[a10] != X._elements[a10] ||
                    _elements[a11] != X._elements[a11] ||
                    _elements[a12] != X._elements[a12] ||
                    _elements[a13] != X._elements[a13] ||
                    _elements[a20] != X._elements[a20] ||
                    _elements[a21] != X._elements[a21] ||
                    _elements[a22] != X._elements[a22] ||
                    _elements[a23] != X._elements[a23] ||
                    _elements[a30] != X._elements[a30] ||
                    _elements[a31] != X._elements[a31] ||
                    _elements[a32] != X._elements[a32] ||
                    _elements[a33] != X._elements[a33]);
        }

    template <class T>
    inline Matrix4<T>&
        Matrix4<T>::SetColumn(Oint column, const Vec3<T>& vec) {
            _flag = 0;
            _elements[column] = vec[X];
            _elements[4 + column] = vec[Y];
            _elements[8 + column] = vec[Z];
            return *this;
        }

    template <class T>
    inline Matrix4<T>&
        Matrix4<T>::SetRow(Oint row, const Vec3<T>& vec) {
            _flag = 0;
            _elements[row * 4] = vec[X];
            _elements[row * 4 + 1] = vec[Y];
            _elements[row * 4 + 2] = vec[Z];

            return *this;
        }

    template <class T>
    inline T
        Matrix4<T>::Set(Oint row, Oint colmun, T value) {
            _flag = 0;
            _elements[row * 4 + colmun] = value;

            return value;
        }

    template <class T>
    inline Vec3<T>
        Matrix4<T>::GetTranslation() const {
            return Vec3<T>(_elements[a30], _elements[a31], _elements[a32]);
        }

    template <class T>
    inline Matrix4<T>
        Matrix4<T>::GetTranspose() const {
            Matrix4<T> result(*this);
            result.Transpose();
            return result;
        }

    template <class T>
    inline Matrix4<T>
        Matrix4<T>::GetInverse() const {
            Matrix4<T> result(*this);
            result.Invert();
            return result;
        }

    template <class T>
    inline void
        Matrix4<T>::Rotate(const Vec3<T>& axis, T r) {
            Rotate(axis[X], axis[Y], axis[Z], r);
        }

    template <class T>
    inline void
        Matrix4<T>::PreRotate(const Vec3<T>& axis, T r) {
            PreRotate(axis[X], axis[Y], axis[Z], r);
        }

    template <class T>
    inline void
        Matrix4<T>::Rotate(const Rotation4<T>& rot) {
            Rotate(rot[X], rot[Y], rot[Z], rot[R]);
        }

    template <class T>
    inline void
        Matrix4<T>::PreRotate(const Rotation4<T>& rot) {
            PreRotate(rot[X], rot[Y], rot[Z], rot[R]);
        }

    template <class T>
    inline void
        Matrix4<T>::Translate(const Vec3<T>& vec) {
            Translate(vec._vec[X], vec._vec[Y], vec._vec[Z]);
        }

    template <class T>
    inline void
        Matrix4<T>::PreTranslate(const Vec3<T>& vec) {
            PreTranslate(vec._vec[X], vec._vec[Y], vec._vec[Z]);
        }

    template <class T>
    inline void
        Matrix4<T>::Scale(const Vec3<T>& vec) {
            Scale(vec._vec[X], vec._vec[Y], vec._vec[Z]);
        }

    template <class T>
    inline void
        Matrix4<T>::PreScale(const Vec3<T>& vec) {
            PreScale(vec._vec[X], vec._vec[Y], vec._vec[Z]);
        }

    template <class T>
    inline Vec3<T>
        Matrix4<T>::GetRow(Oint row) const {
            assert(row < 4);
            return Vec3<T>(_elements[row * 4], _elements[row * 4 + 1], _elements[row * 4 + 2]);
        }

    template <class T>
    inline Vec3<T>
        Matrix4<T>::GetColumn(Oint col) const {
            assert(col < 4);
            return Vec3<T>(_elements[col], _elements[4 + col], _elements[8 + col]);
        }

    template <class T>
    inline T
        Matrix4<T>::Get(Oint row, Oint column) const {
            assert(row < 4 && column < 4);

            return _elements[row * 4 + column];
        }

    template <class T>
    inline Obool
        Matrix4<T>::IsUndefined() const {
            return(_flag == UNDEFINED);
        }

    template <class T>
    inline const T*
        Matrix4<T>::Ptr() const {
            return _elements;
        }

    template <class T>
    /* static */ const
        Matrix4<T> Matrix4<T>::identity;

    template <class T>
    Matrix4<T>::Matrix4(const RotateType, const Oint axis, const T value) {
        if (value == 0.0f)
            *this = identity;
        else {
            _flag = 0;
            T cos = ::cos(value);
            T sin = ::sin(value);

            switch (axis) {
                case X:
                    _elements[a11] = _elements[a22] = cos;
                    _elements[a12] = sin;
                    _elements[a21] = -sin;
                    _elements[a00] = 1.0f;
                    _elements[a01] = _elements[a02] = _elements[a10] = _elements[a20] = 0.0f;
                    break;

                case Y:
                    _elements[a00] = _elements[a22] = cos;
                    _elements[a20] = sin;
                    _elements[a02] = -sin;
                    _elements[a11] = 1.0f;
                    _elements[a01] = _elements[a10] = _elements[a12] = _elements[a21] = 0.0f;
                    break;

                case Z:
                    _elements[a00] = _elements[a11] = cos;
                    _elements[a01] = sin;
                    _elements[a10] = -sin;
                    _elements[a22] = 1.0f;
                    _elements[a02] = _elements[a12] = _elements[a20] = _elements[a21] = 0.0f;
                    break;
                default:
                    //WARNING("Creating undefined matrix");
                    _flag = UNDEFINED;
                    break;
            }
            _elements[a03] = _elements[a13] = _elements[a23] = 0.0f;
            _elements[a30] = _elements[a31] = _elements[a32] = 0.0f;
            _elements[a33] = 1.0f;
        }
    }

    template <class T>
    Matrix4<T>::Matrix4(const RotateType, const Oint axis, const T cos, const T sin)
        : _flag(0) {
        switch (axis) {
            case X:
                _elements[a11] = _elements[a22] = cos;
                _elements[a12] = sin;
                _elements[a21] = -sin;
                _elements[a00] = 1.0f;
                _elements[a01] = _elements[a02] = _elements[a10] = _elements[a20] = 0.0f;
                break;

            case Y:
                _elements[a00] = _elements[a22] = cos;
                _elements[a20] = sin;
                _elements[a02] = -sin;
                _elements[a11] = 1.0f;
                _elements[a01] = _elements[a10] = _elements[a12] = _elements[a21] = 0.0f;
                break;

            case Z:
                _elements[a00] = _elements[a11] = cos;
                _elements[a01] = sin;
                _elements[a10] = -sin;
                _elements[a22] = 1.0f;
                _elements[a02] = _elements[a12] = _elements[a20] = _elements[a21] = 0.0f;
                break;
            default:
                //WARNING("Creating undefined matrix");
                _flag = UNDEFINED;
        }
        _elements[a03] = _elements[a13] = _elements[a23] = 0.0f;
        _elements[a30] = _elements[a31] = _elements[a32] = 0.0f;
        _elements[a33] = 1.0f;
    }

    template <class T>
    Matrix4<T>::Matrix4(const RotateType, T x, T y, T z, T r)
        : _flag(0) {
        if (r == 0.0f) {
            *this = identity;
        }
        else {
            _flag = 0;
            //normalize if necessary
            T d_1 = x*x + y*y + z*z;
            if (d_1 != 1.0f) {
                d_1 = 1.0f / sqrtf(d_1);
                x *= d_1;
                y *= d_1;
                z *= d_1;
            }
            T c = T(::cos(r)), s = T(::sin(r));
            T t = 1.0f - c;
            T xx = x * x, yy = y * y, zz = z * z;
            T xy = x * y, xz = x * z;
            T yz = y * z;

            _elements[a00] = t * xx + c;
            _elements[a01] = t * xy + s * z;
            _elements[a02] = t * xz - s * y;
            _elements[a03] = 0.0f;
            _elements[a10] = t * xy - s * z;
            _elements[a11] = t * yy + c;
            _elements[a12] = t * yz + s * x;
            _elements[a13] = 0.0f;
            _elements[a20] = t * xz + s * y;
            _elements[a21] = t * yz - s * x;
            _elements[a22] = t * zz + c;
            _elements[a23] = 0.0f;

            _elements[a30] = _elements[a31] = _elements[a32] = 0.0f;
            _elements[a33] = 1.0f;
        }
    }

    template <class T>
    Matrix4<T>::Matrix4(const RotateType, const Vec3<T>& vec, T r) {
        if (r == 0.0f) {
            *this = identity;
        }
        else {
            _flag = 0;
            Vec3<T> tmp(vec);
            tmp.Normalize();
            T c = T(::cos(r)), s = T(::sin(r));
            T t = 1.0f - c;
            T xx = tmp[X] * tmp[X];
            T yy = tmp[Y] * tmp[Y];
            T zz = tmp[Z] * tmp[Z];
            T xy = tmp[X] * tmp[Y];
            T xz = tmp[X] * tmp[Z];
            T yz = tmp[Y] * tmp[Z];

            _elements[a00] = t * xx + c;
            _elements[a01] = t * xy + s * tmp[Z];
            _elements[a02] = t * xz - s * tmp[Y];
            _elements[a03] = 0.0f;
            _elements[a10] = t * xy - s * tmp[Z];
            _elements[a11] = t * yy + c;
            _elements[a12] = t * yz + s * tmp[X];
            _elements[a13] = 0.0f;
            _elements[a20] = t * xz + s * tmp[Y];
            _elements[a21] = t * yz - s * tmp[X];
            _elements[a22] = t * zz + c;
            _elements[a23] = 0.0f;

            _elements[a30] = _elements[a31] = _elements[a32] = 0.0f;
            _elements[a33] = 1.0f;
        }
    }

    template <class T>
    Matrix4<T>::Matrix4(const Quaternion<T>& q)
        : _flag(0) {
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

        _elements[a00] = 1.0f - (yy2 + zz2);
        _elements[a01] = xy2 + wz2;
        _elements[a02] = xz2 - wy2;
        _elements[a03] = 0.0f;

        _elements[a10] = xy2 - wz2;
        _elements[a11] = 1.0f - (xx2 + zz2);
        _elements[a12] = yz2 + wx2;
        _elements[a13] = 0.0f;

        _elements[a20] = xz2 + wy2;
        _elements[a21] = yz2 - wx2;
        _elements[a22] = 1.0f - (xx2 + yy2);
        _elements[a23] = 0.0f;
        _elements[a30] = _elements[a31] = _elements[a32] = 0.0f;
        _elements[a33] = 1.0f;
    }

    template <class T>
    Matrix4<T>::Matrix4(const Rotation4<T>& r)
        : _flag(0) {
        if (r[R] == 0.0f) {
            *this = identity;
        }
        else {
            //_flag = 0;
            T c = T(::cos(r[R])), s = T(::sin(r[R]));
            T t = 1.0f - c;
            T xx = r[X] * r[X], yy = r[Y] * r[Y], zz = r[Z] * r[Z];
            T xy = r[X] * r[Y], xz = r[X] * r[Z];
            T yz = r[Y] * r[Z];

            _elements[a00] = t * xx + c;
            _elements[a01] = t * xy + s * r[Z];
            _elements[a02] = t * xz - s * r[Y];
            _elements[a03] = 0.0f;
            _elements[a10] = t * xy - s * r[Z];
            _elements[a11] = t * yy + c;
            _elements[a12] = t * yz + s * r[X];
            _elements[a13] = 0.0f;
            _elements[a20] = t * xz + s * r[Y];
            _elements[a21] = t * yz - s * r[X];
            _elements[a22] = t * zz + c;
            _elements[a23] = 0.0f;

            _elements[a30] = _elements[a31] = _elements[a32] = 0.0f;
            _elements[a33] = 1.0f;
        }
    }

    //multiply the matrix with a rotation matrix
    template <class T>
    inline void
        Matrix4<T>::Rotate(T x, T y, T z, T r) {
            if (r != 0.0f) {
                //normalize if necessary
                T d_1 = x*x + y*y + z*z;
                if (d_1 != 1.0f) {
                    d_1 = 1.0f / sqrtf(d_1);
                    x *= d_1;
                    y *= d_1;
                    z *= d_1;
                }
                // calculate coefficient
                T c = T(::cos(r));
                T s = T(::sin(r));
                T t = 1.0f - c;
                T xx = x * x, yy = y * y, zz = z * z;
                T xy = x * y, xz = x * z;
                T yz = y * z;
                T tmp0[3];
                tmp0[0] = t * xx + c;
                tmp0[1] = t * xy + s * z;
                tmp0[2] = t * xz - s * y;
                T tmp1[3];
                tmp1[0] = t * xy - s * z;
                tmp1[1] = t * yy + c;
                tmp1[2] = t * yz + s * x;
                T tmp2[3];
                tmp2[0] = t * xz + s * y;
                tmp2[1] = t * yz - s * x;
                tmp2[2] = t * zz + c;

                //check for special matrix
                if (_flag == IDENTITY) {
                    _flag = 0;
                    _elements[a00] = tmp0[0];
                    _elements[a01] = tmp0[1];
                    _elements[a02] = tmp0[2];
                    _elements[a10] = tmp1[0];
                    _elements[a11] = tmp1[1];
                    _elements[a12] = tmp1[2];
                    _elements[a20] = tmp2[0];
                    _elements[a21] = tmp2[1];
                    _elements[a22] = tmp2[2];
                }
                else {
                    T tmp[2];
                    //first row
                    tmp[0] = _elements[a00] * tmp0[0] + _elements[a01] * tmp1[0] + _elements[a02] * tmp2[0];
                    tmp[1] = _elements[a00] * tmp0[1] + _elements[a01] * tmp1[1] + _elements[a02] * tmp2[1];
                    _elements[a02] = _elements[a00] * tmp0[2] + _elements[a01] * tmp1[2] + _elements[a02] * tmp2[2];
                    _elements[a00] = tmp[0];
                    _elements[a01] = tmp[1];

                    //second row
                    tmp[0] = _elements[a10] * tmp0[0] + _elements[a11] * tmp1[0] + _elements[a12] * tmp2[0];
                    tmp[1] = _elements[a10] * tmp0[1] + _elements[a11] * tmp1[1] + _elements[a12] * tmp2[1];
                    _elements[a12] = _elements[a10] * tmp0[2] + _elements[a11] * tmp1[2] + _elements[a12] * tmp2[2];
                    _elements[a10] = tmp[0];
                    _elements[a11] = tmp[1];

                    //third row
                    tmp[0] = _elements[a20] * tmp0[0] +
                        _elements[a21] * tmp1[0] +
                        _elements[a22] * tmp2[0];
                    tmp[1] = _elements[a20] * tmp0[1] +
                        _elements[a21] * tmp1[1] +
                        _elements[a22] * tmp2[1];
                    _elements[a22] = _elements[a20] * tmp0[2] +
                        _elements[a21] * tmp1[2] +
                        _elements[a22] * tmp2[2];
                    _elements[a20] = tmp[0];
                    _elements[a21] = tmp[1];

                    //last row
                    tmp[0] = _elements[a30] * tmp0[0] +
                        _elements[a31] * tmp1[0] +
                        _elements[a32] * tmp2[0];
                    tmp[1] = _elements[a30] * tmp0[1] +
                        _elements[a31] * tmp1[1] +
                        _elements[a32] * tmp2[1];
                    _elements[a32] = _elements[a30] * tmp0[2] +
                        _elements[a31] * tmp1[2] +
                        _elements[a32] * tmp2[2];
                    _elements[a30] = tmp[0];
                    _elements[a31] = tmp[1];
                }
            }
        }

    //multiply the matrix with a rotation matrix
    template <class T>
    inline void
        Matrix4<T>::PreRotate(T x, T y, T z, T r) {
            if (r != 0.0f) {
                //normalize if necessary
                T d_1 = x*x + y*y + z*z;
                if (d_1 != 1.0f) {
                    d_1 = 1.0f / sqrt(d_1);
                    x *= d_1;
                    y *= d_1;
                    z *= d_1;
                }
                // calculate coefficient
                T c = T(::cos(r));
                T s = T(::sin(r));
                T t = 1.0f - c;
                T xx = x * x, yy = y * y, zz = z * z;
                T xy = x * y, xz = x * z;
                T yz = y * z;
                T tmp0[3];
                tmp0[0] = t * xx + c;
                tmp0[1] = t * xy + s * z;
                tmp0[2] = t * xz - s * y;
                T tmp1[3];
                tmp1[0] = t * xy - s * z;
                tmp1[1] = t * yy + c;
                tmp1[2] = t * yz + s * x;
                T tmp2[3];
                tmp2[0] = t * xz + s * y;
                tmp2[1] = t * yz - s * x;
                tmp2[2] = t * zz + c;

                //check for special matrix
                if (_flag == IDENTITY) {
                    _flag = 0;
                    _elements[a00] = tmp0[0];
                    _elements[a01] = tmp0[1];
                    _elements[a02] = tmp0[2];
                    _elements[a10] = tmp1[0];
                    _elements[a11] = tmp1[1];
                    _elements[a12] = tmp1[2];
                    _elements[a20] = tmp2[0];
                    _elements[a21] = tmp2[1];
                    _elements[a22] = tmp2[2];
                }
                else {
                    T tmp[2];
                    //first column
                    tmp[0] = tmp0[0] * _elements[a00] +
                        tmp0[1] * _elements[a10] +
                        tmp0[2] * _elements[a20];
                    tmp[1] = tmp1[0] * _elements[a00] +
                        tmp1[1] * _elements[a10] +
                        tmp1[2] * _elements[a20];
                    _elements[a20] = tmp2[0] * _elements[a00] +
                        tmp2[1] * _elements[a10] +
                        tmp2[2] * _elements[a20];
                    _elements[a00] = tmp[0];
                    _elements[a10] = tmp[1];

                    //second column
                    tmp[0] = tmp0[0] * _elements[a01] +
                        tmp0[1] * _elements[a11] +
                        tmp0[2] * _elements[a21];
                    tmp[1] = tmp1[0] * _elements[a01] +
                        tmp1[1] * _elements[a11] +
                        tmp1[2] * _elements[a21];
                    _elements[a21] = tmp2[0] * _elements[a01] +
                        tmp2[1] * _elements[a11] +
                        tmp2[2] * _elements[a21];
                    _elements[a01] = tmp[0];
                    _elements[a11] = tmp[1];

                    //third column
                    tmp[0] = tmp0[0] * _elements[a02] +
                        tmp0[1] * _elements[a12] +
                        tmp0[2] * _elements[a22];
                    tmp[1] = tmp1[0] * _elements[a02] +
                        tmp1[1] * _elements[a12] +
                        tmp1[2] * _elements[a22];
                    _elements[a22] = tmp2[0] * _elements[a02] +
                        tmp2[1] * _elements[a12] +
                        tmp2[2] * _elements[a22];
                    _elements[a02] = tmp[0];
                    _elements[a12] = tmp[1];

                    //last column
                    tmp[0] = tmp0[0] * _elements[a03] +
                        tmp0[1] * _elements[a13] +
                        tmp0[2] * _elements[a23];
                    tmp[1] = tmp1[0] * _elements[a03] +
                        tmp1[1] * _elements[a13] +
                        tmp1[2] * _elements[a23];
                    _elements[a23] = tmp2[0] * _elements[a03] +
                        tmp2[1] * _elements[a13] +
                        tmp2[2] * _elements[a23];
                    _elements[a03] = tmp[0];
                    _elements[a13] = tmp[1];
                }
            }
        }

    template <class T>
    inline void
        Matrix4<T>::Rotate(const Quaternion<T>& q) {
            _flag = 0;

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

            T tmp0[3];
            tmp0[0] = 1.0f - (yy2 + zz2);
            tmp0[1] = xy2 + wz2;
            tmp0[2] = xz2 - wy2;

            T tmp1[3];
            tmp1[0] = xy2 - wz2;
            tmp1[1] = 1.0f - (xx2 + zz2);
            tmp1[2] = yz2 + wx2;

            T tmp2[3];
            tmp2[0] = xz2 + wy2;
            tmp2[1] = yz2 - wx2;
            tmp2[2] = 1.0f - (xx2 + yy2);

            //check for special matrix
            if (_flag == IDENTITY) {
                _flag = 0;
                _elements[a00] = tmp0[0];
                _elements[a01] = tmp0[1];
                _elements[a02] = tmp0[2];
                _elements[a10] = tmp1[0];
                _elements[a11] = tmp1[1];
                _elements[a12] = tmp1[2];
                _elements[a20] = tmp2[0];
                _elements[a21] = tmp2[1];
                _elements[a22] = tmp2[2];
            }
            else {
                T tmp[2];
                //first row
                tmp[0] = _elements[a00] * tmp0[0] +
                    _elements[a01] * tmp1[0] +
                    _elements[a02] * tmp2[0];
                tmp[1] = _elements[a00] * tmp0[1] +
                    _elements[a01] * tmp1[1] +
                    _elements[a02] * tmp2[1];
                _elements[a02] = _elements[a00] * tmp0[2] +
                    _elements[a01] * tmp1[2] +
                    _elements[a02] * tmp2[2];
                _elements[a00] = tmp[0];
                _elements[a01] = tmp[1];

                //second row
                tmp[0] = _elements[a10] * tmp0[0] +
                    _elements[a11] * tmp1[0] +
                    _elements[a12] * tmp2[0];
                tmp[1] = _elements[a10] * tmp0[1] +
                    _elements[a11] * tmp1[1] +
                    _elements[a12] * tmp2[1];
                _elements[a12] = _elements[a10] * tmp0[2] +
                    _elements[a11] * tmp1[2] +
                    _elements[a12] * tmp2[2];
                _elements[a10] = tmp[0];
                _elements[a11] = tmp[1];

                //third row
                tmp[0] = _elements[a20] * tmp0[0] +
                    _elements[a21] * tmp1[0] +
                    _elements[a22] * tmp2[0];
                tmp[1] = _elements[a20] * tmp0[1] +
                    _elements[a21] * tmp1[1] +
                    _elements[a22] * tmp2[1];
                _elements[a22] = _elements[a20] * tmp0[2] +
                    _elements[a21] * tmp1[2] +
                    _elements[a22] * tmp2[2];
                _elements[a20] = tmp[0];
                _elements[a21] = tmp[1];

                //last row
                tmp[0] = _elements[a30] * tmp0[0] +
                    _elements[a31] * tmp1[0] +
                    _elements[a32] * tmp2[0];
                tmp[1] = _elements[a30] * tmp0[1] +
                    _elements[a31] * tmp1[1] +
                    _elements[a32] * tmp2[1];
                _elements[a32] = _elements[a30] * tmp0[2] +
                    _elements[a31] * tmp1[2] +
                    _elements[a32] * tmp2[2];
                _elements[a30] = tmp[0];
                _elements[a31] = tmp[1];
            }
        }

    //multiply the matrix with a rotation matrix
    template <class T>
    inline void
        Matrix4<T>::PreRotate(const Quaternion<T>& q) {
            _flag = 0;

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

            T tmp0[3];
            tmp0[0] = 1.0f - (yy2 + zz2);
            tmp0[1] = xy2 + wz2;
            tmp0[2] = xz2 - wy2;

            T tmp1[3];
            tmp1[0] = xy2 - wz2;
            tmp1[1] = 1.0f - (xx2 + zz2);
            tmp1[2] = yz2 + wx2;

            T tmp2[3];
            tmp2[0] = xz2 + wy2;
            tmp2[1] = yz2 - wx2;
            tmp2[2] = 1.0f - (xx2 + yy2);

            //check for special matrix
            if (_flag == IDENTITY) {
                _flag = 0;
                _elements[a00] = tmp0[0];
                _elements[a01] = tmp0[1];
                _elements[a02] = tmp0[2];
                _elements[a10] = tmp1[0];
                _elements[a11] = tmp1[1];
                _elements[a12] = tmp1[2];
                _elements[a20] = tmp2[0];
                _elements[a21] = tmp2[1];
                _elements[a22] = tmp2[2];
            }
            else {
                T tmp[2];
                //first column
                tmp[0] = tmp0[0] * _elements[a00] +
                    tmp0[1] * _elements[a10] +
                    tmp0[2] * _elements[a20];
                tmp[1] = tmp1[0] * _elements[a00] +
                    tmp1[1] * _elements[a10] +
                    tmp1[2] * _elements[a20];
                _elements[a20] = tmp2[0] * _elements[a00] +
                    tmp2[1] * _elements[a10] +
                    tmp2[2] * _elements[a20];
                _elements[a00] = tmp[0];
                _elements[a10] = tmp[1];

                //second column
                tmp[0] = tmp0[0] * _elements[a01] +
                    tmp0[1] * _elements[a11] +
                    tmp0[2] * _elements[a21];
                tmp[1] = tmp1[0] * _elements[a01] +
                    tmp1[1] * _elements[a11] +
                    tmp1[2] * _elements[a21];
                _elements[a21] = tmp2[0] * _elements[a01] +
                    tmp2[1] * _elements[a11] +
                    tmp2[2] * _elements[a21];
                _elements[a01] = tmp[0];
                _elements[a11] = tmp[1];

                //third column
                tmp[0] = tmp0[0] * _elements[a02] +
                    tmp0[1] * _elements[a12] +
                    tmp0[2] * _elements[a22];
                tmp[1] = tmp1[0] * _elements[a02] +
                    tmp1[1] * _elements[a12] +
                    tmp1[2] * _elements[a22];
                _elements[a22] = tmp2[0] * _elements[a02] +
                    tmp2[1] * _elements[a12] +
                    tmp2[2] * _elements[a22];
                _elements[a02] = tmp[0];
                _elements[a12] = tmp[1];

                //last column
                tmp[0] = tmp0[0] * _elements[a03] +
                    tmp0[1] * _elements[a13] +
                    tmp0[2] * _elements[a23];
                tmp[1] = tmp1[0] * _elements[a03] +
                    tmp1[1] * _elements[a13] +
                    tmp1[2] * _elements[a23];
                _elements[a23] = tmp2[0] * _elements[a03] +
                    tmp2[1] * _elements[a13] +
                    tmp2[2] * _elements[a23];
                _elements[a03] = tmp[0];
                _elements[a13] = tmp[1];
            }
        }

    template <class T>
    inline void
        Matrix4<T>::Rotate(Oint axis, T angle) {
            if (angle != 0.0f) {
                T cos = ::cosf(angle);
                T sin = ::sinf(angle);
                T tmp;
                switch (axis) {
                    case X:
                        if (_flag == IDENTITY) {
                            _elements[a11] = _elements[a22] = cos;
                            _elements[a12] = sin;
                            _elements[a21] = -sin;
                            _flag = 0;
                        }
                        else {
                            tmp = _elements[a01] * cos - _elements[a02] * sin;
                            _elements[a02] = _elements[a01] * sin + _elements[a02] * cos;
                            _elements[a01] = tmp;

                            tmp = _elements[a11] * cos - _elements[a12] * sin;
                            _elements[a12] = _elements[a11] * sin + _elements[a12] * cos;
                            _elements[a11] = tmp;

                            tmp = _elements[a21] * cos - _elements[a22] * sin;
                            _elements[a22] = _elements[a21] * sin + _elements[a22] * cos;
                            _elements[a21] = tmp;

                            tmp = _elements[a31] * cos - _elements[a32] * sin;
                            _elements[a32] = _elements[a31] * sin + _elements[a32] * cos;
                            _elements[a31] = tmp;
                        }
                        break;

                    case Y:
                        if (_flag == IDENTITY) {
                            _elements[a00] = _elements[a22] = cos;
                            _elements[a20] = sin;
                            _elements[a02] = -sin;
                            _flag = 0;
                        }
                        else {
                            tmp = _elements[a00] * cos + _elements[a02] * sin;
                            _elements[a02] = _elements[a02] * cos - _elements[a00] * sin;
                            _elements[a00] = tmp;

                            tmp = _elements[a10] * cos + _elements[a12] * sin;
                            _elements[a12] = _elements[a12] * cos - _elements[a10] * sin;
                            _elements[a10] = tmp;

                            tmp = _elements[a20] * cos + _elements[a22] * sin;
                            _elements[a22] = _elements[a22] * cos - _elements[a20] * sin;
                            _elements[a20] = tmp;

                            tmp = _elements[a30] * cos + _elements[a32] * sin;
                            _elements[a32] = _elements[a32] * cos - _elements[a30] * sin;
                            _elements[a30] = tmp;
                        }
                        break;

                    case Z:
                        if (_flag == IDENTITY) {
                            _elements[a00] = _elements[a11] = cos;
                            _elements[a01] = sin;
                            _elements[a10] = -sin;
                            _flag = 0;
                        }
                        else {
                            tmp = _elements[a00] * cos - _elements[a01] * sin;
                            _elements[a01] = _elements[a00] * sin + _elements[a01] * cos;
                            _elements[a00] = tmp;

                            tmp = _elements[a10] * cos - _elements[a11] * sin;
                            _elements[a11] = _elements[a10] * sin + _elements[a11] * cos;
                            _elements[a10] = tmp;

                            tmp = _elements[a20] * cos - _elements[a21] * sin;
                            _elements[a21] = _elements[a20] * sin + _elements[a21] * cos;
                            _elements[a20] = tmp;

                            tmp = _elements[a30] * cos - _elements[a31] * sin;
                            _elements[a31] = _elements[a30] * sin + _elements[a31] * cos;
                            _elements[a30] = tmp;
                        }
                        break;

                    default:
                        //WARNING("Creating undefined matrix");
                        _flag = UNDEFINED;
                }
            }
        }

    template <class T>
    inline void
        Matrix4<T>::Translate(T x, T y, T z) {
            if (_flag == IDENTITY) {
                if (x != 0.0f || y != 0.0f || z != 0.0f) {
                    _elements[a30] = x;
                    _elements[a31] = y;
                    _elements[a32] = z;
                    _flag = 0;
                }
            }
            else {
                if (_elements[a03] != 0.0f) {
                    _elements[a00] += _elements[a03] * x;
                    _elements[a01] += _elements[a03] * y;
                    _elements[a02] += _elements[a03] * z;
                }
                if (_elements[a13] != 0.0f) {
                    _elements[a10] += _elements[a13] * x;
                    _elements[a11] += _elements[a13] * y;
                    _elements[a12] += _elements[a13] * z;
                }
                if (_elements[a23] != 0.0f) {
                    _elements[a20] += _elements[a23] * x;
                    _elements[a21] += _elements[a23] * y;
                    _elements[a22] += _elements[a23] * z;
                }
                _elements[a30] += _elements[a33] * x;
                _elements[a31] += _elements[a33] * y;
                _elements[a32] += _elements[a33] * z;
            }
        }

    template <class T>
    inline void
        Matrix4<T>::PreTranslate(T x, T y, T z) {
            if (_flag == IDENTITY) {
                if (x != 0.0f || y != 0.0f || z != 0.0f) {
                    _elements[a30] = x;
                    _elements[a31] = y;
                    _elements[a32] = z;
                    _flag = 0;
                }
            }
            else {
                _elements[a30] += x *_elements[a00] + y *_elements[a10] + z *_elements[a20];
                _elements[a31] += x *_elements[a01] + y *_elements[a11] + z *_elements[a21];
                _elements[a32] += x *_elements[a02] + y *_elements[a12] + z *_elements[a22];
                _elements[a33] += x *_elements[a03] + y *_elements[a13] + z *_elements[a23];
            }
        }

    template <class T>
    inline void
        Matrix4<T>::Scale(T sx, T sy, T sz) {
            if (_flag == IDENTITY) {
                if (sx != 0.0f || sy != 0.0f || sz != 0.0f) {
                    _elements[a00] = sx;
                    _elements[a11] = sy;
                    _elements[a22] = sz;
                    _flag = 0;
                }
            }
            else {
                if (sx != 1.0f) {
                    _elements[a00] *= sx;
                    _elements[a10] *= sx;
                    _elements[a20] *= sx;
                    _elements[a30] *= sx;
                }
                if (sy != 1.0f) {
                    _elements[a01] *= sy;
                    _elements[a11] *= sy;
                    _elements[a21] *= sy;
                    _elements[a31] *= sy;
                }
                if (sz != 1.0f) {
                    _elements[a02] *= sz;
                    _elements[a12] *= sz;
                    _elements[a22] *= sz;
                    _elements[a32] *= sz;
                }
            }
        }

    template <class T>
    inline void
        Matrix4<T>::PreScale(T sx, T sy, T sz) {
            if (_flag == IDENTITY) {
                if (sx != 0.0f || sy != 0.0f || sz != 0.0f) {
                    _elements[a00] = sx;
                    _elements[a11] = sy;
                    _elements[a22] = sz;
                    _flag = 0;
                }
            }
            else {
                if (sx != 1.0f) {
                    _elements[a00] *= sx;
                    _elements[a01] *= sx;
                    _elements[a02] *= sx;
                    _elements[a03] *= sx;
                }
                if (sy != 1.0f) {
                    _elements[a10] *= sy;
                    _elements[a11] *= sy;
                    _elements[a12] *= sy;
                    _elements[a13] *= sy;
                }
                if (sz != 1.0f) {
                    _elements[a20] *= sz;
                    _elements[a21] *= sz;
                    _elements[a22] *= sz;
                    _elements[a23] *= sz;
                }
            }
        }

    template <class T>
    inline void
        Matrix4<T>::Scale(T scale) {
            if (scale != 1.0f) {
                if (_flag == IDENTITY) {
                    _elements[a00] = scale;
                    _elements[a11] = scale;
                    _elements[a22] = scale;
                    _flag = 0;
                }
                else {
                    _elements[a00] *= scale;
                    _elements[a10] *= scale;
                    _elements[a20] *= scale;
                    _elements[a30] *= scale;
                    _elements[a01] *= scale;
                    _elements[a11] *= scale;
                    _elements[a21] *= scale;
                    _elements[a31] *= scale;
                    _elements[a02] *= scale;
                    _elements[a12] *= scale;
                    _elements[a22] *= scale;
                    _elements[a32] *= scale;
                }
            }
        }

    template <class T>
    inline void
        Matrix4<T>::PreScale(T scale) {
            if (scale != 1.0f) {
                if (_flag == IDENTITY) {
                    _elements[a00] = scale;
                    _elements[a11] = scale;
                    _elements[a22] = scale;
                    _flag = 0;
                }
                else {
                    _elements[a00] *= scale;
                    _elements[a01] *= scale;
                    _elements[a02] *= scale;
                    _elements[a03] *= scale;
                    _elements[a10] *= scale;
                    _elements[a11] *= scale;
                    _elements[a12] *= scale;
                    _elements[a13] *= scale;
                    _elements[a20] *= scale;
                    _elements[a21] *= scale;
                    _elements[a22] *= scale;
                    _elements[a23] *= scale;
                }
            }
        }

    // equality
    template <class T>
    Obool
        Matrix4<T>::Equal(const Matrix4<T>& X, const T tolerance) const {
            return (((_flag == X._flag) && _flag) ||
                    fabs(_elements[a00] - X._elements[a00]) < tolerance &&
                    fabs(_elements[a01] - X._elements[a01]) < tolerance &&
                    fabs(_elements[a02] - X._elements[a02]) < tolerance &&
                    fabs(_elements[a03] - X._elements[a03]) < tolerance &&
                    fabs(_elements[a10] - X._elements[a10]) < tolerance &&
                    fabs(_elements[a11] - X._elements[a11]) < tolerance &&
                    fabs(_elements[a12] - X._elements[a12]) < tolerance &&
                    fabs(_elements[a13] - X._elements[a13]) < tolerance &&
                    fabs(_elements[a20] - X._elements[a20]) < tolerance &&
                    fabs(_elements[a21] - X._elements[a21]) < tolerance &&
                    fabs(_elements[a22] - X._elements[a22]) < tolerance &&
                    fabs(_elements[a23] - X._elements[a23]) < tolerance &&
                    fabs(_elements[a30] - X._elements[a30]) < tolerance &&
                    fabs(_elements[a31] - X._elements[a31]) < tolerance &&
                    fabs(_elements[a32] - X._elements[a32]) < tolerance &&
                    fabs(_elements[a33] - X._elements[a33]) < tolerance);
        }

    template <class T>
    Matrix4<T>&
        Matrix4<T>::operator*=(const Matrix4<T>& mat) {
            if (_flag || mat._flag) {
                if (_flag == IDENTITY && mat._flag != IDENTITY)
                    return (*this = mat);
                else
                    return *this;
            }

            T tmp[3];
            //first row
            tmp[0] = _elements[a00] * mat._elements[a00] +
                _elements[a01] * mat._elements[a10] +
                _elements[a02] * mat._elements[a20] +
                _elements[a03] * mat._elements[a30];
            tmp[1] = _elements[a00] * mat._elements[a01] +
                _elements[a01] * mat._elements[a11] +
                _elements[a02] * mat._elements[a21] +
                _elements[a03] * mat._elements[a31];
            tmp[2] = _elements[a00] * mat._elements[a02] +
                _elements[a01] * mat._elements[a12] +
                _elements[a02] * mat._elements[a22] +
                _elements[a03] * mat._elements[a32];
            _elements[a03] = _elements[a00] * mat._elements[a03] +
                _elements[a01] * mat._elements[a13] +
                _elements[a02] * mat._elements[a23] +
                _elements[a03] * mat._elements[a33];
            _elements[a00] = tmp[0];
            _elements[a01] = tmp[1];
            _elements[a02] = tmp[2];

            //second row
            tmp[0] = _elements[a10] * mat._elements[a00] +
                _elements[a11] * mat._elements[a10] +
                _elements[a12] * mat._elements[a20] +
                _elements[a13] * mat._elements[a30];
            tmp[1] = _elements[a10] * mat._elements[a01] +
                _elements[a11] * mat._elements[a11] +
                _elements[a12] * mat._elements[a21] +
                _elements[a13] * mat._elements[a31];
            tmp[2] = _elements[a10] * mat._elements[a02] +
                _elements[a11] * mat._elements[a12] +
                _elements[a12] * mat._elements[a22] +
                _elements[a13] * mat._elements[a32];
            _elements[a13] = _elements[a10] * mat._elements[a03] +
                _elements[a11] * mat._elements[a13] +
                _elements[a12] * mat._elements[a23] +
                _elements[a13] * mat._elements[a33];
            _elements[a10] = tmp[0];
            _elements[a11] = tmp[1];
            _elements[a12] = tmp[2];

            //third row
            tmp[0] = _elements[a20] * mat._elements[a00] +
                _elements[a21] * mat._elements[a10] +
                _elements[a22] * mat._elements[a20] +
                _elements[a23] * mat._elements[a30];
            tmp[1] = _elements[a20] * mat._elements[a01] +
                _elements[a21] * mat._elements[a11] +
                _elements[a22] * mat._elements[a21] +
                _elements[a23] * mat._elements[a31];
            tmp[2] = _elements[a20] * mat._elements[a02] +
                _elements[a21] * mat._elements[a12] +
                _elements[a22] * mat._elements[a22] +
                _elements[a23] * mat._elements[a32];
            _elements[a23] = _elements[a20] * mat._elements[a03] +
                _elements[a21] * mat._elements[a13] +
                _elements[a22] * mat._elements[a23] +
                _elements[a23] * mat._elements[a33];
            _elements[a20] = tmp[0];
            _elements[a21] = tmp[1];
            _elements[a22] = tmp[2];

            //last row
            tmp[0] = _elements[a30] * mat._elements[a00] +
                _elements[a31] * mat._elements[a10] +
                _elements[a32] * mat._elements[a20] +
                _elements[a33] * mat._elements[a30];
            tmp[1] = _elements[a30] * mat._elements[a01] +
                _elements[a31] * mat._elements[a11] +
                _elements[a32] * mat._elements[a21] +
                _elements[a33] * mat._elements[a31];
            tmp[2] = _elements[a30] * mat._elements[a02] +
                _elements[a31] * mat._elements[a12] +
                _elements[a32] * mat._elements[a22] +
                _elements[a33] * mat._elements[a32];
            _elements[a33] = _elements[a30] * mat._elements[a03] +
                _elements[a31] * mat._elements[a13] +
                _elements[a32] * mat._elements[a23] +
                _elements[a33] * mat._elements[a33];
            _elements[a30] = tmp[0];
            _elements[a31] = tmp[1];
            _elements[a32] = tmp[2];

            return *this;
        }

    template <class T>
    Matrix4<T>&
        Matrix4<T>::PreMultiply(const Matrix4<T>& mat) {
            if (_flag || mat._flag) {
                if (_flag == IDENTITY && mat._flag != IDENTITY)
                    return (*this = mat);
                else
                    return *this;
            }

            T tmp[3];
            //first column
            tmp[0] = mat._elements[a00] * _elements[a00] +
                mat._elements[a01] * _elements[a10] +
                mat._elements[a02] * _elements[a20] +
                mat._elements[a03] * _elements[a30];
            tmp[1] = mat._elements[a10] * _elements[a00] +
                mat._elements[a11] * _elements[a10] +
                mat._elements[a12] * _elements[a20] +
                mat._elements[a13] * _elements[a30];
            tmp[2] = mat._elements[a20] * _elements[a00] +
                mat._elements[a21] * _elements[a10] +
                mat._elements[a22] * _elements[a20] +
                mat._elements[a23] * _elements[a30];
            _elements[a30] = mat._elements[a30] * _elements[a00] +
                mat._elements[a31] * _elements[a10] +
                mat._elements[a32] * _elements[a20] +
                mat._elements[a33] * _elements[a30];
            _elements[a00] = tmp[0];
            _elements[a10] = tmp[1];
            _elements[a20] = tmp[2];

            //second column
            tmp[0] = mat._elements[a00] * _elements[a01] +
                mat._elements[a01] * _elements[a11] +
                mat._elements[a02] * _elements[a21] +
                mat._elements[a03] * _elements[a31];
            tmp[1] = mat._elements[a10] * _elements[a01] +
                mat._elements[a11] * _elements[a11] +
                mat._elements[a12] * _elements[a21] +
                mat._elements[a13] * _elements[a31];
            tmp[2] = mat._elements[a20] * _elements[a01] +
                mat._elements[a21] * _elements[a11] +
                mat._elements[a22] * _elements[a21] +
                mat._elements[a23] * _elements[a31];
            _elements[a31] = mat._elements[a30] * _elements[a01] +
                mat._elements[a31] * _elements[a11] +
                mat._elements[a32] * _elements[a21] +
                mat._elements[a33] * _elements[a31];
            _elements[a01] = tmp[0];
            _elements[a11] = tmp[1];
            _elements[a21] = tmp[2];

            //third column
            tmp[0] = mat._elements[a00] * _elements[a02] +
                mat._elements[a01] * _elements[a12] +
                mat._elements[a02] * _elements[a22] +
                mat._elements[a03] * _elements[a32];
            tmp[1] = mat._elements[a10] * _elements[a02] +
                mat._elements[a11] * _elements[a12] +
                mat._elements[a12] * _elements[a22] +
                mat._elements[a13] * _elements[a32];
            tmp[2] = mat._elements[a20] * _elements[a02] +
                mat._elements[a21] * _elements[a12] +
                mat._elements[a22] * _elements[a22] +
                mat._elements[a23] * _elements[a32];
            _elements[a32] = mat._elements[a30] * _elements[a02] +
                mat._elements[a31] * _elements[a12] +
                mat._elements[a32] * _elements[a22] +
                mat._elements[a33] * _elements[a32];
            _elements[a02] = tmp[0];
            _elements[a12] = tmp[1];
            _elements[a22] = tmp[2];

            //last column
            tmp[0] = mat._elements[a00] * _elements[a03] +
                mat._elements[a01] * _elements[a13] +
                mat._elements[a02] * _elements[a23] +
                mat._elements[a03] * _elements[a33];
            tmp[1] = mat._elements[a10] * _elements[a03] +
                mat._elements[a11] * _elements[a13] +
                mat._elements[a12] * _elements[a23] +
                mat._elements[a13] * _elements[a33];
            tmp[2] = mat._elements[a20] * _elements[a03] +
                mat._elements[a21] * _elements[a13] +
                mat._elements[a22] * _elements[a23] +
                mat._elements[a23] * _elements[a33];
            _elements[a33] = mat._elements[a30] * _elements[a03] +
                mat._elements[a31] * _elements[a13] +
                mat._elements[a32] * _elements[a23] +
                mat._elements[a33] * _elements[a33];
            _elements[a03] = tmp[0];
            _elements[a13] = tmp[1];
            _elements[a23] = tmp[2];

            return *this;
        }

    template <class T>
    Matrix4<T>&
        Matrix4<T>::operator*=(T value) {
            if (_flag == IDENTITY) {
                _flag = 0;
                _elements[a00] *= value;
                _elements[a11] *= value;
                _elements[a22] *= value;
                _elements[a33] *= value;
                return *this;
            }
            _elements[a00] *= value;
            _elements[a01] *= value;
            _elements[a02] *= value;
            _elements[a03] *= value;
            _elements[a10] *= value;
            _elements[a11] *= value;
            _elements[a12] *= value;
            _elements[a13] *= value;
            _elements[a20] *= value;
            _elements[a21] *= value;
            _elements[a22] *= value;
            _elements[a23] *= value;
            _elements[a30] *= value;
            _elements[a31] *= value;
            _elements[a32] *= value;
            _elements[a33] *= value;

            return *this;
        }

    template <class T>
    Matrix4<T>&
        Matrix4<T>::operator/=(T value) {
            T value_1 = 1.0f / value;
            if (_flag == IDENTITY) {
                _flag = 0;
                _elements[a00] *= value_1;
                _elements[a11] *= value_1;
                _elements[a22] *= value_1;
                _elements[a33] *= value_1;
                return *this;
            }
            _elements[a00] *= value_1;
            _elements[a01] *= value_1;
            _elements[a02] *= value_1;
            _elements[a03] *= value_1;
            _elements[a10] *= value_1;
            _elements[a11] *= value_1;
            _elements[a12] *= value_1;
            _elements[a13] *= value_1;
            _elements[a20] *= value_1;
            _elements[a21] *= value_1;
            _elements[a22] *= value_1;
            _elements[a23] *= value_1;
            _elements[a30] *= value_1;
            _elements[a31] *= value_1;
            _elements[a32] *= value_1;
            _elements[a33] *= value_1;

            return *this;
        }

    template <class T>
    Matrix4<T>&
        Matrix4<T>::operator+=(const Matrix4<T>& matrix) {
            _flag = 0;
            _elements[a00] += matrix._elements[a00];
            _elements[a01] += matrix._elements[a01];
            _elements[a02] += matrix._elements[a02];
            _elements[a03] += matrix._elements[a03];
            _elements[a10] += matrix._elements[a10];
            _elements[a11] += matrix._elements[a11];
            _elements[a12] += matrix._elements[a12];
            _elements[a13] += matrix._elements[a13];
            _elements[a20] += matrix._elements[a20];
            _elements[a21] += matrix._elements[a21];
            _elements[a22] += matrix._elements[a22];
            _elements[a23] += matrix._elements[a23];
            _elements[a30] += matrix._elements[a30];
            _elements[a31] += matrix._elements[a31];
            _elements[a32] += matrix._elements[a32];
            _elements[a33] += matrix._elements[a33];

            return *this;
        }

    template <class T>
    Matrix4<T>&
        Matrix4<T>::operator-=(const Matrix4<T>& matrix) {
            _flag = 0;
            _elements[a00] -= matrix._elements[a00];
            _elements[a01] -= matrix._elements[a01];
            _elements[a02] -= matrix._elements[a02];
            _elements[a03] -= matrix._elements[a03];
            _elements[a10] -= matrix._elements[a10];
            _elements[a11] -= matrix._elements[a11];
            _elements[a12] -= matrix._elements[a12];
            _elements[a13] -= matrix._elements[a13];
            _elements[a20] -= matrix._elements[a20];
            _elements[a21] -= matrix._elements[a21];
            _elements[a22] -= matrix._elements[a22];
            _elements[a23] -= matrix._elements[a23];
            _elements[a30] -= matrix._elements[a30];
            _elements[a31] -= matrix._elements[a31];
            _elements[a32] -= matrix._elements[a32];
            _elements[a33] -= matrix._elements[a33];

            return *this;
        }

    template <class T>
    Matrix4<T>&
        Matrix4<T>::Transpose() {
            _flag = 0;
            T tmp;

            for (Oint t1 = 0; t1 < 4; t1++)
            for (Oint t2 = 0; t2 < t1; t2++) {
                tmp = _elements[t1 * 4 + t2];
                _elements[t1 * 4 + t2] = _elements[t2 * 4 + t1];
                _elements[t2 * 4 + t1] = tmp;
            };

            return *this;
        }

    template <class T>
    Matrix4<T>&
        Matrix4<T>::Invert() {
            if (_flag) {
                return *this;
            }

            T cofactor[16];
            T tmp[6];

            tmp[0] = _elements[a22] * _elements[a33] - _elements[a32] * _elements[a23];
            tmp[1] = _elements[a12] * _elements[a33] - _elements[a32] * _elements[a13];
            tmp[2] = _elements[a12] * _elements[a23] - _elements[a22] * _elements[a13];
            tmp[3] = _elements[a02] * _elements[a33] - _elements[a32] * _elements[a03];
            tmp[4] = _elements[a02] * _elements[a23] - _elements[a22] * _elements[a03];
            tmp[5] = _elements[a02] * _elements[a13] - _elements[a12] * _elements[a03];

            cofactor[0] = _elements[a11] * tmp[0]
                - _elements[a21] * tmp[1]
                + _elements[a31] * tmp[2];

            cofactor[1] = -(_elements[a01] * tmp[0]
                            - _elements[a21] * tmp[3]
                            + _elements[a31] * tmp[4]);

            cofactor[2] = _elements[a01] * tmp[1]
                - _elements[a11] * tmp[3]
                + _elements[a31] * tmp[5];

            cofactor[3] = -(_elements[a01] * tmp[2]
                            - _elements[a11] * tmp[4]
                            + _elements[a21] * tmp[5]);

            T det = (_elements[a00] * cofactor[0]
                     + _elements[a10] * cofactor[1]
                     + _elements[a20] * cofactor[2]
                     + _elements[a30] * cofactor[3]);

            if (det != 0.0f) {
                T det_1 = 1 / det;
                /* all indexes are wrong rom here on*/
                cofactor[4] = -(_elements[a10] * tmp[0]
                                - _elements[a20] * tmp[1]
                                + _elements[a30] * tmp[2]);

                cofactor[5] = _elements[a00] * tmp[0]
                    - _elements[a20] * tmp[3]
                    + _elements[a30] * tmp[4];

                cofactor[6] = -(_elements[a00] * tmp[1]
                                - _elements[a10] * tmp[3]
                                + _elements[a30] * tmp[5]);

                cofactor[7] = _elements[a00] * tmp[2]
                    - _elements[a10] * tmp[4]
                    + _elements[a20] * tmp[5];

                tmp[0] = _elements[a20] * _elements[a31] - _elements[a30] * _elements[a21];
                tmp[1] = _elements[a10] * _elements[a31] - _elements[a30] * _elements[a11];
                tmp[2] = _elements[a10] * _elements[a21] - _elements[a20] * _elements[a11];
                tmp[3] = _elements[a00] * _elements[a31] - _elements[a30] * _elements[a01];
                tmp[4] = _elements[a00] * _elements[a21] - _elements[a20] * _elements[a01];
                tmp[5] = _elements[a00] * _elements[a11] - _elements[a10] * _elements[a01];

                cofactor[8] = _elements[a13] * tmp[0]
                    - _elements[a23] * tmp[1]
                    + _elements[a33] * tmp[2];

                cofactor[9] = -(_elements[a03] * tmp[0]
                                - _elements[a23] * tmp[3]
                                + _elements[a33] * tmp[4]);

                cofactor[10] = _elements[a03] * tmp[1]
                    - _elements[a13] * tmp[3]
                    + _elements[a33] * tmp[5];

                cofactor[11] = -(_elements[a03] * tmp[2]
                                 - _elements[a13] * tmp[4]
                                 + _elements[a23] * tmp[5]);

                cofactor[12] = -(_elements[a12] * tmp[0]
                                 - _elements[a22] * tmp[1]
                                 + _elements[a32] * tmp[2]);

                cofactor[13] = _elements[a02] * tmp[0]
                    - _elements[a22] * tmp[3]
                    + _elements[a32] * tmp[4];

                cofactor[14] = -(_elements[a02] * tmp[1]
                                 - _elements[a12] * tmp[3]
                                 + _elements[a32] * tmp[5]);

                cofactor[15] = _elements[a02] * tmp[2]
                    - _elements[a12] * tmp[4]
                    + _elements[a22] * tmp[5];

                _elements[a00] = cofactor[0] * det_1;
                _elements[a01] = cofactor[1] * det_1;
                _elements[a02] = cofactor[2] * det_1;
                _elements[a03] = cofactor[3] * det_1;
                _elements[a10] = cofactor[4] * det_1;
                _elements[a11] = cofactor[5] * det_1;
                _elements[a12] = cofactor[6] * det_1;
                _elements[a13] = cofactor[7] * det_1;
                _elements[a20] = cofactor[8] * det_1;
                _elements[a21] = cofactor[9] * det_1;
                _elements[a22] = cofactor[10] * det_1;
                _elements[a23] = cofactor[11] * det_1;
                _elements[a30] = cofactor[12] * det_1;
                _elements[a31] = cofactor[13] * det_1;
                _elements[a32] = cofactor[14] * det_1;
                _elements[a33] = cofactor[15] * det_1;
                return *this;
            }
            else {
                //DIAG(DEBUG_MESSAGE, "Warning: singular matrix");
                _flag = UNDEFINED;
                return *this = Matrix4<T>::identity;
            }
        }

    template <class T>
    T
        Matrix4<T>::Determinant() const {
            if (_flag == IDENTITY)
                return 1;

            T cofactor[16];
            T tmp[6];

            tmp[0] = _elements[a22] * _elements[a33] - _elements[a32] * _elements[a23];
            tmp[1] = _elements[a12] * _elements[a33] - _elements[a32] * _elements[a13];
            tmp[2] = _elements[a12] * _elements[a23] - _elements[a22] * _elements[a13];
            tmp[3] = _elements[a02] * _elements[a33] - _elements[a32] * _elements[a03];
            tmp[4] = _elements[a02] * _elements[a23] - _elements[a22] * _elements[a03];
            tmp[5] = _elements[a02] * _elements[a13] - _elements[a12] * _elements[a03];

            cofactor[0] = _elements[a11] * tmp[0]
                - _elements[a21] * tmp[1]
                + _elements[a31] * tmp[2];

            cofactor[1] = -(_elements[a01] * tmp[0]
                            - _elements[a21] * tmp[3]
                            + _elements[a31] * tmp[4]);

            cofactor[2] = _elements[a01] * tmp[1]
                - _elements[a11] * tmp[3]
                + _elements[a31] * tmp[5];

            cofactor[3] = -(_elements[a01] * tmp[2]
                            - _elements[a11] * tmp[4]
                            + _elements[a21] * tmp[5]);

            return (_elements[a00] * cofactor[0] +
                    _elements[a10] * cofactor[1] +
                    _elements[a20] * cofactor[2] +
                    _elements[a30] * cofactor[3]);
        }

    template <class T>
    Obool
        Matrix4<T>::Decompose(Vec3<T>& translation, Vec3<T>& scale, Rotation4<T>& rotation) const {
            Oint i, j;
            Matrix4<T> locmat;
            Matrix4<T> pmat, invpmat, tinvpmat;
            T prhs[4];
            T perspective[4];
            Vec3<T> row[3];

            locmat = *this;

            //normalize
            if (locmat.Get(3, 3) == 0)
                return false;
            for (i = 0; i < 4; i++)
            for (j = 0; j < 4; j++)
                locmat.Set(i, j, locmat.Get(i, j) / locmat.Get(3, 3));

            pmat = locmat;
            for (i = 0; i < 3; i++)
                pmat.Set(i, 3, 0.0f);
            pmat.Set(3, 3, 1.0f);

            if (pmat.Determinant() == 0.0f)
                return false;

            //// First, isolate perspective. This is the messiest.
            if (locmat.Get(0, 3) != 0 || locmat.Get(0, 3) || locmat.Get(0, 3)) {
                //CoreDebug::Out("perspective not implemented");
                // prhs is the right hand side of the equation.
                prhs[0] = locmat.Get(0, 3);
                prhs[1] = locmat.Get(1, 3);
                prhs[2] = locmat.Get(2, 3);
                prhs[3] = locmat.Get(3, 3);
                // Solve the equation by inverting pmat and multiplying
                // prhs by the inverse. (This is the easiest way, not
                // necessarily the best.)
                invpmat = pmat;
                invpmat.Invert();
                tinvpmat = invpmat;
                tinvpmat.Transpose();
                //get the perspective vector
                tinvpmat.MultVec4ByMatrix(prhs, perspective);
                // Clear the perspective partition.
                locmat.Set(0, 3, 0.0);
                locmat.Set(1, 3, 0.0);
                locmat.Set(2, 3, 0.0);
                locmat.Set(3, 3, 1.0);
            }
            else {
                //Message::Out("Perspective: 0, 0, 0");
            }
            //get translation
            translation = Vec3<T>(locmat.Get(3, 0), locmat.Get(3, 1), locmat.Get(3, 2));
            for (i = 0; i < 3; i++) {
                locmat.Set(3, i, 0.0f);
            }

            //get scale & shear
            for (i = 0; i < 3; i++) {
                row[i][X] = locmat.Get(i, 0);
                row[i][Y] = locmat.Get(i, 1);
                row[i][Z] = locmat.Get(i, 2);
            }

            //compute x scale & normalize first row
            scale[X] = row[0].Length();
            row[0] /= scale[X];

            //compute xy shear and make 2nd row ortogonal to first
            T shearxy = row[0] * row[1];
            row[1] = row[1] - row[0] * shearxy;

            //compute y scale and normalize 2nd row
            scale[Y] = row[1].Length();
            row[1] /= scale[Y];
            shearxy /= scale[Y];

            //compute xz and yz shear, ortogonalize 3rd row
            T shearxz = row[0] * row[2];
            row[2] = row[2] - row[0] * shearxz;
            T shearyz = row[1] * row[2];
            row[2] = row[2] - row[1] * shearyz;

            //get z scale and noramlize 3rd row
            scale[Z] = row[2].Length();
            row[2] /= scale[Z];
            shearxz /= scale[Z];
            shearyz /= scale[Z];

            if ((row[0] * (row[1].Cross(row[2]))) < 0) {
                scale *= -1.0f;
                for (i = 0; i < 3; i++) {
                    row[i] *= -1.0;
                }
            }
            //avoid negative values due to numerical problems
            T w = row[0][0] + row[1][1] + row[2][2] + 1.0f;
            if (w > 0)
                w = T(0.5)*sqrt(row[0][0] + row[1][1] + row[2][2] + T(1.0));
            else
                w = 0;

            Obool specialCase = false;
            Quaternion<T> q;
            if (w == 0.0f) {
                specialCase = true;
                if (row[0][0] >= 0.0f) {
                    q = Quaternion<T>(1.0f, 0.0f, 0.0f, PI);
                    row[1] *= -1.0f;
                    row[2] *= -1.0f;
                }
                else if (row[1][1] >= 0.0f) {
                    q = Quaternion<T>(0.0f, 1.0f, 0.0f, PI);
                    row[0] *= -1.0f;
                    row[2] *= -1.0f;
                }
                else if (row[2][2] >= 0.0f) {
                    q = Quaternion<T>(0.0f, 0.0f, 1.0f, PI);
                    row[0] *= -1.0f;
                    row[1] *= -1.0f;
                }
            }

            w = T(0.5)*sqrt(row[0][0] + row[1][1] + row[2][2] + T(1.0));
            T s = 0.25f / w;
            Quaternion<T> q2;
            q2._vec[0] = (row[1][2] - row[2][1])*s;
            q2._vec[1] = (row[2][0] - row[0][2])*s;
            q2._vec[2] = (row[0][1] - row[1][0])*s;
            q2._vec[3] = w;

            if (specialCase)
                q2 = q2*q;

            rotation = Rotation4<T>(q2);

            //rotation[3] =  acosf(w)*2.0f;
            //if (rotation[3] == 0) {
            //  rotation[0] = 1;
            //  rotation[1] = 0;
            //  rotation[2] = 0;
            //} else {
            //  T tmp = 1/sinf(rotation[3]/2.0f);
            //  rotation[0] = qx*tmp;
            //  rotation[1] = qy*tmp;
            //  rotation[2] = qz*tmp;
            //}
            return true;
        }

    template <class T>
    void
        Matrix4<T>::MultVec4ByMatrix(T vector[4], T result[4]) const {
            result[0] = vector[0] * _elements[a00] +
                vector[1] * _elements[a10] +
                vector[2] * _elements[a20] +
                vector[3] * _elements[a30];

            result[1] = vector[0] * _elements[a01] +
                vector[1] * _elements[a11] +
                vector[2] * _elements[a21] +
                vector[3] * _elements[a31];

            result[2] = vector[0] * _elements[a02] +
                vector[1] * _elements[a12] +
                vector[2] * _elements[a22] +
                vector[3] * _elements[a32];

            result[3] = vector[0] * _elements[a03] +
                vector[1] * _elements[a13] +
                vector[2] * _elements[a23] +
                vector[3] * _elements[a33];
        }

    template <class T>
    void
        Matrix4<T>::GetRotation(T& rx, T& ry, T&  rz) const {
            T temp;
            ry = atan2f(_elements[8], sqrtf(_elements[0] * _elements[0] + _elements[4] * _elements[4]));
            //ry = asinf(_elements[8]);
            temp = cosf(ry);
            if (fabs(temp) <= TOLERANCE) {
                //gimbal locks!!!
                rx = 0;
                rz = 0;
            }
            else {
                if (_elements[10] * temp > 0) {
                    rx = atan2f(-_elements[9], _elements[10]);
                }
                else {
                    rx = atan2f(-_elements[9], _elements[10]) + PI;
                }
                if (_elements[0] * temp > 0) {
                    rz = atan2f(-_elements[4], _elements[0]);
                }
                else {
                    rz = atan2f(-_elements[4], _elements[0]) + PI;
                }
            }
        }

} // namespace enterprise_manager

