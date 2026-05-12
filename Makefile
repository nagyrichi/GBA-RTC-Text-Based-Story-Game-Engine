# Butano GBA Skeleton Project

TARGET      		:=  my_gba_game
BUILD       		:=  build
PROJECT_ROOT 		:= $(realpath .)
LIBBUTANO   		?= $(PROJECT_ROOT)/external/butano/butano
LIBBUTANO_FALLBACKS := $(PROJECT_ROOT)/external/butano/butano
PYTHON      		:=  /opt/homebrew/Caskroom/miniforge/base/bin/python3
SOURCES     		:=  src
INCLUDES    		:=  include
DATA        		:=
GRAPHICS    		:=
AUDIO       		:=
DMGAUDIO    		:=
ROMTITLE    		:=  MY_GAME
ROMCODE     		:=  MYGM
USERFLAGS   		:=
USERASFLAGS 		:=
USERLDFLAGS 		:=
USERLIBDIRS 		:=
USERLIBS    		:=
USERBUILD   		:=
EXTTOOL     		:=
INCLUDES 			+= $(PROJECT_ROOT)/external/butano/common/include
GRAPHICS    		:= $(PROJECT_ROOT)/graphics $(PROJECT_ROOT)/external/butano/common/graphics
LIBBUTANO_FOUND 	:= $(shell test -f "$(LIBBUTANO)/butano.mak" && echo "$(LIBBUTANO)" || echo "")

ifndef LIBBUTANOABS
	export LIBBUTANOABS := $(LIBBUTANO)
endif

include $(LIBBUTANOABS)/butano.mak
