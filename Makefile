OUT_DIR 		?= bin
EXECUTABLE_NAME ?= game
SRC_DIR			?= src
CC 				?= gcc

FLAGS			?= -Iinclude -Llib/static
LINK_LIBS		?= -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

$(OUT_DIR)/$(EXECUTABLE_NAME): $(wildcard $(SRC_DIR)/*.c) | $(OUT_DIR)
	$(CC) $^ -o $@ $(FLAGS) $(LINK_LIBS)

$(OUT_DIR):
	mkdir -p $(OUT_DIR)

clean:
	rm -rf $(OUT_DIR)
