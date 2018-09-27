#!/usr/bin/env bash

pio run --target clean
pio run --target upload
pio device monitor