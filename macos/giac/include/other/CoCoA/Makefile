# Makefile for directory CoCoALib/include/CoCoA/.

COCOA_ROOT=../..
include $(COCOA_ROOT)/configuration/autoconf.mk
CWD=include/CoCoA/

# Default is to rebuild the unified header (in library.H)
.PHONY: default
default:
	@echo
	@echo "Rebuilding CoCoALib unified header file in $(CWD) for version $(VERSION)."
	@./MakeUnifiedHeader.sh "$(VERSION)"
	@echo

# Conditionally rebuild library.H only if version has changed.
library.H: $(COCOA_ROOT)/configuration/version
	@$(MAKE) default


.PHONY: clean clean-local
clean: clean-local
	@echo "Cleaned CoCoALib/$(CWD)"

clean-local:
	/bin/rm -f *~

.PHONY: veryclean veryclean-local
veryclean: veryclean-local
	@echo "Verycleaned CoCoALib/$(CWD)"

veryclean-local: clean-local
	/bin/rm -f library.H
