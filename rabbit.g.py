import licant

licant.module("rabbit",
	srcdir="rabbit",
	sources=[
		"inctest.cpp",
		"intersect.cpp"
	],
	include_paths=["."]
)