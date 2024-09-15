#version 330 core
out vec4 FragColor;

in float height;

void main()
{
	vec3 color;

	if (height < 10.0)
	color = mix(vec3(0.0, 0.0, 1.0), vec3(0.0, 0.5, 0.0), height / 10.0);
	else if (height < 20.0)
	color = mix(vec3(0.0, 0.5, 0.0), vec3(0.0, 0.7, 0.0), (height - 10.0) / 10.0);
	else if (height < 30.0)
	color = mix(vec3(0.0, 0.7, 0.0), vec3(0.5, 0.5, 0.0), (height - 20.0) / 10.0);
	else if (height < 40.0)
	color = mix(vec3(0.5, 0.5, 0.0), vec3(0.7, 0.7, 0.0), (height - 30.0) / 10.0);
	else if (height < 50.0)
	color = mix(vec3(0.7, 0.7, 0.0), vec3(0.8, 0.5, 0.0), (height - 40.0) / 10.0);
	else if (height < 60.0)
	color = mix(vec3(0.8, 0.5, 0.0), vec3(0.5, 0.3, 0.0), (height - 50.0) / 10.0);
	else if (height < 70.0)
	color = mix(vec3(0.5, 0.3, 0.0), vec3(0.6, 0.4, 0.4), (height - 60.0) / 10.0);
	else if (height < 80.0)
	color = mix(vec3(0.6, 0.4, 0.4), vec3(0.7, 0.7, 0.7), (height - 70.0) / 10.0);
	else if (height < 90.0)
	color = mix(vec3(0.7, 0.7, 0.7), vec3(0.8, 0.8, 0.8), (height - 80.0) / 10.0);
	else if (height < 100.0)
	color = mix(vec3(0.8, 0.8, 0.8), vec3(0.9, 0.9, 0.9), (height - 90.0) / 10.0);
	else
	color = vec3(0.9, 0.9, 0.9);

	FragColor = vec4(color, 1.0);
}