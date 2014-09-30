#ifndef ENTERPRISE_MANAGER_NUQUATERNION_H
#define ENTERPRISE_MANAGER_NUQUATERNION_H

#include <math.h>

namespace enterprise_manager {

template<class T> class Vec3;
template<class T> class Rotation4;
template<class T> class Matrix3;
template<class T> class Matrix4;

template<class T> class NUQuaternion;

template<class T> NUQuaternion<T>
                      operator+(const NUQuaternion<T>& a, const NUQuaternion<T>& b);

template<class T> NUQuaternion<T>
                      operator-(const NUQuaternion<T>& a, const NUQuaternion<T>& b);

template<class T> NUQuaternion<T>
                      operator*(const NUQuaternion<T>& a, const NUQuaternion<T>& b);

template<class T> NUQuaternion<T>
                      operator*(T s, const NUQuaternion<T>& q);

template<class T> NUQuaternion<T>
                      operator*(const NUQuaternion<T>& q, T s);

template<class T> NUQuaternion<T>
                      operator/(NUQuaternion<T> q, T s);

template<class T> NUQuaternion<T>
                      operator/(NUQuaternion<T> a, NUQuaternion<T> b);

template<class T> bool
                      operator==(const NUQuaternion<T>& a, const NUQuaternion<T>& b);

template<class T> bool
                      operator!=(const NUQuaternion<T>& a, const NUQuaternion<T>& b);

template<class T> NUQuaternion<T>
                      Conjugate(const NUQuaternion<T>& q);

template<class T> NUQuaternion<T>
                      Inverse(const NUQuaternion<T>& q);

template<class T> T
                      Norm(const NUQuaternion<T>& q);

template<class T> T
                      Abs(const NUQuaternion<T>& q);

template<class T> NUQuaternion<T>
                      Exp(const NUQuaternion<T>& q);

template<class T> NUQuaternion<T>
                      Log(const NUQuaternion<T>& q);

template<class T> NUQuaternion<T>
                      Pow(const NUQuaternion<T>& q, T s);

template<class T> NUQuaternion<T>
                      Pow(const NUQuaternion<T>& q, const NUQuaternion<T>& p);

template<class T> NUQuaternion<T>
                      Sin(const NUQuaternion<T>& q);

template<class T> NUQuaternion<T>
                      Cos(const NUQuaternion<T>& q);

template<class T> NUQuaternion<T>
                      Sqrt(const NUQuaternion<T>& q);

template<class T> T
                      Real(const NUQuaternion<T>& q);

template<class T> Vec3<T>
                      Imag(const NUQuaternion<T>& q);

template<class T> T
                      Dot(const NUQuaternion<T> a, const NUQuaternion<T> b);

template<class T> NUQuaternion<T>
                      Slerp(const NUQuaternion<T>& q0, const NUQuaternion<T>& q1, T t);

template<class T> NUQuaternion<T>
                      Xrotation(T angle);

template<class T> NUQuaternion<T>
                      Yrotation(T angle);

template<class T> NUQuaternion<T>
                      Zrotation(T angle);

//Non-Unit Quaternions
template<class T> class NUQuaternion
{
  friend class Rotation4<T>;

public:
  //contructors (no conversion)
  inline                NUQuaternion<T>();
  inline                NUQuaternion<T>(const NUQuaternion<T>&);
  inline explicit       NUQuaternion<T>(T);
  inline explicit       NUQuaternion<T>(const Vec3<T>&);
  inline                NUQuaternion<T>(T, const Vec3<T>&);
  inline                NUQuaternion<T>(T, T, T, T);

  //create a unit quternion, axis is normalized
  inline explicit       NUQuaternion<T>(const Rotation4<T>&);

  inline explicit       NUQuaternion(const Matrix3<T>&);

  //unary operators
  inline NUQuaternion&  operator+=(const NUQuaternion<T>&);
  inline NUQuaternion&  operator-=(const NUQuaternion<T>&);
  inline NUQuaternion&  operator*=(T);
  inline NUQuaternion&  operator*=(const NUQuaternion<T>&);
  inline NUQuaternion&  operator/=(T);
  inline NUQuaternion&  operator/=(const NUQuaternion<T>&);

  // conjugate operator
  inline NUQuaternion   operator~() const;
  inline NUQuaternion   operator-() const;
  inline NUQuaternion   operator+() const;

  bool                  IsPure() const;
  bool                  IsReal() const;
  T                     Normalize();

  // Set to the unit quaternion representing an axis angle rotation.  Assume
  // that axis is a unit vector
  inline void           SetAxisAngle(const Vec3<T>& axis, T angle);

  // Assuming that this a unit quaternion, return the in axis/angle form the
  // orientation which it represents.
  inline void           GetAxisAngle(Vec3<T>& axis, T& angle) const;

  void                  Rotate(const Vec3<T>& axis, T angle);
  void                  Xrotate(T angle);
  void                  Yrotate(T angle);
  void                  Zrotate(T angle);

  template <typename U> friend NUQuaternion<U>
                        operator+(const NUQuaternion<U>& a, const NUQuaternion<U>& b);

  template <typename U> friend NUQuaternion<U>
                        operator-(const NUQuaternion<U>& a, const NUQuaternion<U>& b);

  friend NUQuaternion<T>
                        operator* <>(const NUQuaternion<T>& a, const NUQuaternion<T>& b);

  friend NUQuaternion<T>
                        operator* <>(T s, const NUQuaternion<T>& q);

  friend NUQuaternion<T>
                        operator* <>(const NUQuaternion<T>& q, T s);

  friend NUQuaternion<T>
                        operator/ <>(NUQuaternion<T> q, T s);

  friend NUQuaternion<T>
                        operator/ <>(NUQuaternion<T> a, NUQuaternion<T> b);

  friend bool
                        operator== <>(const NUQuaternion<T>& a, const NUQuaternion<T>& b);

  friend bool
                        operator!= <>(const NUQuaternion<T>& a, const NUQuaternion<T>& b);

  friend NUQuaternion<T>
                        Conjugate<>(const NUQuaternion<T>& q);

  friend NUQuaternion<T>
                        Inverse<>(const NUQuaternion<T>& q);

  friend T
                        Norm<>(const NUQuaternion<T>& q);

  friend T
                        Abs<>(const NUQuaternion<T>& q);

  friend NUQuaternion<T>
                        Exp<>(const NUQuaternion<T>& q);

  friend NUQuaternion<T>
                        Log<>(const NUQuaternion<T>& q);

  friend NUQuaternion<T>
                        Pow<>(const NUQuaternion<T>& q, T s);

  friend NUQuaternion<T>
                        Pow<>(const NUQuaternion<T>& q, const NUQuaternion<T>& p);

  friend NUQuaternion<T>
                        Sin<>(const NUQuaternion<T>& q);

  friend NUQuaternion<T>
                        Cos<>(const NUQuaternion<T>& q);

  friend NUQuaternion<T>
                        Sqrt<>(const NUQuaternion<T>& q);

  friend T
                        Real<>(const NUQuaternion<T>& q);

  friend Vec3<T>
                        Imag<>(const NUQuaternion<T>& q);

  friend T
                        Dot<>(const NUQuaternion<T> a, const NUQuaternion<T> b);

  friend NUQuaternion<T>
                        Slerp<>(const NUQuaternion<T>& q0, const NUQuaternion<T>& q1, T t);

  friend NUQuaternion<T>
                        Xrotation<>(T angle);

  friend NUQuaternion<T>
                        Yrotation<>(T angle);

  friend NUQuaternion<T>
                        Zrotation<>(T angle);

private:
  T w, x, y, z;
};

typedef NUQuaternion<float> NUQuaternionf;
typedef NUQuaternion<double> NUQuaterniond;

} // namespace enterprise_manager

#include "NUQuaternion.inl"

#endif // ENTERPRISE_MANAGER_NUQUATERNION_H
