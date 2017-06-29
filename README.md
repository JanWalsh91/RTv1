# RTv1
Rtv1 - My First Ray Tracer (super awesome parser included!)

Requirements for this proect were:

- Implementing ray tracing method to generated computer images.
- Use parametric equations to determine ray itnersections with spheres, planes, cylinders and cones.
- Be able to modify object position, direction/rotation, and size.
- Use Lambertian method(diffuse shading)
- Use Phong-Blinn method (specular lighting)
- Handle shadows.
- Handle muliple colored lights.
- Have a file that defines objects, lights and the camera(s) which is parsed at the beginning of the program.

Here is a simple file which will be parsed by my program: 
```
#comments start with a hashtag
scene: scene1
{
	resolution: 1200, 1200
        #ambient lighting coefficient:
	ka: 0.01
	camera: cam
	{
		position: 0, 2, -13
		direction: 0, 0, 1
	}
	light: light1
	{
		position: 15, 2, -10
		intensity: 20
                #default color if not provided is white
	}
        #object names are optional
	sphere:
	{
		position: 0, 2, 4
		radius: 2
                #colors can be added by name, hex code, or three ints representing RGB values.
		color: razzle dazzle rose
                #specular coefficient:
		ks: 0.02
		specular exponent: 40
	}
}
```
Here is the output of the file above:
![Rendu 1](https://github.com/JanWalsh91/RTv1/blob/master/screenshots/Rendu_1.png)
Enjoy some other cool pictures!
![Rendu 5](https://github.com/JanWalsh91/RTv1/blob/master/screenshots/Rendu_5.png)
![Rendu 6](https://github.com/JanWalsh91/RTv1/blob/master/screenshots/Rendu_6.png)
![Bonus_4](https://github.com/JanWalsh91/RTv1/blob/master/screenshots/Bonus_4.png)
Inside a Cylinder with about a dozen lights:
![Bonus_5](https://github.com/JanWalsh91/RTv1/blob/master/screenshots/Bonus_5.png)
