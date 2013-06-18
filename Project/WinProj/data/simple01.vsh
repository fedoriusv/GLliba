varying vec3 LightDir_t;
varying vec3 Bisector_t;

uniform vec3 eye;

void main(void)
{
	vec3 point = vec3( gl_ModelViewMatrix * gl_Vertex );
	
	vec3 lightDir = normalize( vec3( gl_LightSource[0].position ) - point );
	vec3 eyePos = normalize( eye - point );
	vec3 bisector = normalize( eyePos + lightDir );
	
	vec3 normal = gl_NormalMatrix * gl_Normal;
	vec3 tangent = gl_NormalMatrix * gl_MultiTexCoord1.xyz;
	vec3 binormal = gl_NormalMatrix * gl_MultiTexCoord2.xyz;
	
	LightDir_t = vec3( dot(lightDir,tangent), dot(lightDir,binormal), dot(lightDir,normal));
	Bisector_t = vec3( dot(bisector,tangent), dot(bisector,binormal), dot(bisector,normal));
	
	gl_TexCoord[0] = gl_MultiTexCoord0;
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	
	
}
