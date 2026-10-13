INPUT=src/exp.c
OUTPUT=build/exp

all: $(OUTPUT)

$(OUTPUT): $(INPUT)
	mkdir -p build
	gcc $< -o $@ -lm
