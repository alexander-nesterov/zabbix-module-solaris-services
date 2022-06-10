ZBX_VERSION=6.0.0
NAME_LIBRARY=solaris-scf.so
ROOT_SOURCES=src
SOURCES=$(ROOT_SOURCES)/module.c $(ROOT_SOURCES)/solaris-scf.c
ZBX_INCLUDE=zabbix/include
CFLAGS=-m64 -fPIC -shared -Wall
LDFLAGS=-lscf

.PHONY: clone
clone:
	@git clone https://github.com/zabbix/zabbix.git --branch $(ZBX_VERSION) --single-branch

.PHONY: build
build:
	gcc $(CFLAGS) $(LDFLAGS) -o $(NAME_LIBRARY) $(SOURCES) -I$(ZBX_INCLUDE)

.PHONY: clean
clean:
	rm -rf *.so