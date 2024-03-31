 # N64 Test Game

 Just testing libdragon. Nothing more.

## TODOs:

### Camera
* Normalize coordinate system(s). Seriously it's all over the place.
* Sort out the quaternion logic. Might be reversed?
* Make camera self-contained. Minimize use of transform outside camera related functions.
* Lerp camera position and rotation about the target.
* Extract clipping planes from camera frustum for culling.

### Renderer
* Implement scene graph and queues.

### Entities
* Pivot early torwards either ECS or sort out actors.

### Collision
* Implement basic collision detection and resolution.

### Assets
* Import mesh from blender
* Caches for textures and models.

### Other refactoring
* Matrix as 1D array instead of 2D.