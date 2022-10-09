
#CXX = g++
CXX = /usr/bin/clang++

EXE = openfest.out
IMGUI_DIR = ..
SOURCES = main.mm
SOURCES += $(IMGUI_DIR)/imgui.cpp $(IMGUI_DIR)/imgui_demo.cpp $(IMGUI_DIR)/imgui_draw.cpp $(IMGUI_DIR)/imgui_tables.cpp $(IMGUI_DIR)/imgui_widgets.cpp
SOURCES += $(IMGUI_DIR)/backends/imgui_impl_glut.cpp  $(IMGUI_DIR)/backends/imgui_impl_opengl2.cpp
OBJS = $(addsuffix .o, $(basename $(notdir $(SOURCES))))

LIBS += -framework OpenGL -framework GLUT
LIBS += -L/usr/local/lib -L/opt/homebrew/lib
LIBS += -lglfw
LDFLAGS += -g

CXXFLAGS = -fdiagnostics-color=always -g -std=c++17 -I$(IMGUI_DIR) -I$(IMGUI_DIR)/backends -I/usr/local/include -I/opt/homebrew/include -I/opt/local/include
CXXFLAGS += -Wall -Wformat
CXXFLAGS += -g -fcolor-diagnostics -fansi-escape-codes -Wall
CFLAGS = $(CXXFLAGS)

%.o:%.cpp
	$(CXX) $(CXXFLAGS) -c -g -o $@ $<

%.o:$(IMGUI_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -g -o $@ $<

%.o:$(IMGUI_DIR)/backends/%.cpp
	$(CXX) $(CXXFLAGS) -c -g -o $@ $<

%.o:%.mm
	$(CXX) $(CXXFLAGS) -ObjC++ -fobjc-weak -fobjc-arc -c -o $@ $<

%.o:$(IMGUI_DIR)/backends/%.mm
	$(CXX) $(CXXFLAGS) -ObjC++ -fobjc-weak -fobjc-arc -c -o $@ $<

all: $(EXE)
	@echo Build complete

$(EXE): $(OBJS)
	$(CXX) -g -o $@ $^ $(CXXFLAGS) $(LIBS)

clean:
	rm -f $(EXE) $(OBJS)
	rm -drf *.dSYM
	rm -f *.out
