# RedEye Camera Module

RedEye Camera Module is software that runs on Raspberry Pi/NVidia
Jetson platform and Linux boxes with a USB camera. It gathers video
images from the camera, optionally runs the video images through a
_Computer Vision_ pipeline, the modified image is then made available
via a built in Webserver.

## Starting redeye

Start Redeye on the Nano. Now start up the UI.


## Camera Features

RedEye was designed as a _Service Oriented Architecture_ which is
comprised of three primary _Micro Services_ which include this _Camera
Module_ a _Control Bub_ and _Web App_.

- Video is M-JPEG streamed over standard HTTP/HTTPs
- Video configuration can be changed on the fly
- REST API for configuration and control
- MQTT for real time messaging events and realtime controls
- Websockets for real Webapp

The RedEye Camera module, like all RedEye components is a _Service
Oriented Architecture_ built on Open Protocols which makes the RedEye
components welcome new applications.

## AEye - Computer Vision Algorithms

The following are examples of OpenCV Computer Vision algorithms or
_pipelines_ that can be fed through the _RedEye_ cam.

- Bigger
- Canny
- Contour
- Gaussian
- Magnify
- Smaller

