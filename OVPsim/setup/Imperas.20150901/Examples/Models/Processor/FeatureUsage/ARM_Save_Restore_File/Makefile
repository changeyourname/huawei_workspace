PLATFORM=platform/platform.${IMPERAS_ARCH}.exe
APPLICATION=application/asmtest.elf
SR_FILE=state

run : $(PLATFORM) $(APPLICATION)
	$(PLATFORM) $(APPLICATION)
	$(PLATFORM) $(APPLICATION) 500 $(SR_FILE) 1 0
	$(PLATFORM) $(APPLICATION) -1  $(SR_FILE) 0 1

$(APPLICATION):
	$(MAKE) -C application

$(PLATFORM):
	$(MAKE) -C platform

clean:
	$(MAKE) -C application clean
	$(MAKE) -C platform clean
	rm -f $(SR_FILE)


help:
	@echo The following targets are available to start simulation
	@echo run    : run simulation using an ICM Platform saving and restoring a state file
