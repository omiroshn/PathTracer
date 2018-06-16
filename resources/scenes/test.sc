{
	"ambient_light": 0.3,
	"camera": {
		"position": [0, 2, -6],
		"angles": [-25, 0, 0]
	},
	"figures": [
		{
			"type": "sphere",
			"center": [0, -1, 0],
			"center2": [0, 0, 1],
			"radius": 2,
			"color": [1, 1, 1],
			"material": "glass"
		},
		{
			"type": "skybox",
			"texture": "resources/textures/desert_skybox.jpg"
		},
		{
			"type": "plane",
			"center": [0, -1, 0],
			"center2": [0, 1, 0],
			"color": [0.9, 0.67, 0.44],
			"material": "diffuse",
			"texture": "resources/textures/test.png",
			"scale": 0.1
		}
	]
}
