#version 130

in vec3 InterpolatedColor;
in vec3 InterpolatedNormal;
in vec3 PixelPosition;

in vec2 InterpolatedTexCoord;

uniform vec3 LightColor;
uniform vec3 LightPosition;
uniform vec3 CamaraPosition;

uniform sampler2D DiffuseTexture;

out vec4 FragColor;

void main() {
	vec3 L = normalize(LightPosition - PixelPosition);
	vec3 R = normalize(reflect(-L, InterpolatedNormal));
	vec3 V = normalize(CamaraPosition - PixelPosition);
	vec3 specular = 0.5f * pow(dot(V, R), 32) * LightColor;
	vec3 diffuse = dot(normalize(InterpolatedNormal), L) * normalize(LightColor);
	vec3 ambient = 0.1f * normalize(LightColor);
	vec3 phong = (ambient + diffuse + specular) * InterpolatedColor;
	FragColor = texture2D(DiffuseTexture, InterpolatedTexCoord);
}