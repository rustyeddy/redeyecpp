#!/bin/sh
gst-launch-1.0 nvarguscamerasrc sensor_id=0 !    'video/x-raw(memory:NVMM),width=1280, height=720, framerate=60/1, format=NV12' !    nvvidconv flip-method=0 ! 'video/x-raw, width=816, height=616' !    nvvidconv ! nvegltransform ! nveglglessink -e

