<i>Melanie-II was developed by Alejandro Alonso on April 2004. This robot won the Hispabot 2004 National Robotics Contest at Spain.</i><br />
<i><br /></i>
<br />
<div class="separator" style="clear: both; text-align: center;">
<a href="http://3.bp.blogspot.com/-hSt7XJFvGQI/UuOc7CX2FVI/AAAAAAAAJZI/fP64a4bHnh8/s1600/mel2c.jpg" imageanchor="1" style="margin-left: 1em; margin-right: 1em;"><img border="0" src="http://3.bp.blogspot.com/-hSt7XJFvGQI/UuOc7CX2FVI/AAAAAAAAJZI/fP64a4bHnh8/s1600/mel2c.jpg" height="287" width="400" /></a></div>
<br />
Melanie is an hexapod robot of 3 degrees of freedom by leg, that by the novel design of legs it has, can transport several kilograms on its body without electrical power overload.&nbsp;The tests in laboratory have shown their capacity to rise and to walk at least with 4'5kg of additional charge, twice its own weight.<br />
<br />
<div class="separator" style="clear: both; text-align: center;">
<object class="BLOGGER-youtube-video" classid="clsid:D27CDB6E-AE6D-11cf-96B8-444553540000" codebase="http://download.macromedia.com/pub/shockwave/cabs/flash/swflash.cab#version=6,0,40,0" data-thumbnail-src="https://ytimg.googleusercontent.com/vi/sboOQ4rsUIg/0.jpg" height="266" width="320"><param name="movie" value="https://youtube.googleapis.com/v/sboOQ4rsUIg&source=uds" /><param name="bgcolor" value="#FFFFFF" /><param name="allowFullScreen" value="true" /><embed width="320" height="266"  src="https://youtube.googleapis.com/v/sboOQ4rsUIg&source=uds" type="application/x-shockwave-flash" allowfullscreen="true"></embed></object></div>
<div class="separator" style="clear: both; text-align: center;">
<i>Melanie-II carrying 4 bricks of milk</i></div>
<div>
<div style="text-align: center;">
<i><br /></i></div>
The version II that is showed in this technical report is an evolution of <b><u><a href="http://automacomp.blogspot.com.es/2004/03/melanie-v10-robust-hexapod-robot-of-3.html">Melanie-I</a></u></b>, to which some interesting capacities have been added, like the direct programming, the generation of movements by<br />
displacement of waves combined with inverse kinematics, or the capacity to walk on rough terrain.<br />
<div class="separator" style="clear: both; text-align: center;">
<br /></div>
<div style="text-align: center;">
<object class="BLOGGER-youtube-video" classid="clsid:D27CDB6E-AE6D-11cf-96B8-444553540000" codebase="http://download.macromedia.com/pub/shockwave/cabs/flash/swflash.cab#version=6,0,40,0" data-thumbnail-src="https://ytimg.googleusercontent.com/vi/cWKl-8FBR9Y/0.jpg" height="266" width="320"><param name="movie" value="https://www.youtube.com/v/cWKl-8FBR9Y?version=3&f=user_uploads&c=google-webdrive-0&app=youtube_gdata" /><param name="bgcolor" value="#FFFFFF" /><param name="allowFullScreen" value="true" /><embed width="320" height="266"  src="https://www.youtube.com/v/cWKl-8FBR9Y?version=3&f=user_uploads&c=google-webdrive-0&app=youtube_gdata" type="application/x-shockwave-flash" allowfullscreen="true"></embed></object></div>
<div class="separator" style="clear: both; text-align: center;">
<i>Melanie walking over rough terrain</i></div>
<br />
There is a version III with superior capacities. Complete information could be obtained here: <b><u><a href="http://automacomp.blogspot.com.es/2004/09/melanie-iii-robust-hexapod-robot-of-3.html">Melanie-III</a></u></b><br />
<div>
<br /></div>
Some basic characteristics that define Melanie-II are the following:<br />
<br />
<i><u>Mechanics</u></i><br />
<ul>
<li>Size (cm): 33 x 31 x 20</li>
<li>Weight: 2.1 Kg</li>
<li>Structure of PVC and Aluminum</li>
<li>6 Legs. 3 degrees of freedom by leg.</li>
<li>Design of legs optimized to diminish consumption and to maximize power&nbsp;</li>
<li>Driven by radio control servos (Twelve of 3kgcm and six of 5kgcm)</li>
</ul>
<i><u>Electronics</u></i><br />
<ul>
<li>Servos control circuit with speed management, controlled via serial port.</li>
<li>I/O circuit, with 28 A/D conversion ports and 8 digital I/O. All chips are controlled via I2C bus. Measurement of the position of the 18 servos taking the signal of their potentiometers. Measurement of the consumption of energy of the servos by measuring the voltage drop in resistances of ½ ohm.&nbsp;</li>
<li>Battery of 6v NiMH 3300mAh for the servos</li>
<li>Battery of 9v NiCd for the control electronics</li>
<li>Distance measurement infrared sensor located at the front and able to be oriented</li>
</ul>
<i><u>Programming</u></i><br />
<ul>
<li>Control program in PC developed in Visual C++ 6.0</li>
<li>Movement sequence recording via direct programming</li>
<li>Movements generation by displacement of three simultaneous waves and use of inverse kinematics algorithms.</li>
<li>Detection of obstacles on the ground by detection of the variation in the current consumption and adaptation of the legs and trajectories to resolve it.</li>
</ul>
<br />
In this work there will be mention to all the mechanical, electronic and programming aspects, as well as conclusions of the experience.<br />
<br />
<div style="-webkit-text-stroke-width: 0px; color: black; font-family: 'Times New Roman'; font-size: medium; font-style: normal; font-variant: normal; font-weight: normal; letter-spacing: normal; line-height: normal; margin: 0px; orphans: auto; text-align: start; text-indent: 0px; text-transform: none; white-space: normal; widows: auto; word-spacing: 0px;">
