#include "bbox.h"

#include "GL/glew.h"

#include <algorithm>
#include <iostream>

namespace CGL {

	bool BBox::intersect(const Ray& r, double& t0, double& t1) const {

		// TODO (Part 2.2):
		// Implement ray - bounding box intersection test
		// If the ray intersected the bouding box within the range given by
		// t0, t1, update t0 and t1 with the new intersection times.
		
		Vector3D temp0 = (min - r.o) / r.d;
		Vector3D temp1 = (max - r.o) / r.d;

		Vector3D tmin = Vector3D(
			std::min(temp0.x, temp1.x),
			std::min(temp0.y, temp1.y),
			std::min(temp0.z, temp1.z)
		);
		Vector3D tmax = Vector3D(
			std::max(temp0.x, temp1.x),
			std::max(temp0.y, temp1.y),
			std::max(temp0.z, temp1.z)
		);

		if (tmin.x > tmax.y || tmin.y > tmax.x || tmin.x > tmax.z || tmin.z > tmax.x || tmin.z > tmax.y || tmin.y >= tmax.z)
			return false;

		t0 = std::min(std::min(tmin.x, tmin.y), tmin.z);
		t1 = std::max(std::max(tmax.x, tmax.y), tmax.z);
		
		if (t0 > r.max_t || t1 < r.min_t)
			return false;
		return true;

	}

	void BBox::draw(Color c, float alpha) const {

		glColor4f(c.r, c.g, c.b, alpha);

		// top
		glBegin(GL_LINE_STRIP);
		glVertex3d(max.x, max.y, max.z);
		glVertex3d(max.x, max.y, min.z);
		glVertex3d(min.x, max.y, min.z);
		glVertex3d(min.x, max.y, max.z);
		glVertex3d(max.x, max.y, max.z);
		glEnd();

		// bottom
		glBegin(GL_LINE_STRIP);
		glVertex3d(min.x, min.y, min.z);
		glVertex3d(min.x, min.y, max.z);
		glVertex3d(max.x, min.y, max.z);
		glVertex3d(max.x, min.y, min.z);
		glVertex3d(min.x, min.y, min.z);
		glEnd();

		// side
		glBegin(GL_LINES);
		glVertex3d(max.x, max.y, max.z);
		glVertex3d(max.x, min.y, max.z);
		glVertex3d(max.x, max.y, min.z);
		glVertex3d(max.x, min.y, min.z);
		glVertex3d(min.x, max.y, min.z);
		glVertex3d(min.x, min.y, min.z);
		glVertex3d(min.x, max.y, max.z);
		glVertex3d(min.x, min.y, max.z);
		glEnd();

	}

	std::ostream& operator<<(std::ostream& os, const BBox& b) {
		return os << "BBOX(" << b.min << ", " << b.max << ")";
	}

} // namespace CGL
