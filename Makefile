CPPFLAGS 	:= -Wall -MMD -MP -std=c++11
GL_FLAGS 	:= -l glfw3dll -lglew32 -lopengl32
INCL_DIRS 	:= -Isrc\thirdparty\glfw-master\include -Isrc\thirdparty\glew-2.1.0\include -Isrc\thirdparty\glm-0.9.9.8 -Isrc\thirdparty\stb_image -Isrc\imgui
LIBS		:= --static -Lsrc\thirdparty\glfw-master\Debug/Lib -Lsrc\thirdparty\glew-2.1.0\lib\Release\x64
BUILD_DIR 	:= out
IMGUI_DIR	:= src/imgui
INTER_DIR 	:= out/int
EXEC_TARGET 	:= Render
SRCS 		:= src/%.cpp
IMGUI_SRCS	:= $(IMGUI_DIR)/%.cpp
OBJS 		:= $(INTER_DIR)/LearnRenderingEngine.o

# glfw3.lib imgui_draw.cpp imgui_tables.cpp imgui_widgets.cpp
Symbols: $(BUILD_DIR)/$(EXEC_TARGET)
	objdump --syms $(BUILD_DIR)/$(EXEC_TARGET).exe > $(BUILD_DIR)/$(EXEC_TARGET).pdb
$(BUILD_DIR)/$(EXEC_TARGET): $(OBJS) out/int/imgui.o out/int/imgui_draw.o out/int/imgui_tables.o out/int/imgui_widgets.o
	# Linka todos los objs en el ejecutable correspondiente
	$(CXX) $(OBJS) -o $@ $(LIBS) $(GL_FLAGS)

$(INTER_DIR)/%.o: $(SRCS)
	# Compila todos los .cpp en .o con sus correspondientes nombres
	$(CXX) -c $(CFLAGS) $(CPPFLAGS) $(INCL_DIRS)  $< -o $@

$(INTER_DIR)/%.o: $(IMGUI_SRCS)
	# Compila todos los .cpp en .o con sus correspondientes nombres
	$(CXX) -c $(CFLAGS) $(CPPFLAGS) $< -o $@
