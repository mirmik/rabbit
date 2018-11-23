#!/usr/bin/env python3
#coding: utf-8

import licant

licant.include("rabbit")

licant.cxx_application("target",
	sources = ["main.cpp"],
	include_modules = ["rabbit"],
)

licant.ex("target")