#ifndef ENTERPRISE_MANAGER_ROTATION4_H
#define ENTERPRISE_MANAGER_ROTATION4_H

#include "DataTypes/Vec3.h"
#include "DataTypes/Quaternion.h"
#include "DataTypes/NUQuaternion.h"
#include <math.h>

namespace enterprise_manager {

/** The Rotation4<T> object specifies one arbitrary rotation. A Rotation4<T> is described by
    four ISO C floating point values. The first three values specify a normalized rotation
    axis vector about which the rotation takes place. The fourth value specifies
    the amount of right-handed rotation about that axis in radians.
  @ingroup dataTypes
*/
template <class T> class Rotation4
{
public:

  /** A constructor. Constructs a new Rotation4<T> object with the default
      values (0,0,1,0).
  */
  inline                Rotation4<T>();

  /** This constructor creates a Rotation4<T> object with the values specified.
    @param  x the x component of the normalized rotation axis vector
    @param  y the y component of the normalized rotation axis vector
    @param  z the z component of the normalized rotation axis vector
    @param  r the amount of right-handed rotation about the axis in radians
  */
  inline                Rotation4<T>(T x, T y, T z, T r);

  /** This constructor creates a Rotation4<T> object with the values specified.
    @param  vec the normalized rotation axis vector
    @param  r the amount of right-handed rotation about the axis in radians
  */
  inline                Rotation4<T>(const Vec3<T>& vec, T r);

  /** This constructor creates a Rotation4<T> object from two direction vectors.
  The resulting rotation will rotate from vec1 to vec2.
    @param  vec1 the first normalized direction vector
    @param  vec2 the second normalized direction vector
  */
  inline                Rotation4<T>(const Vec3<T>& vec1, const Vec3<T>& vec2);

  /** A copy constructor.
    @param  X a reference to an existing object
  */
  inline                Rotation4<T>(const Rotation4<T>& X);

  /** A constructor that creates a Rotation4<T> object from a Quaternion
    @param q a refernece to the quaternion
  */
  inline explicit       Rotation4<T>(const Quaternion<T>& q);

  /** A constructor that creates a Rotation4<T> object from a NUQuaternion
    NB: Must be normalized;
    @param q a refernece to the quaternion
  */
  inline explicit       Rotation4<T>(const NUQuaternion<T>& q);

  /** This assigns the value of a Rotation4<T> to be the same as another.
    @param X reference to a Rotation4<T> object
  */
  inline Rotation4<T>&  operator=(const Rotation4<T>& X);

  /** Subscript operator to retrieve any single component of the Rotation4<T>
    @param  component an Oint identifying the component to retrieve (X=0, Y=1, Z=2, R=3)
    @return a T containing the value of the component
  */
  inline T              operator[](Oint component) const;

  /** Subscript operator to retrieve any single component of the Rotation4<T>
    @param  component an Oint identifying the component to retrieve (X=0, Y=1, Z=2, R=3)
    @return a T containing the value of the component
  */
  inline T&             operator[](const Oint component);

  /** Inequality operator comparing this Rotation4<T> with another specified Rotation4<T>
    @param rot a reference to the rotation to compare with
    @return true if the rotations are inequal, false otherwise
  */
  inline Obool          operator!=(const Rotation4<T>& rot) const;

  /** Inequality operator comparing this Rotation4<T> with another specified Rotation4<T>
    @param rot a reference to the rotation to compare with
    @return true if the rotations are inequal, false otherwise
  */
  inline Obool          operator==(const Rotation4<T>& rot) const;

  /** Negate the value of the rotation
    @return the negated rotation
  */
  inline Rotation4<T>   operator-() const;

  /**
    Sets the rotation so that if the given startVector is rotated with the
    new rotation, then it will become parallel to the endVector.

    @param  startVector [in] Vector that defines starting direction
    @param  endVector [in] Vector that defines end direction
    @return Nothing
  */
  inline void           SetFromVectors(const Vec3f& startVector, const Vec3f& endVector);

  /** This method return a const pointer to the internal array. This is useful
    when an continous array of three values are required
    @return a pointer to the internal array
  */
  inline const T*       Ptr() const;

private:
  //array of elements
  T                      _vec[4];
};

typedef Rotation4<Ofloat> Rotation4f;
typedef Rotation4<Odouble> Rotation4d;

} // namespace enterprise_manager

#include "Rotation4.inl"

#endif // ENTERPRISE_MANAGER_ROTATION4_H
