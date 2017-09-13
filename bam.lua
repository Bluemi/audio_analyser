
Import("bam/lua/print_r.lua")
Import("bam/lua/util.lua")

plattform = "linux";

function ValidiateArg(arg, value)
	if arg == "conf" then
		if conf ~= "debug" and conf ~= "release" then
			error("Invalid value for argument 'conf': '"..value.."'. Valid values are 'debug' and 'release'")
		end
	elseif arg == "dir" then
		
	end
	-- arch
end

function GenerateLibSettings(settings, name)
	Import("bam/lib/" .. name .. "/" .. name .. ".lua")
	lib:configure()
	lib:apply(settings)
end

function GenerateGenerelSettings(settings)
	if conf == "debug" then
		settings.debug = 1
		settings.optimize = 0
	elseif conf == "release" then
		settings.debug = 0
		settings.optimize = 1
	end

	settings.cc.flags:Add("-Wall")
	settings.cc.flags_cxx:Add("--std=c++14")
	settings.cc.includes:Add("src")
	settings.cc.Output = function(settings, input)
		input = input:gsub("^src/", "")
		return PathJoin(PathJoin(build_dir, "obj"), PathBase(input))
	end
	settings.link.Output = function(settings, input)
		return PathJoin(build_dir, PathBase(input))
	end
end

function GenerateClientSettings(settings)
	GenerateLibSettings(settings, "sndfile")
end

if ScriptArgs["conf"] then
	conf = ScriptArgs["conf"]
else
	conf = "debug"
end
ValidiateArg("conf", conf)

if ScriptArgs["dir"] then
	build_dir = ScriptArgs["dir"]
else
	build_dir = "bam/build"
end
ValidiateArg("dir", build_dir)
build_dir = PathJoin(build_dir, conf)

src_dir = "src"
datasrc_dir = "res"

settings = NewSettings()
GenerateGenerelSettings(settings)
GenerateClientSettings(settings)

PseudoTarget("client")
srcs = CollectRecursive(src_dir .. "/*.cpp")
objs = Compile(settings, srcs)
exe = Link(settings, "analyser", objs)
AddDependency("client", exe)

PseudoTarget("data")
do
	local data_files = CollectRecursive(datasrc_dir .. "/")
	for i, file in pairs(data_files) do
		local target = PathJoin(build_dir, file)
		AddJob(target, file .. " > " .. target , "cp " .. file .. " " .. target)
		AddDependency(target, file)
		AddDependency("data", target)
	end
end

PseudoTarget("all", "client", "data")
PseudoTarget("game", "client", "data")
DefaultTarget("game")
