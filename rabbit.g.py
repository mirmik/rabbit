import licant

licant.include("linalg-v3")

licant.module("rabbit",
	srcdir="rabbit",
	sources=["curve2.cpp"],
	include_modules=[
		licant.submodule("linalg-v3")
	],
	include_paths=["."]
)