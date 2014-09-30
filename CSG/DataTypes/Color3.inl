namespace enterprise_manager {

template <class T>
inline Color3<T>&
Color3<T>::operator*=(const T value)
{
  _rgb[0] *= value;
  _rgb[1] *= value;
  _rgb[2] *= value;
  return *this;
}

//template <class T>
//inline /*friend*/ Color3<T>
//operator*(const Color3<T>& color, T value)
//{
//  return Color3<T>(color._rgb[0] * value,
//                color._rgb[1] * value,
//                color._rgb[2] * value);
//}
//
//template <class T>
//inline /*friend*/ Color3<T>
//operator*(T value, const Color3<T>& color)
//{
//  return Color3<T>(color._rgb[0] * value,
//                color._rgb[1] * value,
//                color._rgb[2] * value);
//}

template <class T>
inline Color3<T>&
Color3<T>::operator+=(const Color3<T>& color)
{
  _rgb[0] += color._rgb[0];
  _rgb[1] += color._rgb[1];
  _rgb[2] += color._rgb[2];
  return *this;
}

//template <class T>
//inline /*friend*/ Color3<T>
//operator+(const Color3<T>& color1, const Color3<T>& color2)
//{
//  return Color3<T>(color1._rgb[0] + color2._rgb[0],
//                color1._rgb[1] + color2._rgb[1],
//                color1._rgb[2] + color2._rgb[2]);
//}

template <class T>
inline T&
Color3<T>::operator[](const Oint i)
{
  return _rgb[i];
}

template <class T>
inline T
Color3<T>::operator[](const Oint i) const
{
  return _rgb[i];
}

template <class T>
inline Obool
Color3<T>::Equal(const Color3<T>& rgb, const T tolerance) const
{
	return ((fabs(_rgb[0] - rgb._rgb[0]) < tolerance) &&
          (fabs(_rgb[1] - rgb._rgb[1]) < tolerance) &&
          (fabs(_rgb[2] - rgb._rgb[2]) < tolerance));
}

template <class T>
inline const T*
Color3<T>::Ptr() const
{
  return _rgb;
}

template <class T>
inline
Color3<T>::Color3(T red, T green, T blue)
{
  _rgb[0] = red;
  _rgb[1] = green;
  _rgb[2] = blue;
}

template <class T>
inline
Color3<T>::Color3(const Color3<T>& rgb)
{
  _rgb[0] = rgb._rgb[0];
  _rgb[1] = rgb._rgb[1];
  _rgb[2] = rgb._rgb[2];

}

template <class T>
inline void
Color3<T>::operator=(const Color3<T>& rgb)
{
  _rgb[0] = rgb._rgb[0];
  _rgb[1] = rgb._rgb[1];
  _rgb[2] = rgb._rgb[2];
}

template <class T>
inline Obool
Color3<T>::operator==(const Color3<T>& rgb) const
{
  return (_rgb[0] == rgb._rgb[0] &&
          _rgb[1] == rgb._rgb[1] &&
          _rgb[2] == rgb._rgb[2]);
}

template <class T>
inline Obool
Color3<T>::operator!=(const Color3<T>& rgb) const
{
   return (_rgb[0] != rgb._rgb[0] ||
           _rgb[1] != rgb._rgb[1] ||
           _rgb[2] != rgb._rgb[2]);
}

template <class T>
inline Color3<T>
Color3<T>::_ConvertHSVToRGB(Color3<T> hsv)
{
  Color3<T> rgb;
  T nh = hsv[0];
  if (hsv[1] == 0.0f){
    if (nh == -1.0f)
      rgb._rgb[0] = rgb._rgb[1] = rgb._rgb[2] = hsv[2];
    else
      rgb._rgb[0] = rgb._rgb[1] = rgb._rgb[2] = -1.0f;
  }else{
    if (nh == 360.0f)
      nh = 0.0f;
    nh /= 60.0f;
    Oint i = (Oint)floor(nh);
    T f = nh - i;
    T p = hsv[2] * (1.0f - hsv[1]);
    T q = hsv[2] * (1.0f - (hsv[1] * f));
    T t = hsv[2] * (1.0f - (hsv[1] * (1 - f)));
    switch (i){
    case 0 :
      rgb._rgb[0] = hsv[2];
      rgb._rgb[1] = t;
      rgb._rgb[2] = p;
      break;
    case 1 :
      rgb._rgb[0] = q;
      rgb._rgb[1] = hsv[2];
      rgb._rgb[2] = p;
      break;
    case 2 :
      rgb._rgb[0] = p;
      rgb._rgb[1] = hsv[2];
      rgb._rgb[2] = t;
      break;
    case 3 :
      rgb._rgb[0] = p;
      rgb._rgb[1] = q;
      rgb._rgb[2] = hsv[2];
      break;
    case 4 :
      rgb._rgb[0] = t;
      rgb._rgb[1] = p;
      rgb._rgb[2] = hsv[2];
      break;
    case 5 :
      rgb._rgb[0] = hsv[2];
      rgb._rgb[1] = p;
      rgb._rgb[2] = q;
      break;
    default :
      //MESSAGE(" The RGB values corresponding to the HSV color specified was not found. ");
      rgb._rgb[0] = rgb._rgb[1] = rgb._rgb[2] = -1.0f;
    }
  }
  return rgb;
}
template <class T>
inline void
Color3<T>::GetHSV(T& h, T& s, T& v)
{
  Color3<T> hsv = _ConvertToHSV();
  h = hsv[0];
  s = hsv[1];
  v = hsv[2];
}

template <class T>
inline void
Color3<T>::SetHSV(T h, T s, T v)
{
  Color3<T> hsv(h,s,v);
  Color3<T> rgb = _ConvertHSVToRGB(hsv);
  _rgb[0] = rgb._rgb[0];
  _rgb[1] = rgb._rgb[1];
  _rgb[2] = rgb._rgb[2];
}

template <class T>
inline Color3<T>
Color3<T>::_ConvertToHSV() const
{
  T max = O_MAX(_rgb[0],O_MAX(_rgb[1],_rgb[2]));
  T min = O_MIN(_rgb[0],O_MIN(_rgb[1],_rgb[2]));
  Color3<T> hsv;
  hsv[2] = max;

  if (max>0)
    hsv[1] = (max-min)/max;
  else
    hsv[1] = 0.0f;

  if (hsv[1]==0.0f)
    hsv[0] = -1.0f;
  else{
    T delta = max - min;
    if (_rgb[0]==max)
      hsv[0] = (_rgb[1] - _rgb[2]) / delta;
    else if (_rgb[1] == max)
      hsv[0] = 2 + (_rgb[2] - _rgb[0]) / delta;
    else if (_rgb[2] == max)
      hsv[0] = 4 + (_rgb[0] - _rgb[1]) / delta;
    hsv[0] = hsv[0] * 60.0f;
    if (hsv[0] < 0)
      hsv[0] = hsv[0] + 360;
  }

  return hsv;
}

template <class T>
inline /* static */ Color3<T>
Color3<T>::InterpolateInHSVSpace(const Color3<T>& rgb1, const Color3<T>& rgb2, const T fraction)
{
  return  _ConvertHSVToRGB(_Interpolate(rgb1._ConvertToHSV(), rgb2._ConvertToHSV(), fraction));
}

template <class T>
inline /* static */ Color3<T>
Color3<T>::_Interpolate(Color3<T> hsv1, Color3<T> hsv2, T fraction)
{
  Color3<T> hsv;
  //s
  hsv[1] = fraction * hsv2[1] + (1-fraction)*hsv1[1];
  //v
  hsv[2] = fraction * hsv2[2] + (1-fraction)*hsv1[2];

  //h
  T h = hsv2[0] - hsv1[0];

  if (hsv1[0] == -1.0f){
    if (hsv[1] == 0.0f)
      hsv[0] = -1.0f;
    else
      hsv[0] = hsv2[0];

  } else if (hsv2[0] == -1.0f){
    if (hsv[1] == 0.0f)
      hsv[0] = -1.0f;
    else
      hsv[0] = hsv1[0];

  } else {
    if (h > 180.0f) {
      h = h - 360.0f;
      hsv[0] = hsv1[0] + fraction * h;
      if (hsv[0] < 0.0f)
        hsv[0] = hsv[0] + 360.0f;
      else if (hsv[0] >= 360.0f)
        hsv[0] -= 360.0f;
    } else if (h < -180.0f) {
      h = 360.0f + h;
      hsv[0] = hsv1[0] + fraction * h;
      if (hsv[0] < 0.0f)
        hsv[0] = hsv[0] + 360.0f;
      else if (hsv[0] >= 360.0f)
        hsv[0] -= 360.0f;
    } else {
      hsv[0] = hsv1[0] + fraction * h;
      if (hsv[0] >= 360.0f)
        hsv[0] -= 360.0f;
    }
  }
  return hsv;
}

} // namespace enterprise_manager
