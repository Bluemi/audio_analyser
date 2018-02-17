conf = ScriptArgs["conf"] or "debug"

conf_dir = PathJoin("build/", conf)

lib_dir = PathJoin(conf_dir, "lib/")
lib_name = "audio_analyser"
src_dir = "src/"
build_dir = PathJoin(conf_dir, "obj/")
include_dir = PathJoin(conf_dir, "includes/")
test_src_dir = "tests/"
test_obj_dir = PathJoin(conf_dir, "tests/obj/")
test_bin_dir = PathJoin(conf_dir, "tests/bin/")

sources = CollectRecursive(src_dir .. "*.cpp")
headers = CollectRecursive(src_dir .. "*.hpp")

function GenerateMainSettings()
    settings = NewSettings()
    settings.cc.flags:Add("-Wall")
    settings.cc.flags_cxx:Add("-std=c++17")

    -- include external libraries
    -- include sndfile
	settings.cc.includes:Add("usr/include")
	settings.link.libs:Add("sndfile")

    -- include fftw
	settings.link.libs:Add("fftw3")

    settings.cc.includes:Add(src_dir)
    -- settings.link.flags:Add("-L/usr/lib")
    -- settings.cc.includes:Add("/usr/include")
    settings.cc.Output = function(settings, input)
        input = string.gsub(input, "^" .. src_dir, "")
        return PathJoin(build_dir, PathBase(input))
    end
    settings.lib.Output = function(settings, input)
        return PathJoin(lib_dir, input)
    end
    return settings
end

settings = GenerateMainSettings()

-- compile sources
objects = Compile(settings, sources)
lib_file = StaticLibrary(settings, lib_name, objects)

PseudoTarget("includes")

-- creating includes
for _, header in ipairs(headers) do
    without_src_header = string.gsub(header, "^" .. src_dir, "")
    include_header = PathJoin(include_dir, without_src_header)
    AddJob(include_header, "copying     " .. header, "cp " .. header .. " " .. include_header)
    AddDependency(include_header, header)
    AddDependency("includes", include_header)
end

PseudoTarget("lib")
AddDependency("lib", lib_file)
AddDependency("lib", "includes")

DefaultTarget("lib")

-- creating tests
PseudoTarget("tests")

function GenerateTestSettings()
    settings = NewSettings()
    settings.cc.flags:Add("-Wall")
    settings.cc.flags_cxx:Add("-std=c++17")

    -- include audio analyser
    settings.cc.includes:Add(include_dir)
    settings.link.flags:Add("-L" .. lib_dir)
    settings.link.libs:Add(lib_name)

    -- include external libraries
    -- include sndfile
	settings.cc.includes:Add("/usr/include")
	settings.link.libs:Add("sndfile")

    -- include fftw
	settings.link.libs:Add("fftw3")

    settings.cc.Output = function(settings, input)
        input = string.gsub(input, "^" .. test_src_dir, "")
        return PathJoin(test_obj_dir, PathBase(input))
    end

    return settings
end

test_settings = GenerateTestSettings()
test_sources = CollectRecursive(test_src_dir .. "*.cpp")

test_objects = Compile(settings, test_sources)

for _, test_obj in ipairs(test_objects) do
    x = string.gsub(test_obj, "^" .. test_obj_dir .. "/", "")
    test_bin = Link(test_settings, PathJoin(test_bin_dir, x), test_obj)
    AddDependency(test_bin, lib_file)
    AddDependency("tests", test_bin)
    AddDependency(test_bin, "includes")
end
