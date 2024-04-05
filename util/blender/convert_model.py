import bpy
import bmesh
import sys
import struct
import mathutils


def vec_to_tuple(vector):
    return (vector.x, vector.y, vector.z)


def write_model_header(file, numMeshes):
    magicnum = b'\x41\x45\x4D\x46'
    file.write(magicnum)
    file.write(struct.pack('B', 1)) # Version
    file.write(struct.pack('B', numMeshes))


def write_model(file):
    meshes = bpy.data.meshes
    write_model_header(file, len(meshes))

    # Transform matrix to get into right-handed coords.
    rh_mat = mathutils.Matrix(((1, 0, 0, 0),
                               (0, 0, 1, 0),
                               (0, -1, 0, 0),
                               (0, 0, 0, 1)))
    for obj in bpy.context.scene.objects:
        if obj.type != 'MESH':
            continue

        # Triangulate the mesh.
        mesh = obj.data
        m = bmesh.new()
        m.from_mesh(mesh)
        bmesh.ops.triangulate(m, faces=m.faces[:])
        m.to_mesh(mesh)
        m.free()

        # Grab the transform matrix for the object.
        tmat = rh_mat @ obj.matrix_world

        num_mats = max(len(mesh.materials), 1)
        for mat_idx in range(num_mats):
            material = obj.data.materials[mat_idx]
            if not material:
                continue
            write_mesh(file, mesh, tmat, mat_idx, material)


def write_mesh(file, mesh, tmat, mat_idx, material):

    # For now just export as flat array of interleaved verts and indices.
    unique_vertices = {}
    indices = []

    for poly in mesh.polygons:

        # Skip over polys that aren't using the same material index. Write these out to separate meshes.
        if poly.material_index != mat_idx:
            continue

        for loop_idx in poly.loop_indices:
            vertex = mesh.vertices[mesh.loops[loop_idx].vertex_index]
            uv = mesh.uv_layers.active.data[loop_idx].uv

            # Make unique key
            vertex_world = tmat @ vertex.co
            key = (vec_to_tuple(vertex_world), (uv.x, uv.y), vec_to_tuple(vertex.normal))

            # Check if vertex already in list otherwise append the new one.
            if key in unique_vertices:
                index = unique_vertices[key]
            else:
                index = len(unique_vertices)
                unique_vertices[key] = index
            indices.append(index)

    # Make interleaved vertex array.
    interleaved_vertices = []
    for key, index in unique_vertices.items():
        vertex_data = [*key[0], *key[1], *key[2]]  # Position, UV, Normal
        interleaved_vertices.extend(vertex_data)

    # Write out material name
    mat_name = 'rom:/{}.amtl'.format(material.name)
    file.write(struct.pack(">H", len(mat_name) + 1))
    file.write(mat_name.encode() + b'\x00')

    # Write out the number of vertices and indices
    numVertices: int = int(len(interleaved_vertices) / int(8))
    file.write(struct.pack(">H", numVertices))
    file.write(struct.pack(">H", len(indices)))

    # Now write the vertices and indices.
    for vertex in interleaved_vertices:
        file.write(struct.pack('>f', vertex))  # Write as floats (pos, uv, normal)
    for index in indices:
        file.write(struct.pack('>H', index))  # Write as uint16.


def main():
    bpy.ops.object.mode_set(mode="OBJECT")
    print(sys.argv[-1])
    with open(sys.argv[-1], 'wb') as file:
        write_model(file)


# Execute from entry point
# TODO: Change structure. Gather meshes before exporting.
main()