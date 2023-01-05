#ifndef RABBIT_MESH_H
#define RABBIT_MESH_H

#include <rabbit/geom/surface.h>
#include <rabbit/third/linalg.h>
#include <rabbit/third/stl_reader.h>
#include <vector>

namespace rabbit
{
    template <class T = float> class mesh
    {
    public:
        std::vector<linalg::vec<T, 3>> vertices;
        std::vector<linalg::vec<unsigned int, 3>> triangles;

    public:
        mesh(const std::vector<linalg::vec<T, 3>> &_vertices,
             const std::vector<linalg::vec<unsigned int, 3>> &_triangles)
            : vertices(_vertices), triangles(_triangles)
        {
        }

        mesh() = default;

        mesh(std::vector<linalg::vec<T, 3>> &&_vertices,
             std::vector<linalg::vec<unsigned int, 3>> &&_triangles)
            : vertices(std::move(_vertices)), triangles(std::move(_triangles))
        {
        }

        linalg::vec<T, 3> center()
        {
            linalg::vec<double, 3> acc = {0, 0, 0};
            int n = vertices.size();

            for (auto &v : vertices)
            {
                acc += v;
            }

            return linalg::vec<T, 3>{acc / n};
        }

        void correct_center()
        {
            auto c = center();

            for (auto &v : vertices)
            {
                v -= c;
            }
        }
    };

    template <class T = float>
    mesh<T> surface_rubic_mesh(const surface &surf,
                               T ustrt,
                               T ufini,
                               int utotal,
                               T vstrt,
                               T vfini,
                               int vtotal)
    {
        int iter;

        std::vector<linalg::vec<T, 3>> vertices;
        std::vector<linalg::vec<unsigned int, 3>> triangles;

        vertices.resize((utotal + 1) * (vtotal + 1));
        triangles.resize(2 * utotal * vtotal);

        iter = 0;
        for (int j = 0; j < vtotal + 1; ++j)
        {
            for (int i = 0; i < utotal + 1; ++i)
            {
                T ku = ((T)i / (T)utotal);
                T kv = ((T)j / (T)vtotal);

                T u = ustrt * ((T)1. - ku) + ufini * ku;
                T v = vstrt * ((T)1. - kv) + vfini * kv;

                auto val = surf.value(u, v);
                vertices[iter++] = {(T)val.x, (T)val.y, (T)val.z};
            }
        }

        iter = 0;
        for (int j = 0; j < vtotal; ++j)
        {
            for (int i = 0; i < utotal; ++i)
            {
                unsigned int a = i + (j) * (utotal + 1);
                unsigned int b = i + (j) * (utotal + 1) + 1;
                unsigned int c = i + (1 + j) * (utotal + 1);
                unsigned int d = i + (1 + j) * (utotal + 1) + 1;

                triangles[iter++] = {a, b, c};
                triangles[iter++] = {d, c, b};
            }
        }

        return mesh<T>(std::move(vertices), std::move(triangles));
    }

    template <class T = float>
    mesh<T> surface_rubic_mesh(const surface &surf, int utotal, int vtotal)
    {
        return surface_rubic_mesh<T>(surf,
                                     surf.umin(),
                                     surf.umax(),
                                     utotal,
                                     surf.vmin(),
                                     surf.vmax(),
                                     vtotal);
    }

    template <class T = float> mesh<T> mesh_from_file(const char *path)
    {
        std::vector<float> coords, normals;
        std::vector<unsigned int> tris, solids;

        std::vector<linalg::vec<T, 3>> vertices;
        std::vector<linalg::vec<unsigned int, 3>> triangles;

        stl_reader::ReadStlFile(
            "bulbasaur_dual_body.STL", coords, normals, tris, solids);

        int vertices_total = coords.size() / 3;
        int triangles_total = tris.size() / 3;

        vertices.resize(vertices_total);
        triangles.resize(triangles_total);

        for (unsigned int i = 0; i < vertices_total; ++i)
            vertices[i] = {coords[i * 3], coords[i * 3 + 1], coords[i * 3 + 2]};

        for (unsigned int i = 0; i < triangles_total; ++i)
            triangles[i] = {tris[i * 3], tris[i * 3 + 1], tris[i * 3 + 2]};

        return mesh<T>(std::move(vertices), std::move(triangles));
    }
}

#endif