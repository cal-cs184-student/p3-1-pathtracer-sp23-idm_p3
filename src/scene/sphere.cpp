#include "sphere.h"

#include <cmath>

#include "pathtracer/bsdf.h"
#include "util/sphere_drawing.h"

namespace CGL {
namespace SceneObjects {

bool Sphere::test(const Ray &r, double &t1, double &t2) const {

	// TODO (Part 1.4):
	// Implement ray - sphere intersection test.
	// Return true if there are intersections and writing the
	// smaller of the two intersection times in t1 and the larger in t2.

	double A = (r.d).norm2();
	double B = 2 * dot(r.d, r.o - o);
	double C = (r.o - o).norm2() - r2;

	double discriminant = B * B - 4 * A * C;
	if (discriminant < 0)
		return false;
	t1 = ( - B - sqrt(discriminant)) / (2. * A);
	t2 = ( - B + sqrt(discriminant)) / (2. * A);
	if (t1 <= r.min_t) {
		t1 = t2;
	}
	if (t2 >= r.max_t) {
		t2 = t1;
	}
	return (t1 > r.min_t && t2 < r.max_t);
}

bool Sphere::has_intersection(const Ray &r) const {

	// TODO (Part 1.4):
	// Implement ray - sphere intersection.
	// Note that you might want to use the the Sphere::test helper here.
	double t1, t2;
	return test(r, t1, t2);
}

bool Sphere::intersect(const Ray &r, Intersection *i) const {

	// TODO (Part 1.4):
	// Implement ray - sphere intersection.
	// Note again that you might want to use the the Sphere::test helper here.
	// When an intersection takes place, the Intersection data should be updated
	// correspondingly.
	double t1, t2;
	if (test(r, i->t, t2)) {
		r.max_t = i->t;
		i->n = (r.at_time(i->t) - this->o) / (this->r);
		i->primitive = this;
		i->bsdf = get_bsdf();
		return true;
	}
	return false;
}

void Sphere::draw(const Color &c, float alpha) const {
  Misc::draw_sphere_opengl(o, r, c);
}

void Sphere::drawOutline(const Color &c, float alpha) const {
  // Misc::draw_sphere_opengl(o, r, c);
}

} // namespace SceneObjects
} // namespace CGL
