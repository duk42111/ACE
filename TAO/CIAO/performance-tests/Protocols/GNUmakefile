# -*- makefile -*-
#----------------------------------------------------------------------------
#       GNU ACE Workspace
#
# $Id: GNUACEWorkspaceCreator.pm 94635 2011-10-06 12:59:23Z johnnyw $
#
# This file was generated by MPC.  Any changes made directly to
# this file will be lost the next time it is generated.
#
# MPC Command:
# /home/build/DOC_ROOT/stage-644/ACE_wrappers/bin/mwc.pl -type gnuace -exclude "TAO/TAO_*.mwc,TAO/CIAO/CIAO_*.mwc" -workers 10 -recurse -hierarchy -relative ACE_ROOT=/home/build/DOC_ROOT/stage-644/ACE_wrappers -relative TAO_ROOT=/home/build/DOC_ROOT/stage-644/ACE_wrappers/TAO -relative CIAO_ROOT=/home/build/DOC_ROOT/stage-644/ACE_wrappers/TAO/CIAO -relative DANCE_ROOT=/home/build/DOC_ROOT/stage-644/ACE_wrappers/TAO/DAnCE
#
#----------------------------------------------------------------------------

MAKEFILE = GNUmakefile

ifeq ($(findstring k,$(MAKEFLAGS)),k)
  KEEP_GOING = -
endif

include $(ACE_ROOT)/include/makeinclude/macros.GNU

all: Protocols_idl_gen Protocols_lem_gen Protocols_stub Protocols_Receiver_idl_gen Protocols_Receiver_stub Protocols_Sender_idl_gen Protocols_Sender_stub Protocols_Controller Protocols_Receiver_lem_gen Protocols_Receiver_exec Protocols_skel Protocols_Receiver_svnt Protocols_Sender_lem_gen Protocols_Sender_exec Protocols_Sender_svnt

REMAINING_TARGETS := $(filter-out all,$(TARGETS_NESTED:.nested=)) $(CUSTOM_TARGETS)

$(REMAINING_TARGETS):
	$(KEEP_GOING)@cd common && $(MAKE) -f GNUmakefile.Protocols_idl_gen $(@)
	$(KEEP_GOING)@cd common && $(MAKE) -f GNUmakefile.Protocols_lem_gen $(@)
	$(KEEP_GOING)@cd common && $(MAKE) -f GNUmakefile.Protocols_stub $(@)
	$(KEEP_GOING)@cd Receiver && $(MAKE) -f GNUmakefile.Protocols_Receiver_idl_gen $(@)
	$(KEEP_GOING)@cd Receiver && $(MAKE) -f GNUmakefile.Protocols_Receiver_stub $(@)
	$(KEEP_GOING)@cd Sender && $(MAKE) -f GNUmakefile.Protocols_Sender_idl_gen $(@)
	$(KEEP_GOING)@cd Sender && $(MAKE) -f GNUmakefile.Protocols_Sender_stub $(@)
	$(KEEP_GOING)@cd Controller && $(MAKE) -f GNUmakefile.Protocols_Controller $(@)
	$(KEEP_GOING)@cd Receiver && $(MAKE) -f GNUmakefile.Protocols_Receiver_lem_gen $(@)
	$(KEEP_GOING)@cd Receiver && $(MAKE) -f GNUmakefile.Protocols_Receiver_exec $(@)
	$(KEEP_GOING)@cd common && $(MAKE) -f GNUmakefile.Protocols_skel $(@)
	$(KEEP_GOING)@cd Receiver && $(MAKE) -f GNUmakefile.Protocols_Receiver_svnt $(@)
	$(KEEP_GOING)@cd Sender && $(MAKE) -f GNUmakefile.Protocols_Sender_lem_gen $(@)
	$(KEEP_GOING)@cd Sender && $(MAKE) -f GNUmakefile.Protocols_Sender_exec $(@)
	$(KEEP_GOING)@cd Sender && $(MAKE) -f GNUmakefile.Protocols_Sender_svnt $(@)

.PHONY: Protocols_idl_gen
Protocols_idl_gen:
	$(KEEP_GOING)@cd common && $(MAKE) -f GNUmakefile.Protocols_idl_gen all

.PHONY: Protocols_lem_gen
Protocols_lem_gen: Protocols_idl_gen
	$(KEEP_GOING)@cd common && $(MAKE) -f GNUmakefile.Protocols_lem_gen all

.PHONY: Protocols_stub
Protocols_stub: Protocols_lem_gen
	$(KEEP_GOING)@cd common && $(MAKE) -f GNUmakefile.Protocols_stub all

.PHONY: Protocols_Receiver_idl_gen
Protocols_Receiver_idl_gen: Protocols_idl_gen
	$(KEEP_GOING)@cd Receiver && $(MAKE) -f GNUmakefile.Protocols_Receiver_idl_gen all

.PHONY: Protocols_Receiver_stub
Protocols_Receiver_stub: Protocols_stub Protocols_Receiver_idl_gen
	$(KEEP_GOING)@cd Receiver && $(MAKE) -f GNUmakefile.Protocols_Receiver_stub all

.PHONY: Protocols_Sender_idl_gen
Protocols_Sender_idl_gen:
	$(KEEP_GOING)@cd Sender && $(MAKE) -f GNUmakefile.Protocols_Sender_idl_gen all

.PHONY: Protocols_Sender_stub
Protocols_Sender_stub: Protocols_stub Protocols_Sender_idl_gen
	$(KEEP_GOING)@cd Sender && $(MAKE) -f GNUmakefile.Protocols_Sender_stub all

.PHONY: Protocols_Controller
Protocols_Controller: Protocols_Receiver_stub Protocols_Sender_stub
	$(KEEP_GOING)@cd Controller && $(MAKE) -f GNUmakefile.Protocols_Controller all

.PHONY: Protocols_Receiver_lem_gen
Protocols_Receiver_lem_gen: Protocols_Receiver_idl_gen
	$(KEEP_GOING)@cd Receiver && $(MAKE) -f GNUmakefile.Protocols_Receiver_lem_gen all

.PHONY: Protocols_Receiver_exec
Protocols_Receiver_exec: Protocols_Receiver_stub Protocols_Receiver_lem_gen
	$(KEEP_GOING)@cd Receiver && $(MAKE) -f GNUmakefile.Protocols_Receiver_exec all

.PHONY: Protocols_skel
Protocols_skel: Protocols_stub
	$(KEEP_GOING)@cd common && $(MAKE) -f GNUmakefile.Protocols_skel all

.PHONY: Protocols_Receiver_svnt
Protocols_Receiver_svnt: Protocols_Receiver_exec Protocols_skel
	$(KEEP_GOING)@cd Receiver && $(MAKE) -f GNUmakefile.Protocols_Receiver_svnt all

.PHONY: Protocols_Sender_lem_gen
Protocols_Sender_lem_gen: Protocols_Sender_idl_gen
	$(KEEP_GOING)@cd Sender && $(MAKE) -f GNUmakefile.Protocols_Sender_lem_gen all

.PHONY: Protocols_Sender_exec
Protocols_Sender_exec: Protocols_Sender_stub Protocols_Sender_lem_gen
	$(KEEP_GOING)@cd Sender && $(MAKE) -f GNUmakefile.Protocols_Sender_exec all

.PHONY: Protocols_Sender_svnt
Protocols_Sender_svnt: Protocols_skel Protocols_Sender_exec
	$(KEEP_GOING)@cd Sender && $(MAKE) -f GNUmakefile.Protocols_Sender_svnt all

project_name_list:
	@echo Protocols_Controller
	@echo Protocols_Receiver_exec
	@echo Protocols_Receiver_idl_gen
	@echo Protocols_Receiver_lem_gen
	@echo Protocols_Receiver_stub
	@echo Protocols_Receiver_svnt
	@echo Protocols_Sender_exec
	@echo Protocols_Sender_idl_gen
	@echo Protocols_Sender_lem_gen
	@echo Protocols_Sender_stub
	@echo Protocols_Sender_svnt
	@echo Protocols_idl_gen
	@echo Protocols_lem_gen
	@echo Protocols_skel
	@echo Protocols_stub
