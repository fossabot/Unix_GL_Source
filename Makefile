UBUNTU = $(shell echo "Ubuntu")

all:
	$(MAKE) $(shell lsb_release -si)

# Arch Linux Based Systems
A:
	$(MAKE) -C Arch

# Debian Linux Based Systems
Ubuntu:
	$(MAKE) -C Debian

# Mac OS X
M:
	$(MAKE) -C Mac


clean:
	@rm -rf *o program_arch program_debian program_mac ./Arch/*o ./Debian/*o ./Mac/*o
