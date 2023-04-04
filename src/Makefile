# ************************************************************************* #
#   LTD - Tecnologia Digital 2 - Trabajo Practico 2                         #
# ************************************************************************* #

BUILD_DIR = build
LIBS_OBJS = libbmp.o utils.o
OBJS = $(addprefix $(BUILD_DIR)/, $(LIBS_OBJS))

.PHONY: all clean

all: EdgeDetect_S EdgeDetect_P2H EdgeDetect_P2V EdgeDetect_P4H EdgeDetect_P4V

EdgeDetect_S: EdgeDetect_S.c common.c
	mkdir -p build
	make -C lib
	gcc $(OBJS) $^ -o $@ -lm

EdgeDetect_P2H: EdgeDetect_P2H.c common.c
	mkdir -p build
	make -C lib
	gcc $(OBJS) $^ -o $@ -lm

EdgeDetect_P2V: EdgeDetect_P2V.c common.c
	mkdir -p build
	make -C lib
	gcc $(OBJS) $^ -o $@ -lm

EdgeDetect_P4H: EdgeDetect_P4H.c common.c
	mkdir -p build
	make -C lib
	gcc $(OBJS) $^ -o $@ -lm

EdgeDetect_P4V: EdgeDetect_P4V.c common.c
	mkdir -p build
	make -C lib
	gcc $(OBJS) $^ -o $@ -lm

clean:
	rm -fr $(BUILD_DIR)/*
	rm -f EdgeDetect_S EdgeDetect_P2H EdgeDetect_P2V EdgeDetect_P4H EdgeDetect_P4V	
