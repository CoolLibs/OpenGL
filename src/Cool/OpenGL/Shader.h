#pragma once

namespace Cool {

enum class ShaderType {
	Vertex,
	Fragment,
	Compute
};

struct ShaderCode {
	ShaderType type;
	const char* sourceCode;

	/// <summary>
	/// Constructs a ShaderCode by reading sourceCode from a file.
	/// </summary>
	/// <param name="type">An enum representing the type of the shader (Vertex, Fragment, etc.)</param>
	/// <param name="filePath">The path to the file containing the source code of the shader.</param>
	ShaderCode(ShaderType type, const char* filePath);
	ShaderCode() = default;

	/// <summary>
	/// Constructs a ShaderCode by giving its source code directly.
	/// </summary>
	/// <param name="type">An enum representing the type of the shader (Vertex, Fragment, etc.)</param>
	/// <param name="sourceCode">The source code of the shader.</param>
	/// <returns>A ShaderCode.</returns>
	static ShaderCode FromCode(ShaderType type, const char* sourceCode);
};

class Shader {
public:
	Shader() = default;
	/// <summary>
	/// Creates and compiles a full shader pipeline from the shader codes.
	/// </summary>
	/// <param name="shaderCodes">A list of the shaders : for example a vertex and a framgent shader.</param>
	Shader(const std::vector<ShaderCode>& shaderCodes);
	~Shader();
	Shader(Shader&& o) noexcept;
	void operator=(Shader&& o);

	/// <summary>
	/// Creates and compiles a shader program. You don't need to call this if you used the constructor that takes in shaderCodes.
	/// It can also be used to recompile the shader with different sources as often as you would like.
	/// </summary>
	/// <param name="shaderCodes"></param>
	void createProgram(const std::vector<ShaderCode>& shaderCodes);

	/// <summary>
	/// Binds the shader pipeline.
	/// </summary>
	void bind();

	void setUniform1i   (const char* uniformName, int v);
	void setUniform1f   (const char* uniformName, float v);
	void setUniform2f   (const char* uniformName, const glm::vec2& v);
	void setUniform3f   (const char* uniformName, const glm::vec3& v);
	void setUniform4f   (const char* uniformName, const glm::vec4& v);
	void setUniformMat2f(const char* uniformName, const glm::mat2& mat);
	void setUniformMat3f(const char* uniformName, const glm::mat3& mat);
	void setUniformMat4f(const char* uniformName, const glm::mat4& mat);

private:
	/// <summary>
	/// Creates and compiles a shader, and returns its ID
	/// </summary>
	static GLuint CreateShader(const ShaderCode& shaderCode);

private:
	std::unordered_map<const char*, GLint> m_uniformLocationCache;
	GLint getUniformLocation(const char* uniformName);

private:
	GLuint m_programID = 0; // 0 is an invalid value for an OpenGL shader ID
};

} // namespace Cool