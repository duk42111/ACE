# -*- Makefile -*-

#----------------------------------------------------------------------------
#	$Id: rules.common.GNU 95440 2012-01-17 05:19:09Z jonesc $
#
#	Common targets
#----------------------------------------------------------------------------

.PHONY: __prebuild__

all:              __prebuild__ all.nested all.local
debug:	          debug.nested debug.local
profile:          profile.nested profile.local
binout:           binout.nested binout.local
clean_binout:     clean_binout.nested clean_binout.local
clean_binaries:   clean_binaries.nested clean_binaries.local
clean_idl_stubs:  clean_idl_stubs.nested clean_idl_stubs.local
clean:            clean.nested clean.local
realclean:        realclean.nested realclean.local
clobber:          clobber.nested clobber.local
depend:	          depend.nested depend.local depend_idl.local
rcs_info:         rcs_info.nested rcs_info.local
idl_stubs:        idl_stubs.nested idl_stubs.local
svnignore:	  svnignore.nested svnignore.local
