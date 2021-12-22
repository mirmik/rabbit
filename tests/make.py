#!/usr/bin/env python3

import sys
import licant
from licant.cxx_modules import application
from licant.modules import submodule, module
from licant.libs import include

licant.execute("../rabbit.g.py")


application("runtests",
		sources = [
			"*.cpp",
			"fitting/*.cpp",
			"geom/*.cpp"
		],

		cxx_flags = "-g",
		cc_flags = "-g",
		cxxstd = "c++20",

		include_paths = ["."],
		mdepends = [ "rabbit" ],

		libs=["nos", "ralgo"],
		defines=["RABBIT_REAL_TYPE=double"]
)

licant.ex("runtests")