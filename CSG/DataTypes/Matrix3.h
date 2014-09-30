#ifndef ENTERPRISE_MANAGER_MATRIX3_H
#define ENTERPRISE_MANAGER_MATRIX3_H

#include <math.h>
#include <assert.h>

namespace enterprise_manager {

template <class T> class Quaternion;
template <class T> class Vec2;
template <class T> class Vec3;
template <class T> class Rotation4;
template <class T> class Matrix4;

/** The Matrix3<T> class implements a 3x3 matrix for doing 2d transformations.
The matrix has the form:
|a00 a01 a02|   |r11 r21 0|
|a10 a11 a12|   |r12 r22 0|
|a20 a21 a22|   |tx  ty  1|
*/

template <class T> class Matrix3
{
  friend class Vec2<T>;
  friend class Vec3<T>;
  friend class Matrix4<T>;

public:

  /** special matrix types */
  enum SpecialMatrix{
    IDENTITY = 1,
    UNDEFINED
  };

  /** Scale matrix type  */
  enum ScaleType{
    SCALE
  };

  /** Rotate matrix type */
  enum RotateType{
    ROTATE
  };

  /** Translate matrix type */
  enum TranslateType{
    TRANSLATE
  };

  /** indexes used for code readability */
  enum IndexType {
    a00 = 0,
    a01 = 1,
    a02 = 2,
    a10 = 3,
    a11 = 4,
    a12 = 5,
    a20 = 6,
    a21 = 7,
    a22 = 8
  };

  /** Default constructor which creates a new identity matrix
  */
  inline                Matrix3<T>();

  /** Constructor which copies a 3 x 3 c++ matrix
  */
  inline explicit       Matrix3<T>(const T matrix[3][3]);

  /** Constructor which copies a c++ matrix
  */
  inline explicit       Matrix3<T>(const T matrix[9]);

  /** Contructor which creates a special matrix with no parameters.
    Currently supported matrix types are:
    IDENTITY  : the identity matrix
    UNDEFINED : a matrix where all values are undefined - should be used with caution
    @param  matrix_type the type of matrix to create.
  */
  inline explicit       Matrix3<T>(const SpecialMatrix matrix_type);

  /** Contructor which creates a uniform scale matrix.
    @param  matrix_type the type of matrix to create, must be SCALE
    @param  value the uniform scaling value
  */
  inline                Matrix3<T>(const ScaleType matrix_type, T value);

  /** Contructor which creates a non-uniform scale matrix
    @param  matrix_type the type of matrix to create, must be SCALE
    @param  x the scaling value along the x axis
    @param  y the scaling value along the y axis
  */
  inline                Matrix3<T>(const ScaleType matrix_type, T x, T y);

  /** Contructor which creates a non-uniform scale matrix
    @param  matrix_type the type of matrix to create, must be SCALE
    @param  vector a vector containing the three scaling values
  */
  inline                Matrix3<T>(const ScaleType matrix_type, const Vec2<T>& vector);

  /** Contructor which creates a rotation matrix, which rotates around the Z axis
    @param  matrix_type the type of matrix to create, must be ROTATE
    @param  radians the angle to rotate around the Z axis in radians
  */
  inline                Matrix3<T>(const RotateType matrix_type, T radians);

  /** Contructor which creates a translation matrix
    @param  matrix_type the type of matrix to create, must be TRANSLATE
    @param  x the distance to translate along the x axis
    @param  y the distance to translate along the y axis
  */
  inline                Matrix3<T>(const TranslateType matrix_type, T x, T y);

  /** Contructor which creates a translation matrix
    @param  matrix_type the type of matrix to create, must be TRANSLATE
    @param  vector the displacement vector
  */
  inline                Matrix3<T>(const TranslateType matrix_type, const Vec2<T>& vector);

  /** This is a constructor which creates a new Matrix3<T> object by copying an existing
  one.
    @param  X a reference to an existing matrix
  */
  inline                Matrix3<T>(const Matrix3<T>& X);

  /** The destructor.
  */
  inline                ~Matrix3<T>();

  /** Equality operator comparing the current Matrix3<T> object with another specified
    Matrix3<T> object.
    @param    matrix a reference to a Matrix3<T> object
    @return   true if equal, false otherwise
  */
  inline Obool          operator==(const Matrix3<T>& matrix) const;

  /** Inequality operator comparing the current Matrix3<T> object with another specified
    Matrix3<T> object.
    @param    matrix a reference to a Matrix3<T> object
    @return   true if not equal, false otherwise
  */
  inline Obool          operator!=(const Matrix3<T>& matrix) const;

  /** Method comparing this Matrix3<T> with another specified Matrix3<T>. The method allows
    numerical errors by allowing each element to be within a given tolerance from the
    corresponding element of the specified Matrix3<T>.
    (that is: |this.element - matrix.element| < tolerance)
    @param    matrix a reference to a Matrix3<T> object
    @param    tolerance the tolerance which is used for comparison
    @return   true if equal, false otherwise
  */
  inline Obool          Equal(const Matrix3<T>& matrix, const T tolerance = TOLERANCE ) const;

  /** Assignment operator which sets this matrix equal to a specified matrix.
    @param    matrix a reference to a Matrix3<T> object
    @return   a reference to this matrix after the assignment
  */
  inline Matrix3<T>&    operator=(const Matrix3<T>& matrix);

  /** Multiply this matrix by another specified matrix (this = this * matrix)
    @param    matrix a reference to a Matrix3<T> object
    @return   reference to this matrix after the multiplication
  */
  inline Matrix3<T>&    operator*=(const Matrix3<T>& matrix);

   /** Multiply this matrix by another specified matrix (this = this * matrix)
    @param    matrix a reference to a Matrix3<T> object
    @return   reference to this matrix after the multiplication
  */
  inline Matrix3<T>&    PreMultiply(const Matrix3<T>& matrix);

  /** Multiply two matrixes and return the resulting matrix
    @param    matrix1 a reference to a Matrix3<T> object
    @param    matrix2 a reference to a second Matrix3<T> object
    @return   the matrix resulting from the operation matrix1 * matrix2
  */
  friend Matrix3<T>     operator*(const Matrix3<T>& matrix1, const Matrix3<T>& matrix2)
  {
    Matrix3<T> result(matrix1);
    return (result*=matrix2);
  }

  /** Multiply this matrix by a T
    @param    value a T to multiply the matrix by
    @return   reference to this matrix after the multiplication
  */
  inline Matrix3<T>&    operator*=(T value);

  /** Multiply a matrix by a T and return the resulting matrix
    @param    matrix a reference to a Matrix3<T> object
    @param    value a T to multiply the matrix by
    @return   the matrix resulting from the operation matrix * value
  */
  friend Matrix3<T>     operator*(const Matrix3<T>& matrix, const T value)
  {
    Matrix3<T> result(matrix);
    return (result*=value);
  }

  /** Divide this matrix by a T
    @param    value a T to divide the matrix by
    @return   reference to this matrix after the division
  */
  inline Matrix3<T>&    operator/=(T value);

  /** Divide a matrix by a T and return the resulting matrix
    @param    matrix a reference to a Matrix3<T> object
    @param    value a T to divide the matrix by
    @return   the matrix resulting from the operation matrix / value
  */
  friend Matrix3<T>     operator/(const Matrix3<T>& matrix, const T value)
  {
    Matrix3<T> result(matrix);
    return (result/=value);
  }

  /** Add another specified matrix to this matrix (this = this + matrix)
    @param    matrix a reference to a Matrix3<T> object
    @return   reference to this matrix after the addition
  */
  inline Matrix3<T>&    operator+=(const Matrix3<T>& matrix);

  /** Add two matrixes and return the resulting matrix
    @param    matrix1 a reference to a Matrix3<T> object
    @param    matrix2 a reference to a second Matrix3<T> object
    @return   the matrix resulting from the operation matrix1 + matrix2
  */
  friend Matrix3<T>     operator+(const Matrix3<T>& matrix1, const Matrix3<T>& matrix2)
  {
    Matrix3<T> result(matrix1);
    return (result+=matrix2);
  }

  /** Subtract another specified matrix from this matrix (this = this - matrix)
    @param    matrix a reference to a Matrix3<T> object
    @return   reference to this matrix after the subtraction
  */
  inline Matrix3<T>&    operator-=(const Matrix3<T>& matrix);

  /** Subtract a matrix from another and return the resulting matrix
    @param    matrix1 a reference to a Matrix3<T> object
    @param    matrix2 a reference to a second Matrix3<T> object
    @return   the matrix resulting from the operation matrix1 + matrix2
  */
  friend Matrix3<T>     operator-(const Matrix3<T>& matrix1, const Matrix3<T>& matrix2)
  {
    Matrix3<T> result(matrix1);
    return (result-=matrix2);
  }

  /** Calculate the determinant of the matrix
    @return   a T conatining the determinant of this matrix
  */
  inline T              Determinant() const;

  /** Invert the matrix
    @return   reference to this matrix it has been inverted, if the original
    matrix was singular the result is marked as undefined (can be tested)
  */
  inline Matrix3<T>&    Invert();

  /** Invert the matrix
    @return   reference to this matrix it has been inverted, if the original
    matrix was singular the result is marked as undefined (can be tested)
  */
  inline Matrix3<T>     GetInverse() const;

  /** Transpose the matrix
    @return   reference to this matrix it has been transposed
  */
  inline Matrix3<T>&    Transpose();

  /** Transpose the matrix
    @return   reference to this matrix it has been transposed
  */
  inline Matrix3<T>     GetTranspose() const;

  /** Multiply this matrix by a rotation matrix defined by a
  a specified rotation around the Z axis
    @param    r the angle of rotation (in radians)
    @return   this matrix after the multiplication
  */
  inline Matrix3<T>&    Rotate(T r);

  /** PreMultiply this matrix by a rotation matrix defined by a
  a specified rotation around the Z axis
    @param    r the angle of rotation (in radians)
    @return   this matrix after the multiplication
  */
  inline Matrix3<T>&    PreRotate(T r);

  /** Multiply this matrix by a translation matrix defined by two Ts
    @param    x the x component of the translation
    @param    y the y component of the translation
    @return   this matrix after the multiplication
  */
  inline Matrix3<T>&    Translate(T x, T y);

  /** PreMultiply this matrix by a translation matrix defined by two Ts
    @param    x the x component of the translation
    @param    y the y component of the translation
    @return   this matrix after the multiplication
  */
  inline Matrix3<T>&    PreTranslate(T x, T y);

  /** Multiply this matrix by a translation matrix defined by a vector
    @param    vector a vector defining the translation
    @return   this matrix after the multiplication
  */
  inline Matrix3<T>&    Translate(const Vec2<T>& vector);

  /** PreMultiply this matrix by a translation matrix defined by a vector
    @param    vector a vector defining the translation
    @return   this matrix after the multiplication
  */
  inline Matrix3<T>&    PreTranslate(const Vec2<T>& vector);

  /** Multiply this matrix by a scaling matrix defined by two Ts
    @param    sx the scale factor along the x axis
    @param    sy the scale factor along the y axis
    @return   this matrix after the multiplication
  */
  inline Matrix3<T>&    Scale(const T sx,const T sy);

  /** PreMultiply this matrix by a scaling matrix defined by two Ts
    @param    sx the scale factor along the x axis
    @param    sy the scale factor along the y axis
    @return   this matrix after the multiplication
  */
  inline Matrix3<T>&    PreScale(const T sx,const T sy);

  /** Multiply this matrix by a scaling matrix defined by a vector
    @param    vector a vector defining the scale factors along the three principal axis
    @return   this matrix after the multiplication
  */
  inline Matrix3<T>&    Scale(const Vec2<T>& vector);

  /** PreMultiply this matrix by a scaling matrix defined by a vector
    @param    vector a vector defining the scale factors along the three principal axis
    @return   this matrix after the multiplication
  */
  inline Matrix3<T>&    PreScale(const Vec2<T>& vector);

  /** Multiply this matrix by a uniform scaling matrix
    @param    scale the uniform scaling factor
    @return   this matrix after the multiplication
  */
  inline Matrix3<T>&    Scale(const T scale);

  /** PreMultiply this matrix by a uniform scaling matrix
    @param    scale the uniform scaling factor
    @return   this matrix after the multiplication
  */
  inline Matrix3<T>&    PreScale(const T scale);

  /** Get a spesific element in the Matrix3<T>
    @param    row an Oint specifying the row from which to get the element
    @param    column an Oint specifying the column from which to get the element
    @return    a T containing the value of the specified element.
  */
  inline T              Get(Oint row, Oint column) const;

  /** Get a spesific row from the Matrix3<T>. NB: only the three first elements are
    retrieved. To get the fourth element use get(row, column)
    @param    row an Oint specifying the row from which to get the vector
    @return    a Vec3<T> containing the three first values from the specified row
  */
  inline Vec2<T>        GetRow(Oint row) const;

  /** Get a spesific column from the Matrix3<T>. NB: only the three first elements are
    retrieved. To get the fourth element use get(row, column)
    @param col an int specifying the column from which to get the vector
    @return a Vec3<T> containing the three values in the specified column
  */
  inline Vec2<T>        GetColumn(Oint col) const;

  /** Get a the translation elements of the Matrix3<T>.
    @return a Vec3<T> containing the three translation elements
  */
  inline Vec2<T>        GetTranslation() const;

  /** Set a spesific element in the Matrix3<T>
    @param row an Oint specifying the row in which to set the element
    @param column an Oint specifying the column in which to set the element
    @param value an the new value for the specified element
    @return the new value of the specified element
  */
  inline T              Set(Oint row, Oint column, T value);

  /** Set a spesific row in the Matrix3<T>. NB: the fourth element in the row will not
  be set. In order to set this element use set(row,column)
    @param row an Oint specifying the row in which to set the elements
    @param vector a vector containing the elements to put into the row
    @return a reference to the matrix after altering the row
  */
  inline Matrix3<T>&    SetRow(Oint row, const Vec2<T>& vector);

  /** Set a spesific column in the Matrix3<T>. NB: the fourth element in the column will not
  be set. In order to set this element use set(row,column)
    @param column an Oint specifying the column in which to set the elements
    @param vec a vector containing the elements to put into the column
    @return a reference to the matrix after altering the column
  */
  inline Matrix3<T>&    SetColumn(Oint column, const Vec2<T>& vec);

  /** Check if this matrix is an undefined matrix (a result of an unsuccsessful
  matrix operation)
    @return   true if matrix is undefined, false otherwise
  */
  inline Obool          IsUndefined() const;

  /** Check if this matrix is an identity matrix
    @return   true if matrix is identity, false otherwise
  */
  inline Obool          IsIdentity() const;

  /** This method return a const pointer to the internal array. This is useful
    when an continous array of nine values are required
    @return a pointer to the internal array
  */
  inline const T*       Ptr() const;

  /** An identity matrix, useful for testing
  */
  static const Matrix3<T>
                        identity;

  Obool                 Decompose2D(Vec2<T>& translation, Vec2<T>& scale, T& rotation) const;

  Obool                 Decompose3D(Vec3<T>& scale, Rotation4<T>& rotation) const;

  /**Multiply a Vec3 with the matrix
    @param vector the vector to multiply
    @param result the result of the multiplication
  */
  void                  inline MultVec3ByMatrix(T vector[3], T result[3]) const;

private:
  //array of elements
  T                     _elements[9];

  //special matrix flag (possible values: 0=default, IDENTITY, UNDEFINED)
  Oshort                _flag;
};

typedef Matrix3<Ofloat> Matrix3f;
typedef Matrix3<Odouble> Matrix3d;

} // namespace enterprise_manager

#include "Matrix3.inl"

#endif // ENTERPRISE_MANAGER_MATRIX3_H
