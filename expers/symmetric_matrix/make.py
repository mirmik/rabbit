#!/usr/bin/env python3
#coding:utf-8

import licant

licant.include("rabbit")
licant.include("linalg-v3")

licant.cxx_application("target",
	sources=["main.cpp"],
	mdepends=[
		"rabbit", 
		"linalg-v3"
	],
	libs=["igris", "nos"]
)

licant.ex("target")