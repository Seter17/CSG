#ifndef ENTERPRISE_MANAGER_VEC2_H
#define ENTERPRISE_MANAGER_VEC2_H

#include <math.h>

namespace enterprise_manager {

template <class T> class Matrix3;
template <class T> class Vec3;
template <class T> class Vec4;

/** The Vec2f class implements a row vector with 2 elements (x,y) for describing
vectors and points in 2D.
  @ingroup dataTypes
*/
template <class T> class Vec2
{
  /** Matrix 3 is a friend of Vec2 */
  friend class Matrix3<T>;
  friend class Vec3<T>;
  friend class Vec4<T>;

public:

  /** Default constructor which creates a new zero vector.
  */
  inline                Vec2<T>();

  /** Constructor which specifies the x and y values of a new vector
    @param x the new x value
    @param y the new y value
  */
  inline                Vec2<T>(T x,T y);

/** Copy constructor which creates a copy of an existing vector
    @param vector a reference to the vector to copy
  */
  inline                Vec2<T>(const Vec2<T>& vector);

  /** Destructor.
  */
  inline                ~Vec2<T>();

    /** Multiplication operator which multiplies the vector by a 3x3 transformation matrix.
   @param matrix the matrix to multiply by
   @return a reference to this vector after the multiplication
  */
  Vec2<T>&              operator*=(const Matrix3<T>& matrix);

  /** Multiplication operator which multiplies a vector by a 3x3 transformation matrix.
   @param vector the vector to multiply
   @param matrix the matrix to multiply by
   @return a vector containing the result of the multiplication
  */
  friend Vec2<T>        operator*(const Vec2<T>& vector, const Matrix3<T>& matrix)
  {
    Vec2<T> result(vector);
    return (result*=matrix);
  }

  /** Calculate the dot product of the vector and a second vector.
    @param vector the second vector to use for the calculation
    @return a Ofloat containing the result
  */
  inline T              operator*(const Vec2<T>& vector) const;

  /** Multiply all elements of the vector by a Ofloat
    @param value the Ofloat to multiply by
    @return a reference to this vector after the multiplication
  */
  inline Vec2<T>&       operator*=(const T& value);

  /** Multiply all elements of a vector by a Ofloat
    @param vector the vector to multiply
    @param value the Ofloat to multiply by
    @return a vector containing the result of the multiplication
  */
  friend Vec2<T>        operator*(const Vec2<T>& vector, const T& value)
  {
    Vec2<T> result(vector);
    return (result*=value);
  }

  /** Multiply all elements of a vector by a Ofloat
    @param value the Ofloat to multiply by
    @param vector the vector to multiply
    @return a vector containing the result of the multiplication
  */
  friend Vec2<T>        operator*(const T& value, const Vec2<T>& vector)
  {
    Vec2<T> result(vector);
    return (result*=value);
  }

  /** Divide all elements of the vector by the corresponding values in a second vector.
    @param vector the vector to divide by
    @return a reference to this vector after the division
  */
  inline Vec2<T>&       operator/=(const Vec2<T>& vector);

  /** Divide all elements of a vector by the corresponding values in a second vector.
    @param vector1 the vector to be divided
    @param vector2 the vector to divide by
    @return a vector containing the result of the division
  */
  friend Vec2<T>        operator/(const Vec2<T>& vector1, const Vec2<T>& vector2)
  {
    Vec2<T> result(vector1);
    return (result/=vector2);
  }

  /** Divide all elements of the vector by a Ofloat
    @param value the Ofloat to divide by
    @return a reference to this vector after the division
  */
  inline Vec2<T>&       operator/=(const T& value);

  /** Divide all elements of a vector by a Ofloat
    @param vector the vector to divide
    @param value the Ofloat to divide by
    @return a vector containing the result of the division
  */
  friend Vec2<T>        operator/(const Vec2<T>& vector, T value)
  {
    Vec2<T> result(vector);
    return (result/=value);
  }

  /** Add all elements of a vector to the corresponding values in this vector.
    @param vec the vector to add to this vector
    @return a reference to this vector after the addition
  */
  inline Vec2<T>&       operator+=(const Vec2<T>& vec);

  /** Add all elements of a vector to the corresponding values in a second vector.
    @param vector1 the first vectors
    @param vector2 the second vector
    @return a vector containing the result of the addition
  */
  friend Vec2<T>        operator+(const Vec2<T>& vector1, const Vec2<T>& vector2)
  {
    Vec2<T> result(vector1);
    return (result+=vector2);
  }

  /** Negate the value of the vector
    @return the negated vector
  */
  inline Vec2<T>         operator-() const;

  /** Subtract all elements of a vector from the corresponding values in this vector.
    @param vec the vector to subtract from this vector
    @return a reference to this vector after the subtraction
  */
  inline Vec2<T>&       operator-=(const Vec2<T>& vec);

 /** Subtract all elements of a vector from the corresponding values in a second vector.
    @param vector1 the first vector
    @param vector2 the vector to subtract from the first vector
    @return a vector containing the result of the subtraction
  */
  friend Vec2<T>        operator-(const Vec2<T>& vector1, const Vec2<T>& vector2)
  {
    Vec2<T> result(vector1);
    return (result-=vector2);
  }

  /** Equality operator comparing this Vec2f with another specified Vec2f
    @param vec a reference to the vector to compare with
    @return true if the vectors are equal, false otherwise
  */
  inline Obool           operator==(const Vec2<T>& vec) const;

  /** Equality operator comparing every element in this vector with a specified value
    @param value a Ofloat to compare the alements with
    @return true if all elements are equal to value, false otherwise
  */
  inline Obool           operator==(const T& value) const;

  /** Method comparing this vector with another specified Vec2f. The method allows
    numerical errors by allowing each element to be within a given tolerance from the
    corresponding element of the specified vector.
    (that is: |this.element - vector.element| < tolerance)
    @param vec the vector to compare this vector with
    @param tolerance the tolerance which is used for comparison
    @return true if equal, false otherwise
  */
  inline Obool           Equal(const Vec2<T>& vec, const T& tolerance = TOLERANCE) const;

  /** Method comparing every element in this vector with a specified value. The method allows
    numerical errors by allowing each element to be within a given tolerance from the
    specified value. (that is: |element - value| < tolerance)
    @param value a Ofloat to compare the alements with
    @param tolerance the tolerance which is used for comparison
    @return true if equal, false otherwise
  */
  inline Obool           Equal(const T& value, const T& tolerance = TOLERANCE) const;

  /** Inequality operator comparing this Vec2f with another specified Vec2f
    @param vec a reference to the vector to compare with
    @return true if the vectors are inequal, false otherwise
  */
  inline Obool           operator!=(const Vec2<T>& vec) const;

  /** Inequality operator comparing every element in this vector with a specified value
    @param value a Ofloat to compare the elements with
    @return false if all elements are equal to value, true otherwise
  */
  inline Obool           operator!=(const T& value) const;

 /** Assignment operator setting this vector equal to another specified vector
    @param vec the vector from which to get the values
    @return a refernce to the vector after the assignment
  */
  inline Vec2<T>&       operator=(const Vec2<T>& vec);

  /** Subscript operator for returning the i'th element of a vector.
    @param i an Oint designating which element to retrieve (X=0, Y=1)
    @return a Ofloat reference to the i'th element of the vector
  */
  inline T&             operator[](const Oint i);

  /** Subscript operator for returning the i'th element of a const vector.
    @param i an Oint designating which element to retrieve (X=0, Y=1, Z=2)
    @return a Ofloat reference to the i'th element of the vector
  */
  inline T              operator[](const Oint i) const;

  /** Calculates the length of the vector
    @return a Ofloat containing the length of the vector
  */
  inline T              Length() const;

  /** Calculates the squared length of the vector
    @return a Ofloat containing the squared length of the vector
  */
  inline T              LengthSqr() const;

  /** Normalizes the vector by dividing it by its own length. The resulting vector
    has the same orientation, but always is of unit length.
    @return this vector after being normalized;
  */
  inline Vec2<T>&       Normalize();

  /** Calculates the distance between this vector and a second specified vector
    @param vector a refernce to a specified vector
    @return a Ofloat containing the distance between the vectors
  */
  inline T              Distance(const Vec2<T>& vector) const;

  /** Calculates the squared distance between this vector and a second specified vector
    @param vector a refernce to a specified vector
    @return a Ofloat containing the squared distance between the vectors
  */
  inline T              DistanceSqr(const Vec2<T>& vector) const;

  /** Calculates cosine of the angle between this vector and another specified vector
    @param vector a reference to a specified vector
    @return a Ofloat containing the cosine of the angle
  */
  inline T              CosAngle(const Vec2<T>& vector) const;

  /** Calculates the 'cross' product of this vector and another specified vector
    @param vector a reference to a specified vector
    @return a Ofloat giving the magnitude of the resulting vector
  */
  inline T              Cross(const Vec2<T>& vector) const;

  /** Calculates the componentvise product of this vector and another specified vector
    @param vector a reference to a specified vector
    @return a vector containing the result of the cross product
  */
  inline Vec2<T>        MultiplyComp(const Vec2<T>& vector) const;

  inline void           MaxComp(const Vec2<T>& vector);
  inline void           MinComp(const Vec2<T>& vector);

  /** This method return a const pointer to the internal array. This is useful
    when an continous array of two values are required
    @return a pointer to the internal array
  */
  inline const T*       Ptr() const;

private:
  //array of elements
  T                     _vec[2];
};

typedef Vec2<Ofloat> Vec2f;
typedef Vec2<Odouble> Vec2d;

} // namespace enterprise_manager

#include "Vec2.inl"

#endif // ENTERPRISE_MANAGER_VEC2_H
