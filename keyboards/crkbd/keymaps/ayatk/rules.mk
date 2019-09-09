LOCAL_GLCDFONT = yes         # use each keymaps "crkbdfont.h" insted of "lib/glcdfont.c"

ifeq ($(strip $(LOCAL_GLCDFONT)), yes)
    OPT_DEFS += -DLOCAL_GLCDFONT
endif
