#version 330 core
out vec4 FragColor;

in float height;

void main()
{
	vec3 color;

	if (height < 10.0)
		color = mix(vec3(0.0, 0.0, 1.0), vec3(0.0, 0.5, 0.0), height / 10.0); // Blue to Dark Green
	else if (height < 20.0)
		color = mix(vec3(0.0, 0.5, 0.0), vec3(0.0, 0.7, 0.0), (height - 10.0) / 10.0); // Dark Green to Green
	else if (height < 30.0)
		color = mix(vec3(0.0, 0.7, 0.0), vec3(0.5, 0.5, 0.0), (height - 20.0) / 10.0); // Green to Olive
	else if (height < 40.0)
		color = mix(vec3(0.5, 0.5, 0.0), vec3(0.7, 0.7, 0.0), (height - 30.0) / 10.0); // Olive to Light Olive
	else if (height < 50.0)
		color = mix(vec3(0.7, 0.7, 0.0), vec3(0.8, 0.5, 0.0), (height - 40.0) / 10.0); // Light Olive to Brown
	else if (height < 60.0)
		color = mix(vec3(0.8, 0.5, 0.0), vec3(0.5, 0.3, 0.0), (height - 50.0) / 10.0); // Brown to Dark Brown
	else if(height < 70.0)
		color = mix(vec3(0.5, 0.3, 0.0), vec3(0.6, 0.4, 0.4), (height - 60.0) / 10.0); // Dark Brown to Light Brown
	else if (height < 80.0)
		color = mix(vec3(0.6, 0.4, 0.4), vec3(0.7, 0.7, 0.7), (height - 70.0) / 10.0); // Light Brown to Light Gray
	else
		color = vec3(0.5, 0.5, 0.5); // Gray for mountain peaks


	FragColor = vec4(color, 1.0);
}