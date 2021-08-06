SRC_DIR = .
OUT_DIR = .
CC = g++
CXXFLAGS = -I$(SRC_DIR) -g

_SOURCES = Document.cpp \
		   DocumentFactory.cpp \
		   DocumentIO.cpp \
		   UserInputManager.cpp \
		   UserInterface.cpp \
		   TextDocument/TextDocument.cpp \
		   TextDocument/TextDocumentInterfaces.cpp \
		   SessionManager.cpp
SOURCES = $(patsubst %,$(SRC_DIR)/%,$(_SOURCES))

OBJECTS = $(SOURCES:%.cpp=%.o)

#LIBS = -lm


all: build clean

build: $(OBJECTS)
	$(CC) ${SRC_DIR}/main.cpp $(CXXFLAGS) $(OBJECTS)

%.o: %.cpp
	$(CC) -c $< -o $@ $(CXXFLAGS)

_run: build
	@./a.out
	@rm ./a.out

run: _run clean

_debug: build
	@gdb -q a.out

debug : _debug clean

clean:
	@rm -rvf $(SRC_DIR)/*.o
	@rm -rvf $(SRC_DIR)/*/*.o
