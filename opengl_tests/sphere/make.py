#!/usr/bin/env python3

import licant

licant.include("rabbit", "../../rabbit.g.py")

licant.cxx_application("target",
	mdepends=["rabbit", "rabbit.opengl"],
	sources = ["main.cpp"],
	libs = ["GLEW", "glfw", "GL", "X11", "pthread", "Xrandr", "Xi", "SOIL", "nos", "igris"],
	include_paths=["/usr/include/SOIL"]
)

licant.ex("target")