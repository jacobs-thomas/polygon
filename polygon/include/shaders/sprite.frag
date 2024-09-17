uniform vec3 spriteColor;
uniform sampler2D image;

in vec2 TexCoords; // Passed from vertex shader

out vec4 color;

void main()
{    
    color = vec4(spriteColor, 1.0) * texture(image, TexCoords);
}