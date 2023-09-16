# Default is x86_64
.PHONY: default
default: c-picross

c_source_files := $(shell find src -name *.c)
c_object_files := $(patsubst src/%.c, build/%.o, $(c_source_files))

C_INCLUDE_PATH := include

OUT_NAME := c-picross

GTK_OPTN := "$(pkg-config --cflags --libs gtk+-2.0)"
OPTN := -g `pkg-config --cflags --libs gtk+-2.0`# -Ofast -march=znver3 ou march=native


$(c_object_files): build/%.o : src/%.c
	@echo $(OPTN)
	@mkdir -p $(dir $@) && \
	gcc $(OPTN) -c -Wall -I $(C_INCLUDE_PATH) $(patsubst build/%.o, src/%.c, $@) -o $@ -lm

.PHONY: c-picross
c-picross: $(c_object_files)
	@echo "[C Files] :"
	@echo $(c_source_files)
	@echo "[C OBJ Files] :"
	@echo $(c_object_files)
	@gcc $(OPTN) -Wall -o $(OUT_NAME) $(c_object_files) -lm $(OPTN) 

CLEAN:
	@rm -rfv build/
	@mkdir build
	@echo "CLEAN"