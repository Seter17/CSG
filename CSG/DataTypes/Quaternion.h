#ifndef ENTERPRISE_MANAGER_QUATERNION_H
#define ENTERPRISE_MANAGER_QUATERNION_H

#include <math.h>

namespace enterprise_manager {

template <class T> class Vec3;
template <class T> class Rotation4;
template <class T> class Matrix3;
template <class T> class Matrix4;

/** The Quaternion class implements a unit quaternion.
  It assumes that all operations on the quaternion is done by unit quaternions
  i.e a rotation about an axis.
  @ingroup dataTypes
*/
template<class T> class Quaternion
{
  friend class Vec3<T>;
  friend class Matrix3<T>;
  friend class Matrix4<T>;
  friend class Rotation4<T>;

public :
  /** Default constructor creating a quaternion with no rotation
  */
  inline                Quaternion<T>();

  /** A constructor creating a quaternion from a specified rotation.
    @param rot a Rotation value
  */
  inline explicit       Quaternion<T>(const Rotation4<T>& rot);

  /** Generate a unit quaternion from a vector and a rotation about
    the vector given in radians.
    @param axis the Vec3f to rotate around
    @param radians the angle (in radians) to rotate around the specified vector
  */
  inline                Quaternion<T>(const Vec3<T>& axis, const T radians);

  /** Generate a unit quaternion from a three Ts representing a vector
    and a rotation about the vector given in radians.
    @param x the x component of the vector to rotate around
    @param y the y component of the vector to rotate around
    @param z the z component of the vector to rotate around
    @param radians the angle (in radians) to rotate around the specified vector
  */
  inline                Quaternion<T>(const T x, const T y, const T z, const T radians);

  inline                Quaternion<T>(const T rx, const T ry, const T rz);

  /** This is a constructor creating a new Quaternion object from an existing one.
    @param quaternion a reference to an existing Quaternion object
  */
  inline                Quaternion<T>(const Quaternion<T>& quaternion);

 /** Assignment operator setting this quaternion equal to another specified quaternion
    @param q the quaternion from which to get the values
    @return a reference to the vector after the assignment
  */
  inline Quaternion<T>& operator=(const Quaternion<T>& q);

  inline Obool          IsNullRotation() const;
  inline void           SetRaw(const T& sx, const T& sy, const T& sz, const T& c);

  inline void           GetRaw(T& sx, T& sy, T& sz, T& c) const;

  /** Negate the value of the rotation
    @return the negated rotation
  */
  inline Quaternion<T>  operator-() const;

  /** Multiplication operator. The result is a rotation quaternion where the
    right hand side is preconcatenated with this quaternion.
    @param quat the quaternion to multiply by this quaternion
    @return a reference to this quaternion after the multiplication
  */
  inline Quaternion<T>& operator*=(const Quaternion<T>& quat);

  /** Multiply two quaternions and return the resulting quaternion
    @param    quaternion1 a reference to a Quaternion<T> object
    @param    quaternion2 a reference to a second Quaternion<T> object
    @return   the quaternion resulting from the operation quaternion1 * quaternion2
  */
  friend Quaternion<T>  operator*(const Quaternion<T>& quaternion1, const Quaternion<T>& quaternion2)
  {
    Quaternion<T> result(quaternion1);
    return (result*=quaternion2);
  }

  /** Invert the quaternion
    @return   reference to this quaternion after it has been inverted.
  */
  inline Quaternion<T>& Invert();

  inline void           Normalize();

  /** Spherical interpolation between this and q with
    q given the weight fraction[0, 1] and this given the weight 1-fraction.
    @param q the second quaternion
    @param fraction a T signifying the weight of q
    @return a refernce to this quaternion after the interpolation;
  */
  inline Quaternion<T>  Slerp(const Quaternion<T>& q, const T fraction);

  /** Spherical interpolation between q1 and q2 with
    q2 given the weight fraction[0, 1] and q1 given the weight 1-fraction.
    @param q1 the first quaternion
    @param q2 the second quaternion
    @param fraction a T signifying the weight of the second quaternion
    @return a quaternion containing the interpolated value;
  */
  friend Quaternion<T>  Slerp(const Quaternion<T>& q1, const Quaternion<T>& q2, const T fraction)
  {
    Quaternion<T> result(q1);
    return result.Slerp(q2,fraction);
  }

  inline void           EulerAngles(Ofloat& rx, Ofloat& ry, Ofloat& rz);

private :
  //array of elements
  T                     _vec[4];
};

typedef Quaternion<Ofloat> Quaternionf;

} // namespace enterprise_manager

#include "Quaternion.inl"

#endif // ENTERPRISE_MANAGER_QUATERNION_H
