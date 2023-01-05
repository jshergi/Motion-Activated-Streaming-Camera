# Motion-Activated-Streaming-Camera
Webcam (Logitech C270) will stream to VLC media player upon motion detected by motion sensor (Grove PIR motion sensor), status LEDs indicate state of camera, work light uses a photoresistor to check light level and will turn on in low light

# Intro

1. Motion detected: The camera starts or resumes streaming (streaming is not
instantaneous - there is a delay of about three seconds). The LED matrix displays a
flashing triangle, similar to the “play” symbol. A green LED turns on

2. Motion not detected: The camera continues streaming, but will pause if no motion is
detected within six seconds.

3. Motion not detected for six seconds: The camera pauses streaming. The LED matrix
displays two flashing vertical lines, similar to the “pause” symbol. A red LED turns on.

4. Low light detected: If the ambient light voltage reading is less than 1V, the work light
will turn on.

# Implementation Details (Summary)

Camera and Streaming:
● The functions within Derek Molloy’s capture.c were reorganized to be used with a
thread, *CameraThread. As capture.c will be used with other modules, the contents of
the main() function were placed into two functions, cameraSetup() and cameraCleanup().
These functions were included within capture.h to be called from main.c.

● Further modifications were made to enable the stream to be paused given readings from
the Grove PIR motion sensor. If no motion is detected for six seconds, the stream is
paused until motion is detected again, resuming the stream.

● Camera footage can be easily streamed to VLC Player, with a delay of about three
seconds. This delay does not seem to be alterable or avoidable, and ultimately is not
much of an issue.

Motion Sensor:
● Motion values are always being read using a thread, *CaptureThread, depending on
whether or not motion is detected the LEDs are turned on/off accordingly

● A function is created to read values from the Grove PIR motion sensor, this function is
also used by another thread (*CameraThread) for streaming

LEDs:
● The main work light turns on when the relay is closed. This happens when the
photoresistor measures the amount of ambient light within an area . This process is
happening within the same *CaptureThread mentioned above. When the relay
is open, the main work light is off.

● Within the same thread, the 2 smaller LEDs turn on depending on the value from
the motion sensor. The green LED turns on when there is motion “value of 1” and
turns off when there is no motion “value of 0”. The red LED is just the opposite
of how the green LED works where no motion turns on the light and when there is
motion, it turns off.

# Challenges

Streaming to VLC media player was one of the challenges

# Solution

Adjusted ip addresses after assuming that the BBG is on the same network as the host and that the BBG IP address is 192.168.7.2 and that the host ip is 
192.168.7.1
