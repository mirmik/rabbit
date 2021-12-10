#!/usr/bin/env python3

import sys
import licant
from licant.cxx_modules import application
from licant.modules import submodule, module
from licant.libs import include

licant.execute("../rabbit.g.py")


for real in ["double", "float"]:
	application("runtests_" + real,
		sources = [
			"*.cpp",
			"fitting/*.cpp",
			"geom/*.cpp",	
			"nd/*.cpp"	
		],

		cxx_flags = "-g",
		cc_flags = "-g",
		cxxstd = "c++20",

		include_paths = ["."],
		mdepends = [ "rabbit" ],

		libs=["nos", "igris", "ralgo"],
		defines=["RABBIT_REAL_TYPE=" + real]
)

licant.fileset("all", ["runtests_float", "runtests_double"])

licant.ex("all")