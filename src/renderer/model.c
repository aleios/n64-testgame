#include "model.h"
#include <malloc.h>

struct Model* model_init(uint32_t numMeshes)
{
    struct Model* model = malloc(sizeof(struct Model));

    if(!model) {
        return NULL;
    }

    // Create display list per mesh in the model.
    model->listIds = glGenLists(numMeshes);
    model->materials = malloc(sizeof(struct Material) * numMeshes);
    model->numMeshes = numMeshes;

    return model;
}

void model_destroy(struct Model* model)
{
    if (model)
    {
        // TODO: Clean up buffer objects.
        free(model->materials);
        glDeleteLists(model->listIds, model->numMeshes);
        free(model);
    }
}

void model_render(struct Model* model) {
    for(int i = 0; i < model->numMeshes; ++i) {
        material_apply(model->materials[i]);
        glCallList(model->listIds + i);
    }
}