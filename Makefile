CC=clang
EXE=bored.sh
SRC_DIR = src

boredsh: $(SRC_DIR)/main.c
	$(CC) -o $(EXE) $(SRC_DIR)/main.c

clean:
	rm -f $(EXE)
