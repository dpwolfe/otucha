INC = -I. -Iterasca -Is1 -Irffalcon -I../external/include
C_FLAGS = -g -c -DGL_GLEXT_PROTOTYPES $(INC)

LINK = $(CXX) -v -fPIC -g
LOCAL_UTIL_LIBRARIES = -L../external/lib
OGL_LIBRARIES = -lglew32 -lglfw3 -lGlU32

OBJS = otucha.o Controller.o GLFWController.o ModelView.o ModelViewWithShader.o ShaderProgram.o AffinePoint.o AffineVector.o Matrix3x3.o Matrix4x4.o Block.o

otucha: $(OBJS)
	$(LINK) $(OBJS) $(LOCAL_UTIL_LIBRARIES) $(OGL_LIBRARIES) -s USE_GLFW=3 -o otucha.html --embed-file simple.vsh --embed-file simple.fsh
	
otucha.o: otucha.cpp
	$(CXX) $(C_FLAGS) otucha.cpp
	
Controller.o: terasca/Controller.hpp terasca/Controller.cpp
	$(CXX) $(C_FLAGS) terasca/Controller.cpp
GLFWController.o: terasca/GLFWController.hpp terasca/GLFWController.cpp
	$(CXX) $(C_FLAGS) terasca/GLFWController.cpp
ModelView.o: terasca/ModelView.hpp terasca/ModelView.cpp
	$(CXX) $(C_FLAGS) terasca/ModelView.cpp
ModelViewWithShader.o: terasca/ModelViewWithShader.hpp terasca/ModelViewWithShader.cpp
	$(CXX) $(C_FLAGS) terasca/ModelViewWithShader.cpp
ShaderProgram.o: terasca/ShaderProgram.hpp terasca/ShaderProgram.cpp
	$(CXX) $(C_FLAGS) terasca/ShaderProgram.cpp
 
AffinePoint.o: s1/AffinePoint.hpp s1/AffinePoint.cpp
	$(CXX) $(C_FLAGS) s1/AffinePoint.cpp
AffineVector.o: s1/AffineVector.hpp s1/AffineVector.cpp
	$(CXX) $(C_FLAGS) s1/AffineVector.cpp
Matrix3x3.o: s1/Matrix3x3.hpp s1/Matrix3x3.cpp
	$(CXX) $(C_FLAGS) s1/Matrix3x3.cpp
Matrix4x4.o: s1/Matrix4x4.hpp s1/Matrix4x4.cpp
	$(CXX) $(C_FLAGS) s1/Matrix4x4.cpp
	
Block.o: rffalcon/Block.hpp rffalcon/Block.cpp
	$(CXX) $(C_FLAGS) rffalcon/Block.cpp
