#version 330

in vec3 InterpolatedColor;

out vec4 FragColor;

uniform vec2 Resolution;

void main(){
	vec2 p = gl_FragCoord.xy / Resolution;
	vec2 q = p - vec2(0.5f,0.5f);

	if(length(q)<0.25)
		discard;


	FragColor = vec4(InterpolatedColor, 1.0f);
}
