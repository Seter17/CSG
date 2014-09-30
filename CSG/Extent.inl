namespace enterprise_manager {

template <class T>
Extent<T>::Extent()
{
}

template <class T>
/* virtual */
Extent<T>::~Extent()
{
}

template <class T>
/* static */ Obool
Extent<T>::Overlap(const Extent& extentA, const Extent& extentB)
{
  const Vec3<T>& minA = extentA._min;
  const Vec3<T>& maxA = extentA._max;
  const Vec3<T>& minB = extentB._min;
  const Vec3<T>& maxB = extentB._max;
  if (Greater(minB[X], maxA[X]) || Greater(minA[X], maxB[X]))
    return false;
  if (Greater(minB[Y], maxA[Y]) || Greater(minA[Y], maxB[Y]))
    return false;
  if (Greater(minB[Z], maxA[Z]) || Greater(minA[Z], maxB[Z]))
    return false;
  return true;
}

template <class T> 
inline const Vec3<T>&   
Extent<T>::min() const
{
  return _min;
}

template <class T> 
inline void           
Extent<T>::setMin(const Vec3<T>& min)
{
  _min = min;
}

template <class T> 
inline const Vec3<T>&   
Extent<T>::max() const
{
  return _max;
}

template <class T> 
inline void           
Extent<T>::setMax(const Vec3<T>& max)
{
  _max = max;
}

} // namespace enterprise_manager
