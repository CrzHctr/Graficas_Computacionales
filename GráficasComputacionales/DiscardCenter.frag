in vec3 InterpolatedColor;

out vec4 FragColor;

void main()
{
	FragColor = vec4(InterpolatedColor, 1.0f);
	vec2 pixelPositionInWindow = gl_FragCoord.xy;
	float center = sqrt((pixelPositionInWindow[0] - 300.0f) * (pixelPositionInWindow[0] - 300.0f) + (pixelPositionInWindow[1]-300.0f) * (pixelPositionInWindow[1] - 300.0f));
    if(center <= 0.5f){
    	discard;
	}
}