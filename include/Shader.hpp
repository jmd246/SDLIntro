#ifndef SHADER_HPP
#define	SHADER_HPP
#include <iostream>
#include <glad/glad.h>
#include <sstream>
#include <fstream>
class Shader {
public:
	Shader(std::string vertSrc, std::string fragSrc);
	bool build();
	void use();

	void setBool(std::string& name,bool  val);
	void setFloat(std::string& name,float val);
	void setInt(std::string& name,int val);
	void setFloat3(std::string& name,float x, float y, float z);

private:
	unsigned int id;
	std::string vertCode, fragCode;
};
#endif