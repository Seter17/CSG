#include "config.h"
#include "TriangulatedSurface.h"
#include "Vertex.h"

namespace enterprise_manager {

	/* static*/ CSGReal
		TriangulatedSurface::toleranceSquared = Vertex<CSGReal>::unitTolerance*Vertex<CSGReal>::unitTolerance;

	/* static */ void
		TriangulatedSurface::Weld(const std::vector<Vec3<CSGReal> >& coords, std::vector<Oint>& indices) {
			for (Oint i = 0; i < coords.size(); ++i) {
				for (Oint j = 0; j < i; ++j) {
					if (coords[i].DistanceSqr(coords[j]) < Vertex<CSGReal>::tolerance*Vertex<CSGReal>::tolerance) {
						//coords.erase(coords.begin() + i, coords.begin() + i +1);
						Oint indicesSize = static_cast<Oint>(indices.size());
						for (Oint k = 0; k < indicesSize; ++k) {
							if (indices[k] == i)
								indices[k] = j;
						}
					}
				}
			}
		}

	/* static */ Obool
		TriangulatedSurface::IsValidTriangle(const Vec3<CSGReal>& a, const Vec3<CSGReal>& b, const Vec3<CSGReal>& c) {
			Vec3<CSGReal> ab = b - a;
			Vec3<CSGReal> ac = c - a;

			if (ab.Cross(ac).LengthSqr() > toleranceSquared) {
				// the area of the parallelogram spanned by (ab, ac) is bigger than the tolerance so the triangle is valid
				return true;
			}

			return false;
		}

	/* static */ void
		TriangulatedSurface::VerifyAndRepairTopology(const std::vector<Vec3<CSGReal> >& coords, std::vector<Oint>& indices) {
			CSGReal toleranceSquared = Vertex<CSGReal>::unitTolerance*Vertex<CSGReal>::unitTolerance;
			for (Ouint i = 0; i < indices.size();) {
				Ouint ia = indices[i];
				Ouint ib = indices[i + 1];
				Ouint ic = indices[i + 2];
				if (ia == ib || ia == ic || ib == ic) {
					// the i'te triangle is degenerate... remove it
					indices.erase(indices.begin() + i, indices.begin() + i + 4);
					continue;
				}

				Vec3<CSGReal> a = coords[ia];
				Vec3<CSGReal> b = coords[ib];
				Vec3<CSGReal> c = coords[ic];

				if (IsValidTriangle(a, b, c)) {
					i += 4;
					continue;
				}

				// find the proper ordering of the (start, end, and center) vertices in the invalid triangle: 
				Vec3<CSGReal> ab = b - a;
				Vec3<CSGReal> ac = c - a;

				Ouint center, start, end;
				if (ab*ac < 0) {
					center = i;
					start = i + 1;
					end = i + 2;
				}
				else {
					Vec3<CSGReal> ba = a - b;
					Vec3<CSGReal> bc = c - b;
					if (ba*bc < 0) {
						center = i + 1;
						start = i;
						end = i + 2;
					}
					else {
						center = i + 2;
						start = i;
						end = i + 1;
					}
				}




				// loop through every other triangle in indices list to try and find a neighbouring triangle 
				// that shares the (start, end) edge of the i'te triangle 
				Obool found_match = false;
				Obool removed_before_triangle;
				Obool addedNewTriangle = false;
				for (Oint j = 0; j < indices.size(); j += 4) {
					if (j == i) // WE CAN SKIP THIS CHECK IF WE ALWAYS REMOVE THE i'te triangle
						continue;

					Oint start_candidate = -1;
					Oint end_candidate = -1;
					for (Ouint k = 0; k < 3; k++) {
						if (indices[j + k] == indices[start])
							start_candidate = j + k;
						else if (indices[j + k] == indices[end])
							end_candidate = j + k;
					}

					if (start_candidate == -1 || end_candidate == -1)
						continue;

					found_match = true;

					Ouint other_vertex = j;
					if (start_candidate == other_vertex || end_candidate == other_vertex) {
						other_vertex++;
						if (start_candidate == other_vertex || end_candidate == other_vertex)
							other_vertex++;
					}

					Obool swap = !((start_candidate + 1 == end_candidate) || (start_candidate - 2 == j && end_candidate == j));
					if (swap) {
						Ouint tmp = end_candidate;
						end_candidate = start_candidate;
						start_candidate = tmp;
					}

					// create the new triangles and test them to see if they are valid
					ia = indices[start_candidate];
					ib = indices[center];
					ic = indices[other_vertex];
					if (IsValidTriangle(coords[ia], coords[ib], coords[ib])) {
						// we add the triangle to the indices list        
						indices.push_back(ia);
						indices.push_back(ib);
						indices.push_back(ic);
						indices.push_back(-1);
						addedNewTriangle = true;
					}

					ia = indices[center];
					ib = indices[end_candidate];
					ic = indices[other_vertex];
					if (IsValidTriangle(coords[ia], coords[ib], coords[ib])) {
						// we add the triangle to the indices list        
						indices.push_back(ia);
						indices.push_back(ib);
						indices.push_back(ic);
						indices.push_back(-1);
						addedNewTriangle = true;
					}

					// Remove triangles. If we added a new triangle, than we need to remove both i'te and j'te triangle. 
					// If we didn't add a triangle, than we just need to remove the i'te triangle 
					if (addedNewTriangle) {
						removed_before_triangle = j < i;
						indices.erase(indices.begin() + j, indices.begin() + j + 4);
						if (removed_before_triangle) {
							indices.erase(indices.begin() + i - 4, indices.begin() + i);
							i -= 4;
						}
						else {
							indices.erase(indices.begin() + i, indices.begin() + i + 4);
						}
					}
					else {
						indices.erase(indices.begin() + i, indices.begin() + i + 4);
					}
					break; // continue looping through i
				}
				if (!found_match)
					i += 4;
			}
		}

} // namespace enterprise_manager
