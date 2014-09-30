namespace enterprise_manager {

template <class T>
inline
Matrix3<T>::Matrix3()
  : _flag(IDENTITY)
{
  _elements[a10] = _elements[a20] = 0.0f;
  _elements[a01] = _elements[a21] = 0.0f;
  _elements[a02] = _elements[a12] = 0.0f;
  _elements[a00] = _elements[a11] = _elements[a22] = 1.0f;
}

template <class T>
inline
Matrix3<T>::Matrix3(const SpecialMatrix matrixType)
  : _flag(IDENTITY)
{
  if (matrixType == IDENTITY) {
    _elements[a10] = _elements[a20] = 0.0f;
    _elements[a01] = _elements[a21] = 0.0f;
    _elements[a02] = _elements[a12] = 0.0f;
    _elements[a00] = _elements[a11] = _elements[a22] = 1.0f;

  } else {
    _flag = UNDEFINED;
  }
}

template <class T>
inline
Matrix3<T>::Matrix3(const ScaleType,T value)
  : _flag(0)
{
  _elements[a10] = _elements[a20] = 0.0f;
  _elements[a01] = _elements[a21] = 0.0f;
  _elements[a02] = _elements[a12] = 0.0f;

  _elements[a00] = _elements[a11] = value;
  _elements[a22] = 1.0f;

}

template <class T>
inline
Matrix3<T>::Matrix3(const ScaleType, T x, T y)
  : _flag(0)
{
  _elements[a01] = _elements[a02] = 0.0f;
  _elements[a10] = _elements[a12] = 0.0f;
  _elements[a20] = _elements[a21] = 0.0f;
  _elements[a22] = 1.0f;
  _elements[a00] = x;
  _elements[a11] = y;
}

template <class T>
inline
Matrix3<T>::Matrix3(const ScaleType, const Vec2<T>& vec)
  : _flag(0)
{
  _elements[a01] = _elements[a02] = 0.0f;
  _elements[a10] = _elements[a12] = 0.0f;
  _elements[a20] = _elements[a21] = 0.0f;
  _elements[a22] = 1.0f;
  _elements[a00] = vec[X];
  _elements[a11] = vec[Y];
}

template <class T>
inline
Matrix3<T>::Matrix3(const TranslateType, T x, T y)
  : _flag(0)
{
  _elements[a01] = _elements[a02] = 0.0f;
  _elements[a10] = _elements[a12] = 0.0f;
  _elements[a00] = _elements[a11] = _elements[a22] = 1.0f;
  _elements[a20] = x;
  _elements[a21] = y;
}

template <class T>
inline
Matrix3<T>::Matrix3(const TranslateType, const Vec2<T>& vec)
  : _flag(0)
{
  _elements[a01] = _elements[a02] = 0.0f;
  _elements[a10] = _elements[a12] = 0.0f;
  _elements[a00] = _elements[a11] = _elements[a22] = 1.0f;
  _elements[a20] = vec[X];
  _elements[a21] = vec[Y];
}

template <class T>
inline
Matrix3<T>::Matrix3(const Matrix3<T>& X)
  : _flag(X._flag)
{
  _elements[a00] = X._elements[a00];
  _elements[a01] = X._elements[a01];
  _elements[a02] = X._elements[a02];
  _elements[a10] = X._elements[a10];
  _elements[a11] = X._elements[a11];
  _elements[a12] = X._elements[a12];
  _elements[a20] = X._elements[a20];
  _elements[a21] = X._elements[a21];
  _elements[a22] = X._elements[a22];
}

template <class T>
inline Matrix3<T>&
Matrix3<T>::operator=(const Matrix3<T>& X)
{
  _flag = X._flag;
  _elements[a00] = X._elements[a00];
  _elements[a10] = X._elements[a10];
  _elements[a20] = X._elements[a20];
  _elements[a01] = X._elements[a01];
  _elements[a11] = X._elements[a11];
  _elements[a21] = X._elements[a21];
  _elements[a02] = X._elements[a02];
  _elements[a12] = X._elements[a12];
  _elements[a22] = X._elements[a22];
  return *this;
}

template <class T>
inline
Matrix3<T>::Matrix3(const T matrix[16])
: _flag(0)
{
  _elements[a00] = matrix[0];
  _elements[a01] = matrix[1];
  _elements[a02] = matrix[2];
  _elements[a10] = matrix[3];
  _elements[a11] = matrix[4];
  _elements[a12] = matrix[5];
  _elements[a20] = matrix[6];
  _elements[a21] = matrix[7];
  _elements[a22] = matrix[8];
}

template <class T>
inline
Matrix3<T>::Matrix3(const T matrix[3][3])
: _flag(0)
{
  _elements[a00] = matrix[0][0];
  _elements[a01] = matrix[0][1];
  _elements[a02] = matrix[0][2];
  _elements[a10] = matrix[1][0];
  _elements[a11] = matrix[1][1];
  _elements[a12] = matrix[1][2];
  _elements[a20] = matrix[2][0];
  _elements[a21] = matrix[2][1];
  _elements[a22] = matrix[2][2];

}

template <class T>
inline
Matrix3<T>::~Matrix3()
{
}

template <class T>
inline Obool
Matrix3<T>::operator==( const Matrix3<T>& X ) const
{
  return ( ((_flag == X._flag) && _flag ) ||
	   (_elements[a00] == X._elements[a00] &&
  _elements[a01] == X._elements[a01] &&
  _elements[a02] == X._elements[a02] &&
  _elements[a10] == X._elements[a10] &&
  _elements[a11] == X._elements[a11] &&
  _elements[a12] == X._elements[a12] &&
  _elements[a20] == X._elements[a20] &&
  _elements[a21] == X._elements[a21] &&
	    _elements[a22] == X._elements[a22]));
}

template <class T>
inline Obool
Matrix3<T>::operator!=( const Matrix3<T>& X ) const
{
  return ( _elements[a00] != X._elements[a00] ||
  _elements[a01] != X._elements[a01] ||
  _elements[a02] != X._elements[a02] ||
  _elements[a10] != X._elements[a10] ||
  _elements[a11] != X._elements[a11] ||
  _elements[a12] != X._elements[a12] ||
  _elements[a20] != X._elements[a20] ||
  _elements[a21] != X._elements[a21] ||
  _elements[a22] != X._elements[a22]);
}

template <class T>
inline Matrix3<T>&
Matrix3<T>::Translate(const Vec2<T>& vec)
{
  return Translate(vec._vec[X], vec._vec[Y]);
}

template <class T>
inline Matrix3<T>&
Matrix3<T>::PreTranslate(const Vec2<T>& vec)
{
  return PreTranslate(vec._vec[X], vec._vec[Y]);
}

template <class T>
inline Matrix3<T>&
Matrix3<T>::Scale(const Vec2<T>& vec)
{
  return Scale(vec._vec[X], vec._vec[Y]);
}

template <class T>
inline Matrix3<T>&
Matrix3<T>::PreScale(const Vec2<T>& vec)
{
  return PreScale(vec._vec[X], vec._vec[Y]);
}

template <class T>
inline Matrix3<T>&
Matrix3<T>::SetColumn(Oint column, const Vec2<T>& vec)
{
  _flag = 0;
  _elements[column] = vec[X];
  _elements[3 + column] = vec[Y];
  return *this;
}

template <class T>
inline Matrix3<T>&
Matrix3<T>::SetRow(Oint row, const Vec2<T>& vec)
{
  _flag = 0;
  _elements[row*3] = vec[X];
  _elements[row*3 + 1] = vec[Y];

  return *this;
}

template <class T>
inline T
Matrix3<T>::Set(Oint row, Oint colmun, T value)
{
  _flag = 0;
  _elements[row*3+colmun] = value;

 return value;
}

template <class T>
inline Vec2<T>
Matrix3<T>::GetTranslation() const
{
  return Vec2<T>(_elements[a20], _elements[a21]);
}

template <class T>
inline Matrix3<T>
Matrix3<T>::GetTranspose() const
{
  Matrix3<T> result(*this);
  result.Transpose();
  return result;
}

template <class T>
inline Matrix3<T>
Matrix3<T>::GetInverse() const
{
  Matrix3<T> result(*this);
  result.Invert();
  return result;
}

template <class T>
inline Vec2<T>
Matrix3<T>::GetRow(Oint row) const
{
  assert(row < 3);
  return Vec2<T>(_elements[row*3], _elements[row*3 + 1]);
}

template <class T>
inline Vec2<T>
Matrix3<T>::GetColumn(Oint col) const
{
  assert(col < 3);
  return Vec2<T>(_elements[col], _elements[3 + col]);
}

template <class T>
inline T
Matrix3<T>::Get(Oint row, Oint column) const
{
  assert(row < 3 && column < 3);

  return _elements[row*3+column];
}

template <class T>
inline Obool
Matrix3<T>::IsUndefined() const
{
  return(_flag == UNDEFINED);
}

template <class T>
inline Obool
Matrix3<T>::IsIdentity() const
{
  return(_flag == IDENTITY);
}

template <class T>
inline const T*
Matrix3<T>::Ptr() const
{
  return _elements;
}

template <class T>
/* static */ const
Matrix3<T> Matrix3<T>::identity;

template <class T>
inline
Matrix3<T>::Matrix3(const RotateType, const T value)
  : _flag(0)
{
  T cos = ::cos(value);
  T sin = ::sin(value);
  _elements[a00] = _elements[a11] = cos;
  _elements[a01] = sin;
  _elements[a10] = -sin;
  _elements[a22] = 1.0f;
  _elements[a02] = _elements[a12] = _elements[a20] = _elements[a21] = 0.0f;
}

template <class T>
inline Matrix3<T>&
Matrix3<T>::Rotate(T angle)
{
  if (angle != 0.0f) {
    T cos = ::cosf(angle);
    T sin = ::sinf(angle);
    T tmp;
    if (_flag == IDENTITY) {
      _elements[a00] = _elements[a11] = cos;
      _elements[a01] = sin;
      _elements[a10] = -sin;
      _flag = 0;
    } else {
      tmp = _elements[a00]*cos - _elements[a01]*sin;
      _elements[a01] = _elements[a00]*sin + _elements[a01]*cos;
      _elements[a00] = tmp;

      tmp = _elements[a10]*cos - _elements[a11]*sin;
      _elements[a11] = _elements[a10]*sin + _elements[a11]*cos;
      _elements[a10] = tmp;

      tmp = _elements[a20]*cos - _elements[a21]*sin;
      _elements[a21] = _elements[a20]*sin + _elements[a21]*cos;
      _elements[a20] = tmp;
    }
  }
  return *this;
}

template <class T>
inline Matrix3<T>&
Matrix3<T>::PreRotate(T angle)
{
  if (angle != 0.0f) {
    T cos = ::cos(angle);
    T sin = ::sin(angle);
    T tmp;
    if (_flag == IDENTITY) {
      _elements[a00] = _elements[a11] = cos;
      _elements[a01] = sin;
      _elements[a10] = -sin;
      _flag = 0;
    } else {
      tmp = cos*_elements[a00] + sin*_elements[a10];
      _elements[a10] = _elements[a10]*cos - _elements[a00]*sin;
      _elements[a00] = tmp;

      tmp = cos*_elements[a01] + sin*_elements[a11];
      _elements[a11] = _elements[a11]*cos - _elements[a01]*sin;
      _elements[a01] = tmp;

      tmp = cos*_elements[a02] + sin*_elements[a12];
      _elements[a12] = _elements[a12]*cos - _elements[a02]*sin;
      _elements[a02] = tmp;
    }
  }
  return *this;
}

template <class T>
inline Matrix3<T>&
Matrix3<T>::Translate(T x, T y)
{
  if (_flag == IDENTITY) {
    if (x != 0.0f || y != 0.0f) {
      _elements[a20] = x;
      _elements[a21] = y;
      _flag = 0;
    }
  } else {
    if(_elements[a02] != 0.0f) {
      _elements[a00] += _elements[a02] * x;
      _elements[a01] += _elements[a02] * y;
    }
    if (_elements[a12] != 0.0f) {
      _elements[a10] += _elements[a12] * x;
      _elements[a11] += _elements[a12] * y;
    }
    _elements[a20] += _elements[a22] * x;
    _elements[a21] += _elements[a22] * y;
  }
  return *this;
}

template <class T>
inline Matrix3<T>&
Matrix3<T>::PreTranslate(T x, T y)
{
  if (_flag == IDENTITY) {
    if (x != 0.0f || y != 0.0f) {
      _elements[a20] = x;
      _elements[a21] = y;
      _flag = 0;
    }
  } else {
    _elements[a20] += _elements[a00] * x + _elements[a10] * y;
    _elements[a21] += _elements[a01] * x + _elements[a11] * y;
    _elements[a22] += _elements[a02] * x + _elements[a12] * y;
  }
  return *this;
}

template <class T>
inline Matrix3<T>&
Matrix3<T>::Scale(T sx, T sy)
{
  if (_flag == IDENTITY) {
    if (sx != 1.0f || sy != 1.0f) {
      _elements[a00] = sx;
      _elements[a11] = sy;
      _flag = 0;
    }
  } else {
    if (sx != 1.0f) {
      _elements[a00] *= sx;
      _elements[a10] *= sx;
      _elements[a20] *= sx;
    }
    if (sy != 1.0f) {
      _elements[a01] *= sy;
      _elements[a11] *= sy;
      _elements[a21] *= sy;
    }
  }
  return *this;
}

template <class T>
inline Matrix3<T>&
Matrix3<T>::PreScale(T sx, T sy)
{
  if (_flag == IDENTITY) {
    if (sx != 1.0f || sy != 1.0f) {
      _elements[a00] = sx;
      _elements[a11] = sy;
      _flag = 0;
    }
  } else {
    if (sx != 1.0f) {
      _elements[a00] *= sx;
      _elements[a01] *= sx;
      _elements[a02] *= sx;
    }
    if (sy != 1.0f) {
      _elements[a10] *= sy;
      _elements[a11] *= sy;
      _elements[a12] *= sy;
    }
  }
  return *this;
}

template <class T>
inline Matrix3<T>&
Matrix3<T>::Scale(T scale)
{
  if (scale != 1.0f) {
    if (_flag == IDENTITY) {
      _elements[a00] = scale;
      _elements[a11] = scale;
      _flag = 0;
    } else {
      _elements[a00] *= scale;
      _elements[a01] *= scale;
      _elements[a10] *= scale;
      _elements[a11] *= scale;
      _elements[a20] *= scale;
      _elements[a21] *= scale;
    }
  }
  return *this;
}

template <class T>
inline Matrix3<T>&
Matrix3<T>::PreScale(T scale)
{
  if (scale != 1.0f) {
    if (_flag == IDENTITY) {
      _elements[a00] = scale;
      _elements[a11] = scale;
      _flag = 0;
    } else {
      _elements[a00] *= scale;
      _elements[a01] *= scale;
      _elements[a02] *= scale;
      _elements[a10] *= scale;
      _elements[a11] *= scale;
      _elements[a12] *= scale;
    }
  }
  return *this;
}

// equality
template <class T>
inline Obool
Matrix3<T>::Equal(const Matrix3<T>& X, const T tolerance) const
{
  return ( ((_flag == X._flag) && _flag) ||
    fabs(_elements[a00] - X._elements[a00]) < tolerance &&
    fabs(_elements[a01] - X._elements[a01]) < tolerance &&
    fabs(_elements[a02] - X._elements[a02]) < tolerance &&
    fabs(_elements[a10] - X._elements[a10]) < tolerance &&
    fabs(_elements[a11] - X._elements[a11]) < tolerance &&
    fabs(_elements[a12] - X._elements[a12]) < tolerance &&
    fabs(_elements[a20] - X._elements[a20]) < tolerance &&
    fabs(_elements[a21] - X._elements[a21]) < tolerance &&
    fabs(_elements[a22] - X._elements[a22]) < tolerance);
}

template <class T>
inline Matrix3<T>&
Matrix3<T>::operator*=(const Matrix3<T>& mat)
{
  if (_flag || mat._flag) {
    if ( _flag == IDENTITY && mat._flag != IDENTITY)
      return (*this = mat);
    else
      return *this;
  }

  T tmp[3];
  //first row
  tmp[0] = _elements[a00] * mat._elements[a00] +
           _elements[a01] * mat._elements[a10] +
           _elements[a02] * mat._elements[a20];
  tmp[1] = _elements[a00] * mat._elements[a01] +
           _elements[a01] * mat._elements[a11] +
           _elements[a02] * mat._elements[a21];
  _elements[a02] = _elements[a00] * mat._elements[a02] +
           _elements[a01] * mat._elements[a12] +
           _elements[a02] * mat._elements[a22];
  _elements[a00] = tmp[0];
  _elements[a01] = tmp[1];

    //second row
  tmp[0] = _elements[a10] * mat._elements[a00] +
           _elements[a11] * mat._elements[a10] +
           _elements[a12] * mat._elements[a20];
  tmp[1] = _elements[a10] * mat._elements[a01] +
           _elements[a11] * mat._elements[a11] +
           _elements[a12] * mat._elements[a21];
  _elements[a12] = _elements[a10] * mat._elements[a02] +
           _elements[a11] * mat._elements[a12] +
           _elements[a12] * mat._elements[a22];
  _elements[a10] = tmp[0];
  _elements[a11] = tmp[1];

    //third row
  tmp[0] = _elements[a20] * mat._elements[a00] +
           _elements[a21] * mat._elements[a10] +
           _elements[a22] * mat._elements[a20];
  tmp[1] = _elements[a20] * mat._elements[a01] +
           _elements[a21] * mat._elements[a11] +
           _elements[a22] * mat._elements[a21];
  _elements[a22] = _elements[a20] * mat._elements[a02] +
           _elements[a21] * mat._elements[a12] +
           _elements[a22] * mat._elements[a22];
  _elements[a20] = tmp[0];
  _elements[a21] = tmp[1];

  return *this;
}

template <class T>
inline Matrix3<T>&
Matrix3<T>::PreMultiply(const Matrix3<T>& mat)
{
  if (_flag || mat._flag) {
    if ( _flag == IDENTITY && mat._flag != IDENTITY)
      return (*this = mat);
    else
      return *this;
  }

  T tmp[2];
  //first column
  tmp[0] = mat._elements[a00] * _elements[a00] +
    mat._elements[a01] * _elements[a10] +
    mat._elements[a02] * _elements[a20];
  tmp[1] = mat._elements[a10] * _elements[a00] +
    mat._elements[a11] * _elements[a10] +
    mat._elements[a12] * _elements[a20];
  _elements[a20] = mat._elements[a20] * _elements[a00] +
    mat._elements[a21] * _elements[a10] +
    mat._elements[a22] * _elements[a20];
  _elements[a00] = tmp[0];
  _elements[a10] = tmp[1];

  //second column
  tmp[0] = mat._elements[a00] * _elements[a01] +
    mat._elements[a01] * _elements[a11] +
    mat._elements[a02] * _elements[a21];
  tmp[1] = mat._elements[a10] * _elements[a01] +
    mat._elements[a11] * _elements[a11] +
    mat._elements[a12] * _elements[a21];
  _elements[a21] = mat._elements[a20] * _elements[a01] +
    mat._elements[a21] * _elements[a11] +
    mat._elements[a22] * _elements[a21];
  _elements[a01] = tmp[0];
  _elements[a11] = tmp[1];

  //third column
  tmp[0] = mat._elements[a00] * _elements[a02] +
    mat._elements[a01] * _elements[a12] +
    mat._elements[a02] * _elements[a22];
  tmp[1] = mat._elements[a10] * _elements[a02] +
    mat._elements[a11] * _elements[a12] +
    mat._elements[a12] * _elements[a22];
  _elements[a22] = mat._elements[a20] * _elements[a02] +
    mat._elements[a21] * _elements[a12] +
    mat._elements[a22] * _elements[a22];
  _elements[a02] = tmp[0];
  _elements[a12] = tmp[1];

  return *this;
}

template <class T>
inline Matrix3<T>&
Matrix3<T>::operator*=(T value)
{
  if (value != 1.0f) {
    if (_flag == IDENTITY) {
      _flag = 0;
      _elements[a00] *= value;
      _elements[a11] *= value;
      _elements[a22] *= value;
    } else {
      _elements[a00] *= value;
      _elements[a01] *= value;
      _elements[a02] *= value;
      _elements[a10] *= value;
      _elements[a11] *= value;
      _elements[a12] *= value;
      _elements[a20] *= value;
      _elements[a21] *= value;
      _elements[a22] *= value;
    }
    return *this;
  }
}

//template <class T>
//inline Matrix3<T>
//operator*(const Matrix3<T>& matrix1, T value)
//{
//  Matrix3<T> result(matrix1);
//  result *= value;
//  return result;
//}

template <class T>
inline Matrix3<T>&
Matrix3<T>::operator/=(T value)
{
  T value_1 = 1.0f/value;
  if (_flag == IDENTITY) {
    _flag = 0;
    _elements[a00] *= value_1;
    _elements[a11] *= value_1;
    _elements[a22] *= value_1;
    return *this;
  }
  _elements[a00] *= value_1;
  _elements[a01] *= value_1;
  _elements[a02] *= value_1;
  _elements[a10] *= value_1;
  _elements[a11] *= value_1;
  _elements[a12] *= value_1;
  _elements[a20] *= value_1;
  _elements[a21] *= value_1;
  _elements[a22] *= value_1;

  return *this;
}

//template <class T>
//inline Matrix3<T>
//operator/(const Matrix3<T>& matrix1, T value)
//{
//  Matrix3<T> result(matrix1);
//  result /= value;
//  return result;
//}

template <class T>
inline Matrix3<T>&
Matrix3<T>::operator+=(const Matrix3<T>& matrix)
{
  _flag = 0;
  _elements[a00] += matrix._elements[a00];
  _elements[a01] += matrix._elements[a01];
  _elements[a02] += matrix._elements[a02];
  _elements[a10] += matrix._elements[a10];
  _elements[a11] += matrix._elements[a11];
  _elements[a12] += matrix._elements[a12];
  _elements[a20] += matrix._elements[a20];
  _elements[a21] += matrix._elements[a21];
  _elements[a22] += matrix._elements[a22];
  return *this;
}

//template <class T>
//inline Matrix3<T>
//operator+(const Matrix3<T>& matrix1, const Matrix3<T>& matrix2)
//{
//  Matrix4<T> result(matrix1);
//  result += matrix2;
//  return result;
//}

template <class T>
inline Matrix3<T>&
Matrix3<T>::operator-=(const Matrix3<T>& matrix)
{
  _flag = 0;
  _elements[a00] -= matrix._elements[a00];
  _elements[a01] -= matrix._elements[a01];
  _elements[a02] -= matrix._elements[a02];
  _elements[a10] -= matrix._elements[a10];
  _elements[a11] -= matrix._elements[a11];
  _elements[a12] -= matrix._elements[a12];
  _elements[a20] -= matrix._elements[a20];
  _elements[a21] -= matrix._elements[a21];
  _elements[a22] -= matrix._elements[a22];

  return *this;
}

//template <class T>
//inline Matrix3<T>
//operator-(const Matrix3<T>& matrix1, const Matrix3<T>& matrix2)
//{
//  Matrix3<T> result(matrix1);
//  result -= matrix2;
//  return result;
//}

template <class T>
inline Matrix3<T>&
Matrix3<T>::Transpose()
{
  if (_flag) {
    return *this;
  }

  T tmp;
  for (Oint t1 = 0; t1 < 3; t1++)
    for (Oint t2 = 0; t2 < t1; t2++) {
      tmp = _elements[t1*3 + t2];
      _elements[t1*3 + t2] = _elements[t2*3 + t1];
      _elements[t2*3 + t1] = tmp;
    };

  return *this;
}

template <class T>
inline Matrix3<T>&
Matrix3<T>::Invert()
{
  if (_flag) {
    return *this;
  }
  T cofactor[9];
  cofactor[0] = (_elements[a11]*_elements[a22] - _elements[a12]*_elements[a21]);
  cofactor[1] = -(_elements[a10]*_elements[a22] - _elements[a12]*_elements[a20]);
  cofactor[2] = (_elements[a10]*_elements[a21] - _elements[a11]*_elements[a20]);

  T det = _elements[a00] * cofactor[0] +
          _elements[a01] * cofactor[1] +
          _elements[a02] * cofactor[2];

  if (det != 0.0f) {
    T det_1 = 1/det;

    cofactor[3] = -(_elements[a01]*_elements[a22] - _elements[a02]*_elements[a21]);
    cofactor[4] =  (_elements[a00]*_elements[a22] - _elements[a02]*_elements[a20]);
    cofactor[5] = -(_elements[a00]*_elements[a21] - _elements[a01]*_elements[a20]);
    cofactor[6] =  (_elements[a01]*_elements[a12] - _elements[a02]*_elements[a11]);
    cofactor[7] = -(_elements[a00]*_elements[a12] - _elements[a02]*_elements[a10]);
    cofactor[8] =  (_elements[a00]*_elements[a11] - _elements[a01]*_elements[a10]);

    _elements[a00] = cofactor[0]*det_1;
    _elements[a10] = cofactor[1]*det_1;
    _elements[a20] = cofactor[2]*det_1;
    _elements[a01] = cofactor[3]*det_1;
    _elements[a11] = cofactor[4]*det_1;
    _elements[a21] = cofactor[5]*det_1;
    _elements[a02] = cofactor[6]*det_1;
    _elements[a12] = cofactor[7]*det_1;
    _elements[a22] = cofactor[8]*det_1;
    return *this;
  } else {
    //DIAG(DEBUG_MESSAGE, "Warning: singular matrix");
    _flag = UNDEFINED;
    return *this = Matrix3<T>::identity;
  }
}

template <class T>
inline T
Matrix3<T>::Determinant() const
{
  if (_flag == IDENTITY)
    return 1;

  return (_elements[a00] * (_elements[a11]*_elements[a22] - _elements[a12]*_elements[a21]) -
          _elements[a01] * (_elements[a10]*_elements[a22] - _elements[a12]*_elements[a20]) +
          _elements[a02] * (_elements[a10]*_elements[a21] - _elements[a11]*_elements[a20]));
}

template <class T>
Obool
Matrix3<T>::Decompose3D(Vec3<T>& scale, Rotation4<T>& rotation) const
{
  Oint i,j;
  Matrix3<T> locmat;
  Vec3<T> row[3];

  //normalize
  for (i=0; i < 3; i++)
    for (j=0; j < 3 ; j++)
      locmat.Set(i,j,Get(i,j));

  //get scale & shear
  for (i=0; i < 3; i++) {
    row[i][X] = locmat.Get(i,0);
    row[i][Y] = locmat.Get(i,1);
    row[i][Z] = locmat.Get(i,2);
  }

  //compute x scale & normalize first row
  scale[X] = row[0].Length();
  row[0] /= scale[X];

  //compute xy shear and make 2nd row ortogonal to first
  T shearxy = row[0]*row[1];
  row[1] = row[1]-row[0]*shearxy;

  //compute y scale and normalize 2nd row
  scale[Y] = row[1].Length();
  row[1] /= scale[Y];
  shearxy /= scale[Y];

  //compute xz and yz shear, ortogonalize 3rd row
  T shearxz = row[0]*row[2];
  row[2] = row[2] - row[0]*shearxz;
  T shearyz = row[1]*row[2];
  row[2] = row[2] - row[1]*shearyz;

  //get z scale and noramlize 3rd row
  scale[Z] = row[2].Length();
  row[2] /= scale[Z];
  shearxz /= scale[Z];
  shearyz /= scale[Z];

  if ((row[0]*(row[1].Cross(row[2]))) < 0) {
    scale *= -1.0f;
    for (i= 0; i < 3; i++) {
      row[i] *= -1.0;
    }
  }
  T w=T(0.5)*sqrt(row[0][0]+row[1][1]+row[2][2]+T(1.0));

  Obool specialCase = false;
  Quaternion<T> q;
  if (w == 0.0f) {
    specialCase = true;
    if (row[0][0] >= 0.0f) {
      q = Quaternion<T>(1.0f, 0.0f, 0.0f, PI);
      row[1] *= -1.0f;
      row[2] *= -1.0f;
    } else if (row[1][1] >= 0.0f) {
      q = Quaternion<T>(0.0f, 1.0f, 0.0f, PI);
      row[0] *= -1.0f;
      row[2] *= -1.0f;
    } else if (row[2][2] >= 0.0f) {
      q = Quaternion<T>(0.0f, 0.0f, 1.0f, PI);
      row[0] *= -1.0f;
      row[1] *= -1.0f;
    }
  }

  w=T(0.5)*sqrt(row[0][0]+row[1][1]+row[2][2]+T(1.0));
  T s=0.25f/w;
  Quaternion<T> q2;
  q2._vec[0] = (row[1][2]-row[2][1])*s;
  q2._vec[1] = (row[2][0]-row[0][2])*s;
  q2._vec[2] = (row[0][1]-row[1][0])*s;
  q2._vec[3] = w;

  if (specialCase)
    q2 = q2*q;

  rotation = Rotation4<T>(q2);

  return true;
}

template <class T>
Obool
Matrix3<T>::Decompose2D(Vec2<T>& translation, Vec2<T>& scale, T& rotation) const
{
  Ouint i,j;
  Matrix3<T> locmat;
  Matrix3<T> pmat, invpmat, tinvpmat;
  T prhs[3];
  T perspective[3];
  Vec2<T> row[2];

  locmat = *this;

  //normalize
  if (locmat.Get(2,2) == 0)
    return false;
  for (i=0; i < 3; i++)
    for (j=0; j < 3 ; j++)
      locmat.Set(i,j,locmat.Get(i,j)/locmat.Get(2,2));

  pmat = locmat;
  for (i=0; i < 2; i++)
    pmat.Set(i,2, 0.0f);
  pmat.Set(2,2,1.0f);

  if (pmat.Determinant() == 0.0f)
    return false;

  //// First, isolate perspective. This is the messiest.
  if (locmat.Get(0,2) != 0 || locmat.Get(1,2) != 0) {
    //CoreDebug::Out("perspective not implemented");
    // prhs is the right hand side of the equation.
    prhs[0] = locmat.Get(0,2);
    prhs[1] = locmat.Get(1,2);
    prhs[2] = locmat.Get(2,2);
    // Solve the equation by inverting pmat and multiplying
    // prhs by the inverse. (This is the easiest way, not
    // necessarily the best.)
    invpmat = pmat;
    invpmat.Invert();
    tinvpmat = invpmat;
    tinvpmat.Transpose();
    //get the perspective vector
    tinvpmat.MultVec3ByMatrix(prhs, perspective);
    // Clear the perspective partition.
    locmat.Set(0,2, 0.0);
    locmat.Set(1,2, 0.0);
    locmat.Set(2,2, 0.0);
  } else {
    //Message::Out("Perspective: 0, 0, 0");
  }
  //get translation
  translation = Vec2<T>(locmat.Get(2,0), locmat.Get(2,1));
  for (i=0; i < 2; i++) {
    locmat.Set(2,i, 0.0f);
  }

  //get scale & shear
  for (i=0; i < 2; i++) {
    row[i][X] = locmat.Get(i,0);
    row[i][Y] = locmat.Get(i,1);
  }

  //compute x scale & normalize first row
  scale[X] = row[0].Length();
  row[0] /= scale[X];

  //compute xy shear and make 2nd row ortogonal to first
  T shearxy = row[0]*row[1];
  row[1] = row[1]-row[0]*shearxy;

  //compute y scale and normalize 2nd row
  scale[Y] = row[1].Length();
  row[1] /= scale[Y];
  shearxy /= scale[Y];

  //compute xz and yz shear, ortogonalize 3rd row
  //T shearxz = row[0]*row[2];
  //row[2] = row[2] - row[0]*shearxz;
  //T shearyz = row[1]*row[2];
  //row[2] = row[2] - row[1]*shearyz;

  //get z scale and noramlize 3rd row
  //scale[Z] = row[2].Length();
  //row[2] /= scale[Z];
  //shearxz /= scale[Z];
  //shearyz /= scale[Z];

  //check for left hand
  //if ((row[0]*(row[1].Cross(row[2]))) < 0) {
  //  scale *= -1.0f;
  //  for (i= 0; i < 3; i++) {
  //    row[i] *= -1.0;
  //  }
  //}

  //here we should have:
  //  row[0] = {cos(r), -sin(r))
  //  row[1] = {sin(r),  cos(r))
  rotation = acos(row[0][0]);
  if (row[1][0] < 0)
    rotation = 2*PI-rotation;

  return true;
}

template <class T>
inline void
Matrix3<T>::MultVec3ByMatrix(T vector[3], T result[3]) const
{
  result[0] = vector[0] * _elements[a00] +
    vector[1] * _elements[a10] +
    vector[2] * _elements[a20];

  result[1] = vector[0] * _elements[a01] +
    vector[1] * _elements[a11] +
    vector[2] * _elements[a21];

  result[2] = vector[0] * _elements[a02] +
    vector[1] * _elements[a12] +
    vector[2] * _elements[a22];
}

} // namespace enterprise_manager

