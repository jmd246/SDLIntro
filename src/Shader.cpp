#include <Shader.hpp>
#include <SDL3/SDL_opengl.h>

	Shader::Shader(std::string vertSrc,std::string fragSrc) {
		std::ifstream vertFile,fragFile;
		// Set the exception mask to throw on badbit and failbit
		vertFile.exceptions(std::ifstream::badbit | std::ifstream::failbit);
		fragFile.exceptions(std::ifstream::badbit | std::ifstream::failbit);
		try {
			//open files
			vertFile.open(vertSrc);
			fragFile.open(fragSrc);
			std::stringstream	vShaderStream, fShaderStream;
			vShaderStream << vertFile.rdbuf();
			fShaderStream << fragFile.rdbuf();
			//read file stroe as string
			vertCode = vShaderStream.str();
			fragCode = fShaderStream.str();
			//close files
			vertFile.close();
			fragFile.close();
		}
		catch (const std::ios_base::failure& e) {
			std::cerr << "file	failed	to	be	opened " << e.what() << std::endl;
		}
	}
	 bool Shader::build() {
		 unsigned int vert, frag;
		 int success;
		 char log[512];
		 vert = glCreateShader(GL_VERTEX_SHADER);
		 frag = glCreateShader(GL_FRAGMENT_SHADER);
		 const char *vertSrc = vertCode.c_str(), *fragSrc = fragCode.c_str();
		 
		 glShaderSource(vert, 1, &vertSrc, NULL);
		 glCompileShader(vert);
		 glGetShaderiv(vert ,GL_COMPILE_STATUS, &success);
		 if (!success) {
			 glGetShaderInfoLog(vert, 512, NULL, log);
			 std::cout << log << std::endl;
			 return false;
		 }
		 glShaderSource(frag, 1, &fragSrc, NULL);
		 glCompileShader(frag);
		 glGetShaderiv(frag, GL_COMPILE_STATUS, &success);
		 if (!success) {
			 glGetShaderInfoLog(vert, 512, NULL, log);
			 std::cout << log << std::endl;
			 return false;
		 }
		 id = glCreateProgram();
		 glAttachShader(id, vert);
		 glAttachShader(id, frag);
		 glLinkProgram(id);
		 glGetProgramiv(id, GL_LINK_STATUS, &success);
		 if (!success) {
			 glGetProgramInfoLog(id, 512, NULL, log);
			 std::cout << log << std::endl;
			 return false;
		 }
		 glDeleteShader(vert);
		 glDeleteShader(frag);
		return true;
	}
	void Shader::use() {
		glUseProgram(id);
	}

	void Shader::setBool(std::string &name,bool  val) {
		glUniform1i(glGetUniformLocation(id, name.c_str()), val);
	}
	void Shader::setFloat(std::string& name, float val) {
		glUniform1f(glGetUniformLocation(id, name.c_str()), val);
	}
	void Shader::setInt(std::string& name, int val) {
		glUniform1i(glGetUniformLocation(id, name.c_str()), val);

	}
	void Shader::setFloat3(std::string& name, float x, float y, float z) {
		glUniform3f(glGetUniformLocation(id, name.c_str()), x,y,z);
	}