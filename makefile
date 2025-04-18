# Compiler and flags
CC = gcc
CFLAGS = `pkg-config --cflags gtk+-3.0` -Wall -g
LDFLAGS = `pkg-config --libs gtk+-3.0`

# Source and object files
SRCS = main.c controller.c calculatorView.c matrixCalculatorView.c conversionView.c sampleModel.c view.c
OBJS = $(SRCS:.c=.o)

# Output executable
TARGET = calculator_app

# Build rule
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -f $(OBJS) $(TARGET)
