import licant

licant.module("rabbit",
	srcdir="rabbit",
	sources=[
		"inctest.cpp",
		"intersect.cpp",
		"space/screw.cpp"
	],
	include_paths=["."]
)