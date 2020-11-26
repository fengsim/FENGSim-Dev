For webGL’s transition, we need to look at: World space, Model Space, view space, model view, clip space, NDC space and Windows space.  
  
**World Space:** 

World space is where all the models in the system are. It can be referenced to when we perform the matrices’ transition. We can call the coordinate system in the World Space World Coordinate System. We normally use the world coordinate system to express an object. 


Figure 1: The world coordinate system is represented by a matrix as an identity matrix
 
**Model Space:** 

Model space in a world space can be interpreted as an object such a house or a person in the universe. Taking the house as an example, The x-axis is where the house is facing, and the x and y axis represent the horizontal and vertical axis, with these axis, we can build a coordinate system. We can use this coordinate system to make and describe the house’s model space. This model space can be called a model coordinate system. 


Figure 2: Coordinate system representation: Black - World Coordinate System, Grey - Model Space Coordinate system


Model Transformation: By default, the model coordinate system will be at the world coordinate system’s origin, and the axis will be the same as the world coordinate systems. We can perform scaling, translating, rotating to move the models around. Under these situations, the model and the model coordinates will be changed with respect to the world coordinate system. 


**View space:**

The view space concept can be interpreted as viewing the matrices from the view of a camera or a viewer. The view space can be expressed as the coordinates from the world space mentioned above. From the camera’s point of view, the view x and y axis  represents the camera’s horizontal and vertical movements, the z axis represents the depth of the camera. Thus the object or matrices with z axis coordinates that are positive are behind the camera, thus making them not visible for the viewers to see.  

Figure 3: Sample view space representation from a camera 

**Model view:**

When we render a model, normally we start off by transforming the model from model space to world space, and then from world space to view space. For both of the transformations we have the corresponding transformation matrices: the model matrix and view matrix. We can combine the matrices and form a compound matrix, and we call this compound matrix a Model view matrix. From the model view matrix, we can transform the end points of the model from the model space to the camera’s view space. There are two main benefits:    
If there are many models in the world space, and each model has many end points. Then it is more efficient to transform the endpoints to the view-space at once by using a compound compared to doing two matrices transformations. 


Since a space can be infinitely sized, the process of transforming the end points from model space to world space requires different （accuracy to calculate). This mainly relies on the distance between the end points from the world space’s origin. Similarly, when we transform the end points from world space to view space, the processing accuracy relies on the distance between the endpoint and the camera. Thus it will make sense to take high accuracy calculations when the endpoints are close the the camera, but it would not when the endpoints got distance between the camera because the possibility of loss of accuracy. When the model and camera are close to each other, and both of them are far away from the origin of world space, loss of accuracy can be a result of two space transformations. Thus having a compound matrix can increase accuracy. 
Clip space: The camera cannot capture everything in the space. Each camera will specify a perspective, the perspective sets what a camera can see, every model in the camera’s perspective will be preserved; and every model outside of the perspective will be deleted. The models lying on the border of the camera’s perspective will be clipped, the parts that's in side the perspective will be saved, the parts that's outside of the perspective will be deleted, this process is called clipping. 


The perspective mentioned above refers to an area surrounded by 6 planes, these planes are called clip planes. In those, two of the planes are rather important, they are perpendicular to the camera's direction. The plane that's further away from the camera is called far clip plane, the closer one is called near clip plane. These two planes decide the depth of the camera’s vision. 
Clip transformation: The process of transforming an endpoint from view space to clip space is called clip transformation, we can achieve this from a clip matrix. 

**NDC Space**

Because of the vass number of different resolutions there are in the market, it is hard to accommodate for every resolution. To overcome this problem, we transform endpoints to standard device space before rendering them to the screen. 
For orthographic projection, every endpoint’s coordinates in clip space are between [-1, 1], under these conditions, there is not a need for transition, the clip space itself is NDC Space.


For point projection, we only need to normalize the homogeneous coordinates in clip space. Making its w weight 1, and then the x, y, z values will be between [-1, 1]. Under these conditions, the normalization process is the process of transforming the endpoints from clip space to NDC Space.
Before normalizing the weight w is proportional to the distance between the endpoint and the camera. So, the further away the endpoints are from the camera, the bigger the w values. When w are bigger, after normalization, x, y, z are smaller. This way we can achieve the perspective shrinkage and projection effects. The normalization process is the projection process. 

**Window Space:**

This means the display area on a screen. The window space doesn’t only depend on the screen resolution or the window size, the window’s position on the screen is important as well. This is because in NDC space, every endpoint’s value is between [-1, 1], so no matter what the window space looks like, we can project the endpoints on the specific parts of the screen. 


