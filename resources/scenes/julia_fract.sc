{
	"ambient_light" : 0.3,
	"camera": {
		"position": [0, 0.5, -4],
		"angles": [0, 0, 0]
	},
	"figures": [
		{
			"type": "sphere",
			"center": [0, 0, 0],
			"radius": 1.3,
			"color": [1, 1, 1],
			"material": "transparent"
		},
		{
			"type": "julia_fract",
			"center": [-0.45, 0.526, 0.112],
			"color": [1, 1, 0.38],
			"material": "diffuse"
		},
		{
			"type": "plane",
			"center": [0, 2, 0],
			"center2": [0, -1, 0],
			"color": [0.9, 0.67, 0.44],
			"emission": 1,
			"material": "emissive"
		},
		{
			"type": "plane",
			"center": [0, 0, 2],
			"center2": [0, 0, 1],
			"color": [0.9, 0.67, 0.44],
			"material": "diffuse"
		},
		{
			"type": "plane",
			"center": [-3, 0, 0],
			"center2": [1, 0, 0],
			"color": [0.5, 0.1, 0],
			"material": "diffuse"
		},
		{
			"type": "plane",
			"center": [3, 0, 0],
			"center2": [1, 0, 0],
			"color": [0, 0.1, 0.5],
			"material": "diffuse"
		},
		{
			"type": "plane",
			"center": [0, -1, 0],
			"center2": [0, 1, 0],
			"color": [0, 0.1, 0.5],
			"material": "diffuse"
		}
	]
}
