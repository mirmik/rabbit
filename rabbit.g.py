import licant

licant.module("rabbit",
	srcdir="rabbit",
	sources=[
		"inctest.cpp",
		"intersect.cpp",
		"space/screw.cpp",
	],
	include_paths=["."]
)

licant.module("rabbit.gazebo", sources=["rabbit/space/gazebo.cpp"])