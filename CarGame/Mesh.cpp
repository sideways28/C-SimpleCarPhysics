#include "Mesh.h"


Mesh::Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> textures, Material material)
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;

	texCount = textures.size();
	meshMat = material;

	this->SetupMesh();
}


Mesh::~Mesh()
{
}

void Mesh::SetupMesh()
{
	// Create buffers/arrays
	glGenVertexArrays(1, &this->VAO);
	glBindVertexArray(this->VAO);

	// A great thing about structs is that their memory layout is sequential for all its items.
	// The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
	// again translates to 3/2 floats which translates to a byte array.

	glGenBuffers(1, &this->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);// Load data into vertex buffers
	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), &this->vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &this->EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), &this->indices[0], GL_STATIC_DRAW);

	// Set the vertex attribute pointers
	// Vertex Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
	// Vertex Normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Normal));
	// Vertex Texture Coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, TexCoords));

	glBindVertexArray(0);
}

void Mesh::Draw(GLuint shaderID)
{
	glUniform1i(glGetUniformLocation(shaderID, "material.texCount"), texCount);//Set the texCount to check the material with no texture

	glUniform3f(glGetUniformLocation(shaderID, "material.ambient"), meshMat.ambient.r, meshMat.ambient.g, meshMat.ambient.b);
	glUniform3f(glGetUniformLocation(shaderID, "material.diffuse"), meshMat.diffuse.r, meshMat.diffuse.g, meshMat.diffuse.b);
	glUniform3f(glGetUniformLocation(shaderID, "material.specular"), meshMat.specular.r, meshMat.specular.g, meshMat.specular.b);
	glUniform1f(glGetUniformLocation(shaderID, "material.opacity"), meshMat.opacity);
	//glUniform1f(glGetUniformLocation(shaderID, "material.shininess"), meshMat.shininess);

	//glUniform3f(glGetUniformLocation(shaderID, "material.ambient"), 0.2f, 0.2f, 0.2f);
	//glUniform3f(glGetUniformLocation(shaderID, "material.diffuse"), 0.4f, 0.4f, 0.4f);
	//glUniform3f(glGetUniformLocation(shaderID, "material.specular"), 0.7f, 0.7f, 0.7f);
	glUniform1f(glGetUniformLocation(shaderID, "material.shininess"), 16);
	


	// Bind appropriate textures
	GLuint diffuseNr = 1;
	GLuint specularNr = 1;

	for (GLuint i = 0; i < this->textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i); // Active proper texture unit before binding
		// Retrieve texture number (the N in diffuse_textureN)
		stringstream ss;
		string number;
		string name = this->textures[i].type;
		if (name == "texture_diffuse")
			ss << diffuseNr++; // Transfer GLuint to stream
		else if (name == "texture_specular")
			ss << specularNr++; // Transfer GLuint to stream
		number = ss.str();

		// Now set the sampler to the correct texture unit
		glUniform1i(glGetUniformLocation(shaderID, ("material" + name + number).c_str()), i);
		// And finally bind the texture
		glBindTexture(GL_TEXTURE_2D, this->textures[i].id);
	}

	// Also set each mesh's shininess property to a default value (if you want you could extend this to another mesh property and possibly change this value)
	//glUniform1f(glGetUniformLocation(shaderID, "material.shininess"), 16.0f);

	// Draw mesh
	glBindVertexArray(this->VAO);
	glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	// Always good practice to set everything back to defaults once configured.
	for (GLuint i = 0; i < this->textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}
