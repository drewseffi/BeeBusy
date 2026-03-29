# Notes

## To-Do

- Spawn plant pots randomly [DONE]
- Ability to get flowers from box [DONE]
- Ability to plant flowers [DONE]
- Score system [DONE]
- Bees speed up based on number of bees passed [DONE]
  - Algorithm for bee speed [DONE]
- More bees spawn based on number of bees passed [DONE]
  - Algorithm for bee spawns [DONE]
- Power-up spawning
- Ability to pick up power-ups
- Power-ups give buffs
- Player animations
- Bee animations
- Power-up animations
- Seed sound
- Pot sound
- Bee sounds (Maybe)
- Power-up sounds 

## Bugs

Number of bees passed is wrong on laptop build [FIXED]
-- Was a problem with defining `this->var = var` leading to the program allocating a random point in memory to the variable. Always define correctly in the constructor.

Score not centered on game over screen


## General

Don't load textures in objects that will get cloned

Always define correctly in the constructor or face the consequences of random memory being used

When doing `for (auto var : vars)` always use a reference to avoid copying large objects
