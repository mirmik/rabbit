#!/usr/bin/env python3
#coding:utf-8

import licant

licant.include("igris")
licant.include("nos")
licant.include("rabbit")
licant.include("linalg")

licant.cxx_application("target",
	sources=["main.cpp"],
	mdepends=[
		"rabbit", 
		"nos",
		"linalg"
	]
)

licant.ex("target")