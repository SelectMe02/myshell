PROJ_DIR = $(shell pwd)
SRC_DIR = $(PROJ_DIR)/src
INC_DIR = $(PROJ_DIR)/include
OBJ_DIR = $(PROJ_DIR)/obj
BIN_DIR = $(PROJ_DIR)/bin

$(BIN_DIR)/myshell: $(OBJ_DIR)/myshell.o $(OBJ_DIR)/ls_command.o | $(BIN_DIR)
	gcc -o $@ $^

$(BIN_DIR):
	mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	gcc -c -o $@ $< -I$(INC_DIR)

$(OBJ_DIR):
	mkdir -p $@

clean:
	rm -f $(OBJ_DIR)/*.o $(BIN_DIR)/myshell

distclean:
	rm -f $(OBJ_DIR)/*.o $(BIN_DIR)/myshell
	rm -rf $(OBJ_DIR) $(BIN_DIR)