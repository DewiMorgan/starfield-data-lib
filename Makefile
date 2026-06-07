CXX = g++
CXXFLAGS = -std=c++20 -O3 -Isrc
LDFLAGS = -lmysqlclient -lz

# Directories
BIN_DIR = bin
CORE_DIR = src/core
DB_DIR = src/db
TOOLS_DIR = src/tools

# Object files
CORE_OBJS = $(CORE_DIR)/parser.o $(CORE_DIR)/indexer.o
DB_OBJS = $(DB_DIR)/mysql_client.o

# Target binaries
TARGETS = $(BIN_DIR)/sdl_bulk_dump $(BIN_DIR)/sdl_search $(BIN_DIR)/starfield_reader $(BIN_DIR)/dump_record $(BIN_DIR)/header_dump

.PHONY: all clean test

all: $(TARGETS)

$(BIN_DIR)/sdl_bulk_dump: $(TOOLS_DIR)/sdl_bulk_dump.o $(CORE_OBJS) $(DB_OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o $@

$(BIN_DIR)/sdl_search: $(TOOLS_DIR)/sdl_search.o $(CORE_OBJS) $(DB_OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o $@

$(BIN_DIR)/starfield_reader: $(TOOLS_DIR)/starfield_reader.o $(CORE_OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o $@

$(BIN_DIR)/dump_record: $(TOOLS_DIR)/dump_record.o $(CORE_OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o $@

$(BIN_DIR)/header_dump: $(TOOLS_DIR)/header_dump.o
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o $@

# Generic rule for object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(CORE_DIR)/*.o $(DB_DIR)/*.o $(TOOLS_DIR)/*.o
	rm -rf $(BIN_DIR)

test: all
	@echo "Running tests..."
	# For now, just check if binaries exist and run a dry-run if possible
	# Real test integration would go here
	./$(BIN_DIR)/sdl_bulk_dump --help || echo "Tests failing or help not implemented"
