namespace enterprise_manager {

template <class T>
inline
Rotation4<T>::Rotation4()
{
  _vec[0] = 0.0f;
  _vec[1] = 0.0f;
  _vec[2] = 1.0f;
  _vec[3] = 0.0f;
}

template <class T>
inline
Rotation4<T>::Rotation4(const Rotation4<T>& X)
{
  _vec[0] = X._vec[0];
  _vec[1] = X._vec[1];
  _vec[2] = X._vec[2];
  _vec[3] = X._vec[3];
}

template <class T>
inline
Rotation4<T>::Rotation4(T x, T y, T z, T r)
{
  _vec[0] = x;
  _vec[1] = y;
  _vec[2] = z;
  _vec[3] = r;
}

template <class T>
inline
Rotation4<T>::Rotation4(const Vec3<T>& vec, T r)
{
  _vec[0] = vec[X];
  _vec[1] = vec[Y];
  _vec[2] = vec[Z];
  _vec[3] = r;
}

template <class T>
inline
Rotation4<T>::Rotation4(const Vec3<T>& vec1, const Vec3<T>& vec2)
{
  Vec3<T> axis = vec1.Cross(vec2);
  T length = axis.Length();
  if (length > 0) {
    axis /= length;
    _vec[3] = vec1.CosAngle(vec2);
    if (_vec[3] > 1.0f)
      _vec[3] = 1.0f;
    if (_vec[3] < -1.0f)
      _vec[3] = -1.0f;
    _vec[3] = acosf(_vec[3]);
  } else { //vec1 and vec2 are paralell
    if (vec1*vec2 >= 0.0f) { //same direction (no rotation)
      _vec[3] = 0.0f;
      axis = Vec3<T>(0.0f, 1.0f, 0.0f);
    } else { //opposite dir (
      _vec[3] = PI;
      axis = vec1.Cross(Vec3<T>(1.0f, 0.0f, 0.0f)); //use x axis)
      length = axis.Length();
      if (length > 0.0f)
        axis /= length;
      else
        axis = Vec3<T>(0.0f, 1.0f, 0.0f);
    }
  }
  _vec[0] = axis[X];
  _vec[1] = axis[Y];
  _vec[2] = axis[Z];
}

template <class T>
inline
Rotation4<T>::Rotation4(const Quaternion<T>& q)
{
#ifdef O_PLATFORM_WINDOWS
  if (abs(q._vec[R]) >= 1.0f) {
#else
  if (fabs(q._vec[R]) >= 1.0f) {
#endif
    _vec[0] = 1;
    _vec[1] = 0;
    _vec[2] = 0;
    _vec[3] = 0;
  } else {
    _vec[3] = acos(q._vec[R])*2.0f;
  //if (_vec[3] == 0.0f) {
  //  _vec[0] = 1;
  //  _vec[1] = 0;
  //  _vec[2] = 0;
  //} else {
    T tmp = 1/sin(_vec[3]/2.0f);
    _vec[0] = q._vec[X]*tmp;
    _vec[1] = q._vec[Y]*tmp;
    _vec[2] = q._vec[Z]*tmp;
  }
}

template <class T>
inline
Rotation4<T>::Rotation4(const NUQuaternion<T>& q)
{
  if (fabsf(q.w) >= 1.0f) {
    _vec[0] = 1;
    _vec[1] = 0;
    _vec[2] = 0;
    _vec[3] = 0;
  } else {
    _vec[3] = acosf(q.w)*2.0f;
  //}
  //if (_vec[3] == 0.0f) {
  //  _vec[0] = 1;
  //  _vec[1] = 0;
  //  _vec[2] = 0;
  //} else {
    T tmp = 1/sinf(_vec[3]/2.0f);
    _vec[0] = q.x*tmp;
    _vec[1] = q.y*tmp;
    _vec[2] = q.z*tmp;
  }
}

template <class T>
inline Rotation4<T>&
Rotation4<T>::operator=(const Rotation4<T>& X)
{
  _vec[0] = X._vec[0];
  _vec[1] = X._vec[1];
  _vec[2] = X._vec[2];
  _vec[3] = X._vec[3];
  return *this;
}

template <class T>
inline Obool
Rotation4<T>::operator!=(const Rotation4<T>& rot) const
{
  return (_vec[0] != rot._vec[0] ||
          _vec[1] != rot._vec[1] ||
          _vec[2] != rot._vec[2] ||
          _vec[3] != rot._vec[3]);
}

template <class T>
inline Obool
Rotation4<T>::operator==(const Rotation4<T>& rot) const
{
  return (_vec[0] == rot._vec[0] &&
          _vec[1] == rot._vec[1] &&
          _vec[2] == rot._vec[2] &&
          _vec[3] == rot._vec[3]);
}

template <class T>
inline Rotation4<T>
Rotation4<T>::operator-() const
{
  return Rotation4<T>(_vec[0],_vec[1],_vec[2],-_vec[3]);
}

template <class T>
inline T
Rotation4<T>::operator[](Oint component) const
{
  return _vec[component];
}

template <class T>
inline T&
Rotation4<T>::operator[](const Oint component)
{
  return _vec[component];
}

template <class T>
inline void
Rotation4<T>::SetFromVectors(const Vec3f& startVector, const Vec3f& endVector)
{
  // The angle is, eh, the angle between the vectors
  Ofloat angle = acos(startVector.CosAngle(endVector));
  Vec3f axis;

  if (fabs(angle) < 0.001) {
    // Vectors are parallel so any axis is OK.
    _vec[0] = 1.0f;
    _vec[1] = 0.0f;
    _vec[2] = 0.0f;
    _vec[3] = 0.0f;
    return;
  }

  if (fabs(angle) > (PI - 0.0001))
  {
    // Vectors are opposing each other, cross product won't work
    axis = Vec3f(1.0f, 0.0f, 0.0f);

    if (axis * startVector > 0.1f)
    {
      axis = Vec3f(0.0f, 0.0f, 1.0f);
    }

    axis = axis.Cross(startVector);
    axis.Normalize();
  }
  else {
    // Rotation axis is the cross product of the vectors
    axis = startVector.Cross(endVector);
    axis.Normalize();
  }

  _vec[0] = axis[0];
  _vec[1] = axis[1];
  _vec[2] = axis[2];
  _vec[3] = angle;
}

template <class T>
inline const T*
Rotation4<T>::Ptr() const
{
  return _vec;
}
} // namespace enterprise_manager

