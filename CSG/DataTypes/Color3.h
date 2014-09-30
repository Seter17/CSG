#ifndef ENTERPRISE_MANAGER_COLOR3_H
#define ENTERPRISE_MANAGER_COLOR3_H

namespace enterprise_manager {

/** This class is used for handeling RGB color values.
  @ingroup dataTypes
*/
template <class T> class Color3
{
public:

  /** Enum describing the components of a rgb color */
  enum RGB_TYPE {
      R = 0,
      G = 1,
      B = 2
  };

  /** This is a constructor creating a Color3<T> object with the values specified.
    @param  red the value of the red component
    @param  green the value of the green component
    @param  blue the value of the blue component
  */
  inline                Color3<T>(T red = 0.0f, T green = 0.0f, T blue = 0.0f);

  /** This is a copy constructor creating a new Color3<T> object from an existing one.
    @param  rgb a reference to an existing Color3<T> object
  */
  inline                Color3<T>(const Color3<T>& rgb);

  /** Multiply all elements of the color by a T
    @param value the T to multiply by
    @return a reference to this color after the multiplication
  */
  inline Color3<T>&     operator*=(T value);

  /** Multiply all elements of a color by a T
    @param color the color to multiply
    @param value the T to multiply by
    @return a color containing the result of the multiplication
  */
  friend Color3<T>      operator*(const Color3<T>& color, T value)
  {
    Color3<T> result(color);
    return (result*=value);
  };

  /** Multiply all elements of a color by a T
    @param color the color to multiply
    @param value the T to multiply by
    @return a color containing the result of the multiplication
  */
  friend Color3<T>      operator*(T value, const Color3<T>& color)
  {
    Color3<T> result(color);
    return (result*=value);
  };

  /** Add all elements of a color to the corresponding values in this color.
    @param color the color to add to this color
    @return a reference to this vector after the addition
  */
  inline Color3<T>&     operator+=(const Color3<T>& color);

  /** Add all elements of a color to the corresponding values in a second color.
    @param color1 the first color
    @param color2 the second color
    @return a color containing the result of the addition
  */
  friend Color3<T>      operator+(const Color3<T>& color1, const Color3<T>& color2)
  {
    Color3<T> result(color1);
    return (result+=color2);
  }

  /** This is an asignment operator setting the value of the Color3<T> equal to an existing one.
    @param  rgb a reference to an existing Color3<T> object
  */
  inline void           operator=(const Color3<T>& rgb);

  /** This is an asignment operator setting the value of the Color3<T> equal to an existing one.
    @param  rgb a reference to an existing Color3<T> object
  */
  inline Obool          operator==(const Color3<T>& rgb) const;

  /** This is an asignment operator setting the value of the Color3<T> equal to an existing one.
    @param  rgb a reference to an existing Color3<T> object
  */
  inline Obool          operator!=(const Color3<T>& rgb) const;

  /** Method comparing this color with another specified Color3<T>. The method allows
  numerical errors by allowing each element to be within a given tolerance from the
  corresponding element of the specified color.
  (that is: |this.element - color.element| < tolerance)
    @param    rgb a color to compare this color with
    @param    tolerance the tolerance which is used for comparison
    @return   true if equal, false otherwise
  */
  inline Obool           Equal(const Color3<T>& rgb, const T tolerance = TOLERANCE) const;

  /** This method interpolates between two rgb values in HSV color space
    @param rgb1 the first rgb value
    @param rgb2 the second rgb value
    @param fraction a float from 0 to 1
    @result the interpolated rgb value
  */
  inline static Color3<T>
                        InterpolateInHSVSpace(const Color3<T>& rgb1, const Color3<T>& rgb2, const T fraction);

  /** This method gets the hsv (hue/saturation/value) values corresponding to this color
    @param h will contain the hue on return
    @param s will contain the saturation on return
    @param v will contain the value on return
  */
  inline void           GetHSV(T& h, T& s, T& v);

  /** This method sets the color equal to a set of hsv (hue/saturation/value) values
    @param h the hue to use for this color
    @param s the saturation to use for this color
    @param v the value to use for this color
  */
  inline void           SetHSV(T h, T s, T v);

  /** Subscript operator for returning the i'th element of a color.
    @param i an Oint designating which element to retrieve (R=0, G=1, B=2)
    @return a T reference to the i'th element of the vector
  */
  inline T&             operator[](const Oint i);

  /** Subscript operator for returning the i'th element of a const vector.
    @param i an Oint designating which element to retrieve (R=0, G=1, B=2)
    @return a T reference to the i'th element of the vector
  */
  inline T              operator[](const Oint i) const;

  /** This method return a const pointer to the internal array. This is useful
    when an continous array of three values are required
    @return a pointer to the internal rgb array
  */
  inline const T*       Ptr() const;

private:
  //this method interpolates between two colors specified in HSV space
  inline static Color3<T>
                        _Interpolate(Color3<T> hsv1, Color3<T> hsv2, T fraction);

  // This method converts from the RGB color space to the HSV color space.
  inline Color3<T>      _ConvertToHSV() const;

  // This method converts from the HSV color space to the RGB color space.
  inline static Color3<T>
                        _ConvertHSVToRGB(Color3<T> hsv);

  //array containing the rgb values
  T                     _rgb[3];
};

typedef Color3<Ofloat> Color3f;

} // namespace enterprise_manager

#include "Color3.inl"

#endif // ENTERPRISE_MANAGER_COLOR3_H
