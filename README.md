# 3D-Puppet-Manipulation
Here’s an expanded description that captures all the functionality of your 3D puppet project:

---

**3D Puppet Animation Project**

This project is a 3D puppet simulator developed in C++, providing an interactive experience where users can control and animate a 3D puppet model. The program offers various commands for manipulating the puppet's limbs and torso, as well as controlling the camera and lighting. 

The 3D puppet simulation includes a menu for user interaction, which offers the following options:

1. **Run!**
   - Starts the puppet in a running motion. The puppet is only capable of running, unable to walk, so this command initiates a rapid motion animation.

2. **Stop Running**
   - Halts the puppet's running animation. While the puppet may not stop immediately, this command signals it to eventually cease running and come to a stop.

3. **How do I...**
   - Provides information about the keyboard commands available to control different parts of the puppet, allowing for customized movements and animations of the limbs, torso, and more. Each key command corresponds to a specific action for greater control and flexibility.

4. **Bye~**
   - Exits the program, signaling the end of the interaction with the puppet.

### Keyboard Controls for Puppet Movement

Each keyboard command is mapped to a specific movement for the puppet’s limbs and body. This allows users to perform detailed animations through individual joint rotations:

- **Arm Movements**
  - `"q", "Q"`: Rotate the left upper arm backward and forward at the shoulder joint.
  - `"w", "W"`: Rotate the right upper arm backward and forward at the shoulder joint.
  - `"e", "E"`: Rotate the left forearm downward and upward at the elbow.
  - `"r", "R"`: Rotate the right forearm downward and upward at the elbow.

- **Torso Movements**
  - `"y", "Y"`: Rotate the torso to the left about the waist.
  - `"u", "U"`: Rotate the torso forward and backward about the waist.

- **Leg Movements**
  - `"a", "A"`: Rotate the left upper leg backward and forward at the hip joint.
  - `"s", "S"`: Rotate the right upper leg backward and forward at the hip joint.
  - `"d", "D"`: Rotate the left lower leg downward and upward at the knee.
  - `"f", "F"`: Rotate the right lower leg downward and upward at the knee.
  - `"g", "G"`: Rotate the left foot backward and forward at the ankle.
  - `"h", "H"`: Rotate the right foot backward and forward at the ankle.

### Camera and Lighting Controls

Users can adjust the camera perspective and lighting in the scene to create dynamic and customized viewpoints:

- **Camera Movement**
  - `Key_UP`: Rotate the camera upward.
  - `Key_DOWN`: Rotate the camera downward.
  - `Key_LEFT`: Rotate the camera to the left.
  - `Key_RIGHT`: Rotate the camera to the right.

- **Lighting Adjustments**
  - `"k", "l"`: Rotate the lighting around the X-axis to illuminate the puppet from different horizontal angles.
  - `"o", "p"`: Rotate the lighting around the Y-axis to create different vertical lighting effects.

---
