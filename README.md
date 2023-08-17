<html>

<head>
<meta http-equiv="Content-Language" content="es">
<meta name="GENERATOR" content="Microsoft FrontPage 4.0">
<meta name="ProgId" content="FrontPage.Editor.Document">
</head>

<font size="4"><b><i>Melanie-II&nbsp;</i></b></font>
      <p>By Alejandro Alonso Puig<br>
      April 2004<br>
 
<hr>
<i>Melanie-II was developed by Alejandro Alonso on April 2004. This robot won the Hispabot 2004 National Robotics Contest at Spain.</i><br />
<i><br /></i>
<br />
<p align="center"><img border="0" src="http://3.bp.blogspot.com/-hSt7XJFvGQI/UuOc7CX2FVI/AAAAAAAAJZI/fP64a4bHnh8/s1600/mel2c.jpg" width="600" ></p>

<br />
Melanie is an hexapod robot of 3 degrees of freedom by leg, that by the novel design of legs it has, can transport several kilograms on its body without electrical power overload.&nbsp;The tests in laboratory have shown their capacity to rise and to walk at least with 4'5kg of additional charge, twice its own weight. See Video with <a href="https://youtu.be/sboOQ4rsUIg">Melanie-II carrying 4 bricks of milk</a><br />
<br />
<div>
<div style="text-align: center;">
<i><br /></i></div>
The version II that is showed in this technical report is an evolution of <b><u><a href="http://automacomp.blogspot.com.es/2004/03/melanie-v10-robust-hexapod-robot-of-3.html">Melanie-I</a></u></b>, to which some interesting capacities have been added, like the direct programming, the generation of movements by<br />
displacement of waves combined with inverse kinematics, or the capacity to walk on rough terrain. See Video with <a href="https://youtu.be/cWKl-8FBR9Y">Melanie-II walking over rough terrain</a><br />
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
<br>
<br>
More information: <br>
<ul>
  <li><p align="justify"><a href="Documentation\melanie-II_doc_en.pdf">Technical documentation</a></li>
  <li><p align="justify"><a href="Melanie-II_Program">Program</a></li>
  <li><p align="justify"><a href="Media">Pictures</a></li>
  <li><p align="justify"><a href="https://github.com/aalonsopuig/Melanie-I_Hexapod_Robot.git">Repository of Melanie-I</a></li>
  <li><p align="justify"><a href="https://github.com/aalonsopuig/Melanie-III_Hexapod_Robot.git">Repository of Melanie-III</a></li>
</ul>

</body>

</html>

