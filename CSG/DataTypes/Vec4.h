#ifndef ENTERPRISE_MANAGER_VEC4_H
#define ENTERPRISE_MANAGER_VEC4_H

#include <math.h>
#include <assert.h>

namespace enterprise_manager {

template <class T> class Vec2;
template <class T> class Vec3;
template <class T> class Matrix4;
template <class T> class Quaternion;

/** The Vec4<T> class implements a row vector with 3 elements (x,y,z) for describing
vectors and points in 3D. It is implemented to work optimal with the Matrix4f class
*/
template <class T> class Vec4
{
  /** Matrix 4 is a friend of Vec4 */
  friend class Matrix4<T>;

public:

  /** Default constructor which creates a new zero vector.
  */
  inline                Vec4<T>();

  /** Constructor which specifies the four elements of the vector
    @param v0 the value of the first element
    @param v1 the value of the second element
    @param v2 the value of the third element
    @param v3 the value of the fourth element
  */
  inline                Vec4<T>(const T& v0, const T& v1, const T& v2, const T& v3);

  /** Copy constructor which creates a copy of an existing vector
    @param  vector a reference to the vector to copy
  */
  inline                Vec4<T>(const Vec4<T>& vector);

  /** Copy constructor which creates a copy of an existing vec2 and two other elements
    @param  vector a reference to the vector to copy
  */
  inline                Vec4<T>(const Vec2<T>& vector, const T& v3, const T& v4);

  /** Copy constructor which creates a copy of two existing vec2
    @param  vector a reference to the vector to copy
  */
  inline                Vec4<T>(const Vec2<T>& vector1, const Vec2<T>& vector2);

  /** Copy constructor which creates a copy of an existing vec3 and one other elements
    @param  vector a reference to the vector to copy
  */
  inline                Vec4<T>(const Vec3<T>& vector, const T& v0);

  /** The destructor.
  */
  inline                ~Vec4<T>();

  /** Multiplication operator which multiplies the vector by a 4x4 transformation matrix.
   @param matrix the matrix to multiply by
   @return a reference to this vector after the multiplication
  */
  Vec4<T>&              operator*=(const Matrix4<T>& matrix);

  /** Multiplication operator which multiplies a vector by a 4x4 transformation matrix.
   @param vector the vector to multiply
   @param matrix the matrix to multiply by
   @return a vector containing the result of the multiplication
  */
  friend Vec4<T>        operator*(const Vec4<T>& vector, const Matrix4<T>& matrix)
  {
    Vec4<T> result(vector);
    return (result*=matrix);
  }

  /** Calculate the dot product of the vector and a second vector.
    @param vector the second vector to use for the calculation
    @return a T containing the result
  */
  inline T              operator*(const Vec4<T>& vector) const;

  /** Multiply all elements of the vector by a T
    @param value the T to multiply by
    @return a reference to this vector after the multiplication
  */
  inline Vec4<T>&       operator*=(const T& value);

  /** Multiply all elements of a vector by a T
    @param vector the vector to multiply
    @param value the T to multiply by
    @return a vector containing the result of the multiplication
  */
  friend Vec4<T>        operator*(const Vec4<T>& vector, const T& value)
  {
    Vec4<T> result(vector);
    return (result*=value);
  }

  /** Multiply all elements of a vector by a T
    @param vector the vector to multiply
    @param value the T to multiply by
    @return a vector containing the result of the multiplication
  */
  friend Vec4<T>        operator*(const T& value, const Vec4<T>& vector)
  {
    Vec4<T> result(vector);
    return (result*=value);
  }

  /** Divide all elements of the vector by the corresponding values in a second vector.
    @param vector the vector to divide by
    @return a reference to this vector after the division
  */
  inline Vec4<T>&       operator/=(const Vec4<T>& vector);

  /** Divide all elements of a vector by the corresponding values in a second vector.
    @param vector1 the vector to be divided
    @param vector2 the vector to divide by
    @return a vector containing the result of the division
  */
  friend Vec4<T>        operator/(const Vec4<T>& vector1, const Vec4<T>& vector2)
  {
    Vec4<T> result(vector1);
    return (result/=vector2);
  }

  /** Divide all elements of the vector by a T
    @param value the T to divide by
    @return a reference to this vector after the division
  */
  inline Vec4<T>&       operator/=(const T& value);

  /** Divide all elements of a vector by a T
    @param vector the vector to divide
    @param value the T to divide by
    @return a vector containing the result of the division
  */
  friend Vec4<T>        operator/(const Vec4<T>& vector, const T& value)
  {
    Vec4<T> result(vector);
    return (result/=value);
  }

  /** Add all elements of a vector to the corresponding values in this vector.
    @param vec the vector to add to this vector
    @return a reference to this vector after the addition
  */
  inline Vec4<T>&       operator+=(const Vec4<T>& vec);

  /** Add all elements of a vector to the corresponding values in a second vector.
    @param vector1 the first vectors
    @param vector2 the second vector
    @return a vector containing the result of the addition
  */
  friend Vec4<T>        operator+(const Vec4<T>& vector1, const Vec4<T>& vector2)
  {
    Vec4<T> result(vector1);
    return (result+=vector2);
  }

  /** Negate the value of the vector
    @return the negated vector
  */
  inline Vec4<T>         operator-() const;

  /** Subtract all elements of a vector from the corresponding values in this vector.
    @param vec the vector to subtract from this vector
    @return a reference to this vector after the subtraction
  */
  inline Vec4<T>&       operator-=(const Vec4<T>& vec);

 /** Subtract all elements of a vector from the corresponding values in a second vector.
    @param vector1 the first vector
    @param vector2 the vector to subtract from the first vector
    @return a vector containing the result of the subtraction
  */
  friend Vec4<T>        operator-(const Vec4<T>& vector1, const Vec4<T>& vector2)
  {
    Vec4<T> result(vector1);
    return (result-=vector2);
  }

  /** Equality operator comparing this Vec4<T> with another specified Vec4<T>
    @param vec a reference to the vector to compare with
    @return true if the vectors are equal, false otherwise
  */
  inline Obool           operator==(const Vec4<T>& vec) const;

  /** Equality operator comparing every element in this vector with a specified value
    @param value a T to compare the alements with
    @return true if all elements are equal to value, false otherwise
  */
  inline Obool           operator==(const T& value) const;

  /** Method comparing this vector with another specified Vec4<T>. The method allows
  numerical errors by allowing each element to be within a given tolerance from the
  corresponding element of the specified vector.
  (that is: |this.element - vector.element| < tolerance)
    @param vec the vector to compare this vector with
    @param tolerance the tolerance which is used for comparison
    @return true if equal, false otherwise
  */
  inline Obool           Equal(const Vec4<T>& vec, const T& tolerance = TOLERANCE) const;

  /** Method comparing every element in this vector with a specified value. The method allows
  numerical errors by allowing each element to be within a given tolerance from the
  specified value. (that is: |element - value| < tolerance)
    @param value a T to compare the alements with
    @param tolerance the tolerance which is used for comparison
    @return true if equal, false otherwise
  */
  inline Obool           Equal(const T& value, const T& tolerance = TOLERANCE) const;

  /** Inequality operator comparing this Vec4<T> with another specified Vec4<T>
    @param vec a reference to the vector to compare with
    @return true if the vectors are inequal, false otherwise
  */
  inline Obool           operator!=(const Vec4<T>& vec) const;

/** Inequality operator comparing every element in this vector with a specified value
    @param value a T to compare the elements with
    @return false if all elements are equal to value, true otherwise
  */
  inline Obool           operator!=(const T& value) const;

 /** Assignment operator setting this vector equal to another specified vector
    @param vec the vector from which to get the values
    @return a refernce to the vector after the assignment
  */
  inline Vec4<T>&       operator=(const Vec4<T>& vec);

  /** Subscript operator for returning the i'th element of a vector.
    @param i an Oint designating which element to retrieve (X=0, Y=1, Z=2)
    @return a T reference to the i'th element of the vector
  */
  inline T&             operator[](const Oint i);

  /** Subscript operator for returning the i'th element of a const vector.
    @param i an Oint designating which element to retrieve (X=0, Y=1, Z=2)
    @return a T reference to the i'th element of the vector
  */
  inline T              operator[](const Oint i) const;

  /** Calculates the length of the vector
    @return a T containing the length of the vector
  */
  inline T              Length() const;

  /** Calculates the squared length of the vector
    @return a T containing the squared length of the vector
  */
  inline T              LengthSqr() const;

  /** Normalizes the vector by dividing it by its own length. The resulting vector
  has the same orientation, but always is of unit length.
    @return this vector after being normalized;
  */
  inline Vec4<T>&       Normalize();

  /** Calculates the distance between this vector and a second specified vector
    @param vector a refernce to a specified vector
    @return a T containing the distance between the vectors
  */
  inline T              Distance(const Vec4<T> &vector) const;

  /** Calculates the squared distance between this vector and a second specified vector
    @param vector a refernce to a specified vector
    @return a T containing the squared distance between the vectors
  */
  inline T              DistanceSqr(const Vec4<T> &vector) const;

  /** Calculates cosine of the angle between this vector and another specified vector
    @param vector a reference to a specified vector
    @return a T containing the cosine of the angle
  */
  inline T              CosAngle(const Vec4<T>& vector) const;

  /** Calculates the cross product of this vector and another specified vector
    @param vector a reference to a specified vector
    @return a vector containing the result of the cross product
  */
  inline Vec4<T>        Cross(const Vec4<T>& vector) const;

  /** Calculates the componentvise product of this vector and another specified vector
    @param vector a reference to a specified vector
    @return a vector containing the result of the cross product
  */
  inline Vec4<T>        MultiplyComp(const Vec4<T>& vector) const;

  /** This method return a const pointer to the internal array. This is useful
    when an continous array of two values are required
    @return a pointer to the internal array
  */
  inline const T*       Ptr() const;

private:
  //array of elements
  T                     _vec[4];
};

typedef Vec4<Ofloat> Vec4f;
typedef Vec4<Odouble> Vec4d;

} // namespace enterprise_manager

#include "Vec4.inl"

#endif // ENTERPRISE_MANAGER_VEC4_H
