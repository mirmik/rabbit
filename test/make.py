#!/usr/bin/env python3

import sys
import licant
from licant.cxx_modules import application
from licant.modules import submodule, module
from licant.libs import include

licant.execute("../rabbit.g.py")
licant.include("ralgo")


for real in ["double", "float"]:
	application("runtests_" + real,
		sources = [
			"main.cpp",
			"intersect.cpp",	
			"htrans3.cpp",		
			"nearest.cpp",		
			"line2.cpp",
			"optimize.cpp",
			"svd.cpp",
			"pose3.cpp",
			"fitting/*.cpp"		
		],

		cxx_flags = "-g",
		cc_flags = "-g",

		include_paths = ["."],
		mdepends = [ "rabbit", "ralgo" ],

		libs=["nos", "igris"],
		defines=["RABBIT_REAL_TYPE=" + real]
)

licant.fileset("all", ["runtests_float", "runtests_double"])

licant.ex("all")