Motion blur was backwards - as it it literally blurred the 
exact opposite direction it should - and applied regardless 
of distance from the player, now it applies on close objects 
more than far objects based on the square of the distance.

To install, just pick whether you want the weapon to be blurred
or not, and use the gamedata directoy in that folder.

In the console, the recommended setting is mblur 0.15. You can
play around with the values until you reach your desired strength,
between 0 (no blur) and 1 (strong blur).

In Anomaly_Shader.h, you can adjust the mblur sample count,
currently set at 16 (originally was 12). If you desire yet stronger
blur, you can also increase the mblur_clamp value, although be aware
that small changes to this value result in large amplification 
of motion blur.