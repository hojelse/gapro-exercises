# Exercise 8

For you exercise to be evaluated, it must be able to be run following these steps:

Drag and drop the submission folder inside SimpleRenderEngineProject
Add submission folder as subdirectory in SimpleRenderEngineProject/CMakeLists.txt Please check that this is possible before submission, if not we will notify you.

![main](media/main.png)

# 8.1 Controlling the bird
See `ComponentController` in the game section of the project
- Apply an appropriate constant linear velocity to the bird,
  to make it move to the right at constant speed
- On spacebar press, apply an appropriate upwards inpulse

# 8.2 Create wall colliders
See `ComponentSpawner` in the game section of the project
- Create a collider for the floor
- The walls should not move or rotate on space, only the bird
  (keep in mind that the camera is locked on the bird, so it will look like the opposite, but it's normal)
- (optional) End the game when the bird collides with a wall or floor
To show a debug draw of the physic bodies, press F2

# 8.3 Spawn pickups
See `ComponentSpawner` in the game section of the project
- Spawn coins (following a similar appropach to the walls)
- The coins should not overlap walls
- When the bird collides with a coin, the latter should disappear
- The bird velocity and position should not be affected by the coins in any way
You can create a new `ComponentPickup` to handle the despawning, or you can trigger it from the general controller
