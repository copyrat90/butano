#---------------------------------------------------------------------------------------------------------------------
.SUFFIXES:
#---------------------------------------------------------------------------------------------------------------------

ifeq ($(strip $(WONDERFUL_TOOLCHAIN)),)
    $(error "WONDERFUL_TOOLCHAIN not found")
endif

BN_TOOLS	:=	$(LIBBUTANOABS)/tools
include $(BN_TOOLS)/wt_setup.mak

BN_TOOLCHAIN_CFLAGS	:=	-DBN_WONDERFUL
BN_GRIT				:=	$(WONDERFUL_TOOLCHAIN)/thirdparty/blocksds/core/tools/grit/grit
BN_MMUTIL			:=	$(WONDERFUL_TOOLCHAIN)/thirdparty/blocksds/core/tools/mmutil/mmutil

#---------------------------------------------------------------------------------------------------------------------
# Butano custom base rules without flto:
#---------------------------------------------------------------------------------------------------------------------
include $(BN_TOOLS)/custom_base_rules.mak

#---------------------------------------------------------------------------------------------------------------------
# Butano custom link rule for avoiding issues when linking too much object files:
#---------------------------------------------------------------------------------------------------------------------
%.elf:
	$(SILENTMSG) Linking ROM...
ifdef ADD_COMPILE_COMMAND
	$(ADD_COMPILE_COMMAND) end
endif
	@echo $(OFILES) > bn_ofiles.txt
	$(_V)$(ROMLINK) -o $(OUTPUT).gba --output-elf $(OUTPUT).elf $(ROMLINKFLAGS) -- $(LIBPATHS) @bn_ofiles.txt \
	$(WF_CRT0) $(LIBS) $(LDFLAGS)

#---------------------------------------------------------------------------------------------------------------------
# Options for code generation:
#---------------------------------------------------------------------------------------------------------------------
include $(BN_TOOLS)/codegen_options.mak

BN_LDFLAGS_SUFFIX	:=	$(foreach path,$(WF_ARCH_LIBDIRS),-L$(path)/lib) $(USERLDFLAGS)

ifndef DEFAULTLIBS
	LDFLAGS     =	-gdwarf-4 $(ARCH) -nostdlib -Wl,--no-warn-rwx-segments,-Map,$(notdir $*.map) $(BN_LDFLAGS_SUFFIX)
else
	LDFLAGS     =	-gdwarf-4 $(ARCH) -Wl,--no-warn-rwx-segments,-Map,$(notdir $*.map) $(BN_LDFLAGS_SUFFIX)
endif

#---------------------------------------------------------------------------------------------------------------------
# Sources setup:
#---------------------------------------------------------------------------------------------------------------------
include $(BN_TOOLS)/sources_setup.mak

#---------------------------------------------------------------------------------------------------------------------
# Don't remove intermediary files (avoid rebuilding graphics files more than once):
#---------------------------------------------------------------------------------------------------------------------
.SECONDARY:

ifneq ($(BUILD),$(notdir $(CURDIR)))
#---------------------------------------------------------------------------------------------------------------------
# Common setup:
#---------------------------------------------------------------------------------------------------------------------
include $(BN_TOOLS)/common_setup.mak

#---------------------------------------------------------------------------------------------------------------------
else
 
#---------------------------------------------------------------------------------------------------------------------
# Main targets:
#---------------------------------------------------------------------------------------------------------------------

$(OUTPUT).gba       :   $(OUTPUT).elf
	@echo Fixing $(notdir $@) ...
	$(_V)$(WONDERFUL_TOOLCHAIN)/bin/wf-gbatool fix $@ -t "$(ROMTITLE)" --code "$(ROMCODE)"

$(OUTPUT).elf       :	$(OFILES)

$(OFILES_SOURCES)   :   $(HFILES)

#---------------------------------------------------------------------------------------------------------------------
# The bin2o rule should be copied and modified for each extension used in the data directories:
#---------------------------------------------------------------------------------------------------------------------

#---------------------------------------------------------------------------------------------------------------------
# This rule links in binary data with the .bin extension:
#---------------------------------------------------------------------------------------------------------------------
%.bin.o	%_bin.h : %.bin
#---------------------------------------------------------------------------------------------------------------------
	@echo "$<"
	@$(MKDIR) -p $(@D)
	$(_V)$(WF)/bin/wf-bin2c -a 4 $(@D) $< $*_bin
	@$(PYTHON) -B $(BN_TOOLS)/butano_awful_tool.py --file="$(@D)/$*_bin.c"
	$(_V)$(CC) $(CFLAGS) -MMD -MP -c -o $(@D)/$*.bin.o $(@D)/$*_bin.c

-include $(DEPSDIR)/*.d

#---------------------------------------------------------------------------------------------------------------------
endif
#---------------------------------------------------------------------------------------------------------------------
