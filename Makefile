##### Make sure all is the first target.
all:

CXX ?= g++
CC  ?= gcc




CFLAGS  += -g -pthread -Wall 
CFLAGS  += -rdynamic -funwind-tables

CFLAGS = -O2 -I./include -I./Mqtt

CFLAGS  += -I.
CFLAGS  += -I./inc    
CFLAGS  += -I./Mqtt  
DIR_LIBMQTT = Mqtt

DIR_OBJ = obj

DIRS = 	$(DIR_LIBMQTT)
FILES = $(foreach dir, $(DIRS),$(wildcard $(dir)/*.c))	
		


CFLAGS += -D__unused="__attribute__((__unused__))"

#LDFLAGS += -L./usr/lib/gpac
LDFLAGS += -ldl

LDFLAGS +=  -L./Mqtt/lib -lmosquitto
LDFLAGS +=  -ldl -lm  -lstdc++


C_SRC=

C_SRC+= osp.c
C_SRC+= DevList.c
C_SRC+= cJSON.c
C_SRC+= $(FILES)

CXX_SRC=


OBJ=
DEP=
OBJECTS_DIR   = objects/

# Files

CXXFLAGS += -std=c++11 $(CFLAGS)


OBJ_CAM_SRV = osp.o
TARGETS    += Monitor_server
$(TARGETS): $(OBJ_CAM_SRV)
TARGET_OBJ += $(OBJ_CAM_SRV)

FILE_LIST := files.txt
COUNT := ./make/count.sh

OBJ=$(CXX_SRC:.cpp=.o) $(C_SRC:.c=.o)
DEP=$(OBJ:.o=.d) $(TARGET_OBJ:.o=.d)

CXXFLAGS += -std=c++11 -g 
CXXFLAGS += -lc -lm -pthread
#include ./common.mk
.PHONY: all clean distclean

all: $(TARGETS)

clean:
	rm -f $(TARGETS) $(FILE_LIST)
	find . -name "*.o" -delete
	find . -name "*.d" -delete

distclean:
	rm -f $(TARGETS) $(FILE_LIST)
	find . -name "*.o" -delete
	find . -name "*.d" -delete

-include $(DEP)

%.o: %.c 
	@[ -f $(COUNT) ] && $(COUNT) $(FILE_LIST) $^ || true
	@$(CC) -c $< -MM -MT $@ -MF $(@:.o=.d) $(CFLAGS) $(LIBQCAM_CFLAGS)
	$(CC) -c $< $(CFLAGS) -o $@ $(LIBQCAM_CFLAGS) $(INCPATH)


%.o: %.cpp 
	@$(CXX) -c $< -MM -MT $@ -MF $(@:.o=.d) $(CXXFLAGS)
	$(CXX) -c $< $(CXXFLAGS) -o $@   $(INCPATH)
	

$(TARGETS): $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LDFLAGS)
	@[ -f $(COUNT) -a -n "$(FILES)" ] && $(COUNT) $(FILE_LIST) $(FILES) || true
	@[ -f $(COUNT) ] && $(COUNT) $(FILE_LIST) || true
