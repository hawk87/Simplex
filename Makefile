ifneq ($(words $(MAKECMDGOALS)),1)
.DEFAULT_GOAL = all
%:
	@$(MAKE) $@ --no-print-directory -rRf $(firstword $(MAKEFILE_LIST))
else
ifndef ECHO
T := $(shell $(MAKE) $(MAKECMDGOALS) --no-print-directory \
      -nrRf $(firstword $(MAKEFILE_LIST)) \
      ECHO="COUNTTHIS" | grep -c "COUNTTHIS")

N := x
C = $(words $N)$(eval N := x $N)
ECHO = echo "`expr " [\`expr $C '*' 100 / $T\`" : '.*\(....\)$$'`%]"
endif

MKDIR_P = mkdir -p
SRC_DIR = ./src
OUT_DIR = ./bin

.PHONY: directories
#.PHONY: all clean

all: directories main
	@$(ECHO) All done

main: main.o simplex.o twophases.o
	gcc -o ${OUT_DIR}/main ${OUT_DIR}/main.o ${OUT_DIR}/simplex.o ${OUT_DIR}/twophases.o
	@$(ECHO) Linking $@
	@sleep 0.1

simplex.o: ${SRC_DIR}/simplex.c
	gcc -g -c -o ${OUT_DIR}/simplex.o ${SRC_DIR}/simplex.c
	@$(ECHO) Compiling $@
	@sleep 0.1

twophases.o: ${SRC_DIR}/twophases.c
	gcc -g -c -o ${OUT_DIR}/twophases.o ${SRC_DIR}/twophases.c
	@$(ECHO) Compiling $@
	@sleep 0.1

main.o: ${SRC_DIR}/main.c
	gcc -g -c -o ${OUT_DIR}/main.o ${SRC_DIR}/main.c
	@$(ECHO) Compiling $@
	@sleep 0.1

directories: ${OUT_DIR}

${OUT_DIR}:
	${MKDIR_P} ${OUT_DIR}

clean:
	rm -rf ${OUT_DIR}
	@$(ECHO) Clean done

endif
