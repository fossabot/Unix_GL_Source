#include "shader.hpp"



namespace OpenGLEngine {


  std::string Shader::loadShaderCode(const std::string& filename)
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

  void Shader::checkShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
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

  GLuint Shader::createShader(const std::string& text, unsigned int type)
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

  // CONSTRUCTOR & DESTRUCTOR ----------------------------------------------
  Shader::Shader(unsigned int id, std::string name) : Component(id, name) {}

  Shader::~Shader() {

    clean();

  }

  void Shader::clean() {

    for(unsigned int i = 0; i < NUM_SHADERS; i++) {
      glDetachShader(program, shaders[i]);
      glDeleteShader(shaders[i]);
    }
    glDeleteProgram(program);

  }

  void Shader::reset(const std::string& filename) {

    clean();
    loadShaderToGpu(filename);

  }
  // -----------------------------------------------------------------------



  // FUNCTIONS -------------------------------------------------------------
  void Shader::initialize() {

  }


  void Shader::setupAttributes() {

    glBindAttribLocation(program, 0, "VertexPosition");
    glBindAttribLocation(program, 1, "VertexNormal");
    glBindAttribLocation(program, 2, "VertexTexcoord");
    glBindAttribLocation(program, 3, "BoneIds");
    glBindAttribLocation(program, 4, "BoneWeights");
    
  }

  void Shader::linkNValidate() {

    glLinkProgram(program);
    checkShaderError(program, GL_LINK_STATUS, true, "Error linking shader program");

    glValidateProgram(program);
    checkShaderError(program, GL_LINK_STATUS, true, "Invalid shader program");

  }

  void Shader::setupUniforms() {

    uniforms[MODEL_U] = glGetUniformLocation(program, "Model");
    uniforms[VIEW_U] = glGetUniformLocation(program, "View");
    uniforms[PROJECTION_U] = glGetUniformLocation(program, "Projection");
    uniforms[CAMERA_POSITION] = glGetUniformLocation(program, "CameraPosition");
    uniforms[CAMERA_DIRECTION] = glGetUniformLocation(program, "CameraDirection");
    uniforms[DELTATIME] = glGetUniformLocation(program, "DeltaTime");
    uniforms[TIME] = glGetUniformLocation(program, "Time");

  }

  void Shader::loadShaderToGpu(const std::string& filename) {

    program = glCreateProgram();
    shaders[VERTEX_SHADER] = createShader(loadShaderCode(filename + ".vs"), GL_VERTEX_SHADER);
    shaders[FRAGMENT_SHADER] = createShader(loadShaderCode(filename + ".fs"), GL_FRAGMENT_SHADER);

    for (unsigned int i = 0; i < NUM_SHADERS; i++)
      glAttachShader(program, shaders[i]);

    setupAttributes();
    linkNValidate();
    setupUniforms();

  }

  void Shader::bind() {
    glUseProgram(program);
  }

  void Shader::unbind() {
    glUseProgram(0);
  }

  void Shader::update(Transform worldTransform, Camera mainCamera, float deltaTime) {

  	glm::mat4 model = worldTransform.Model();
  	glm::mat4 view = mainCamera.GetViewMatrix();
  	glm::mat4 projection = mainCamera.GetProjectionMatrix();
  	glUniformMatrix4fv(uniforms[MODEL_U], 1, 0, &model[0][0]);
  	glUniformMatrix4fv(uniforms[VIEW_U], 1, 0, &view[0][0]);
  	glUniformMatrix4fv(uniforms[PROJECTION_U], 1, 0, &projection[0][0]);
  	glUniform3fv(uniforms[CAMERA_POSITION], 1, &mainCamera.GetPosition()[0]);
	glUniform3fv(uniforms[CAMERA_DIRECTION], 1, &mainCamera.GetDirection()[0]);
	glUniform1f(uniforms[TIME], SDL_GetTicks());
  	glUniform1f(uniforms[DELTATIME], deltaTime);

  }
  // -----------------------------------------------------------------------



  // GETTERS & SETTERS -----------------------------------------------------
  GLuint Shader::Program() {
    return program;
  }
  // -----------------------------------------------------------------------


}
