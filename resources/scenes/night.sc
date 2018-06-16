{
	"ambient_light" : 0.3,
	"camera": {
		"position": [-3.5, 0.5, 1],
		"angles": [10, 270, 0]
	},
	"figures": [
		{
			"type": "skybox",
			"texture": "resources/textures/sky_moonscape.jpg"
		},
		{
			"type": "plane",
			"center": [0, 0, 0],
			"center2": [0, 1, 0],
			"color": [0.9, 0.67, 0.44],
			"material": "diffuse",
			"texture": "resources/textures/desert.jpg",
			"scale": 0.1
		},
		{
			"type": "sphere",
			"center": [0, 1, 0],
			"radius": 1,
			"color": [1, 1, 1],
			"material": "reflect",
		},
	]
}
