import licant

licant.module("rabbit",
	srcdir="rabbit",
	sources=[
		"inctest.cpp",
		"intersect.cpp",
	],
	include_paths=["."]
)

licant.module("rabbit.opengl",
	sources=[
		"rabbit/opengl/opengl_shader_program.cpp",
		"rabbit/opengl/shader_collection.cpp",
		"rabbit/opengl/drawer.cpp",
		"rabbit/font/naive.cpp",
		"rabbit/opengl/window.cpp",
	]
)

licant.module("rabbit.qt_opengl",
	sources=[
		"rabbit/opengl/qt_drawer.cpp",
	]
)

licant.module("rabbit.mesh",
	sources=[
		"rabbit/mesh.cpp"
	]
)

licant.module("rabbit.gazebo", sources=["rabbit/space/gazebo.cpp"])
