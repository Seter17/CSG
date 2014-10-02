#ifndef ENTERPRISE_MANAGER_MATRIX4_H
#define ENTERPRISE_MANAGER_MATRIX4_H

#include <math.h>
#include <assert.h>

namespace enterprise_manager {

	template <class T> class Matrix3;
	template <class T> class Quaternion;
	template <class T> class Rotation4;
	template <class T> class Vec3;

	//special matrix types which requires no parameters
	enum SpecialMatrix {
		IDENTITY = 1,
		UNDEFINED
	};

	//special matrix types which requires one parameters
	enum ScaleType {
		SCALE
	};

	//special matrix types which requires two parameters
	enum RotateType {
		ROTATE
	};

	//special matrix types which requires three parameters
	enum TranslateType {
		TRANSLATE
	};

	/** The Matrix4<T> class implements a 4x4 matrix for doing 3d transformations.
	The matrix is transposed relative to the matrixes described in Computer Graphics
	(Foley, van Dam, Feiner, Hughes 1990), but similar to OpenGL, Performer etc.
	That is, the matrix has the form:
	|a00 a01 a02 a03|   |r11 r21 r31 0|
	|a10 a11 a12 a13|   |r12 r22 r32 0|
	|a20 a21 a22 a23| = |r13 r23 r33 0|
	|a30 a31 a32 a33|   |tx  ty  tz  1|
	@ingroup dataTypes
	*/
	template <class T> class Matrix4 {
		/** Vec3 is a friend of Matrix4 */
		friend class Vec3<T>;

	public:

		/** indexes used for code readability */
		enum IndexType {
			a00 = 0,
			a01 = 1,
			a02 = 2,
			a03 = 3,
			a10 = 4,
			a11 = 5,
			a12 = 6,
			a13 = 7,
			a20 = 8,
			a21 = 9,
			a22 = 10,
			a23 = 11,
			a30 = 12,
			a31 = 13,
			a32 = 14,
			a33 = 15
		};

		/** Default constructor which creates a new identity matrix
		*/
		inline                Matrix4<T>();

		/** Constructor which copies a 4 x 4 c++ matrix
		*/
		inline explicit       Matrix4<T>(const T matrix[4][4]);

		/** Constructor which copies a c++ matrix
		*/
		inline explicit       Matrix4<T>(const T matrix[16]);

		/** Contructor which creates a special matrix with no parameters.
		  Currently supported matrix types are:
		  IDENTITY  : the identity matrix
		  UNDEFINED : a matrix where all values are undefined - should be used with caution
		  @param  matrix_type the type of matrix to create.
		  */
		inline explicit       Matrix4<T>(const SpecialMatrix matrix_type);

		/** Contructor which creates a uniform scale matrix.
		  @param  matrix_type the type of matrix to create, must be SCALE
		  @param  value the uniform scaling value
		  */
		inline                Matrix4<T>(const ScaleType matrix_type, T value);

		/** Contructor which creates a non-uniform scale matrix
		  @param  matrix_type the type of matrix to create, must be SCALE
		  @param  x the scaling value along the x axis
		  @param  y the scaling value along the y axis
		  @param  z the scaling value along the z axis
		  */
		inline                Matrix4<T>(const ScaleType matrix_type, T x, T y, T z);

		/** Contructor which creates a non-uniform scale matrix
		@param  matrix_type the type of matrix to create, must be SCALE
		@param  vector a vector containing the three scaling values
		*/
		inline                Matrix4<T>(const ScaleType matrix_type, const Vec3<T>& vector);

		/** Contructor which creates a rotation matrix, which rotates around one of the
		  three pricipal axis (X, Y, Z).
		  @param  matrix_type the type of matrix to create, must be ROTATE
		  @param  axis the axis to roatate around
		  @param  radians the angle to rotate around the given axis in radians
		  */
		Matrix4<T>(const RotateType matrix_type, Oint axis, T radians);

		/** Contructor which creates a rotation matrix, which rotates around one of the
		  three pricipal axis (X, Y, Z).
		  @param  matrix_type the type of matrix to create, must be ROTATE
		  @param  axis the axis to roatate around
		  @param  cos the cosine of the angle to rotate
		  @param  sin the sine of the angle to rotate
		  */
		Matrix4<T>(const RotateType matrix_type, Oint axis, T cos, T sin);

		/** Contructor which creates a rotation matrix, which rotates around a specified axis
		  @param  matrix_type the type of matrix to create, must be ROTATE
		  @param  x the x component of the rotation axis
		  @param  y the y component of the rotation axis
		  @param  z the z component of the rotation axis
		  @param  r the angle to rotate (in radians)
		  */
		Matrix4<T>(const RotateType matrix_type, T x, T y, T z, T r);

		/** Contructor which creates a rotation matrix, which rotates around a specified axis
		  @param  matrix_type the type of matrix to create, must be ROTATE
		  @param  axis a vector specifying the axis of rotation
		  @param  r the angle to rotate (in radians)
		  */
		Matrix4<T>(const RotateType matrix_type, const Vec3<T>& axis, T r);

		/** Contructor which creates a translation matrix
		  @param  matrix_type the type of matrix to create, must be TRANSLATE
		  @param  x the distance to translate along the x axis
		  @param  y the distance to translate along the y axis
		  @param  z the distance to translate along the z axis
		  */
		Matrix4<T>(const TranslateType matrix_type, T x, T y, T z);

		/** Contructor which creates a translation matrix
		  @param  matrix_type the type of matrix to create, must be TRANSLATE
		  @param  vector the displacement vector
		  */
		Matrix4<T>(const TranslateType matrix_type, const Vec3<T>& vector);

		/** Contructor which creates a matrix corresponding to the rotation represented by
		  a specified Quaternion
		  @param  quaternion a Quaternion representing a rotation.
		  */
		explicit              Matrix4<T>(const Quaternion<T>& quaternion);

		/** Contructor which creates a matrix corresponding to the rotation represented by
		  a rotation object
		  @param  rotation a rotation object
		  */
		explicit              Matrix4<T>(const Rotation4<T>& rotation);

		/** This is a constructor which creates a new Matrix4<T> object by copying an existing
		  one.
		  @param  X a reference to an existing matrix
		  */
		inline                Matrix4<T>(const Matrix4<T>& X);

		/** This is a constructor which creates a new Matrix4<T> object by copying an existing
		  Matrix3<T>
		  @param  X a reference to an existing Matrix3<T>
		  */
		inline explicit       Matrix4<T>(const Matrix3<T>& X);

		/** The destructor.
		*/
		inline                ~Matrix4<T>();

		/** Equality operator comparing the current Matrix4<T> object with another specified
		  Matrix4<T> object.
		  @param    matrix a reference to a Matrix4<T> object
		  @return   true if equal, false otherwise
		  */
		Obool                  operator==(const Matrix4<T>& matrix) const;

		/** Inequality operator comparing the current Matrix4<T> object with another specified
		  Matrix4<T> object.
		  @param    matrix a reference to a Matrix4<T> object
		  @return   true if not equal, false otherwise
		  */
		Obool                  operator!=(const Matrix4<T>& matrix) const;

		/** Method comparing this Matrix4<T> with another specified Matrix4<T>. The method allows
		  numerical errors by allowing each element to be within a given tolerance from the
		  corresponding element of the specified Matrix4<T>.
		  (that is: |this.element - matrix.element| < tolerance)
		  @param    matrix a reference to a Matrix4<T> object
		  @param    tolerance the tolerance which is used for comparison
		  @return   true if equal, false otherwise
		  */
		Obool                  Equal(const Matrix4<T>& matrix, const T tolerance = TOLERANCE) const;

		/** Assignment operator which sets this matrix equal to a specified matrix.
		  @param    matrix a reference to a Matrix4<T> object
		  @return   a reference to this matrix after the assignment
		  */
		inline Matrix4<T>&    operator=(const Matrix4<T>& matrix);

		/** Multiply this matrix by another specified matrix (this = this * matrix)
		  @param    matrix a reference to a Matrix4<T> object
		  @return   reference to this matrix after the multiplication
		  */
		Matrix4<T>&           operator*=(const Matrix4<T>& matrix);

		/** PreMultiply this matrix by another specified matrix (this = matrix * this)
		  @param    matrix a reference to a Matrix4<T> object
		  @return   reference to this matrix after the multiplication
		  */
		Matrix4<T>&           PreMultiply(const Matrix4<T>& matrix);

		/** Multiply two matrixes and return the resulting matrix
		  @param    matrix1 a reference to a Matrix4<T> object
		  @param    matrix2 a reference to a second Matrix4<T> object
		  @return   the matrix resulting from the operation matrix1 * matrix2
		  */
		friend Matrix4<T>     operator*(const Matrix4<T>& matrix1, const Matrix4<T>& matrix2) {
			Matrix4<T> result(matrix1);
			return (result *= matrix2);
		}

		/** Multiply this matrix by a T
		  @param    value a T to multiply the matrix by
		  @return   reference to this matrix after the multiplication
		  */
		Matrix4<T>&           operator*=(T value);

		/** Multiply a matrix by a T and return the resulting matrix
		  @param    matrix a reference to a Matrix4<T> object
		  @param    value a T to multiply the matrix by
		  @return   the matrix resulting from the operation matrix * value
		  */
		friend Matrix4<T>     operator*(const Matrix4<T>& matrix, const T value) {
			Matrix4<T> result(matrix);
			return (result *= value);
		}

		/** Divide this matrix by a T
		  @param    value a T to divide the matrix by
		  @return   reference to this matrix after the division
		  */
		Matrix4<T>&           operator/=(T value);

		/** Divide a matrix by a T and return the resulting matrix
		  @param    matrix a reference to a Matrix4<T> object
		  @param    value a T to divide the matrix by
		  @return   the matrix resulting from the operation matrix / value
		  */
		friend Matrix4<T>     operator/(const Matrix4<T>& matrix, const T value) {
			Matrix4<T> result(matrix);
			return (result /= value);
		}

		/** Add another specified matrix to this matrix (this = this + matrix)
		  @param    matrix a reference to a Matrix4<T> object
		  @return   reference to this matrix after the addition
		  */
		Matrix4<T>&           operator+=(const Matrix4<T>& matrix);

		/** Add two matrixes and return the resulting matrix
		  @param    matrix1 a reference to a Matrix4<T> object
		  @param    matrix2 a reference to a second Matrix4<T> object
		  @return   the matrix resulting from the operation matrix1 + matrix2
		  */
		friend Matrix4<T>     operator+(const Matrix4<T>& matrix1, const Matrix4<T>& matrix2) {
			Matrix4<T> result(matrix1);
			return (result += matrix2);
		}

		/** Subtract another specified matrix from this matrix (this = this - matrix)
		  @param    matrix a reference to a Matrix4<T> object
		  @return   reference to this matrix after the subtraction
		  */
		Matrix4<T>&           operator-=(const Matrix4<T>& matrix);

		/** Subtract a matrix from another and return the resulting matrix
		  @param    matrix1 a reference to a Matrix4<T> object
		  @param    matrix2 a reference to a second Matrix4<T> object
		  @return   the matrix resulting from the operation matrix1 + matrix2
		  */
		friend Matrix4<T>     operator-(const Matrix4<T>& matrix1, const Matrix4<T>& matrix2) {
			Matrix4<T> result(matrix1);
			return (result -= matrix2);
		}

		/** Calculate the determinant of the matrix
		  @return   a T conatining the determinant of this matrix
		  */
		T                     Determinant() const;

		/** Invert the matrix
		  @return   reference to this matrix it has been inverted, if the original
		  matrix was singular the result is marked as undefined (can be tested)
		  */
		Matrix4<T>&           Invert();

		/** Get the inverse of the matrix. Does not modify the original matrix
		  @return   the inverted matrix, if the original matrix was singular the result
		  is marked as undefined (can be tested)
		  */
		inline Matrix4<T>     GetInverse() const;

		/** Decompose the matrix
		  @param translation
		  @param scale
		  @param rotation
		  @return   true on success, false on failure
		  */
		Obool                 Decompose(Vec3<T>& translation, Vec3<T>& scale, Rotation4<T>& rotation) const;

		/**Multiply a Vec4 with the matrix
		  @param vector the vector to multiply
		  @param result the result of the multiplication
		  */
		void                  MultVec4ByMatrix(T vector[4], T result[4]) const;

		/** Transpose the matrix
		  @return   reference to this matrix after it has been transposed
		  */
		Matrix4<T>&           Transpose();

		/** Get the transpose of a matrix (does not modify the original)
		  @return   the transposed matrix
		  */
		inline Matrix4<T>     GetTranspose() const;

		/** Multiply this matrix by a rotation matrix defined by a
		  a specified rotation around a specified axis
		  @param    x the x component of the axis of rotation
		  @param    y the y component of the axis of rotation
		  @param    z the z component of the axis of rotation
		  @param    r the angle of rotation (in radians)
		  @return   this matrix after the multiplication
		  */
		inline void           Rotate(T x, T y, T z, T r);
		inline void           Rotate(const Quaternion<T>& q);

		/** PreMultiply this matrix by a rotation matrix defined by a
		  a specified rotation around a specified axis (similar to glRotate)
		  @param    x the x component of the axis of rotation
		  @param    y the y component of the axis of rotation
		  @param    z the z component of the axis of rotation
		  @param    r the angle of rotation (in radians)
		  @return   this matrix after the multiplication
		  */
		inline void           PreRotate(T x, T y, T z, T r);
		inline void           PreRotate(const Quaternion<T>& q);

		/** Multiply this matrix by a rotation matrix defined by a
		  a specified rotation around a specified axis
		  @param    axis a vector specifying the axis of rotation
		  @param    r the angle of rotation (in radians)
		  @return   this matrix after the multiplication
		  */
		inline void           Rotate(const Vec3<T>& axis, T r);

		/** PreMultiply this matrix by a rotation matrix defined by a
		  a specified rotation around a specified axis
		  @param    axis a vector specifying the axis of rotation
		  @param    r the angle of rotation (in radians)
		  @return   this matrix after the multiplication
		  */
		inline void           PreRotate(const Vec3<T>& axis, T r);

		/** Multiply this matrix by a rotation matrix defined by a
		  Rotation object
		  @param    rot a rotation object describing the rotation
		  @return   this matrix after the multiplication
		  */
		inline void           Rotate(const Rotation4<T>& rot);

		/** PreMultiply this matrix by a rotation matrix defined by a
		  Rotation object
		  @param    rot a rotation object describing the rotation
		  @return   this matrix after the multiplication
		  */
		inline void           PreRotate(const Rotation4<T>& rot);

		/** Multiply this matrix by a rotation matrix defined by a
		  a specified rotation around one of the three pricipal axis
		  @param    axis the principal axis to rotate around (X, Y or Z)
		  @param    r the angle of rotation (in radians)
		  @return   this matrix after the multiplication
		  */
		inline void           Rotate(Oint axis, T r);

		/** Multiply this matrix by a translation matrix defined by three Ts
		  @param    x the x component of the translation
		  @param    y the y component of the translation
		  @param    z the z component of the translation
		  @return   this matrix after the multiplication
		  */
		inline void           Translate(T x, T y, T z);

		/** PreMultiply this matrix by a translation matrix defined by three Ts (similar to glTranslate)
		  @param    x the x component of the translation
		  @param    y the y component of the translation
		  @param    z the z component of the translation
		  @return   this matrix after the multiplication
		  */
		inline void           PreTranslate(T x, T y, T z);

		/** Multiply this matrix by a translation matrix defined by a vector
		  @param    vector a vector defining the translation
		  @return   this matrix after the multiplication
		  */
		inline void           Translate(const Vec3<T>& vector);

		/** PreMultiply this matrix by a translation matrix defined by a vector
		  @param    vector a vector defining the translation
		  @return   this matrix after the multiplication
		  */
		inline void           PreTranslate(const Vec3<T>& vector);

		/** Multiply this matrix by a scaling matrix defined by three Ts
		  @param    sx the scale factor along the x axis
		  @param    sy the scale factor along the y axis
		  @param    sz the scale factor along the z axis
		  @return   this matrix after the multiplication
		  */
		inline void           Scale(const T sx, const T sy, const T sz);

		/** PreMultiply this matrix by a scaling matrix defined by three Ts (similar to glScale)
		  @param    sx the scale factor along the x axis
		  @param    sy the scale factor along the y axis
		  @param    sz the scale factor along the z axis
		  @return   this matrix after the multiplication
		  */
		inline void           PreScale(const T sx, const T sy, const T sz);

		/** Multiply this matrix by a scaling matrix defined by a vector
		  @param    vector a vector defining the scale factors along the three principal axis
		  @return   this matrix after the multiplication
		  */
		inline void           Scale(const Vec3<T>& vector);

		/** PreMultiply this matrix by a scaling matrix defined by a vector
		  @param    vector a vector defining the scale factors along the three principal axis
		  @return   this matrix after the multiplication
		  */
		inline void           PreScale(const Vec3<T>& vector);

		/** Multiply this matrix by a uniform scaling matrix
		  @param    scale the uniform scaling factor
		  @return   this matrix after the multiplication
		  */
		inline void           Scale(const T scale);

		/** PreMultiply this matrix by a uniform scaling matrix
		  @param    scale the uniform scaling factor
		  @return   this matrix after the multiplication
		  */
		inline void           PreScale(const T scale);

		/** Get a spesific element in the Matrix4<T>
		  @param    row an Oint specifying the row from which to get the element
		  @param    column an Oint specifying the column from which to get the element
		  @return    a T containing the value of the specified element.
		  */
		inline T              Get(Oint row, Oint column) const;

		/** Get a spesific row from the Matrix4<T>. NB: only the three first elements are
		  retrieved. To get the fourth element use get(row, column)
		  @param    row an Oint specifying the row from which to get the vector
		  @return    a Vec3<T> containing the three first values from the specified row
		  */
		inline Vec3<T>        GetRow(Oint row) const;

		/** Get a spesific column from the Matrix4<T>. NB: only the three first elements are
		  retrieved. To get the fourth element use get(row, column)
		  @param col an int specifying the column from which to get the vector
		  @return a Vec3<T> containing the three first values in the specified column
		  */
		inline Vec3<T>        GetColumn(Oint col) const;

		/** Get a the translation elements of the Matrix4<T>.
		  @return    a Vec3<T> containing the three translation elements
		  */
		inline Vec3<T>        GetTranslation() const;

		/** Get the euler rotations of the Matrix4<T>.
		  @param rx rotation around x axis
		  @param ry rotation around y axis
		  @param rz rotation around z axis
		  */
		void                  GetRotation(T& rx, T& ry, T& rz) const;

		/** Set a spesific element in the Matrix4<T>
		  @param row an Oint specifying the row in which to set the element
		  @param column an Oint specifying the column in which to set the element
		  @param value the new value of the specified element
		  @return a T containing the new value of the specified element
		  */
		inline T              Set(Oint row, Oint column, T value);

		/** Set a spesific row in the Matrix4<T>. NB: the fourth element in the row will not
		 be set. In order to set this element use set(row,column)
		 @param row an Oint specifying the row in which to set the elements
		 @param vector a vector containing the elements to put into the row
		 @return a reference to the matrix after altering the row
		 */
		inline Matrix4<T>&    SetRow(Oint row, const Vec3<T>& vector);

		/** Set a spesific column in the Matrix4<T>. NB: the fourth element in the column will not
		 be set. In order to set this element use set(row,column)
		 @param column an Oint specifying the column in which to set the elements
		 @param vec a vector containing the elements to put into the column
		 @return a reference to the matrix after altering the column
		 */
		inline Matrix4<T>&    SetColumn(Oint column, const Vec3<T>& vec);

		/** Check if this matrix is an undefined matrix (a result of an unsuccsessful
		  matrix operation)
		  @return   true if matrix is undefined, false otherwise
		  */
		inline Obool          IsUndefined() const;

		/** This method return a const pointer to the internal array. This is useful
		  when an continous array of 16 values are required
		  @return a pointer to the internal array
		  */
		inline const T*       Ptr() const;

		/** An identity matrix, useful for testing
		*/
		static const Matrix4<T>
			identity;

	private:
		//array of elements
		T                     _elements[16];
		//special matrix flag (possible values: 0=default, IDENTITY, UNDEFINED)
		Oshort                 _flag;
	};

	typedef Matrix4<Ofloat> Matrix4f;
	typedef Matrix4<Odouble> Matrix4d;

} // namespace enterprise_manager

#include "Matrix4.inl"

#endif // ENTERPRISE_MANAGER_MATRIX4_H
