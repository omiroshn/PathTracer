{
	"ambient_light" : 0.8,
	"camera": {
		"position": [0, 0.5, -4],
		"angles": [0, 0, 0]
	},
	"figures": [
		{
			"type": "sphere",
			"center": [0, 1, 0],
			"radius": 1,
			"color": [1, 1, 1],
			"material": "diffuse",
			"specular": 0.1,
			"texture": "resources/textures/jupiter.jpg"
		},
		{
			"type": "disc",
			"center": [0, 1, 0],
			"center2": [0.5, -1, 0.4],
			"radius": 1.3,
			"color": [1, 1, 1],
			"material": "negative"
		},
		{
			"type": "disc",
			"center": [0, 1, 0],
			"center2": [0.5, -1, 0.4],
			"radius": 1.94,
			"color": [1, 1, 1],
			"material": "diffuse",
			"texture": "resources/textures/saturn.jpg"
		},
		{
			"type": "skybox",
			"texture": "resources/textures/night_sky.png"
		}
	]
}
