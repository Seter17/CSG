#ifndef ENTERPRISE_MANAGER_CONFIG_H
#define ENTERPRISE_MANAGER_CONFIG_H

#include <limits>

#define O_MIN(a, b)  (((a) < (b)) ? (a) : (b))
#define O_MAX(a, b)  (((a) > (b)) ? (a) : (b))

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#endif 

typedef size_t Osize; //size types for everything but fields (32/64 bit)
typedef unsigned short Ofsize; //size type for fields

// 64  bits types.
typedef double CSGReal;
typedef double Odouble;
typedef double Odouble;
typedef long long Ovlong;
typedef long long Oint64;
typedef unsigned long long Ouvlong;
typedef unsigned long long Ouint64;

// 32 bits types.
typedef float Ofloat;
typedef float Ofloat32;
typedef int Oint;
typedef int Oint32;
typedef unsigned int Ouint;
typedef unsigned int Ouint32;
typedef long Olong;
typedef unsigned long Oulong;

// 16 bits types.
typedef wchar_t Owchar;
typedef short Oshort;
typedef short Oint16;
typedef unsigned short Oushort;
typedef unsigned short Ouint16;

// 8 bits types
typedef char Ochar;
typedef char Obyte;
typedef char Oint8;
typedef unsigned char Ouchar;
typedef unsigned char Ouint8;

// Boolean type.
typedef bool Obool;

enum AXIS_TYPE {
  X = 0,
  Y = 1,
  Z = 2,
  R = 3
};

const Ofloat PI = (Ofloat)3.14159265358979323846;
const Ofloat LN2 = (Ofloat)0.69314718055994530941723212145818;
const Oint   MAX_EXP_FLOAT = std::numeric_limits<Ofloat>::max_exponent10;

const Ofloat MAX_FLOAT = (Ofloat)std::numeric_limits<Ofloat>::max();
const Ofloat MIN_FLOAT = -MAX_FLOAT;
const Oint   MAX_INT = (Oint)std::numeric_limits<Oint>::max();
const Ouint  MAX_UINT = (Ouint)std::numeric_limits<Ouint>::max();
const Oint   MAX_USHORT = (Oushort)std::numeric_limits<Oushort>::max();
const Oint   MAX_SHORT = (Oshort)std::numeric_limits<Oshort>::max();
const Oint   MAX_ULONG = (Oulong)std::numeric_limits<Oulong>::max();
const Oint   MAX_LONG = (Olong)std::numeric_limits<Olong>::max();

const Ofloat TOLERANCE = (Ofloat)0.00001;

#endif // ENTERPRISE_MANAGER_CONFIG_H
