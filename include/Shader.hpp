#ifndef SHADER_HPP
#define	SHADER_HPP
#include <iostream>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <sstream>
#include <fstream>
class Shader {
public:
	Shader(std::string vertSrc, std::string fragSrc);
	bool build();
	void use() const;

	void setBool(std::string& name,bool  val)	const;
	void setFloat(std::string& name,float val)	const;
	void setInt(std::string& name,int val)	const;
	void setFloat3(std::string& name,float x, float y, float z)	const;
	void setMat4(std::string& name,const glm::mat4& matrix)	const;

private:
	unsigned int id;
	std::string vertCode, fragCode;
};
#endif