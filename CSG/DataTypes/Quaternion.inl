namespace enterprise_manager {

template <class T>
inline
Quaternion<T>::Quaternion()
{
  _vec[0] = 0.0f;
  _vec[1] = 0.0f;
  _vec[2] = 0.0f;
  _vec[3] = 1.0f;
}

template <class T>
inline
Quaternion<T>::Quaternion(const T x, const T y, const T z, const T radians)
{
  Vec3<T> norm(x,y,z);
  norm.Normalize();
  T stmp = T(::sin(0.5f * radians));
  T ctmp = T(::cos(0.5f * radians));

  _vec[0] = stmp * norm[X];
  _vec[1] = stmp * norm[Y];
  _vec[2] = stmp * norm[Z];
  _vec[3] = ctmp ;
}

template <class T>
inline
Quaternion<T>::Quaternion(const T rx, const T ry, const T rz)
{
  Ofloat c1 = ::cos(ry*0.5f);
  Ofloat s1 = ::sin(ry*0.5f);
  Ofloat c2 = ::cos(rx*0.5f);
  Ofloat s2 = ::sin(rx*0.5f);
  Ofloat c3 = ::cos(rz*0.5f);
  Ofloat s3 = ::sin(rz*0.5f);
  Ofloat c1c2 = c1*c2;
  Ofloat s1s2 = s1*s2;
  _vec[R] =c1c2*c3 - s1s2*s3;
  _vec[X] =c1c2*s3 + s1s2*c3;
  _vec[Y] =s1*c2*c3 + c1*s2*s3;
  _vec[Z] =c1*s2*c3 - s1*c2*s3;
}

template <class T>
inline
Quaternion<T>::Quaternion(const Vec3<T>& axis, const T radians)
{
  Vec3<T> norm(axis);
  norm.Normalize();
  T stmp = T(::sin(0.5f * radians));
  T ctmp = T(::cos(0.5f * radians));

  _vec[0] = stmp * norm[X];
  _vec[1] = stmp * norm[Y];
  _vec[2] = stmp * norm[Z];
  _vec[3] = ctmp ;
}

template <class T>
inline
Quaternion<T>::Quaternion(const Rotation4<T>& rot)
{
  if (rot[R] == 0) {
    //optimization for common case
    _vec[0] = 0;
    _vec[1] = 0;
    _vec[2] = 0;
    _vec[3] = 1;
  } else {
    Vec3<T> norm(rot[X], rot[Y], rot[Z]);
    norm.Normalize();
    T stmp = T(::sin(0.5f * rot[R]));
    T ctmp = T(::cos(0.5f * rot[R]));

    _vec[0] = stmp * norm[X];
    _vec[1] = stmp * norm[Y];
    _vec[2] = stmp * norm[Z];
    _vec[3] = ctmp ;
  }
}

template <class T>
inline
Quaternion<T>::Quaternion(const Quaternion<T>& quaternion)
{
  _vec[0] = quaternion._vec[0];
  _vec[1] = quaternion._vec[1];
  _vec[2] = quaternion._vec[2];
  _vec[3] = quaternion._vec[3];
}

template <class T>
inline Quaternion<T>&
Quaternion<T>::operator=(const Quaternion<T>& quaternion)
{
  _vec[0] = quaternion._vec[0];
  _vec[1] = quaternion._vec[1];
  _vec[2] = quaternion._vec[2];
  _vec[3] = quaternion._vec[3];
  return *this;
}

template <class T>
inline Obool
Quaternion<T>::IsNullRotation() const
{
  return _vec[3] >= 1;
}

template <class T>
inline void
Quaternion<T>::SetRaw(const T& sx, const T& sy, const T& sz, const T& c)
{
  _vec[0] = sx;
  _vec[1] = sy;
  _vec[2] = sz;
  _vec[3] = c;
}

template <class T>
inline void
Quaternion<T>::GetRaw(T& sx, T& sy, T& sz, T& c) const
{
  sx = _vec[0];
  sy = _vec[1];
  sz = _vec[2];
  c = _vec[3];
}

template <class T>
inline Quaternion<T>&
Quaternion<T>::Invert()
{
  _vec[0] *= -1.0f;
  _vec[1] *= -1.0f;
  _vec[2] *= -1.0f;
  return *this;
}

template <class T>
inline void
Quaternion<T>::Normalize()
{
  T s = static_cast<T>(::sqrt(_vec[0] * _vec[0] + _vec[1] * _vec[1] + _vec[2] * _vec[2] + _vec[3] * _vec[3]));
  T invs =  1 / s;
  _vec[0] *= invs;
  _vec[1] *= invs;
  _vec[2] *= invs;
  _vec[3] *= invs;
}

template <class T>
inline Quaternion<T>
Quaternion<T>::operator-() const
{
  Quaternion<T> result;
  result._vec[0] = -_vec[0];
  result._vec[1] = -_vec[1];
  result._vec[2] = -_vec[2];
  result._vec[3] = _vec[3];
  return result;
}

template <class T>
inline Quaternion<T>&
Quaternion<T>::operator*=(const Quaternion<T>& quaternion)
{
  T tmp[3];
  tmp[0] = _vec[R] * quaternion._vec[X] + _vec[X] * quaternion._vec[R] + _vec[Y] * quaternion._vec[Z] - _vec[Z] * quaternion._vec[Y];
  tmp[1] = _vec[R] * quaternion._vec[Y] + _vec[Y] * quaternion._vec[R] + _vec[Z] * quaternion._vec[X] - _vec[X] * quaternion._vec[Z];
  tmp[2] = _vec[R] * quaternion._vec[Z] + _vec[Z] * quaternion._vec[R] + _vec[X] * quaternion._vec[Y] - _vec[Y] * quaternion._vec[X];
  _vec[3] = _vec[R] * quaternion._vec[R] - _vec[X] * quaternion._vec[X] - _vec[Y] * quaternion._vec[Y] - _vec[Z] * quaternion._vec[Z];
  _vec[0] = tmp[0];
  _vec[1] = tmp[1];
  _vec[2] = tmp[2];
  return *this;
}

template <class T>
inline Quaternion<T>
Quaternion<T>::Slerp(const Quaternion<T>& q, const T fraction)
{
  if (fraction == 0.0f)
    return *this;
  if (fraction == 1.0f)
    return (*this=q);

  T beta, alpha;
  T theta;
  T sin_t, cos_t;
  Obool bflip;

  cos_t = _vec[X] * q._vec[X] + _vec[Y] * q._vec[Y] +
          _vec[Z] * q._vec[Z] + _vec[R] * q._vec[R];

  if (cos_t < 0.0f) {
    cos_t = -cos_t;
    bflip = true;
  } else
    bflip = false;

  if (1.0f - cos_t < TOLERANCE) {
    beta = 1.0f - fraction;
    alpha = fraction;
  } else {
    theta = acosf(cos_t);
    sin_t = 1.0f / ::sinf(theta);
    beta = ::sinf((1.0f - fraction) * theta) * sin_t;
    alpha = ::sinf(fraction * theta) * sin_t;
  }

  if (bflip)
    alpha = -alpha;

  /* interpolate */
  _vec[X] = beta * _vec[X] + alpha * q._vec[X];
  _vec[Y] = beta * _vec[Y] + alpha * q._vec[Y];
  _vec[Z] = beta * _vec[Z] + alpha * q._vec[Z];
  _vec[R] = beta * _vec[R] + alpha * q._vec[R];

  //testing: This test is needed to make sure that the vector defining the rotation axis is not to short.
  // If the length is too short, later computations will fail, therefore we use an approximation in these cases.
//  T sum = result._vec[X] + result._vec[Y] + result._vec[Z];
//  if (-0.001 < sum && sum < 0.001) {
//    result = Quaternion<T>();
//  }

  return *this;
}

template <class T>
inline void
Quaternion<T>::EulerAngles(Ofloat& rx, Ofloat& ry, Ofloat& rz)
{
  Ofloat test = _vec[X]*_vec[Y] + _vec[Z]*_vec[R];
  if (test > 0.499) { // singularity at north pole
    ry = 2 * atan2(_vec[X],_vec[R]);
    rx = PI*0.5f;
    rz = 0;
    return;
  }
  if (test < -0.499) { // singularity at south pole
    ry = -2 * atan2(_vec[X],_vec[R]);
    rx = - PI*0.5f;
    rz = 0;
    return;
  }
  Ofloat sqx = _vec[X]*_vec[X];
  Ofloat sqy = _vec[Y]*_vec[Y];
  Ofloat sqz = _vec[Z]*_vec[Z];
  ry = atan2(2*_vec[Y]*_vec[R]-2*_vec[X]*_vec[Z] , 1 - 2*sqy - 2*sqz);
  rx = asin(2*test);
  rz = atan2(2*_vec[X]*_vec[R]-2*_vec[Y]*_vec[Z] , 1 - 2*sqx - 2*sqz);
}

} // namespace enterprise_manager

