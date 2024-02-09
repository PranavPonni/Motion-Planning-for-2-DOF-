Motion-Planning-for-2-DOF-
Robot consists of mobile base and rotates in 2D plane, with 2 DOF link mechanism. C programming.

Make a simulator for a mobile manipulator robot shown in Fig. 1. This robot consists of a mobile base that can move and rotate in a 2D plane, and a robot arm with a 2-DOF link mechanism mounted on the mobile base.
• Suppose that the robot is in the 3D space field shown in Fig. 2. The robot moves between the black dots on the grid. It can stop, turn, and collect objects only on the dots.
• Make a simulator that can perform the tasks below.

[1] First, the user places several target objects in the space. Objects can be placed arbitrarily, either on the black dots or elsewhere. Read the keyboard input or external file to obtain the number of objects and the coordinates (x, y, z) of each object.
[2] Determine if the robot can reach each object, and if not, remove it from the list.
The robot can measure the absolute position (x,y,z) of the object accurately by the sensor installed in the room.
[3]
Initially, the robot is at the home position shown in Fig. 2, facing in the x-axis direction. Once the objects that can be reached are determined, the robot moves the mobile base to the point where it can reach the first object. Then, the robot performs the reaching operation. The robot repeats this process until it has collected all the objects it can reach.
[4]
The history of each motion (coordinates and angle of mobile base, joint angles of the arm) should be recorded in a CSV file.
[5] After collecting all objects, the robot should return to the home position.
