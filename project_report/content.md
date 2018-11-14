### 1. Introduction

Experimentation forms one of the two pillars of scientific methodology. It serves as a way to validate theoretical conclusions and poses new problems to be solved. As experiments begin to mature, diving deeper into the complexity of underlying phenomena, the delicacy with which  they need to be carried out also increases. This demands for more precision in the measurement techniques employed. While a great amount of precision can be acheived with human faculties alone, sometimes the requirement far exceeds our limitations. Also, it consumes a lot of time, which could otherwise be invested in analysis and interpretation of the result.

This is where computers and computer-controlled machinery become useful. Their capability of carrying out fine adjustments and measurements much more efficiently makes them favourable for various applications in modern laboratories. For instance, computer controlled stepper motors are a type of motion-control positioning system used in CNCs. In the field of lasers and optics they are frequently used in precision positioning equipment such as linear stages, rotation stages, goniometers, etc.[1] Such devices are usually quite expensive, making them common only in advanced research laboratories. Still, moderately precise stepper motors are commercially available, and, with a bit of C programming, can be controlled using a cheap Arduino board equipped with a microcontroller. This opens up a wide range possibilities to manually build precision tracking instruments in smaller labs with less expensive equipments.

This project aimed to explore this possibility to construct a precision-rotation assembly using a stepper motor and other parts, for controlling the hand-operated Brewster Angle experiment apparatus.

### 2. Background

The aim of the OS8 - Polarization & Brewester's Angle experiment[2] of the Lab course is to study the phenomenon of optical polarisation. The objectives are to find the Brewster's Angle for a given interface (and hence find it's refractive index), and to validate Fresnel's equations by plotting the variation of reflection coefficient for the interface with angle of incidence. The experimental procedure involves measuring the intensity variations of a LASER beam refltected off the surface of a given sample, using a detector mounted on a hand rotated goniometer.[3]

While doing this experiment, I noted the following drawbacks to the apparatus:

* Inaccuracy of the rotating assembly: the precesion depended on the experimenter.
* Usage of a small area photodiode: ideally the total intensity needs to be measured, which require a large area photo diode; so I opted to measure the intensity at the brightest point on the spot. But now it took a long time to track the brightest point on the beam manually.
* Lack of precision and short range of the measurement unit: the device has a least count of single decimal place, and a range of 0 - 200mA / microA depending on the sensitivity used. This  resolution was found to be inadequate at low intensities. At high intensities the unit overflowed.


The IS1 - Stepper motor experiment[4] is aimed to build an understanding of the basic operation of a computer controlled bipolar stepper motor. The main objective here is to learn how to program an Arduino to generate the digital waveform necessary to drive the stepper motor. Different programs are developed that explore various features of the Arduino like outputting digital pulses, reading analog input, and responding to a sensor signal.

The rotation of the stepper motor can be controlled with fine precision. The analog input of the Arduino has a range of 0 - 5V with a least count of 0.00489 V at its analog input terminal. The stepper motor can precisely control the goniometer of the Brewster Angle apparatus; meanwhile the Arduino can continuously monitor the detector output with high resolution and determine the maximum obtained intensity with simple logic. Thus, this simple experiment has the potential to remedy the aforementioned drawbacks of the Brewster Angle apparatus, which lay the inspiration for this project.

### 3. Proposal

The central objectives of this project were:

1. To construct an electronic circuit to translate the detector output to Arduino's analog input;
2. To build a mechanical assembly needed to transmit the torque of rotation of the stepper motor to the goniometer; and
3. To program the Arduino with necessary logic to control the whole assembly.

At the onset itself it must be made clear that this project did not aim to build a commercial-grade equipment to be permenantly attached to the Brewster Angle apparatus. Instead, it should be considered as a just a demonstration of the larger real-life application of the stepper motor device.

#### 3.1 Design decisions

Inorder to achieve the above proposals, foremost the second objective (which required to construct physical hardware), two approaches could be followed:

* Design all the moving parts of the assembly, purchase necessary items and make a dedicated hardware with the help of the department workshop.
* Utilise whatever mechanical components available in the M.Sc. Labs to construct the assembly, which can be dismantled and returned back to their sources after use.

Owing to the time constraints on the project, I chose to follow the latter, do-it-yourself approach. This allowed me to jump right into the implementation of the project without delay, gave immediate feedback about what worked and what didn't, and liberated me from any dependecy on external sources to explore on my own.

#### 3.2 Expected challeges

This posed the challenging part of the experiment, which was engineering the moving parts myself, which involved handling mechanical devices like gears, belts, pulleys, etc. As I resolved to reuse existing lab equipments, I was also required to modify the main components in a non-permanent fashion. I decided on a trial-and-error approach to arrive at a working solution.

### 4. Experiment

#### 4.1 Understanding the detector

The detector of the Brewster Angle apparatus uses a photodiode[4] as its sensor. The output is fed into the measurement unit via a universal 3.5mm audio jack-and-plug connection. The photodiode is operated in photoconductive mode[5], with the measurement unit providing a biasing voltage of 5V via the same connection (this was determined using a multimeter and a spare 3.5mm plug). The unit then internally measures the current that flows in the circuit. When no light is incident on the photodiode, its resistance is very high (~~"M"Omega) and almost no current flows in the circuit. When it is exposed to light, its resistance decreases and the current increases.

This operation of the photodiode was replicated using the circuit given in fig. 1. The biasing voltage was taken from the built-in 5V DC output pin of the Arduino itself, eliminating the need for an external voltage source. As the Arduino could measure only analog voltage values, a variable shunt resistance was connected in series with the photodiode, the voltage across which was fed into the Arduino's analog input pin. Hence the Arduino recorded light intensities as voltages. The range of voltage measurements can be fine tuned by adjusting the variable resistance.

<center>

![Figure 1]()
</center>

The sensor value was monitored using the Serial output monitor of the Arduino software.

#### 4.2 Attaching the rotating assembly on the goniometer

This turned out to be the most challenging part of the project, and took the lion share of time to complete. The hand-operated goniometer of this particular apparatus does not feature a circular cross section for attaching a rotating component, neither was it designed to ever have such an addition. The asymetric rectangular shape of the component made attaching a convoyer belt impractical as well. In the end I had to pull apart the instrument to find a spot to fix a circular rotating wheel as a separate layer.

Fig. 2 shows the circular ring with a toothed belt overlay along its circumference, made out of an old laser holder. On the ring is attached a holder like arrangement for attaching it to the goniometer. The assembly is mounted just below the goniometer, turning the later along with it.

<center>

![Figure 2]()
</center>

#### 4.3 Torque transmission shaft

The bipolar stepper motor used in the experiment has a full-step resolution of 1.8^@. This is too large for precise rotation of the goniometer. Driving the stepper motor in half-step mode gives a precision of 0.9^@ which is still not small enough for precision rotation. Furthermore, half-stepping reduces the torque supplied by the motor. So I decided to use combinations of gears to reduce the resolution futher. This was the motive behind attaching a toothed belt around the rotating wheel attached to the goniometer. A gear approximately fitting the teeth of the belt was procured from M.Sc. Electromagnetics Lab.

##### 4.3.1 First model

At first the gear was directly attached to the vertically oriented stepper motor. This was then brought in contact with the goniometer wheel. The gears fairly transimitted the motion and the motor was able to provide enough torque to rotate the goniometer. Rough trials were successful in positioning the detector at the spot of the beam using the C program logic (discussed in 4.4 below). Photographs of the arrangement are given in Fig. 3.

<center>

![Figure 3]()
</center>

The gear ratio for the arrangement was calculated to be approximately 3:1, thus bringing down the resolution to ~~0.6^@. This resolution is still impractical for precise rotation, necessitating a better model. As the output gear was already fixed, the only solution was to make the input gear as small as possible. But such smalls gear were not available.

##### 4.3.2 Improved model

The screw of the horizontally aligned stepper motor has a very fine pitch of ~~1.5mm per revolution. If the linear motion of the screw could be transformed back into rotation, it could make a very good driver gear that would greatly improve the gear ratio. There was a second gear of finer cogs, which fitted perfectly with the thread of the horizontal screw. So I decided to combine the two available gears onto a single shaft that would transmit the linear motion of the horizontal screw into rotation of the wheel attached to the goniometer (fig. 4).

<center>

![Figure 4]()
</center>

The combined gears thus effectively became a _double reduction gear_[6]. Instead of direct calculation, the total reduction of the gear chain was estimated by comparing the rotations of the screw and the goniometer. It turned out to be ~~360:1, i.e. one full revolution of the screw produced merely 1^@ deflection of the goniometer. Thus the resolution of the assembly reduced to nearly 1.8^@/360 which is equal to 0.005^@ or 0.3 arc min. This is over three times finer than the resolution achievable by hand operation of the device.

#### 4.4 Controlling program and logic

Except for the tracking and sensing algroithm, the C program written for the Stepper motor experiment was reused _as is_ for the project. The tracking algorithm used is a simple linear search for the maximum value of detected intensity. The relevant parts of the code with comments are given below.

#### 4.5 Fixing the final assembly on the breadboard

The optical bench along with the stepper motor table was finally mounted on an optical breadboard. Holders were used to fix them to the board to prevent wobbling and facilitate stable operation. The final configuration was as shown in fig. 5.

<center>

![Figure 5]()
</center>

### 5. Result and Discussions

The whole assembly mostly functioned as expected, apart for some minor irregularities in the motion which could be improved by better engineering. Succesive scans were made for a small range of angles of incidence. The console output showing peak voltages detected during each scan is shown in fig. 6. Clearly the Arduino is able to record the intensities at a finer precision, wider range and at a smaller least count. This would allow to plot a smoother intensity-vs-angle curve than the original experiment. Unfortunately the entire Brewster Angler experiment  could not be redone with the improved equipment due to the time contraints on the project. 

<center>

![Figure 6]()
</center>

A second time, the smooth variation of the detector output as it was made to scan slowly through the laser beam spot was recorded in the Arduino's serial plotter. The plots (which should ideally be Gaussians) for three different scans are shown in fig. 7. Instead of the peak value, the total area under the curves can be taken as a better measure of the total intensity of light received by the detector.

<center>

![Figure 7]()
</center>

### 6. Conclusions

The project turned out to be much more challenging to implement than expected. Still an acceptable solution was obtained after much deliberation and trials. As already mentioned, the engineering is far from ideal, but the constructed precision-rotation assembly has satisfactorily served the original purpose, which was to get a flair of the real-world application of computer controlled electro-mechanical machinery.

Even though the mechanical drawbacks of the apparatus has been resolved by this project, the optical drawbacks related to the polarisation of the LASER beam and calibration of the polariser[7] still persists. Some solution needs to be employed to overcome those issues, which is yet to be explored. Only with that in place along with the precision-rotation system, the Brewster Angle experimental setup can be considered to have the fineness required for ultra-precise meaurement.

### References

### Acknowledgement
