lib = {
	path = PathDir(ModuleFilename()),
}

function lib:configure()
end

function lib:apply(settings)
	settings.cc.includes:Add("usr/local/include")
	settings.link.libs:Add("fftw3f")
end
