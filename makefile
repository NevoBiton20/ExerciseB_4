CXX=clang++-14
CXXFLAGS=-std=c++2a -Werror -Wsign-conversion
VALGRIND_FLAGS=-v --leak-check=full --show-leak-kinds=all  --error-exitcode=99
SOURCES= Complex.cpp
OBJECTS=$(subst .cpp,.o,$(SOURCES))

tree: mainP
	./$^

mainP: Main.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o mainP -lsfml-graphics -lsfml-window -lsfml-system

demo: demoRun
	./$^

testing: test
	./$^

demoRun: Demo.o
	$(CXX) $(CXXFLAGS) $^ -o demoRun -lsfml-graphics -lsfml-window -lsfml-system

test: TestCounter.o Test.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o test

tidy:
	clang-tidy $(SOURCES) -checks=bugprone-*,clang-analyzer-*,cppcoreguidelines-*,performance-*,portability-*,readability-*,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-cppcoreguidelines-owning-memory --warnings-as-errors=-* --

valgrind: demo tree
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./demo 2>&1 | { egrep "lost| at " || true; }
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./test 2>&1 | { egrep "lost| at " || true; }

%.o: %.cpp
	$(CXX) $(CXXFLAGS) --compile $< -o $@

clean:
	rm -f *.o demo demoRun mainP test