# Wind River Workbench generated Makefile.
# Do not edit!!!
#
# The file ".wrmakefile" is the template used by the Wind River Workbench to
# generate the makefiles of this project. Add user-specific build targets and
# make rules only(!) in this project's ".wrmakefile" file. These will then be
# automatically dumped into the makefiles.

WIND_HOME := $(subst \,/,$(WIND_HOME))
WIND_BASE := $(subst \,/,$(WIND_BASE))
WIND_USR := $(subst \,/,$(WIND_USR))
WRVX_COMPBASE := $(subst \,/,$(WRVX_COMPBASE))

all : pre_build main_all post_build

_clean ::
	@echo "make: removing targets and objects of `pwd`"

TRACE=0
TRACEON=$(TRACE:0=@)
TRACE_FLAG=$(TRACEON:1=)

MAKEFILE := Makefile

FLEXIBLE_BUILD := 1

BUILD_SPEC = SIMNTdiab
DEBUG_MODE = 1
ifeq ($(DEBUG_MODE),1)
MODE_DIR := Debug
else
MODE_DIR := NonDebug
endif
OBJ_DIR := .
WS_ROOT_DIR := Z:/cmmaiimpl2
PRJ_ROOT_DIR := Z:/cmmai/src



#Global Build Macros
PROJECT_TYPE = DKM
DEFINES = 
EXPAND_DBG = 0


#BuildSpec specific Build Macros
VX_CPU_FAMILY = simpc
CPU = SIMNT
TOOL_FAMILY = diab
TOOL = diab
TOOL_PATH = 
CC_ARCH_SPEC = -tX86LH:vxworks67
VSB_DIR = $(WIND_BASE)/target/lib
VSB_CONFIG_FILE = $(VSB_DIR)/h/config/vsbConfig.h
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 

IDE_LIBRARIES = 



#BuildTool flags
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
DEBUGFLAGS_C++-Compiler = -g
DEBUGFLAGS_Linker = -g
DEBUGFLAGS_Partial-Image-Linker = 
DEBUGFLAGS_Librarian = 
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_C-Compiler = -XO -Xsize-opt
DEBUGFLAGS_C++-Compiler = -XO -Xsize-opt
DEBUGFLAGS_Linker = -XO -Xsize-opt
DEBUGFLAGS_Partial-Image-Linker = 
DEBUGFLAGS_Librarian = 
DEBUGFLAGS_Assembler = -XO -Xsize-opt
endif


#Project Targets
PROJECT_TARGETS = cmmai/$(MODE_DIR)/cmmai.out \
	 cmmai_partialImage/$(MODE_DIR)/cmmai_partialImage.o


#Rules

# cmmai
ifeq ($(DEBUG_MODE),1)
cmmai/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -g
cmmai/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -g
cmmai/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -g
cmmai/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
cmmai/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
cmmai/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -g
else
cmmai/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -XO -Xsize-opt
cmmai/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -XO -Xsize-opt
cmmai/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -XO -Xsize-opt
cmmai/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
cmmai/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
cmmai/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -XO -Xsize-opt
endif
cmmai/$(MODE_DIR)/% : IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
cmmai/$(MODE_DIR)/% : IDE_LIBRARIES = 
cmmai/$(MODE_DIR)/% : PROJECT_TYPE = DKM
cmmai/$(MODE_DIR)/% : DEFINES = 
cmmai/$(MODE_DIR)/% : EXPAND_DBG = 0
cmmai/$(MODE_DIR)/% : VX_CPU_FAMILY = simpc
cmmai/$(MODE_DIR)/% : CPU = SIMNT
cmmai/$(MODE_DIR)/% : TOOL_FAMILY = diab
cmmai/$(MODE_DIR)/% : TOOL = diab
cmmai/$(MODE_DIR)/% : TOOL_PATH = 
cmmai/$(MODE_DIR)/% : CC_ARCH_SPEC = -tX86LH:vxworks67
cmmai/$(MODE_DIR)/% : VSB_DIR = $(WIND_BASE)/target/lib
cmmai/$(MODE_DIR)/% : VSB_CONFIG_FILE = $(VSB_DIR)/h/config/vsbConfig.h
cmmai/$(MODE_DIR)/% : LIBPATH = 
cmmai/$(MODE_DIR)/% : LIBS = 
cmmai/$(MODE_DIR)/% : OBJ_DIR := cmmai/$(MODE_DIR)

OBJECTS_cmmai = cmmai_partialImage/$(MODE_DIR)/cmmai_partialImage.o

cmmai/$(MODE_DIR)/cmmai.out : $(OBJECTS_cmmai)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@";rm -f "$@";ddump -Ng $(OBJECTS_cmmai) $(IDE_LIBRARIES) | tclsh $(WIND_BASE)/host/resource/hutils/tcl/munch.tcl -c pentium > $(OBJ_DIR)/ctdt.c; $(TOOL_PATH)dcc $(DEBUGFLAGS_Linker) $(CC_ARCH_SPEC) -Xdollar-in-ident -Xforce-declarations  $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL  -D_VSB_CONFIG_FILE=\"$(VSB_CONFIG_FILE)\"   $(DEFINES)  -o $(OBJ_DIR)/ctdt.o -c $(OBJ_DIR)/ctdt.c; $(TOOL_PATH)dld -tX86LH:vxworks67 -X -r5 -f 0x90,1,1 -r4 -o "$@" $(OBJ_DIR)/ctdt.o $(OBJECTS_cmmai) $(IDE_LIBRARIES) $(LIBPATH) $(LIBS) $(ADDED_LIBPATH) $(ADDED_LIBS) && if [ "$(EXPAND_DBG)" = "1" ]; then plink "$@";fi

cmmai/$(MODE_DIR)/cmmai_compile_file : $(FILE) ;

_clean :: cmmai/$(MODE_DIR)/cmmai_clean

cmmai/$(MODE_DIR)/cmmai_clean : 
	$(TRACE_FLAG)if [ -d "cmmai" ]; then cd "cmmai"; rm -rf $(MODE_DIR); fi


# cmmai_partialImage
ifeq ($(DEBUG_MODE),1)
cmmai_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -g
cmmai_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -g
cmmai_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -g
cmmai_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
cmmai_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
cmmai_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -g
else
cmmai_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -XO -Xsize-opt
cmmai_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -XO -Xsize-opt
cmmai_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -XO -Xsize-opt
cmmai_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
cmmai_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
cmmai_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -XO -Xsize-opt
endif
cmmai_partialImage/$(MODE_DIR)/% : IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
cmmai_partialImage/$(MODE_DIR)/% : IDE_LIBRARIES = 
cmmai_partialImage/$(MODE_DIR)/% : PROJECT_TYPE = DKM
cmmai_partialImage/$(MODE_DIR)/% : DEFINES = 
cmmai_partialImage/$(MODE_DIR)/% : EXPAND_DBG = 0
cmmai_partialImage/$(MODE_DIR)/% : VX_CPU_FAMILY = simpc
cmmai_partialImage/$(MODE_DIR)/% : CPU = SIMNT
cmmai_partialImage/$(MODE_DIR)/% : TOOL_FAMILY = diab
cmmai_partialImage/$(MODE_DIR)/% : TOOL = diab
cmmai_partialImage/$(MODE_DIR)/% : TOOL_PATH = 
cmmai_partialImage/$(MODE_DIR)/% : CC_ARCH_SPEC = -tX86LH:vxworks67
cmmai_partialImage/$(MODE_DIR)/% : VSB_DIR = $(WIND_BASE)/target/lib
cmmai_partialImage/$(MODE_DIR)/% : VSB_CONFIG_FILE = $(VSB_DIR)/h/config/vsbConfig.h
cmmai_partialImage/$(MODE_DIR)/% : LIBPATH = 
cmmai_partialImage/$(MODE_DIR)/% : LIBS = 
cmmai_partialImage/$(MODE_DIR)/% : OBJ_DIR := cmmai_partialImage/$(MODE_DIR)

cmmai_partialImage/$(MODE_DIR)/Objects/cmmai/boxManager.o : $(PRJ_ROOT_DIR)/boxManager.c
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -Xforce-declarations   -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL  -D_VSB_CONFIG_FILE=\"$(VSB_CONFIG_FILE)\"   $(DEFINES) -o "$@" -c "$<"


cmmai_partialImage/$(MODE_DIR)/Objects/cmmai/devices.o : $(PRJ_ROOT_DIR)/devices.c
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -Xforce-declarations   -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL  -D_VSB_CONFIG_FILE=\"$(VSB_CONFIG_FILE)\"   $(DEFINES) -o "$@" -c "$<"


cmmai_partialImage/$(MODE_DIR)/Objects/cmmai/eventManager.o : $(PRJ_ROOT_DIR)/eventManager.c
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -Xforce-declarations   -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL  -D_VSB_CONFIG_FILE=\"$(VSB_CONFIG_FILE)\"   $(DEFINES) -o "$@" -c "$<"


cmmai_partialImage/$(MODE_DIR)/Objects/cmmai/eventToString.o : $(PRJ_ROOT_DIR)/eventToString.c
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -Xforce-declarations   -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL  -D_VSB_CONFIG_FILE=\"$(VSB_CONFIG_FILE)\"   $(DEFINES) -o "$@" -c "$<"


cmmai_partialImage/$(MODE_DIR)/Objects/cmmai/logsManager.o : $(PRJ_ROOT_DIR)/logsManager.c
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -Xforce-declarations   -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL  -D_VSB_CONFIG_FILE=\"$(VSB_CONFIG_FILE)\"   $(DEFINES) -o "$@" -c "$<"


cmmai_partialImage/$(MODE_DIR)/Objects/cmmai/masterTask.o : $(PRJ_ROOT_DIR)/masterTask.c
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -Xforce-declarations   -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL  -D_VSB_CONFIG_FILE=\"$(VSB_CONFIG_FILE)\"   $(DEFINES) -o "$@" -c "$<"


cmmai_partialImage/$(MODE_DIR)/Objects/cmmai/networkInterface.o : $(PRJ_ROOT_DIR)/networkInterface.c
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -Xforce-declarations   -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL  -D_VSB_CONFIG_FILE=\"$(VSB_CONFIG_FILE)\"   $(DEFINES) -o "$@" -c "$<"


cmmai_partialImage/$(MODE_DIR)/Objects/cmmai/networkListener.o : $(PRJ_ROOT_DIR)/networkListener.c
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -Xforce-declarations   -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL  -D_VSB_CONFIG_FILE=\"$(VSB_CONFIG_FILE)\"   $(DEFINES) -o "$@" -c "$<"


cmmai_partialImage/$(MODE_DIR)/Objects/cmmai/printManager.o : $(PRJ_ROOT_DIR)/printManager.c
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -Xforce-declarations   -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL  -D_VSB_CONFIG_FILE=\"$(VSB_CONFIG_FILE)\"   $(DEFINES) -o "$@" -c "$<"


OBJECTS_cmmai_partialImage = cmmai_partialImage/$(MODE_DIR)/Objects/cmmai/boxManager.o \
	 cmmai_partialImage/$(MODE_DIR)/Objects/cmmai/devices.o \
	 cmmai_partialImage/$(MODE_DIR)/Objects/cmmai/eventManager.o \
	 cmmai_partialImage/$(MODE_DIR)/Objects/cmmai/eventToString.o \
	 cmmai_partialImage/$(MODE_DIR)/Objects/cmmai/logsManager.o \
	 cmmai_partialImage/$(MODE_DIR)/Objects/cmmai/masterTask.o \
	 cmmai_partialImage/$(MODE_DIR)/Objects/cmmai/networkInterface.o \
	 cmmai_partialImage/$(MODE_DIR)/Objects/cmmai/networkListener.o \
	 cmmai_partialImage/$(MODE_DIR)/Objects/cmmai/printManager.o

cmmai_partialImage/$(MODE_DIR)/cmmai_partialImage.o : $(OBJECTS_cmmai_partialImage)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dld -tX86LH:vxworks67 -X -r5 -f 0x90,1,1  -o "$@" $(OBJECTS_cmmai_partialImage) $(ADDED_OBJECTS) $(IDE_LIBRARIES) $(LIBPATH) $(LIBS) $(ADDED_LIBPATH) $(ADDED_LIBS) && if [ "$(EXPAND_DBG)" = "1" ]; then plink "$@";fi

cmmai_partialImage/$(MODE_DIR)/cmmai_partialImage_compile_file : $(FILE) ;

_clean :: cmmai_partialImage/$(MODE_DIR)/cmmai_partialImage_clean

cmmai_partialImage/$(MODE_DIR)/cmmai_partialImage_clean : 
	$(TRACE_FLAG)if [ -d "cmmai_partialImage" ]; then cd "cmmai_partialImage"; rm -rf $(MODE_DIR); fi

DEP_FILES := cmmai_partialImage/$(MODE_DIR)/Objects/cmmai/boxManager.d cmmai_partialImage/$(MODE_DIR)/Objects/cmmai/devices.d cmmai_partialImage/$(MODE_DIR)/Objects/cmmai/eventManager.d \
	 cmmai_partialImage/$(MODE_DIR)/Objects/cmmai/eventToString.d cmmai_partialImage/$(MODE_DIR)/Objects/cmmai/logsManager.d cmmai_partialImage/$(MODE_DIR)/Objects/cmmai/masterTask.d \
	 cmmai_partialImage/$(MODE_DIR)/Objects/cmmai/networkInterface.d cmmai_partialImage/$(MODE_DIR)/Objects/cmmai/networkListener.d cmmai_partialImage/$(MODE_DIR)/Objects/cmmai/printManager.d
-include $(DEP_FILES)


WIND_SCOPETOOLS_BASE := $(subst \,/,$(WIND_SCOPETOOLS_BASE))

clean_scopetools :
	$(TRACE_FLAG)rm -rf $(PRJ_ROOT_DIR)/.coveragescope/db

CLEAN_STEP := clean_scopetools


-include $(PRJ_ROOT_DIR)/*.makefile

-include *.makefile

main_all : external_build $(PROJECT_TARGETS)
	@echo "make: built targets of `pwd`"

# entry point for extending the build
external_build ::
	@echo ""

# main entry point for pre processing prior to the build
pre_build :: $(PRE_BUILD_STEP) generate_sources
	@echo ""

# entry point for generating sources prior to the build
generate_sources ::
	@echo ""

# main entry point for post processing after the build
post_build :: $(POST_BUILD_STEP) deploy_output
	@echo ""

# entry point for deploying output after the build
deploy_output ::
	@echo ""

clean :: external_clean $(CLEAN_STEP) _clean

# entry point for extending the build clean
external_clean ::
	@echo ""
