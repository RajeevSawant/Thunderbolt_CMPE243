#!/bin/bash

# 
# This file executes from the build directory by the Eclipse "Pre Build" step
#

python ../_can_dbc/dbc_parse.py -i ../../243.dbc -s COM_BRIDGE > ../_can_dbc/generated_can.h