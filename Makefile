CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g -Isrc `pkg-config --cflags gtkmm-3.0`
LIBS = `pkg-config --libs gtkmm-3.0`
TARGET = digital-logic-suite

SOURCES = main.cpp \
          src/MainWindow.cpp

OBJDIR = obj
OBJECTS = $(SOURCES:%.cpp=$(OBJDIR)/%.o)

# Set locale environment
export LC_ALL=C.UTF-8
export LANG=C.UTF-8

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LIBS)

$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: clean run all
