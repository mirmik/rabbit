import licant

licant.module("rabbit",
	srcdir="rabbit",
	sources=[
		"inctest.cpp",
		"intersect.cpp",
		"space/screw.cpp",
		"space/pose3.cpp",
		"mesh.cpp"
	],
	include_paths=["."]
)

licant.module("rabbit.opengl",
	sources=[
		"rabbit/opengl/opengl_shader_program.cpp",
		"rabbit/opengl/shader_collection.cpp",
		"rabbit/opengl/drawer.cpp",
		"rabbit/font/naive.cpp",
	]
)

licant.module("rabbit.gazebo", sources=["rabbit/space/gazebo.cpp"])