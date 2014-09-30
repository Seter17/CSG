#ifndef ENTERPRISE_MANAGER_EXTENT_H
#define ENTERPRISE_MANAGER_EXTENT_H

#include "Vertex.h"
#include <vector>

namespace enterprise_manager {

// The class Extent represents an the extent (bounding box) of an Object or
// Polygon. Algorithms taken from "Constructive Solid Geometry for Polyhedral
// Objects" by Laidlaw, Trumbore and Hughes.
template <class T> class Extent
{
  friend class Object<T>;
  friend class Polygon<T>;

public:
  inline const Vec3<T>& min() const;
  inline const Vec3<T>& max() const;
protected:
                        Extent();
  virtual               ~Extent();

  // Test if extentA overlaps extentB.
  static Obool          Overlap(const Extent& extentA, const Extent& extentB);

  inline void           setMin(const Vec3<T>& min);
  inline void           setMax(const Vec3<T>& max);
private:
  Vec3<T>               _min;
  Vec3<T>               _max;
};

} // namespace enterprise_manager

#include "Extent.inl"

#endif // ENTERPRISE_MANAGER_EXTENT_H
