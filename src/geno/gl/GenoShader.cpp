/*******************************************************************************
 *
 * Copyright (c) 2018 Gnarly Narwhal
 *
 * -----------------------------------------------------------------------------
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files(the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 *******************************************************************************/

#include <iostream>
#include <fstream>
#include <cstring>

#include "GenoGL.h"

#include "GenoShader.h"

int32 GenoShader::active = 0;

GenoShader::GenoShader(const char * vert, const char * frag, bool file) {
	uint32 vertId = loadShader(vert, GL_VERTEX_SHADER, file);
	uint32 fragId = loadShader(frag, GL_FRAGMENT_SHADER, file);
	program = glCreateProgram();
	glAttachShader(program, vertId);
	glAttachShader(program, fragId);
	glLinkProgram(program);

	int result, length;
	glGetProgramiv(program, GL_LINK_STATUS, &result);
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);

	if (length > 1) {
		char * message = new char[length + 1];
		glGetProgramInfoLog(program, length, 0, message);
		std::cerr << message << std::endl;
		delete[] message;
	}

	glDetachShader(program, vertId);
	glDetachShader(program, fragId);

	glDeleteShader(vertId);
	glDeleteShader(fragId);
}

GenoShader::GenoShader(const char * vert, const char * geom, const char * frag, bool file) {
	uint32 vertId = loadShader(vert, GL_VERTEX_SHADER, file);
	uint32 geomId = loadShader(geom, GL_GEOMETRY_SHADER, file);
	uint32 fragId = loadShader(frag, GL_FRAGMENT_SHADER, file);
	program = glCreateProgram();
	glAttachShader(program, vertId);
	glAttachShader(program, geomId);
	glAttachShader(program, fragId);
	glLinkProgram(program);


	int result, length;
	glGetProgramiv(program, GL_LINK_STATUS, &result);
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);

	if (length > 1) {
		char * message = new char[length + 1];
		glGetProgramInfoLog(program, length, 0, message);
		std::cerr << message << std::endl;
		delete[] message;
	}

	glDetachShader(program, vertId);
	glDetachShader(program, geomId);
	glDetachShader(program, fragId);

	glDeleteShader(vertId);
	glDeleteShader(geomId);
	glDeleteShader(fragId);
}

uint32 GenoShader::loadShader(const char * path, int32 type, bool file) {
	int length;
	char * input;
	if (file) {
		std::ifstream fin(path, std::ifstream::binary);
		if (fin) {
			std::string contents((std::istreambuf_iterator<char>(fin)), std::istreambuf_iterator<char>());

			input = new char[contents.length() + 1];
			memcpy(input, contents.c_str(), contents.length());
			input[contents.length()] = 0;

			fin.close();
		}
		#ifdef _DEBUG
		else {
			std::cerr << "Genome Error (GenoShader): Cannot find shader '" << path << "'!" << std::endl;
			return 0;
		}
		#endif
	}
	else {
		length = strlen(path);
		input = new char[length];
		strcpy(input, path);
	}

	uint32 id = glCreateShader(type);
	glShaderSource(id, 1, &input, 0);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

	if (length > 1) {
		if(file)
			std::cerr << "Genome Error (GenoShader): Shader '" << path << "' compilation failed!" << std::endl;
		else
			std::cerr << "Genome Error (GenoShader): Shader compilation failed!" << std::endl;
		char * message = new char[length + 1];
		glGetShaderInfoLog(id, length, 0, message);
		std::cerr << "\t" << message << std::endl;
		delete [] message;
	}

	return id; 
	delete [] input;
}

void GenoShader::enable() {
	if (active != program) {
		glUseProgram(program);
		active = program;
	}
}

void GenoShader::disable() {
	if (active != 0) {
		glUseProgram(0);
		active = 0;
	}
}

GenoShader::~GenoShader() {
	glDeleteProgram(program);
}

GenoMvpShader::GenoMvpShader(const char * vert, const char * frag, bool file) :
	GenoShader(vert, frag, file) {
	mvpLoc = glGetUniformLocation(program, "mvp");
}

GenoMvpShader::GenoMvpShader(const char * vert, const char * frag, const char * geom, bool file) :
	GenoShader(vert, frag, geom, file) {
	mvpLoc = glGetUniformLocation(program, "mvp");
}

void GenoMvpShader::setMvp(const GenoMatrix4f & mvp) {
	glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, mvp.m);
}

void GenoMvpShader::setMvp(const float * mvp) {
	glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, mvp);
}