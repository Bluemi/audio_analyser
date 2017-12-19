lib_dir = "target/lib/"
lib_name = "audio_analyser"
lib_file = lib_dir .. "lib" .. lib_name .. ".a"
src_dir = "src/"
build_dir = "target/build/debug/"
include_dir = "target/includes/"
test_src_dir = "tests/"
test_bin_dir = "target/tests/"
tmp_dependency_file = "/tmp/bam.dep"

sources = CollectRecursive(src_dir .. "*.cpp")
headers = CollectRecursive(src_dir .. "*.hpp")

targets = {}

lib_extra_libraries = "-I/usr/include/ -L/usr/lib -lsndfile"

linked_libraries = "-I " .. src_dir .. " " .. lib_extra_libraries

compiler_flags = "-Wall"

function ExecuteCommandAndReturn(command)
    local lines = {}
    os.execute(command .. ' > ' .. tmp_dependency_file)
    local f = io.open(tmp_dependency_file)
    if not f then return lines end
    local k = 1
    for line in f:lines() do
        lines[k] = line
        k = k + 1
    end
    f:close()
    return lines
end

-- function CompileWithArgs(compiler, flags, sources, )
-- end


-- create compiling Jobs + Dependencies
for i, source in ipairs(sources) do
    object_file = string.gsub(string.gsub(source, src_dir, ""), ".cpp", ".o")
    full_path = PathJoin(build_dir, object_file)
    -- create targets
    targets[i] = full_path
    AddJob(full_path, "compiling   " .. source, "g++ " .. linked_libraries .. " -c " .. source .. " -o " .. full_path)
    lines = ExecuteCommandAndReturn("g++ -MM -I" .. src_dir .. " " .. source)
    dependencies = {}
    for _, l in ipairs(lines) do
        local i = 1
        for dep in string.gmatch(l, "%S+") do
            if i > 1 then
                if dep ~= "\\" then
                    table.insert(dependencies, dep)
                end
            end
            i = i + 1
        end
    end

    AddDependency(full_path, dependencies)
end

-- building lib
-- creating object_file_str
object_file_str = ""
for _, target in ipairs(targets) do
    object_file_str = object_file_str .. " " .. target
end

-- ar command
AddJob(lib_file, "building    " .. lib_file, "ar rs " .. lib_file .. object_file_str .. " 2>/dev/null")
AddDependency(lib_file, targets)

-- creating includes
include_headers = {}

for _, header in ipairs(headers) do
    without_src_header = string.gsub(header, src_dir, "")
    include_header = PathJoin(include_dir, without_src_header)
    AddJob(include_header, "copying     " .. header, "cp " .. header .. " " .. include_header)
    AddDependency(include_header, header)
    table.insert(include_headers, include_header)
end

-- creating tests
test_sources = CollectRecursive(test_src_dir .. "*.cpp")

for _, test_source in ipairs(test_sources) do
    file = string.gsub(test_source, "tests/", "")
    path = string.gsub(file, ".cpp", "")
    target_executable = PathJoin(test_bin_dir, path)
    AddJob(target_executable, "create test " .. target_executable, "g++ " .. compiler_flags .. " " .. test_source .. " -o " .. target_executable .. " -L" .. lib_dir .. " -l" .. lib_name .. " -I" .. include_dir .. " " .. lib_extra_libraries)
    AddDependency(target_executable, test_source, lib_file, include_headers)
end
