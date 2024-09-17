layout (location = 0) in vec2 position;    // vec2 position
layout (location = 1) in vec2 texCoords;   // vec2 texture coordinates

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 projection;

void main()
{
    // Pass texture coordinates to fragment shader
    TexCoords = texCoords;
    
    // Compute the final position using the model and projection matrices
    gl_Position = projection * model * vec4(position, 0.0, 1.0);
}