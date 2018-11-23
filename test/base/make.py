#!/usr/bin/env python3
#coding: utf-8

import licant

licant.include("rabbit")
licant.include("gxx")

licant.cxx_application("target",
	sources = ["main.cpp"],
	include_modules = [
		"rabbit", 
		licant.submodule("gxx", "posix"),
		licant.submodule("gxx.print", "cout"),
		licant.submodule("gxx.dprint", "cout")
	],
)

licant.ex("target")