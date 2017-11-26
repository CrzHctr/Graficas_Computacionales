#version 330

in vec2 InterpolatedTexCoord;
in vec3 InterpolatedColor;
in vec3 PixelPosition;
in vec3 InterpolatedNormal;
in vec4 PixelPositionLightSpace;

out vec4 FragColor;

uniform vec3 LightPosition;
uniform vec3 LightColor;
uniform vec3 CamaraPosition;
uniform mat4 modelMatrix;
uniform sampler2D DiffuseTexture;
uniform sampler2D DiffuseTexture2;
uniform sampler2D ShadowMap;

float IsPixelOccluded(vec4 fragPosLightSpace)
{
	// Realizar la corrección de perspectiva. Coordenadas en rango [-1, 1] -> Normalized Device Space
	vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;

	// Transformar projCoords al rango [0, 1]. (projCoords * 0.5f + 0.5f)
	projCoords = projCoords * 0.5f + 0.5f;

	// Muestrear el mapa de profundidad usando projCoords.xy como coordenadas de textura.
	// Con esto obtenemos la profundidad del pixel en el primer render (desde la luz).
	float closestDepth = texture2D(ShadowMap, projCoords.xy).r;

	// La profundidad del pixel desde la actual cámara (ya transformado) está en projCoords.z
	float currentDepth = projCoords.z;

	// Si la profundidad del render actual es mayor a closestDepth, regresar 1.0f
	// De lo contrario, regresar 0.0f
	float shadow = currentDepth - 0.005f > closestDepth ? 1.0f : 0.0f;
	return shadow;
}

void main()
{

	vec3 ambient = 0.1f * normalize(LightColor);
	vec3 L = normalize(LightPosition - PixelPosition);
	vec3 R = normalize(reflect(-L, InterpolatedNormal));
	vec3 V = normalize(CamaraPosition - PixelPosition);
	vec3 diffuse = clamp(dot(normalize(InterpolatedNormal), L), 0,1)*normalize(LightColor);
	vec3 specular = 0.5f * pow(clamp(dot(V,R),0,1),32)*normalize(LightColor);
	float shadow = IsPixelOccluded(PixelPositionLightSpace);
	vec3 phong = (ambient + (1.0f - shadow) * (diffuse + specular));
	FragColor = vec4(phong, 1.0f)* texture2D(DiffuseTexture, InterpolatedTexCoord);
}