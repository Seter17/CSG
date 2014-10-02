#ifndef CSG_TRIANGULATEDSURFACE_H
#define CSG_TRIANGULATEDSURFACE_H

#include <vector>
#include "DataTypes/Vec3.h"

namespace enterprise_manager {

	class TriangulatedSurface {
	public:
		static void Weld(const std::vector<Vec3<CSGReal> >& coords, std::vector<Oint>& indices);

		static void VerifyAndRepairTopology(const std::vector<Vec3<CSGReal> >& coords, std::vector<Oint>& indices);
		static Obool IsValidTriangle(const Vec3<CSGReal>& a, const Vec3<CSGReal>& b, const Vec3<CSGReal>& c);
	private:
		static CSGReal toleranceSquared;
	};

} // namespace enterprise_manager

#endif // CSG_TRIANGULATEDSURFACE_H
