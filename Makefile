CXX = g++
CXXFLAGS = -std=c++20 -O3 -Isrc
COVERAGE_FLAGS = -std=c++20 -O0 --coverage -Isrc
LDFLAGS = -lmysqlclient -lz

# Directories
BIN_DIR = bin
CORE_DIR = src/core
DB_DIR = src/db
TOOLS_DIR = src/tools
TEST_DIR = test
DOCTEST_DIR = third_party/doctest

# Object files
CORE_OBJS = $(CORE_DIR)/parser.o $(CORE_DIR)/indexer.o
DB_OBJS = $(DB_DIR)/mysql_client.o

# Target binaries
TARGETS = $(BIN_DIR)/sdl_bulk_dump $(BIN_DIR)/sdl_search $(BIN_DIR)/starfield_reader $(BIN_DIR)/dump_record $(BIN_DIR)/header_dump

# Test configuration
TEST_CXXFLAGS = $(CXXFLAGS) -I$(DOCTEST_DIR) -I$(CORE_DIR) -I$(DB_DIR)

.PHONY: all clean test coverage

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
	find src -name "*.gc*" -delete
	rm -f *.gcda *.gcno *.gcov

coverage: clean
	@echo "Building with coverage..."
	$(MAKE) all CXXFLAGS="$(COVERAGE_FLAGS)"
	@echo "Running all tests..."
	$(MAKE) test CXXFLAGS="$(COVERAGE_FLAGS)" TEST_CXXFLAGS="$(COVERAGE_FLAGS) -I$(DOCTEST_DIR) -I$(CORE_DIR) -I$(DB_DIR)"
	@echo "Generating coverage reports..."
	gcov $(CORE_DIR)/*.cpp $(DB_DIR)/*.cpp
	@echo "--- Coverage Summary ---"
	gcov -s $(CORE_DIR)/*.cpp $(DB_DIR)/*.cpp

# Run a specific test: e.g., make test-smoke, make test-parser
test-%: all
	@echo "Running test suite: $*"
	@mkdir -p $(BIN_DIR)
	@FILE=$$(find $(TEST_DIR) -name "*$**.cpp" | head -n 1); \
	if [ -z "$$FILE" ]; then echo "Test suite '$*' not found in $(TEST_DIR)"; exit 1; fi; \
	bin=$(BIN_DIR)/test_$*; \
	$(CXX) $(TEST_CXXFLAGS) $$FILE $(CORE_OBJS) $(DB_OBJS) $(LDFLAGS) -o $$bin && ./$$bin

test: all
	@if [ -n "$(TEST)" ]; then \
		$(MAKE) test-$(TEST); \
	else \
		echo "Running all tests..."; \
		for file in $$(find $(TEST_DIR) -name "*.cpp"); do \
			name=$$(basename $$file .cpp); \
			$(MAKE) test-$$name; \
		done; \
	fi
