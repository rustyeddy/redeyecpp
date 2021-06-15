#!/bin/bash

gst-launch-1.0 nvarguscamerasrc num-buffers=200 ! 'video/x-raw(memory:NVMM),width=1920, height=1080, framerate=30/1, format=NV12' ! omxh264enc ! qtmux ! filesink location=test.mp4 -e
