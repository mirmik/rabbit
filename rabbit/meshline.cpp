/*#include <rabbit/meshline.h>

using namespace rabbit;

meshline
rubic_curve_meshline(const curve &crv, real umin, real umax, int utotal)
{
    int iter = 0;
    std::vector<vec3> vertices;
    std::vector<ivec2> lines;

    vertices.resize(utotal + 1);
    lines.resize(utotal);

    iter = 0;
    for (int i = 0; i < utotal + 1; ++i)
    {
        real ku = ((real)i / (real)utotal);
        real u = ustrt * ((real)1. - ku) + ufini * ku;

        vertices[iter++] = surf.value(u, v);
    }

    iter = 0;
    for (int i = 0; i < utotal; ++i)
    {
        int a = i;
        int b = i + 1;

        lines[iter++] = {a, b};
    }

    return {std::move(vertices), std::move(lines)};
}*/