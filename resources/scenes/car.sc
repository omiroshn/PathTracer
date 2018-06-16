{
	"ambient_light" : 0.3,
	"camera": {
		"position": [10, 20, -40],
		"angles": [0, -45, 0]
	},
	"figures": [
		{
			"type": "skybox",
			"texture": "resources/textures/desert_skybox.jpg"
		},
		{
			"type": "plane",
			"center": [0, 0, 0],
			"center2": [0, 1, 0],
			"color": [0.9, 0.67, 0.44],
			"material": "diffuse",
			"texture": "resources/textures/desert.jpg",
			"scale": 0.1
		}
	],
	"external_object": "resources/models/car/car.obj"
}
