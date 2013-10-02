DIRS = bin
TARGET = bin/ssivm

$(TARGET): $(DIRS)
	gcc -o $@ src/main.c
$(DIRS):
	mkdir -p $@

run: $(TARGET)
	$(TARGET)

clean:
	rm -rf $(DIRS)
