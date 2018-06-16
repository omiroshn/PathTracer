{
	"ambient_light" : 0.3,
	"camera": {
		"position": [0, 4.5, -16],
		"angles": [-5, 0, 0]
	},
	"figures": [
		{
			"type": "sphere",
			"center": [-95, 100, -46],
			"radius": 30,
			"color": [1, 1, 1],
			"emission": 8,
			"material": "emissive"
		},
		{
			"type": "sphere",
			"center": [-6, 2, 0],
			"radius": 2,
			"color": [1, 1, 1],
			"material": "diffuse"
		},
		{
			"type": "sphere",
			"center": [0, 2, 0.5],
			"radius": 2,
			"color": [1, 1, 1],
			"material": "reflect",
			"specular": 0.1
		},
		{
			"type": "sphere",
			"center": [6, 2, 0],
			"radius": 2,
			"color": [1, 1, 1],
			"material": "reflect",
			"specular": 0.9
		},
		{
			"type": "plane",
			"center": [0, 0, 18],
			"center2": [0, 0, -1],
			"color": [1, 1, 1],
			"material": "diffuse"
		},
		{
			"type": "plane",
			"center": [0, 0, 0],
			"center2": [0, 1, 0],
			"color": [1, 1, 1],
			"material": "diffuse"
		}
	]
}
