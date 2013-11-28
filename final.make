# GNU Make project makefile autogenerated by Premake
ifndef config
  config=debug
endif

ifndef verbose
  SILENT = @
endif

ifndef CC
  CC = gcc
endif

ifndef CXX
  CXX = g++
endif

ifndef AR
  AR = ar
endif

ifeq ($(config),debug)
  OBJDIR     = obj/Debug
  TARGETDIR  = debug
  TARGET     = $(TARGETDIR)/final
  DEFINES   += -D_DEBUG -DDEBUG
  INCLUDES  += -Ivecmath/include
  CPPFLAGS  += -MMD -MP $(DEFINES) $(INCLUDES)
  CFLAGS    += $(CPPFLAGS) $(ARCH) -g -std=c++0x
  CXXFLAGS  += $(CFLAGS) 
  LDFLAGS   += `if [ "\`uname\`" = "Darwin" ]; then echo "-framework OpenGL -framework GLUT -lRK4_mac"; else echo "-lGL -lGLU -lglut -lRK4"; fi;` -Llib -Ldebug
  LIBS      += -lvecmath
  RESFLAGS  += $(DEFINES) $(INCLUDES) 
  LDDEPS    += debug/libvecmath.a
  LINKCMD    = $(CXX) -o $(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(ARCH) $(LIBS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
	@echo Running post-build commands
	cp debug/final final
  endef
endif

ifeq ($(config),release)
  OBJDIR     = obj/Release
  TARGETDIR  = release
  TARGET     = $(TARGETDIR)/final
  DEFINES   += -DNDEBUG
  INCLUDES  += -Ivecmath/include
  CPPFLAGS  += -MMD -MP $(DEFINES) $(INCLUDES)
  CFLAGS    += $(CPPFLAGS) $(ARCH) -O2 -std=c++0x
  CXXFLAGS  += $(CFLAGS) 
  LDFLAGS   += -s `if [ "\`uname\`" = "Darwin" ]; then echo "-framework OpenGL -framework GLUT -lRK4_mac"; else echo "-lGL -lGLU -lglut -lRK4"; fi;` -Llib -Lrelease
  LIBS      += -lvecmath
  RESFLAGS  += $(DEFINES) $(INCLUDES) 
  LDDEPS    += release/libvecmath.a
  LINKCMD    = $(CXX) -o $(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(ARCH) $(LIBS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
	@echo Running post-build commands
	cp release/final final
  endef
endif

OBJECTS := \
	$(OBJDIR)/camera.o \
	$(OBJDIR)/particleSystem.o \
	$(OBJDIR)/main.o \
	$(OBJDIR)/ClothSystem.o \
	$(OBJDIR)/TimeStepper.o \
	$(OBJDIR)/simpleSystem.o \
	$(OBJDIR)/pendulumSystem.o \
	$(OBJDIR)/PhysicalSystem.o \
	$(OBJDIR)/SpringSystem.o \
	$(OBJDIR)/FlockSystem.o \
	$(OBJDIR)/Foid.o \

RESOURCES := \

SHELLTYPE := msdos
ifeq (,$(ComSpec)$(COMSPEC))
  SHELLTYPE := posix
endif
ifeq (/bin,$(findstring /bin,$(SHELL)))
  SHELLTYPE := posix
endif

.PHONY: clean prebuild prelink

all: $(TARGETDIR) $(OBJDIR) prebuild prelink $(TARGET)
	@:

$(TARGET): $(GCH) $(OBJECTS) $(LDDEPS) $(RESOURCES)
	@echo Linking final
	$(SILENT) $(LINKCMD)
	$(POSTBUILDCMDS)

$(TARGETDIR):
	@echo Creating $(TARGETDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) mkdir -p $(TARGETDIR)
else
	$(SILENT) mkdir $(subst /,\\,$(TARGETDIR))
endif

$(OBJDIR):
	@echo Creating $(OBJDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) mkdir -p $(OBJDIR)
else
	$(SILENT) mkdir $(subst /,\\,$(OBJDIR))
endif

clean:
	@echo Cleaning final
ifeq (posix,$(SHELLTYPE))
	$(SILENT) rm -f  $(TARGET)
	$(SILENT) rm -rf $(OBJDIR)
else
	$(SILENT) if exist $(subst /,\\,$(TARGET)) del $(subst /,\\,$(TARGET))
	$(SILENT) if exist $(subst /,\\,$(OBJDIR)) rmdir /s /q $(subst /,\\,$(OBJDIR))
endif

prebuild:
	$(PREBUILDCMDS)

prelink:
	$(PRELINKCMDS)

ifneq (,$(PCH))
$(GCH): $(PCH)
	@echo $(notdir $<)
	-$(SILENT) cp $< $(OBJDIR)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
endif

$(OBJDIR)/camera.o: src/camera.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/particleSystem.o: src/particleSystem.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/main.o: src/main.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/ClothSystem.o: src/ClothSystem.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/TimeStepper.o: src/TimeStepper.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/simpleSystem.o: src/simpleSystem.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/pendulumSystem.o: src/pendulumSystem.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/PhysicalSystem.o: src/PhysicalSystem.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/SpringSystem.o: src/SpringSystem.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/FlockSystem.o: src/FlockSystem.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Foid.o: src/Foid.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"

-include $(OBJECTS:%.o=%.d)
