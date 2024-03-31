#include <malloc.h>
#include "plane.h"
#include "../math/vector3.h"
#include "../math/vector2.h"

struct PlaneVertex {
    struct Vector3 pos;
    struct Vector3 normal;
    uint32_t color;
};

struct Plane* plane_init(float size, int segments)
{
    struct Plane* plane = malloc(sizeof(struct Plane));

    plane->list = glGenLists(1);

    // Create and generate buffers.
    glGenBuffersARB(2, plane->buffers);
    glGenVertexArrays(1, &plane->vao);
    glBindVertexArray(plane->vao);

    // Make the mesh.
    uint32_t numVertices = (segments + 1) * (segments + 1);
    uint32_t numIndices = segments * segments * 6;
    plane->numIndices = numIndices;

    // Enable states.
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glBindBufferARB(GL_ARRAY_BUFFER_ARB, plane->buffers[0]);
    glBufferDataARB(GL_ARRAY_BUFFER_ARB, numVertices * sizeof(struct PlaneVertex), NULL, GL_STATIC_DRAW_ARB);

    // Attrib pointers
    glVertexPointer(3, GL_FLOAT, sizeof(struct PlaneVertex), (void*)(0*sizeof(float)));
    glNormalPointer(GL_FLOAT, sizeof(struct PlaneVertex), (void*)(3*sizeof(float)));
    glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(struct PlaneVertex), (void*)(6*sizeof(float)));

    glBindVertexArray(0);

    struct PlaneVertex* vertices = glMapBufferARB(GL_ARRAY_BUFFER_ARB, GL_WRITE_ONLY_ARB);

    const float p0 = size / 2.0f;
    const float incr = size / segments;
    for(uint32_t y = 0; y < segments + 1; ++y)
    {
        for(uint32_t x = 0; x < segments + 1; ++x)
        {
            uint32_t i = y * (segments + 1) + x;
            struct PlaneVertex* v = &vertices[i];

            v->pos.x = p0 - incr * x;
            v->pos.y = 0.0f;
            v->pos.z = p0 - incr * y;

            v->normal.x = 0.0f;
            v->normal.y = 0.0f;
            v->normal.z = 0.0f;

            v->color = 0xFFFFFFFF;
        }
    }

    glUnmapBufferARB(GL_ARRAY_BUFFER_ARB);

    // Write indices
    glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, plane->buffers[1]);
    glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB, numIndices * sizeof(uint16_t), NULL, GL_STATIC_DRAW_ARB);

    uint16_t* indices = glMapBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, GL_WRITE_ONLY_ARB);

    for(uint32_t y = 0; y < segments; ++y)
    {
        for(uint32_t x = 0; x < segments; ++x)
        {
            uint32_t i = (y * segments + x) * 6;

            uint32_t row_start = y * (segments + 1);
            uint32_t next_row_start = (y + 1) * (segments + 1);

            indices[i + 0] = x + row_start;
            indices[i + 1] = x + next_row_start;
            indices[i + 2] = x + row_start + 1;
            indices[i + 3] = x + next_row_start;
            indices[i + 4] = x + next_row_start + 1;
            indices[i + 5] = x + row_start + 1;
        }
    }

    glUnmapBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB);

    glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
    glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);

    // Compile display list.
    glNewList(plane->list, GL_COMPILE);
    {
        glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, plane->buffers[1]);
        glBindVertexArray(plane->vao);
        glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, 0);
        glBindVertexArray(0);
        glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);
    }
    glEndList();

    return plane;
}

void plane_destroy(struct Plane* plane)
{
    glDeleteBuffersARB(2, plane->buffers);
    glDeleteLists(plane->list, 1);
    free(plane);
}

void plane_render(struct Plane* plane)
{
    glCallList(plane->list);
}