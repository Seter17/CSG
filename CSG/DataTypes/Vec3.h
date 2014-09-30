#ifndef ENTERPRISE_MANAGER_VEC3_H
#define ENTERPRISE_MANAGER_VEC3_H

#include <math.h>
#include <assert.h>

namespace enterprise_manager {

template <class T> class Matrix4;
template <class T> class Matrix3;
template <class T> class Quaternion;
template <class T> class Vec4;
template <class T> class Vec2;

/** The Vec3<T> class implements a row vector with 3 elements (x,y,z) for describing
vectors and points in 3D. It is implemented to work optimal with the Matrix4f class
  @ingroup dataTypes
*/
template <class T> class Vec3
{
  /** Matrix 4 is a friend of Vec3 */
  friend class Matrix4<T>;
  friend class Vec4<T>;

public:

  /** Default constructor which creates a new zero vector.
  */
  inline                Vec3<T>();

  /** Constructor which specifies the x, y and z values of a new vector
    @param x the new x value
    @param y the new y value
    @param z the new z value
  */
  inline                Vec3<T>(const T& x, const T& y, const T& z);

  /** Copy constructor which creates a copy of an existing vec2 and one other elements
    @param  vector a reference to the vector to copy
  */
  inline                Vec3<T>(const Vec2<T>& vector, const T& z);

  /** Copy constructor which creates a copy of an existing vector
    @param  vector a reference to the vector to copy
  */
  inline                Vec3<T>(const Vec3<T>& vector);

  /** The destructor.
  */
  inline                ~Vec3<T>();

  /** Multiplication operator which multiplies the vector by a 4x4 transformation matrix.
   @param matrix the matrix to multiply by
   @return a reference to this vector after the multiplication
  */
  Vec3<T>&              operator*=(const Matrix4<T>& matrix);
  Vec3<T>&              operator*=(const Matrix3<T>& matrix);

  /** Multiplication operator which multiplies the vector by a 4x4 transformation matrix.
  Assumes that the last column of the matrix contains {0, 0, 0, 1}.
   @param matrix the matrix to multiply by
   @return a reference to this vector after the multiplication
  */
  inline Vec3<T>&       FastMultiply(const Matrix4<T>& matrix);

  /** Multiplication operator which multiplies the vector by a unit quaternion.
   @param q the quaternion to multiply by
   @return a reference to this vector after the multiplication
  */
  Vec3<T>&              operator*=(const Quaternion<T>& q);

  /** Multiplication operator which multiplies a vector by a 4x4 transformation matrix.
   @param vector the vector to multiply
   @param matrix the matrix to multiply by
   @return a vector containing the result of the multiplication
  */
  friend Vec3<T>        operator*(const Vec3<T>& vector, const Matrix4<T>& matrix)
  {
    Vec3<T> result(vector);
    return (result*=matrix);
  }

  friend Vec3<T>        operator*(const Vec3<T>& vector, const Matrix3<T>& matrix)
  {
    Vec3<T> result(vector);
    return (result*=matrix);
  }

  friend Vec3<T>        operator*(const Vec3<T>& vector, const Quaternion<T>& q)
  {
    Vec3<T> result(vector);
    return (result*=q);
  }

  /** Rotate the vector using a 4x4 transformation matrix. The vector will not be rotated
    @param matrix the matrix used for rotation
    @return a reference to this vector after the rotation
  */
  Vec3<T>&              Rotate(const Matrix4<T>& matrix);

  /** Calculate the dot product of the vector and a second vector.
    @param vector the second vector to use for the calculation
    @return a T containing the result
  */
  inline T              operator*(const Vec3<T>& vector) const;

  /** Multiply all elements of the vector by a T
    @param value the T to multiply by
    @return a reference to this vector after the multiplication
  */
  inline Vec3<T>&       operator*=(const T& value);

  /** Multiply all elements of a vector by a T
    @param vector the vector to multiply
    @param value the T to multiply by
    @return a vector containing the result of the multiplication
  */
  friend Vec3<T>        operator*(const Vec3<T>& vector, const T& value)
  {
    Vec3<T> result(vector);
    return (result*=value);
  }

  /** Multiply all elements of a vector by a T
    @param vector the vector to multiply
    @param value the T to multiply by
    @return a vector containing the result of the multiplication
  */
  friend Vec3<T>        operator*(const T& value, const Vec3<T>& vector)
  {
    Vec3<T> result(vector);
    return (result*=value);
  }

  /** Divide all elements of the vector by the corresponding values in a second vector.
    @param vector the vector to divide by
    @return a reference to this vector after the division
  */
  inline Vec3<T>&       operator/=(const Vec3<T>& vector);

  /** Divide all elements of a vector by the corresponding values in a second vector.
    @param vector1 the vector to be divided
    @param vector2 the vector to divide by
    @return a vector containing the result of the division
  */
  friend Vec3<T>        operator/(const Vec3<T>& vector1, const Vec3<T>& vector2)
  {
    Vec3<T> result(vector1);
    return (result/=vector2);
  }

  /** Divide all elements of the vector by a T
    @param value the T to divide by
    @return a reference to this vector after the division
  */
  inline Vec3<T>&       operator/=(const T& value);

  /** Divide all elements of a vector by a T
    @param vector the vector to divide
    @param value the T to divide by
    @return a vector containing the result of the division
  */
  friend Vec3<T>        operator/(const Vec3<T>& vector, const T& value)
  {
    Vec3<T> result(vector);
    return (result/=value);
  }

  /** Add all elements of a vector to the corresponding values in this vector.
    @param vec the vector to add to this vector
    @return a reference to this vector after the addition
  */
  inline Vec3<T>&       operator+=(const Vec3<T>& vec);

  /** Add all elements of a vector to the corresponding values in a second vector.
    @param vector1 the first vectors
    @param vector2 the second vector
    @return a vector containing the result of the addition
  */
  friend Vec3<T>        operator+(const Vec3<T>& vector1, const Vec3<T>& vector2)
  {
    Vec3<T> result(vector1);
    return (result+=vector2);
  }

  /** Negate the value of the vector
    @return the negated vector
  */
  inline Vec3<T>         operator-() const;

  /** Subtract all elements of a vector from the corresponding values in this vector.
    @param vec the vector to subtract from this vector
    @return a reference to this vector after the subtraction
  */
  inline Vec3<T>&       operator-=(const Vec3<T>& vec);

 /** Subtract all elements of a vector from the corresponding values in a second vector.
    @param vector1 the first vector
    @param vector2 the vector to subtract from the first vector
    @return a vector containing the result of the subtraction
  */
  friend Vec3<T>        operator-(const Vec3<T>& vector1, const Vec3<T>& vector2)
  {
    Vec3<T> result(vector1);
    return (result-=vector2);
  }
  /** Equality operator comparing this Vec3<T> with another specified Vec3<T>
    @param vec a reference to the vector to compare with
    @return true if the vectors are equal, false otherwise
  */
  inline Obool           operator==(const Vec3<T>& vec) const;

  /** Equality operator comparing every element in this vector with a specified value
    @param value a T to compare the alements with
    @return true if all elements are equal to value, false otherwise
  */
  inline Obool           operator==(const T& value) const;

  /** Method comparing this vector with another specified Vec3<T>. The method allows
  numerical errors by allowing each element to be within a given tolerance from the
  corresponding element of the specified vector.
  (that is: |this.element - vector.element| < tolerance)
    @param vec a  vector to compare theis vector with
    @param tolerance the tolerance which is used for comparison
    @return true if equal, false otherwise
  */
  inline Obool           Equal(const Vec3<T>& vec, const T& tolerance = TOLERANCE) const;

  /** Method comparing every element in this vector with a specified value. The method allows
  numerical errors by allowing each element to be within a given tolerance from the
  specified value. (that is: |element - value| < tolerance)
    @param value a T to compare the alements with
    @param tolerance the tolerance which is used for comparison
    @return true if equal, false otherwise
  */
  inline Obool           Equal(const T& value, const T& tolerance = TOLERANCE) const;

  /** Inequality operator comparing this Vec3<T> with another specified Vec3<T>
    @param vec a reference to the vector to compare with
    @return true if the vectors are inequal, false otherwise
  */
  inline Obool           operator!=(const Vec3<T>& vec) const;

/** Inequality operator comparing every element in this vector with a specified value
    @param value a T to compare the elements with
    @return false if all elements are equal to value, true otherwise
  */
  inline Obool           operator!=(const T& value) const;

 /** Assignment operator setting this vector equal to another specified vector
    @param vec the vector from which to get the values
    @return a refernce to the vector after the assignment
  */
  inline Vec3<T>&       operator=(const Vec3<T> & vec);

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
  inline Vec3<T>&       Normalize();

  /** Calculates the distance between this vector and a second specified vector
    @param vector a refernce to a specified vector
    @return a T containing the distance between the vectors
  */
  inline T              Distance(const Vec3<T> &vector) const;

  /** Calculates the squared distance between this vector and a second specified vector
    @param vector a refernce to a specified vector
    @return a T containing the squared distance between the vectors
  */
  inline T              DistanceSqr(const Vec3<T> &vector) const;

  /** Calculates the distance between this vector and a segment of a line 
    specified by start and end vectors (s0 and s1)
    @return a T containing the squared distance between the vectors
  */
  inline T              DistanceToSegment(Vec3<T> s0, Vec3<T> s1) const;

  /** Calculates cosine of the angle between this vector and another specified vector
    @param vector a reference to a specified vector
    @return a T containing the cosine of the angle
  */
  inline T              CosAngle(const Vec3<T>& vector) const;

  /** Calculates the angle between this vector and the specified axis.
    @param axis is the axis to compare with
    @param normalised indicates whether the vector is already normalised.
    @return a T containing the angle arcsin
  */
  inline T              AngleToAxis(Oint axis, Obool normalised = false) const;

  /** Calculates the cross product of this vector and another specified vector
    @param vector a reference to a specified vector
    @return a vector containing the result of the cross product
  */
  inline Vec3<T>        Cross(const Vec3<T>& vector) const;

  /** Calculates the componentvise product of this vector and another specified vector
    @param vector a reference to a specified vector
    @return a vector containing the result of the cross product
  */
  inline Vec3<T>        MultiplyComp(const Vec3<T>& vector) const;

  inline void           MaxComp(const Vec3<T>& vector);
  inline void           MinComp(const Vec3<T>& vector);

  /** This method return a const pointer to the internal array. This is useful
    when an continous array of two values are required
    @return a pointer to the internal array
  */
  inline const T*       Ptr() const;

  /**
    Find whether a given point is an interior point of a triangle
    @param testPoint the point to be tested
    @param u the first vertex of the triangle
    @param v the second vertex of the triangle
    @param w the third vertex of the triangle
    @param ix the x projection axis
    @param iy the y projection axis
    @param isCcw flag indicating whether the vertices are in counterclockwise order
    @param alpha is the alpha coefficient
    @param beta is the beta coefficient
    @param tolerance is the numerical tolerance for the function
  */
  static Obool          IsInteriorPoint(const Vec3<T>& testPoint, const Vec3<T>& u,const Vec3<T>& v,const Vec3<T>& w, Ochar ix, Ochar iy, Obool isCcw,Ofloat& alpha, Ofloat& beta, T tolerance = TOLERANCE);

  /**
    Find the projection axes of a plane from its normal direction.
    @param normal the normal vector
    @param ix [out] the x axis for projection
    @param iy [out] the y axis for projection
  */
  static void           FindProjectionAxes(const Vec3<T>& normal, Ochar& ix, Ochar& iy);

  /**
    Find the intersection point of a vector and a triangle
    @param normal the normal of the plane to be tested
    @param vector the vector whose intersection point is to be found
    @param refPoint is a reference point on the plane
    @param origin the local origin of the vector
    @param tolerance the tolerance used for evaluating whether the vector lies on the plane
    @param intersection is the intersection point in the plane if the vector is not parallel
    @param true if an intersection point was found, false otherwise
  */
  static Obool          FindPlane2VectorIntersection(const Vec3<T>& normal, const Vec3<T>& vector, const Vec3<T>& refPoint, const Vec3<T>& origin, Vec3<T>& intersection, T tolerance ); //= TOLERANCE);

  /**
    Find the signed distance from a given point to a plane using the Hessian Normal form of the plane.
    The sign is positive if the point is on the same side of the plane as the direction of the normal, negative if on the other side.
    @param normal is the normalised (unit vector) normal to the plane.
    @param P0 is the distance from the plane to the origin.
    @param testPoint the coordinates of the test point.
    @return the signed distance from the point to the plane.
  */
  static T              FindSignedDistanceToPlane(const Vec3<T>& normal, T P0, const Vec3<T>& testPoint);

  inline Obool          operator<(const Vec3<T>& vec) const;

#if DEBUG
	void				PrintToFileCSV(const char* fPuth, const char* id) const;
#endif

private:
  //array of elements
  T                     _vec[3];
};

typedef Vec3<Ofloat> Vec3f;
typedef Vec3<Odouble> Vec3d;

} // namespace enterprise_manager

#include "Vec3.inl"

#endif // ENTERPRISE_MANAGER_VEC3_H
