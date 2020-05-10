LOCAL_GLCDFONT = yes         # use each keymaps "crkbdfont.h" insted of "lib/glcdfont.c"
COMBO_ENABLE = yes

ifeq ($(strip $(LOCAL_GLCDFONT)), yes)
    OPT_DEFS += -DLOCAL_GLCDFONT
endif
