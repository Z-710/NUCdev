CC = gcc
CFLAGS = -Wall -Werror
SRC = src
OUTPUT = output
OBJ = $(OUTPUT)/types.o $(OUTPUT)/loadProducts.o $(OUTPUT)/compress.o $(OUTPUT)/admin.o $(OUTPUT)/customer.o $(OUTPUT)/loadUsers.o $(OUTPUT)/login.o $(OUTPUT)/main.o

all: main.out

main.out: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o main.out

$(OUTPUT)/types.o: $(SRC)/types.c $(SRC)/system.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OUTPUT)/admin.o: $(SRC)/admin.c $(SRC)/system.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OUTPUT)/customer.o: $(SRC)/customer.c $(SRC)/system.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OUTPUT)/loadUsers.o: $(SRC)/loadUsers.c $(SRC)/system.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OUTPUT)/loadProducts.o: $(SRC)/loadProducts.c $(SRC)/system.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OUTPUT)/login.o: $(SRC)/login.c $(SRC)/system.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OUTPUT)/compress.o: $(SRC)/compress.c $(SRC)/system.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OUTPUT)/main.o: $(SRC)/main.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f main.out $(OBJ)

