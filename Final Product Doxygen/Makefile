#############################################################################
#
# Project Makefile
#
# (c) Wouter van Ooijen (www.voti.nl) 2016
#
# This file is in the public domain.
# 
#############################################################################

# source files in this project (main.cpp is automatically assumed)
SOURCES := gameControl.cpp parameterControl.cpp ir_Decoder.cpp ir_Receiver.cpp ir_Encoder.cpp ir_Led.cpp keypad.cpp OLED.cpp trigger.cpp gameInfoEntity.cpp

# header files in this project
HEADERS := gameControl.hpp parameterControl.hpp ir_Decoder.hpp ir_Receiver.hpp ir_Encoder.hpp ir_Led.hpp keypad.hpp OLED.hpp trigger.hpp gameInfoEntity.hpp

# other places to look for files for this project
SEARCH  := 

SERIAL_PORT := /dev/ttyACM0
# set RELATIVE to the next higher directory and defer to the Makefile.due
RELATIVE := $(RELATIVE)../
include $(RELATIVE)Makefile.due
