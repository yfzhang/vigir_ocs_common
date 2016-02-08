#!/usr/bin/env python
# Lucas Walter
# Feb 2016
# publish a flattened cube as a shape_msgs/Mesh

import rospy

from geometry_msgs.msg import Point
from shape_msgs.msg import Mesh, MeshTriangle

rospy.init_node('square_mesh')
mesh = Mesh()

for y in range(-1, 2, 2):
    for x in range(-1, 2, 2):
        pt = Point()
        pt.x = x
        pt.y = y
        pt.z =  0.0
        mesh.vertices.append(pt)

tri = MeshTriangle()
tri.vertex_indices[0] = 0
tri.vertex_indices[1] = 1
tri.vertex_indices[2] = 2
mesh.triangles.append(tri)

tri = MeshTriangle()
tri.vertex_indices[0] = 1
tri.vertex_indices[1] = 3
tri.vertex_indices[2] = 2
mesh.triangles.append(tri)

pub = rospy.Publisher("square_mesh", Mesh, queue_size=1)

rate = rospy.Rate(1)

while not rospy.is_shutdown():
    pub.publish(mesh)
    rate.sleep()
