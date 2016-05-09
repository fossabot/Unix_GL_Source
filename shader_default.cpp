#include "shader_default.h"



namespace OpenGLEngine {
  std::string DefaultShader::loadShaderCode(const std::string& filename)
  {
  	std::ifstream file;
  	file.open((filename).c_str());
  	std::string output;
  	std::string line;
  	if (file.is_open())
  	{
  		while (file.good())
  		{
  			getline(file, line);
  			output.append(line + "\n");
  		}
  	} else {
  		std::cerr << "Unable to load shader: " << filename << std::endl;
  	}
  	return output;
  }

  void DefaultShader::checkShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
  {
  	GLint success = 0;
  	GLchar error[1024] = { 0 };
  	if (isProgram)
  		glGetProgramiv(shader, flag, &success);
  	else
  		glGetShaderiv(shader, flag, &success);

  	if (success == GL_FALSE)
  	{
  		if (isProgram)
  			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
  		else
  			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

  		std::cerr << errorMessage << ": '" << error << "'" << std::endl;
  	}
  }

  GLuint DefaultShader::createShader(const std::string& text, unsigned int type)
  {
  	GLuint shader = glCreateShader(type);

  	if (shader == 0)
  		std::cerr << "Error compiling shader type " << type << std::endl;

  	const GLchar* p[1];
  	p[0] = text.c_str();
  	GLint lengths[1];
  	lengths[0] = text.length();
  	glShaderSource(shader, 1, p, lengths);
  	glCompileShader(shader);
  	checkShaderError(shader, GL_COMPILE_STATUS, false, "Error compiling shader!");
  	return shader;
  }

  DefaultShader::DefaultShader() {}

  DefaultShader::~DefaultShader() {
    for(unsigned int i = 0; i < NUM_SHADERS; i++) {
      glDetachShader(m_program, m_shaders[i]);
      glDeleteShader(m_shaders[i]);
    }
    glDeleteProgram(m_program);
  }

  void DefaultShader::initialize() {}

  void DefaultShader::setupAttributes() {
    glBindAttribLocation(m_program, 0, "VertexPosition");
    glBindAttribLocation(m_program, 1, "VertexNormal");
    glBindAttribLocation(m_program, 2, "VertexTexcoord");
  }

  void DefaultShader::linkNValidate() {
    glLinkProgram(m_program);
    checkShaderError(m_program, GL_LINK_STATUS, true, "Error linking shader program");
    glValidateProgram(m_program);
    checkShaderError(m_program, GL_LINK_STATUS, true, "Invalid shader program");
  }

  void DefaultShader::setupUniforms() {
    m_uniforms[MODEL_U] = glGetUniformLocation(m_program, "Model");
    m_uniforms[VIEW_U] = glGetUniformLocation(m_program, "View");
    m_uniforms[PROJECTION_U] = glGetUniformLocation(m_program, "Projection");
    m_uniforms[CAMERA_POSITION] = glGetUniformLocation(m_program, "CameraPosition");
    m_uniforms[CAMERA_DIRECTION] = glGetUniformLocation(m_program, "CameraDirection");
    m_uniforms[DELTATIME] = glGetUniformLocation(m_program, "DeltaTime");
    m_uniforms[TIME] = glGetUniformLocation(m_program, "Time");
  }

  void DefaultShader::loadShaderToGpu(const std::string& filename) {
    m_program = glCreateProgram();
    m_shaders[VERTEX_SHADER] = createShader(loadShaderCode(filename + ".vs"), GL_VERTEX_SHADER);
    m_shaders[FRAGMENT_SHADER] = createShader(loadShaderCode(filename + ".fs"), GL_FRAGMENT_SHADER);
    for (unsigned int i = 0; i < NUM_SHADERS; i++)
      glAttachShader(m_program, m_shaders[i]);
    setupAttributes();
    linkNValidate();
    setupUniforms();
  }

  void DefaultShader::bind() {
    glUseProgram(m_program);
  }

  void DefaultShader::unbind() {
    glUseProgram(0);
  }

  void DefaultShader::update(Transform worldTransform, Camera mainCamera, float deltaTime) {
  	glm::mat4 model = worldTransform.Model();
  	glm::mat4 view = mainCamera.View();
  	glm::mat4 projection = mainCamera.Projection();
  	glUniformMatrix4fv(m_uniforms[MODEL_U], 1, 0, &model[0][0]);
  	glUniformMatrix4fv(m_uniforms[VIEW_U], 1, 0, &view[0][0]);
  	glUniformMatrix4fv(m_uniforms[PROJECTION_U], 1, 0, &projection[0][0]);
  	glUniform3fv(m_uniforms[CAMERA_POSITION], 1, &mainCamera.GetPosition()[0]);
    glUniform3fv(m_uniforms[CAMERA_DIRECTION], 1, &mainCamera.GetDirection()[0]);
    glUniform1f(m_uniforms[TIME], SDL_GetTicks());
  	glUniform1f(m_uniforms[DELTATIME], deltaTime);
  }

  GLuint DefaultShader::Program() {
    return m_program;
  }
}
