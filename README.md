I created this project to simulate the behavior of space-time, blackhole and gravity.<br>
A blackhole is massive, its mass is equal to 2.6 billion solar masses, or 2.6 billion suns.<br>
It's so massive that we can’t see it because the gravitational pull is so strong, there is so much matter in there that any light that is traveling towards it,
once it in certain proximity can no longer escape it. This proximity is called the event horizon.<br>
The radius of a blackhole, or the distance between the center of the blackhole and the event horizon is called the Schwarzschild radius.
Schwarzschild radius is 2 * the universal gravitational constant (G) * mass of the blackhole(M) / square(c) where c is the speed of light. <br>
The accretion disk is all the matter that is orbiting the black hole. Its 3 times the Schwarzschild radius.
At 1.5 times the Schwarzschild radius is where the light will orbit is where the photons orbits.<br>
So when light hits the blackhole (travel towards the blackhole), they temporarily bend around the photon orbit and then either spiral in and die in the blackhole
or they spiral out and just go out.<br>
So the question is, are they bending? Or are they simply traveling in a straight line through the curve of space-time?
So now we can think about why the space-time bends around a supermassive object.<br>
This project is clearly out of the scope of the Theory of relativity. 
This is just simulating the behavior of photons (beams of light), and other matter and how they might behave in the presence of a black hole.<br><br>


We have the following cases here:<br>

If it is traveling towards the blackhole, all particles, including light should get sucked-in by the blackhole.<br>
If outside the photon orbit, ie the grey area or the accretion disk, the matter orbits, the light particles bends.<br>
If inside the red area(photon orbit), matter objects get absorbed and die, this is event horizon past which nothing can escape.<br>
In the red area (photon orbit) only light can orbit as light has no mass, but in the grey area (accretion disk), the matter can also orbit.<br>
The photon sphere is an unstable orbit, ie eventually all the light particles will either fall in the black hole or spiral out and head off to infinity.<br>
<br>

Working Theory<br>

• Simulated the behavior of light particles, gravity & other matter around the Schwarzschild blackhole using C++ & SFML. <br>
• Created objects using SFML Texture and Sprites. Simulated the bending of light particles through space-time curve by
programming the equation of circle with the angular speed, radial acceleration & the angle of rotation.<br>
• Simulated the gravitational-pull by programming a Spaghettification or “noodle effect” of planets and other heavy bodies. <br>
This is achieved by increasing the movement and the width and decreasing the height of the Sprites at the same time.<br>


Demo<br><br>
![](blackhole.gif)

<br><br>
<b>Behaviour of the light particles.<b>
  
  At the beginning of the video, we can see that the light particles that are traveling towards the event horizon are sucked in instantly. <br>
  The light particle traveling towards the red region (photon orbit) orbits around and eventually falls into the blackhole.<br>
  The light particle in the grey region (accretion disk) temporarily bends and orbits around the accretion region and eventually spirals in the red region, once it's pulled in the red region it spirals out and heads off to infinity.
  
