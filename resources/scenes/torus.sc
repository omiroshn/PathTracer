{
	"camera": {
		"position": [0, 2, -7],
		"angles": [0, 0, 0]
	},
	"figures": [
		{
			"type": "torus",
			"center": [0, 2, 0],
			"center2": [0, 1, 0],
			"radius": 0.5,
			"radius2": 1,
			"color": [1, 1, 1],
			"material": "diffuse",
			"texture": "resources/textures/brick.jpeg"
		},
		{
			"type": "plane",
			"center": [0, 20, 0],
			"center2": [0, -1, 0],
			"color": [1, 1, 1],
			"emission": 1,
			"material": "emissive"
		},
		{
			"type": "plane",
			"center": [0, 0, 0],
			"center2": [0, 1, 0],
			"color": [0.9, 0.67, 0.44],
			"material": "diffuse"
		},
		{
			"type": "plane",
			"center": [0, 0, 20],
			"center2": [0, 0, 1],
			"color": [0.9, 0.67, 0.44],
			"material": "diffuse"
		},
		{
			"type": "plane",
			"center": [20, 0, 0],
			"center2": [1, 0, 0],
			"color": [0.5, 0.1, 0],
			"material": "diffuse"
		},
		{
			"type": "plane",
			"center": [-20, 0, 0],
			"center2": [1, 0, 0],
			"color": [0, 0.1, 0.5],
			"material": "diffuse"
		}
	]
}
