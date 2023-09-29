# Exercise 5

This week you should focus on the [mandatory assignment](https://github.itu.dk/chca/GameProgramming23-Exercises/tree/main/Exercises/Exercise4),
but if you are done, or if but if you want to try and get your hands dirty with this week's topics, here are a couple of suggestions:

## Transform matricies
Get one of the previous exercises, possibly one that uses something of a GameObject/Component architecture, or the Exercise4 checkpoint,
and replace positions and rotations with matricies. You can use 2D matricies (ie, a `glm::mat3`, remember homogeneous coordinates from the lecture)
for simplicity, or 3D matricies (`glm::mat4`) if you want to avoid more rafctors in the future (spoilers!)

## Data Drive Scene Graph
Get one of the previous execises and remove the hardcoded object instantiations and initializations, reading the objects and their data from a json file instead
(remember, SimpleRenderEngine already comes bundled up with rapidjson, check the documentation or the code responsible of creating a sprite atlas to get an idea
how to use it)
