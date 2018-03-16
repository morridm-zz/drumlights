<!--
  Title: Blink to the beat drum lights
  Description: How to make flashing LEDs for your drum kit or drum set
  Author: David Morris
  Tags: neopixel , drum , lights , arduino , trinket , adafruit , LED , make , blink , Piezo , knock sensor, led, sound, react, how to make leds flash to music with an arduino, cassettepunk, sound , reactive 
  -->

<head>
  <meta name="author" content="David Morris">
  <meta name="description" content="Animated LED Drum Lights">  
  <meta name='keywords' content='neopixel , drum , lights , arduino , trinket , adafruit , LED , make , blink , Piezo , knock sensor, led, sound, react, how to make leds flash to music with an arduino , cassettepunk , sound , reactive '>  
  <meta name="google-site-verification" content="8z6ABWhrKxR3toUiw3lN3x8rqX0ixnN-jqz16jV6QoQ" />
</head>    
  
## Animated LED Drum Lights

My daughter and I added interactive leds to her drum set for fun and a learning experience.  This is our project we setup for us to take it from concept to reality.  

Note:  I originally used the Arduino IDE for this project but switched to [PlatformIO for VSCode](https://platformio.org/get-started/ide?install=vscode) when I updated/refactored the project for use with an Adafruit Trinket Pro 5v instead of the regular Trinket 5v.  

I was not aware of PlatformIO when I orginally started this project and stumbled opon it.  I'm so glad I did!  PlatformIO is night and day better than the Arduino IDE.  If you have not yet, make the change to [PlatformIO with VSCode](https://platformio.org/get-started/ide?install=vscode). 

- [ ] Pro(s): This is a great arduino learning project and will be awesome when implemented.
- [ ] Con(s): Expensive, when making one for every drum/cymbal in the set.  You could probably use fewer trinkets if powering from an external source instead of USB.  I thought about this later but just went ahead with one trinket per drum/cymbal.

--- 

##### Current Status

We finished the [first version](https://vimeo.com/250054557/) of the project and very happy how it worked out.  We are currently working on an upgraded version of it.  The second iteration uses adafruit trinket pro and includes a potentiometer to provide the user the ability control the sensitivity of the piezo sensor on the fly w/o additional programming, and powered via a switching power supply instead of the usb input.


| Latest Testing Video(s) |
|:---|
|[Testing sensor sensitivity and code changes](https://vimeo.com/250054557/) | 
|[New version using Trinket Pro, added an animation mode button, and a knob/potentiometer to control sensitivity of piezo sensor](https://vimeo.com/259484616) |

---
##### [Story](https://www.mountaingoatsoftware.com/agile/user-stories):
- [ ] As a drummer, she wants the drums to blink colored lights when she hits a drum, for entertainment and a wow factor.

##### [Task(s)](https://www.mountaingoatsoftware.com/blog/the-difference-between-a-story-and-a-task): 

- [ ] See our [Scrum Board](https://trello.com/tiltedworld), if you need a list of tasks to complete this project.

---

| | Diagrams |
|---|---|
| Version 1 with Trinket 5v powered via Micro USB Cable | <a href="/images/drumLightsFritzImage.png"><img src="/images/drumLightsFritzImage.png" align="left" height="300" width="600" ></a> | 
| Version 2 with Trinket Pro 5v powered by 5.5/2.1 barrel connector and [power brick](https://www.amazon.com/gp/product/B00Z9X4GLW/) - added Potentiometer (adjust piezo sensitivity) and Button for animation modes. | <a href="/images/DrumLightsUsingTrinketPro5v_frtiz.png"><img src="/images/DrumLightsUsingTrinketPro5v_frtiz.png" align="left" height="300" width="600" ></a> | 
| Drum sketch for reference | <a href="/images/RoughSketchOfSetup.jpg"><img src="/images/RoughSketchOfSetup.jpg" align="left" height="300" width="600" ></a> |  

---

- [ ] Click [here](http://a.co/bAPFz74) for amazon shopping list.  If you have time to wait on delivery, you might consider searching for parts on [Aliexpress](https://www.aliexpress.com/wholesale?catId=400502&initiative_id=AS_20180310142541&SearchText=potentiometer) to save money. 

---

|    | [Parts List](http://a.co/bAPFz74)                                                                                                                                               | Notes    | Qty  |
|----|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|----------|------|
|    | <a href="/images/20171225_163032-01.jpg"><img src="/images/20171225_163032-01.jpg" align="left" height="250" width="400" ></a>                                                 |          | 8    | 
| 1  | [Adafruit Trinket 5v](https://www.adafruit.com/product/1501), if not adding a POT and/or Button.  I used a [Trinket Pro](https://www.adafruit.com/product/2000) in version 2 of my build since it has more power, memory, and available pins. | 5v       | 8    |
| 2  | [Plugable 7-Port USB Hub](http://amzn.to/2iOpsIM).  I ended up including the Floor Tom in the project so get an 8-10 port instead for expansion. For my Trinket Pro version, I used barrel power connectors instead and this [brick](https://www.amazon.com/gp/product/B00Z9X4GLW/)                              | Optional | 1    |
| 3  | [Adafruit Mini Skinny NeoPixel Digital RGB LED Strip - 60 LED - WHITE](http://bit.ly/2yWCvAM) OR [ALITOVE 5m WS2812B Individually Addressable LED Strip Light 16.4ft ](https://www.amazon.com/dp/B014R5PC42/?th=1).  I like the ALITOVE better because they are cheaper and work really well.  I am [using](https://vimeo.com/259484616) them for my upgraded version of the project.  I used the circumference of the drum heads to calculate the length/number of led strips needed for drums and height of cymbal stands for cymbals.  meters of led strip needed = ( (drum * 3.14) * 0.0254 ).  e.g., 22" Bass Drum -> round( ( ( 22*3.14 ) * 0.0254 ) ) = 2 | 9-11m | 9-11 | 
| 4  | [10 Proto Boards](https://www.amazon.com/gp/product/B0778G64QZ/).                                                                                                              | Pkg 5    | 2    |  
| 5  | [Multiple colors of 22 AWG Solid Core Wire](https://www.amazon.com/gp/product/B076P5MXJJ/)                                                                                     |          | 1    |
| 6  | [Multiple colors of 22 AWG Stranded Wire](https://www.amazon.com/gp/product/B01LH1FYHO/)                                                                                       |          | 1    |
| 7  | [Micro-USB Cable](http://amzn.to/2BsBP8A)                                                                                                                                      | Pkg 10   | 1    |
| 8  | [Panasonic FC 1000uF 35v 105c Radial Electrolytic Capacitor Low ESR - Pkg 10](http://amzn.to/2AIzdQJ).  I found [these](https://www.radioshack.com/products/radioshack-1000uf-35v-20-radial-lead-electrolytic-capacitor) later which are a little cheaper.             | Pkg 10   | 1    |
| 9  | [Tenma Solder Wire, 0.04](https://www.amazon.com/gp/product/B008EX8KMU/)                                                                                                       |          | 1    |
| 10 | [1M 0hm resistor - Pkg 25](http://amzn.to/2yWDbWQ)                                                                                                                             | Pkg 25   | 1    |
| 11 | [470 Ohm Resistors - Pkg 25](http://amzn.to/2jEXj7z)                                                                                                                           | Pkg 25   | 1    |
| 12 | [RGBZONE 20Pairs JST SM 3PIN Plug Male to Female EL Wire Cable Connector Adapter for WS2811 WS2812B Dream color LED Stip Light](https://www.amazon.com/gp/product/B075K4HLTQ/) | Pkg 20   | 1    |
| 13 | [RGBZONE 20Pairs JST SM 2Pin Plug Male to Female EL Wire Cable Connector Adapter For 3528 5050 LED Light Strip](https://www.amazon.com/gp/product/B00T2U76V0/)                 | Pkg 20   | 1    |
| 14 | [Flex cable wrap](https://www.amazon.com/gp/product/B01095EMLI) Cable wrap in an attempt to make the wires less obvious.                                                       |          | 1    |
| 15 | [15 20mm Piezo Disc Elements - Knock Sensors](http://amzn.to/2kPogsB) | Pkg 15   | 1   |
| 16 | [I ordered these knock sensors also. I replaced my 20mm ones with these.](https://www.allelectronics.com/item/pe-49/piezo-element/1.html) | | 8 |
| 17 | [AVR Programmer](https://www.sparkfun.com/products/11801) Consider this if you need to address more than 80-90 neopixels to get access to more memory on the ATTiny85 the trinket uses.  If you have a trinket pro or trinket mo; then you do not need this. | | 1 |

---

#### Guesstimates:

|  |  |  |  |  |  |  |  |  |  |  |  | Option A | Option B | 
|:---|:---|:---|:---|:---|:---|:---|:---|:---|:---|:---|:---|:---|:---| 
| drum | diameter / length | Estimated length of LEDs needed in meters | Microcontroller (Trinket 5v) | Protoboard | Guesstimate on stranded and solid core 22awg wire used | Guesstimate on solder used | 1000uF 35V Capacitor | Piezo Sensor | JST Connectors-2&3pin | 1M 0hm Resistor | 470 0hm Resistor | Automotive LED Strip - Amazon (WS2812B) | Adafruit NeoPixels (WS2812B) | 
| Snare | 14.00 | 1.12 | $6.95 | $1.92 | $1.50 | $0.32 | $1.00 | $0.50 | $0.78 | $0.06 | $0.23 | $7.21 | $24.95 | 
| Middle Tom | 12.00 | 0.96 | $6.95 | $1.92 | $1.50 | $0.32 | $1.00 | $0.50 | $0.78 | $0.06 | $0.23 | $7.21 | $24.95 | 
| Hi Tom | 10.00 | 0.80 | $6.95 | $1.92 | $1.50 | $0.32 | $1.00 | $0.50 | $0.78 | $0.06 | $0.23 | $7.21 | $24.95 | 
| Bass / Kick | 22.00 | 1.75 | $6.95 | $1.92 | $1.50 | $0.32 | $1.00 | $0.50 | $0.78 | $0.06 | $0.23 | $14.42 | $49.90 | 
| Floor Tom | 16.00 | 1.28 | $6.95 | $1.92 | $1.50 | $0.32 | $1.00 | $0.50 | $0.78 | $0.06 | $0.23 | $7.21 | $24.95 | 
| Hi Hat Cymbal | 65.62 | 1.67 | $6.95 | $1.92 | $1.50 | $0.32 | $1.00 | $0.50 | $0.78 | $0.06 | $0.23 | $14.42 | $49.90 | 
| Crash Cymbal | 65.62 | 1.67 | $6.95 | $1.92 | $1.50 | $0.32 | $1.00 | $0.50 | $0.78 | $0.06 | $0.23 | $14.42 | $49.90 | 
| Ride Cymbal | 65.62 | 1.67 | $6.95 | $1.92 | $1.50 | $0.32 | $1.00 | $0.50 | $0.78 | $0.06 | $0.23 | $14.42 | $49.90 | 
| <b>Total(s)</b> | <b></b> | <b>11</b> | <b>$55.60</b> | <b>$15.33</b> | <b>$11.98</b> | <b>$2.55</b> | <b>$8.00</b> | <b>$4.00</b> | <b>$6.23</b> | <b>$0.48</b> | <b>$1.85</b> | <b>$78.60</b> | <b>$272.01</b> | 

---

| Option (assuming 11m of led strips) |	Total $ |	$ / Drum | 
|:---|:---|:---| 
| [Option A - Automotive LEDs](https://www.amazon.com/dp/B014R5PC42/?th=1) |	$184.62 | $23.08 | 
| [Option B - Neopixels](https://www.adafruit.com/product/2959) |	$378.03 | $47.25 | 
| Difference | -$193.40 |	-$24.18 | 

---

#### Guides:
- [ ] 1. Projects found while researching online:

  * [cassettepunk](http://cassettepunk.com/small-projects/drum-lights/) drum lights.  Uses trinket and piezo sensors.  
  * [tomatoskins LED Drum Setup](https://www.instructables.com/id/Light-Up-Drum-Kit/).  Uses piezo sensors and a 555 Timer IC.
  * [Measuring trigger hit duration and velocity](https://beammyselfintothefuture.wordpress.com/2015/01/28/sensing-hit-velocity-and-quick-subsequent-hits-of-a-piezo-with-an-arduino-teensy/) 
  * [Adafruit](https://learn.adafruit.com/gemma-powered-neopixel-led-sound-reactive-drums/overview) uses Mic instead of knock sensor.    
  * [Knock sensor tutorial](https://www.arduino.cc/en/Tutorial/KnockSensor)  
  * LED Strip Animation Examples
     * [Tweaking4all's](https://www.tweaking4all.com/hardware/arduino/adruino-led-strip-effects/)  
     * [FastLED](https://github.com/FastLED/FastLED/wiki/Overview#quickexample)  
  * We also considered using ["EL-Wire"](https://www.adafruit.com/category/50) instead of neopixels.  This may be something to consider in your own project.
- [ ] 2. [Adafruit Neopixel UberGuide](https://learn.adafruit.com/adafruit-neopixel-uberguide)
- [ ] 3. [Adafruit Trinket Clockspeed Guide](https://learn.adafruit.com/introducing-trinket/16mhz-vs-8mhz-clock)
- [ ] 4. [Adafruit Trinket Guide](https://learn.adafruit.com/introducing-trinket)
- [ ] 5. [Neopixel LED Animation Examples/Guide](https://www.tweaking4all.com/hardware/arduino/adruino-led-strip-effects/)

#### Software:
- [ ] 1. [Fritzing tool](http://fritzing.org/download/)
- [ ] 2. [Tinkercad Design Tool - 3D Printing](https://www.tinkercad.com)
- [ ] 3. [Tinkercad Circuits Tool - Breadboard prototyping](https://www.tinkercad.com/circuits)
- [ ] 4. [Arduino IDE](https://www.arduino.cc/en/Main/Software) to program "[trinket](http://bit.ly/2ji37ag)"

   * Note:  You will also need to install the [adafruit neopixel library](https://learn.adafruit.com/adafruit-neopixel-uberguide) in the IDE after installing the Arduino IDE.  

---

#### Enclosure Designs:
- [ ] 1.[Enclosure Design](/stl/enclosure/) - I did not have any white plastic to print with so I am just going to spray paint the enclosures with white spray paint when done to match the color of the drum set.

|  |  
|:---:| 
<a href="/images/20171225_202945.jpg"><img src="/images/20171225_202945.jpg" align="left" height="250" width="325" >Version 1 - Trinket</a> | 
<a href="/images/20171225_204757.jpg"><img src="/images/20171225_204757.jpg" align="left" height="250" width="325" ></a> | 
<a href="/images/20180310_100626.jpg"><img src="/images/20180310_100626.jpg" align="left" height="250" width="325" >Version 2 - Trinket Pro</a> | 
      
---

#### Videos:
- [ ] 1. [Breadboard test](https://vimeo.com/246706150)
- [ ] 2. [Testing concept on cajon](https://vimeo.com/246627364)
- [ ] 3. [Testing set after finishing floor tom](https://vimeo.com/250054557/)

---

#### Lessons Learned:
- [ ] 1. If the sketched code goes beyond 58% program storage, the trinkety/ATTiny85 appears to not have enough ram to address more than 90 neopixels/leds at runtime.  Going to try an [AVR Programmer](https://www.sparkfun.com/products/11801) to see if I can reclaim some memory by removing the bootloader.  When I tried to add some more animation effects, the code was too large to power the 107 pixels I needed on the KICK.  The strip would not turn on due to lack of memory/heap dump.  I kept the code minimal so I could address all the pixels on the KICK drum for now.

   * [Instructable on how to use AVR Programmer](https://www.instructables.com/id/Save-27K-of-flash-memory-on-an-Adafruit-Trinket/)
- [ ] 2. The piezo sensors are a lot more sensitive than I thought they would be.  A threshold of around 65 seems to be the magic number to prevent false knocks/vibrations from other drums in the kit.  Considering doing a while loop to only count a "hit" if so many occur within a few milliseconds but that makes code somewhat large/memory constraints.
- [ ] 3. Would be nice to add a potentiometer to control the piezo "sensitivity" from the controller instead of having to reprogram to try different settings.  I am going to add this feature in future builds but looks like a [Trinket Pro 5v](https://www.adafruit.com/product/2000) might be a better controller to use since it has more analog inputs than the regular Trinket 5v.

   * [Prototyping](https://vimeo.com/250728026) using a potentiometer knob with a Trinket Pro to allow for adjusting drumstick hit sensitivity realtime.
- [ ] 4. I considered using an ATTiny85 chip by itself thinking it would be cheaper but hard to beat the features of the trinket 5v when comparing bang for your buck and less soldering.  The trinket 5v worked out really well but would use a Trinket Pro in the future for the kick drum to make addressing more pixels easier.  Trinket 5v was plenty for the other drums since they used less pixels/leds on the strip.
- [ ] 5. I think it would be nice to just build one big enclosure with all 8 trinkets in it in the future instead of 8 individual ones and just run wires from it under the kick drum to each drum in the set.  It might be easier to hide the wires that way.  I would consider cable management more in the next version of this project.
- [ ] 6. [How to power using a dc adapter](https://playground.arduino.cc/Learning/WhatAdapter)

--- 

#### Project Images:
|  |  |  | 
|:---:|:---:|:---:|
|<a href="/images/20171210_095139.jpg"><img src="/images/20171210_095139.jpg" align="left" height="250" width="325" ></a> | <a href="/images/20171209_181501.jpg"><img src="/images/20171209_181501.jpg" align="left" height="250" width="325" ></a> | <a href="/images/20171210_110332.jpg"><img src="/images/20171210_110332.jpg" align="left" height="250" width="325" ></a> |
|<a href="/images/20171210_110353.jpg"><img src="/images/20171210_110353.jpg" align="left" height="250" width="325" ></a> | <a href="/images/20171210_110415.jpg"><img src="/images/20171210_110415.jpg" align="left" height="250" width="325" ></a> | <a href="/images/ProtoBoardWorkInProgress.jpg"><img src="/images/ProtoBoardWorkInProgress.jpg" align="left" height="250" width="325" ></a> |
|<a href="/images/20171215_211205.jpg"><img src="/images/20171215_211205.jpg" align="left" height="250" width="325" ></a> | <a href="/images/20171221_214608.jpg"><img src="/images/20171221_214608.jpg" align="left" height="250" width="325" ></a> | <a href="/images/20171221_214621.jpg"><img src="/images/20171221_214621.jpg" align="left" height="250" width="325" ></a> |
|<a href="/images/20171221_223541-01.jpeg"><img src="/images/20171221_223541-01.jpeg" align="left" height="250" width="325" ></a> | <a href="/images/20171224_205943.jpg"><img src="/images/20171224_205943.jpg" align="left" height="250" width="325" ></a> | <a href="/images/20171224_205958.jpg"><img src="/images/20171224_205958.jpg" align="left" height="250" width="325" ></a> |
|<a href="/images/20171224_210018.jpg"><img src="/images/20171224_210018.jpg" align="left" height="250" width="325" ></a> | <a href="/images/20171225_153238.jpg"><img src="/images/20171225_153238.jpg" align="left" height="250" width="325" ></a> | <a href="/images/20171225_153247.jpg"><img src="/images/20171225_153247.jpg" align="left" height="250" width="325" ></a> |
|<a href="/images/20171225_160417.jpg"><img src="/images/20171225_160417.jpg" align="left" height="250" width="325" ></a> | <a href="/images/20171225_203416.jpg"><img src="/images/20171225_203416.jpg" align="left" height="250" width="325" ></a> | <a href="/images/20171228_232709.jpg"><img src="/images/20171228_232709.jpg" align="left" height="250" width="325" ></a> |
|<a href="/images/20171228_232719.jpg"><img src="/images/20171228_232719.jpg" align="left" height="250" width="325" ></a> | <a href="/images/20171231_174619.jpg"><img src="/images/20171231_174619.jpg" align="left" height="250" width="325" ></a> | <a href="/images/20171231_174634.jpg"><img src="/images/20171231_174634.jpg" align="left" height="250" width="325" ></a> |
|<a href="/images/20180105_163129.jpg"><img src="/images/20180105_163129.jpg" align="left" height="250" width="325" ></a> | <a href="/images/20180106_174938.jpg"><img src="/images/20180106_174938.jpg" align="left" height="250" width="325" ></a> | <a href="/images/20180310_100642.jpg"><img src="/images/20180310_100642.jpg" align="left" height="250" width="325" ></a> |
|<a href="/images/20180310_100637.jpg"><img src="/images/20180310_100637.jpg" align="left" height="250" width="325" ></a> | <a href="/images/20180310_100626.jpg"><img src="/images/20180310_100626.jpg" align="left" height="250" width="325" ></a> | 



