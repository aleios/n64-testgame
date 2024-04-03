import json
import sys
import struct


def write_material_header(output_file):
    magicnum = b'\x41\x4D\x54\x4C'
    output_file.write(magicnum)
    output_file.write(struct.pack('B', 1))  # version


def write_material(input_fname, output_fname, input_file):
    # Read json
    data = json.load(input_file)

    # Write to binary file.
    with open(output_fname, "wb") as output_file:
        write_material_header(output_file)

        # Depth test enable
        depthTestEnable = data.get("depth_test", True)
        output_file.write(struct.pack('B', depthTestEnable))

        # Depth write
        depthWriteEnable = data.get("depth_write", True)
        output_file.write(struct.pack('B', depthWriteEnable))

        # backface culling
        cullFaceEnable = data.get("cull_faces", True)
        output_file.write(struct.pack('B', cullFaceEnable))

        # Texture
        texture = data.get("texture", "")
        texture = texture.replace(".png", ".sprite")
        texture = "rom:/" + texture
        print(texture)
        output_file.write(struct.pack('>H', len(texture) + 1))
        if len(texture) > 0:
            output_file.write(str.encode(texture) + b'\x00')


def main():
    input_fname = sys.argv[-2]
    output_fname = sys.argv[-1]
    print("Input: ", input_fname, "\nOutput: ", output_fname)
    with open(input_fname, "r") as input_file:
        write_material(input_fname, output_fname, input_file)


main()
