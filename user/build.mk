
# SOURCE_PATH - the root of all sources. Defaults to the module dir
# USRSRC - relative path to SOURCE_PATH for the sources to build

# determine where user sources are, relative to project root
ifdef APP
USER_MAKEFILE ?= $(APP).mk
# when TARGET_FILE is defined on the command line,
endif

ifdef APPDIR
# APPDIR is where the sources are found
# if TARGET_DIR is not defined defaults to $(APPDIR)/target
# if TARGET_FILE_NAME is not defined, defaults to the name of the $(APPDIR)
SOURCE_PATH = $(APPDIR)
endif


ifdef TEST
INCLUDE_PLATFORM?=1
include $(MODULE_PATH)/tests/tests.mk
-include $(MODULE_PATH)/$(USRSRC)/test.mk
endif

USRSRC_SLASH = $(and $(USRSRC),$(USRSRC)/)
USER_MAKEFILE ?= build.mk
usrmakefile = $(wildcard $(SOURCE_PATH)/$(USRSRC_SLASH)$(USER_MAKEFILE))
ifeq ("$(usrmakefile)","")
INCLUDE_DIRS += $(SOURCE_PATH)/$(USRSRC)  # add user sources to include path
# add C and CPP files - if USRSRC is not empty, then add a slash
CPPSRC += $(call target_files,$(USRSRC_SLASH),*.cpp)
CSRC += $(call target_files,$(USRSRC_SLASH),*.c)

APPSOURCES=$(call target_files,$(USRSRC_SLASH),*.cpp)
APPSOURCES+=$(call target_files,$(USRSRC_SLASH),*.c)
ifeq ($(strip $(APPSOURCES)),)
$(error "No sources found in $(SOURCE_PATH)/$(USRSRC)")
endif
else
include $(usrmakefile)
endif

INCLUDE_DIRS += $(MODULE_PATH)/libraries

CPPSRC += $(call target_files,libraries/,*.cpp)

CPPFLAGS += -std=gnu++11

CPPFLAGS += `pkg-config gtkmm-3.0 --cflags` # FIXME: Command added due to gtkmm usage

CPPFLAGS += -L /lib64 # FIXME: Threading

BUILTINS_EXCLUDE =
CFLAGS += $(addprefix -fno-builtin-,$(BUILTINS_EXCLUDE))

CFLAGS += $(EXTRA_CFLAGS)
