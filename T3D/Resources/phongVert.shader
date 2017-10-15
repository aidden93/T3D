//out vec4 color;
//out vec4 P;
//out vec3 N;
varying vec4 P;
varying vec3 N;

void main()
{
    // Transform the vertex position
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;


	P = gl_ModelViewMatrix * gl_Vertex;
	N = normalize(gl_NormalMatrix * gl_Normal);

	//color = phongIllumination(P, N);
}

//Moved to the phongFrag.shader
/*vec4 phongIllumination(vec4 P, vec3 N) {
	// Ambient calculation
	vec4 ambient = gl_FrontMaterial.ambient * gl_LightModel.ambient;

	// Emission calculation
	vec4 emission = gl_FrontMaterial.emission;

	// Diffuse calculation

	vec3 L = normalize(gl_LightSource[0].position.xyz - vec3(P * gl_LightSource[0].position.w));
	float diffuseIntensity = max(dot(N, L), 0);
	vec4 diffuse = gl_FrontMaterial.diffuse * gl_LightSource[0].diffuse * diffuseIntensity;

	// Specular calculation
	vec3 R = normalize(reflect(L, N));
	vec3 V = normalize(P.xyz);
	float specularIntensity = pow(max(dot(R, V), 0), 0.2*gl_FrontMaterial.shininess);
	vec4 specular = gl_FrontMaterial.specular * gl_LightSource[0].specular * specularIntensity;

	return clamp(ambient + emission + diffuse + specular, 0, 1);
}*/