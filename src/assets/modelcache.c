#include "modelcache.h"
#include <libdragon.h>

struct Model* modelcache_load(const char* filename) {
    FILE* f = asset_fopen(filename, NULL);

    // Read and match: AEMF
    int magicNum;
    fread(&magicNum, 1, 4, f);
    if(magicNum != 0x41454D46) {
        fclose(f);
        return 0;
    }

    // Read version #
    uint8_t version;
    fread(&version, sizeof(uint8_t), 1, f);

    // Read number of meshes within the model.
    uint8_t numMeshes;
    fread(&numMeshes, sizeof(uint8_t), 1, f);

    if(numMeshes == 0) {
        fclose(f);
        return 0;
    }

    struct Model* model = model_init(numMeshes);

    // Iterate meshes
    for(uint16_t i = 0; i < numMeshes; ++i) {

        // Read number of vertices and indices.
        uint16_t numVertices;
        fread(&numVertices, sizeof(uint16_t), 1, f);
        uint16_t numIndices;
        fread(&numIndices, sizeof(uint16_t), 1, f);

        debugf("VX: %u, %u\n", numVertices, numIndices);

        // Generate device objects
        GLuint buffers[2];
        GLuint vao;
        glGenVertexArrays(1, &vao);
        glGenBuffersARB(2, buffers); // TODO: Either track these in mesh or pull from a pool... cause we ain't freeing em.
        glBindVertexArray(vao);
        glBindBufferARB(GL_ARRAY_BUFFER_ARB, buffers[0]);

        // Map data according to current assumption (Pos, UV, Normals)
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);

        // Attrib pointers
        const int sz = 8 * sizeof(float);
        glVertexPointer(3, GL_FLOAT, sz, (void*)(0*sizeof(float)));
        glTexCoordPointer(2, GL_FLOAT, sz, (void*)(3*sizeof(float)));
        glNormalPointer(GL_FLOAT, sz, (void*)(5*sizeof(float)));

        glBindVertexArray(0);

        // Read straight from file and upload vertices.
        glBufferDataARB(GL_ARRAY_BUFFER_ARB, numVertices * sz, 0, GL_STATIC_DRAW_ARB);
        void* verts = glMapBufferARB(GL_ARRAY_BUFFER_ARB, GL_WRITE_ONLY_ARB);
        fread(verts, sz, numVertices, f);
        glUnmapBufferARB(GL_ARRAY_BUFFER_ARB);

        // Read straight from file and upload indices.
        glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, buffers[1]);
        glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB, numIndices * sizeof(uint16_t), 0, GL_STATIC_DRAW_ARB);
        void* indices = glMapBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, GL_WRITE_ONLY_ARB);
        fread(indices, sizeof(uint16_t), numIndices, f);
        glUnmapBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB);
        glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);

        // List compilation.
        glNewList(model->listIds + i, GL_COMPILE);
        {
            glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, buffers[1]);
            glBindVertexArray(vao);
            glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, 0);
            glBindVertexArray(0);
            glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);
        }
        glEndList();
    }

    fclose(f);
    return model;
}

struct Model* modelcache_get(const char* filename) {
    return modelcache_load(filename); // TODO: Make actual cache.
}

void modelcache_release(struct Model* model) {
    // TODO: Implement with cache.
    model_destroy(model);
}