namespace enterprise_manager {

template<class T>
NUQuaternion<T>::NUQuaternion()
: w(0), x(0), y(0), z(0)
{
}

template<class T>
NUQuaternion<T>::NUQuaternion(const NUQuaternion<T>& q)
: w(q.w), x(q.x), y(q.y), z(q.z)
{
}

template<class T>
NUQuaternion<T>::NUQuaternion(T re)
: w(re), x(0), y(0), z(0)
{
}

// Create a 'pure' quaternion
template<class T>
NUQuaternion<T>::NUQuaternion(const Vec3<T>& im)
: w(0), x(im[X]), y(im[Y]), z(im[Z])
{
}

template<class T>
NUQuaternion<T>::NUQuaternion(T re, const Vec3<T>& im)
: w(re), x(im[X]), y(im[Y]), z(im[Z])
{
}

template<class T>
NUQuaternion<T>::NUQuaternion(T _w, T _x, T _y, T _z)
: w(_w), x(_x), y(_y), z(_z)
{
}

template<class T>
NUQuaternion<T>::NUQuaternion(const Rotation4<T>& rot)
: w(), x(), y(), z()
{
  T l = rot[X]*rot[X]+rot[Y]*rot[Y]+rot[Z]*rot[Z];
  T s = ::sin(rot[R] * static_cast<T>(0.5));
  T c = ::cos(rot[R] * static_cast<T>(0.5));

  s /= l;
  x = s * rot[X];
  y = s * rot[Y];
  z = s * rot[Z];
  w = c;
}

// Create a quaternion from a rotation matrix
template<class T> NUQuaternion<T>::NUQuaternion(const Matrix3<T>& m)
{
  T trace = m[0][0] + m[1][1] + m[2][2];
  T root;

  if (trace > 0)
  {
    root = static_cast<T>(sqrt(trace + 1));
    w = static_cast<T>(0.5) * root;
    root = static_cast<T>(0.5) / root;
    x = (m[2][1] - m[1][2]) * root;
    y = (m[0][2] - m[2][0]) * root;
    z = (m[1][0] - m[0][1]) * root;
  }
  else
  {
    int i = 0;
    if (m[1][1] > m[i][i])
      i = 1;
    if (m[2][2] > m[i][i])
      i = 2;
    int j = (i == 2) ? 0 : i + 1;
    int k = (j == 2) ? 0 : j + 1;

    root = static_cast<T>(sqrt(m[i][i] - m[j][j] - m[k][k] + 1));
    T* xyz[3] = { &x, &y, &z };
    *xyz[i] = static_cast<T>(0.5) * root;
    root = static_cast<T>(0.5) / root;
    w = (m[k][j] - m[j][k]) * root;
    *xyz[j] = (m[j][i] + m[i][j]) * root;
    *xyz[k] = (m[k][i] + m[i][k]) * root;
  }
}

template<class T>
NUQuaternion<T>&
NUQuaternion<T>::operator+=(const NUQuaternion<T>& a)
{
  x += a.x; y += a.y; z += a.z; w += a.w;
  return *this;
}

template<class T>
NUQuaternion<T>&
NUQuaternion<T>::operator-=(const NUQuaternion<T>& a)
{
  x -= a.x; y -= a.y; z -= a.z; w -= a.w;
  return *this;
}

template<class T>
NUQuaternion<T>&
NUQuaternion<T>::operator*=(const NUQuaternion<T>& q)
{
  *this = NUQuaternion<T>(w * q.w - x * q.x - y * q.y - z * q.z,
    w * q.x + x * q.w + y * q.z - z * q.y,
    w * q.y + y * q.w + z * q.x - x * q.z,
    w * q.z + z * q.w + x * q.y - y * q.x);

  return *this;
}

template<class T>
NUQuaternion<T>&
NUQuaternion<T>::operator*=(T s)
{
  x *= s; y *= s; z *= s; w *= s;
  return *this;
}

template<class T>
NUQuaternion<T>&
NUQuaternion<T>::operator/=(T s)
{
  T d = 1/s;
  x *= d; y *= d; z *= d; w *= d;
  return *this;
}

template<class T>
NUQuaternion<T>&
NUQuaternion<T>::operator/=(const NUQuaternion<T>& b)
{
  retun (*this *= (~b / Abs(b)));
}

// conjugate operator
template<class T>
NUQuaternion<T>
NUQuaternion<T>::operator~() const
{
  return NUQuaternion<T>(w, -x, -y, -z);
}

template<class T>
NUQuaternion<T>
NUQuaternion<T>::operator-() const
{
  return NUQuaternion<T>(-w, -x, -y, -z);
}

template<class T> NUQuaternion<T>
NUQuaternion<T>::operator+() const
{
  return *this;
}

// NUQuaternion methods

template<class T> bool
NUQuaternion<T>::IsReal() const
{
  return (x == 0 && y == 0 && z == 0);
}

template<class T> bool
NUQuaternion<T>::IsPure() const
{
  return w == 0;
}

template<class T> T
NUQuaternion<T>::Normalize()
{
  T s = static_cast<T>(::sqrt(w * w + x * x + y * y + z * z));
  T invs =  1 / s;
  x *= invs;
  y *= invs;
  z *= invs;
  w *= invs;

  return s;
}

// Set to the unit quaternion representing an axis angle rotation.  Assume
// that axis is a unit vector
template<class T> void
NUQuaternion<T>::SetAxisAngle(const Vec3<T>& axis, T angle)
{
  T s = ::sin(angle * static_cast<T>(0.5));
  T c = ::cos(angle * static_cast<T>(0.5));

  x = s * axis[X];
  y = s * axis[Y];
  z = s * axis[Z];
  w = c;
}

// Assuming that this a unit quaternion, return the in axis/angle form the
// orientation which it represents.
template<class T> void
NUQuaternion<T>::GetAxisAngle(Vec3<T>& axis, T& angle) const
{
  // The quaternion has the form:
  // w = cos(angle/2), (x y z) = sin(angle/2)*axis

  T magSquared = x * x + y * y + z * z;
  if (magSquared > static_cast<T>(1e-10))
  {
    T s = 1 / static_cast<T>(::sqrt(magSquared));
    axis[X] = x * s;
    axis[Y] = y * s;
    axis[Z] = z * s;
    if (w <= -1 || w >= 1)
      angle = 0;
    else
      angle = static_cast<T>(acos(w)) * 2;
  }
  else
  {
    // The angle is zero, so we pick an arbitrary unit axis
    axis[X] = 1;
    axis[Y] = 0;
    axis[Z] = 0;
    angle = 0;
  }
}

// Assuming that this is a unit quaternion representing an orientation,
// apply a rotation of angle radians about the specfied axis
template<class T> void
NUQuaternion<T>::Rotate(const Vec3<T>& axis, T angle)
{
  NUQuaternion q;
  q.SetAxisAngle(axis, angle);
  *this = q * *this;
}

// Assuming that this is a unit quaternion representing an orientation,
// apply a rotation of angle radians about the x-axis
template<class T> void
NUQuaternion<T>::Xrotate(T angle)
{
  T s, c;

  s = ::sin(angle * static_cast<T>(0.5));
  c = ::cos(angle * static_cast<T>(0.5));

  *this = NUQuaternion<T>(c, s, 0, 0) * *this;
}

// Assuming that this is a unit quaternion representing an orientation,
// apply a rotation of angle radians about the y-axis
template<class T> void
NUQuaternion<T>::Yrotate(T angle)
{
  T s, c;

  s = ::sin(angle * static_cast<T>(0.5));
  c = ::cos(angle * static_cast<T>(0.5));

  *this = NUQuaternion<T>(c, 0, s, 0) * *this;
}

// Assuming that this is a unit quaternion representing an orientation,
// apply a rotation of angle radians about the z-axis
template<class T> void
NUQuaternion<T>::Zrotate(T angle)
{
  T s, c;

  s = ::sin(angle * static_cast<T>(0.5));
  c = ::cos(angle * static_cast<T>(0.5));

  *this = NUQuaternion<T>(c, 0, 0, s) * *this;
}

template<class T> NUQuaternion<T>
operator+(const NUQuaternion<T>& a, const NUQuaternion<T>& b)
{
  return NUQuaternion<T>(a.w + b.w, a.x + b.x, a.y + b.y, a.z + b.z);
}

template<class T> NUQuaternion<T>
operator-(const NUQuaternion<T>& a, const NUQuaternion<T>& b)
{
  return NUQuaternion<T>(a.w - b.w, a.x - b.x, a.y - b.y, a.z - b.z);
}

template<class T> NUQuaternion<T>
operator*(const NUQuaternion<T>& a, const NUQuaternion<T>& b)
{
  return NUQuaternion<T>(a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z,
    a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y,
    a.w * b.y + a.y * b.w + a.z * b.x - a.x * b.z,
    a.w * b.z + a.z * b.w + a.x * b.y - a.y * b.x);
}

template<class T> NUQuaternion<T>
operator*(T s, const NUQuaternion<T>& q)
{
  return NUQuaternion<T>(s * q.w, s * q.x, s * q.y, s * q.z);
}

template<class T> NUQuaternion<T>
operator*(const NUQuaternion<T>& q, T s)
{
  return NUQuaternion<T>(s * q.w, s * q.x, s * q.y, s * q.z);
}

//// equivalent to multiplying by the quaternion (0, v)
//template<class T> NUQuaternion<T>
//operator*(const Vec3<T>& v, const NUQuaternion<T>& q)
//{
//  return NUQuaternion<T>(-v[X] * q.x - v[Y] * q.y - v[Z] * q.z,
//    v[X] * q.w + v[Y] * q.z - v[Z] * q.y,
//    v[Y] * q.w + v[Z] * q.x - v[X] * q.z,
//    v[Z] * q.w + v[X] * q.y - v[Y] * q.x);
//}

template<class T> NUQuaternion<T>
operator/(NUQuaternion<T> q, T s)
{
  return q * (1 / s);
}

template<class T> NUQuaternion<T>
operator/(NUQuaternion<T> a, NUQuaternion<T> b)
{
  return a * (~b / Abs(b));
}

template<class T> bool
operator==(const NUQuaternion<T>& a, const NUQuaternion<T>& b)
{
  return a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w;
}

template<class T> bool
operator!=(const NUQuaternion<T>& a, const NUQuaternion<T>& b)
{
  return a.x != b.x || a.y != b.y || a.z != b.z || a.w != b.w;
}

// elementary functions
template<class T> NUQuaternion<T>
Conjugate(const NUQuaternion<T>& q)
{
  return NUQuaternion<T>(q.w, -q.x, -q.y, -q.z);
}

template<class T> NUQuaternion<T>
Inverse(const NUQuaternion<T>& q)
{
  return NUQuaternion<T>(-q.w, -q.x, -q.y, -q.z);
}

template<class T> T
Norm(const NUQuaternion<T>& q)
{
  return q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w;
}

template<class T> T
Abs(const NUQuaternion<T>& q)
{
  return static_cast<T>(::sqrt(Norm(q)));
}

template<class T> NUQuaternion<T>
Exp(const NUQuaternion<T>& q)
{
  if (q.IsReal())
  {
    return NUQuaternion<T>(static_cast<T>(::exp(q.w)));
  }
  else
  {
    T l = static_cast<T>(::sqrt(q.x * q.x + q.y * q.y + q.z * q.z));
    T s = static_cast<T>(::sin(l));
    T c = static_cast<T>(::cos(l));
    T e = static_cast<T>(::exp(q.w));
    T t = e * s / l;
    return NUQuaternion<T>(e * c, t * q.x, t * q.y, t * q.z);
  }
}

template<class T> NUQuaternion<T>
Log(const NUQuaternion<T>& q)
{
  if (q.IsReal())
  {
    if (q.w > 0)
    {
      return NUQuaternion<T>(static_cast<T>(::log(q.w)));
    }
    else if (q.w < 0)
    {
      // The log of a negative purely real quaternion has
      // infinitely many values, all of the form (ln(-w), PI * I),
      // where I is any unit vector.  We arbitrarily choose an I
      // of (1, 0, 0) here and whereever else a similar choice is
      // necessary.  Geometrically, the set of roots is a sphere
      // of radius PI centered at ln(-w) on the real axis.
      return NUQuaternion<T>(static_cast<T>(::log(-q.w)), static_cast<T>(PI), 0, 0);
    }
    else
    {
      // error . . . ln(0) not defined
      return NUQuaternion<T>(0);
    }
  }
  else
  {
    T l = static_cast<T>(::sqrt(q.x * q.x + q.y * q.y + q.z * q.z));
    T r = static_cast<T>(::sqrt(l * l + q.w * q.w));
    T theta = static_cast<T>(::atan2(l, q.w));
    T t = theta / l;
    return NUQuaternion<T>(static_cast<T>(::log(r)), t * q.x, t * q.y, t * q.z);
  }
}

template<class T> NUQuaternion<T>
Pow(const NUQuaternion<T>& q, T s)
{
  return Exp(s * Log(q));
}

template<class T> NUQuaternion<T>
Pow(const NUQuaternion<T>& q, const NUQuaternion<T>& p)
{
  return Exp(p * Log(q));
}

template<class T> NUQuaternion<T>
Sin(const NUQuaternion<T>& q)
{
  if (q.isReal())
  {
    return NUQuaternion<T>(static_cast<T>(sin(q.w)));
  }
  else
  {
    T l = static_cast<T>(sqrt(q.x * q.x + q.y * q.y + q.z * q.z));
    T m = q.w;
    T s = static_cast<T>(sin(m));
    T c = static_cast<T>(cos(m));
    T il = 1 / l;
    T e0 = static_cast<T>(exp(-l));
    T e1 = static_cast<T>(exp(l));

    T c0 = static_cast<T>(-0.5) * e0 * il * c;
    T c1 = static_cast<T>(0.5) * e1 * il * c;

    return NUQuaternion<T>(static_cast<T>(0.5) * e0 * s, c0 * q.x, c0 * q.y, c0 * q.z) +
      NUQuaternion<T>(static_cast<T>(0.5) * e1 * s, c1 * q.x, c1 * q.y, c1 * q.z);
  }
}

template<class T> NUQuaternion<T>
Cos(const NUQuaternion<T>& q)
{
  if (q.isReal())
  {
    return NUQuaternion<T>(static_cast<T>(cos(q.w)));
  }
  else
  {
    T l = static_cast<T>(sqrt(q.x * q.x + q.y * q.y + q.z * q.z));
    T m = q.w;
    T s = static_cast<T>(sin(m));
    T c = static_cast<T>(cos(m));
    T il = 1 / l;
    T e0 = static_cast<T>(exp(-l));
    T e1 = static_cast<T>(exp(l));

    T c0 = static_cast<T>(0.5) * e0 * il * s;
    T c1 = static_cast<T>(-0.5) * e1 * il * s;

    return NUQuaternion<T>(static_cast<T>(0.5) * e0 * c, c0 * q.x, c0 * q.y, c0 * q.z) +
      NUQuaternion<T>(static_cast<T>(0.5) * e1 * c, c1 * q.x, c1 * q.y, c1 * q.z);
  }
}

template<class T> NUQuaternion<T>
Sqrt(const NUQuaternion<T>& q)
{
  // In general, the square root of a quaternion has two values, one
  // of which is the negative of the other.  However, any negative purely
  // real quaternion has an infinite number of square roots.
  // This function returns the positive root for positive reals and
  // the root on the positive i axis for negative reals.
  if (q.isReal())
  {
    if (q.w >= 0)
      return NUQuaternion<T>(static_cast<T>(sqrt(q.w), 0, 0, 0));
    else
      return NUQuaternion<T>(0, static_cast<T>(sqrt(-q.w), 0, 0));
  }
  else
  {
    T b = static_cast<T>(sqrt(q.x * q.x + q.y * q.y + q.z * q.z));
    T r = static_cast<T>(sqrt(q.w * q.w + b * b));
    if (q.w >= 0)
    {
      T m = static_cast<T>(sqrt(static_cast<T>(0.5) * (r + q.w)));
      T l = b / (2 * m);
      T t = l / b;
      return NUQuaternion<T>(m, q.x * t, q.y * t, q.z * t);
    }
    else
    {
      T l = static_cast<T>(sqrt(static_cast<T>(0.5) * (r - q.w)));
      T m = b / (2 * l);
      T t = l / b;
      return NUQuaternion<T>(m, q.x * t, q.y * t, q.z * t);
    }
  }
}

template<class T> T
Real(const NUQuaternion<T>& q)
{
  return q.w;
}

template<class T> Vec3<T>
Imag(const NUQuaternion<T>& q)
{
  return Vec3<T>(q.x, q.y, q.z);
}
template<class T> T
Dot(const NUQuaternion<T> a, const NUQuaternion<T> b)
{
  return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

template<class T> NUQuaternion<T>
Slerp(const NUQuaternion<T>& q0, const NUQuaternion<T>& q1, T t)
{
  T c = Dot(q0, q1);

  // Because of potential rounding errors, we must clamp c to the domain of acos.
  if (c > static_cast<T>(1.0))
    c = static_cast<T>(1.0);
  else if (c < static_cast<T>(-1.0))
    c = static_cast<T>(-1.0);

  T angle = static_cast<T>(acos(c));

  if (static_cast<T>(::fabs(angle)) < static_cast<T>(1.0e-5))
    return q0;

  T s = static_cast<T>(::sin(angle));
  T is = 1 / s;

  return q0 * (static_cast<T>(::sin((1 - t)) * angle) * is) +
    q1 * (static_cast<T>(::sin(t * angle)) * is);
}

template<class T> NUQuaternion<T>
Xrotation(T angle)
{
  T s, c;

  s = ::sin(angle * static_cast<T>(0.5));
  c = ::cos(angle * static_cast<T>(0.5));

  return NUQuaternion<T>(c, s, 0, 0);
}

template<class T> NUQuaternion<T>
Yrotation(T angle)
{
  T s, c;

  s = ::sin(angle * static_cast<T>(0.5));
  c = ::cos(angle * static_cast<T>(0.5));

  return NUQuaternion<T>(c, 0, s, 0);
}

template<class T> NUQuaternion<T>
Zrotation(T angle)
{
  T s, c;

  s = ::sin(angle * static_cast<T>(0.5));
  c = ::cos(angle * static_cast<T>(0.5));

  return NUQuaternion<T>(c, 0, 0, s);
}

} // namespace enterprise_manager

