#include <Shader.h>
#include <stdlib.h>


GLuint Shader::loadShader(GLenum shaderType, const char* pSource) {
    GLuint shader = glCreateShader(shaderType);
    if (shader) {
        glShaderSource(shader, 1, &pSource, NULL);
        glCompileShader(shader);
        GLint compiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        if (!compiled) {
            GLint infoLen = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
            if (infoLen) {
                char* buf = (char*) malloc(infoLen);
                if (buf) {
                    glGetShaderInfoLog(shader, infoLen, NULL, buf);
                    #ifndef WINDOWS_FRAMEWORK
                    LOGE("Could not compile shader %d:\n%s\n",
                            shaderType, buf);
                    #else
 
                    #endif
                     
                         
                    free(buf);
                }
                glDeleteShader(shader);
                shader = 0;
            }
        }
    }
    return shader;
} 

Shader::Shader(void)
{
	
	opacity = 1;

	static const char gVertexShader[] = 
    "attribute vec3 vPosition;\n"
	"attribute vec2 vUv;\n"
	"uniform mat4 Projection;\n"
	"uniform mat4 Translation;\n"
	"uniform mat4 Scale;\n"
	"uniform mat4 Rotation;\n"
	"varying vec2 Uv;\n"
    "void main() {\n"
	"  gl_Position = vec4(vPosition,1.0);\n"
	"  gl_Position *= Scale;\n"	
	"  gl_Position *= Rotation;\n"	
	"  gl_Position *= Translation;\n"	
	"  gl_Position *= Projection;\n"	
	"  Uv = vUv;\n"
    "}\n";
 
    static const char gFragmentShader[] = 
	"precision mediump float;\n"
	"varying vec2 Uv;\n"
	"uniform sampler2D s_texture;\n"
    "uniform vec3 color; \n"
	"uniform float opacity; \n"
	"void main() {\n"
    "gl_FragColor = texture2D(s_texture,Uv)*1;\n"//opacityn muutokset
    "}\n"; 

	PS = loadShader(GL_FRAGMENT_SHADER,gFragmentShader); 
    VS = loadShader(GL_VERTEX_SHADER,gVertexShader); 

    Program = glCreateProgram(); 
  

    glAttachShader(Program,VS); 
    glAttachShader(Program,PS); 
    glLinkProgram(Program); 

    glBindAttribLocation(Program,0,"vPosition"); 

	glBindAttribLocation(Program,1,"vUv"); 

	Position = glGetAttribLocation(Program,"vPosition");
	Uv = glGetAttribLocation(Program,"vUv");
	loc = glGetUniformLocation(Program, "s_texture");
	loc2 = glGetUniformLocation(Program, "Projection");
	loc3 = glGetUniformLocation(Program, "Translation");
	loc4 = glGetUniformLocation(Program, "Rotation");
	loc5 = glGetUniformLocation(Program, "Scale");
	loc6 = glGetUniformLocation(Program, "color");
	loc7 = glGetUniformLocation(Program, "opacity");


}


Shader::~Shader(void)
{
}
