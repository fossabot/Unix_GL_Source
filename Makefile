
# Arch Linux Based Systems
A:
	$(MAKE) -C Arch

# Debian Linux Based Systems
D:
	$(MAKE) -C Debian

# Mac OS X
M:
	$(MAKE) -C Mac


clean:
	rm -rf *o program_arch program_debian program_mac
