start: compile run
run:
	@cvlc ./test1.wav &
	@./bam/build/debug/analyser
	@pkill vlc
printlog:
	@if [ -f debug.log ]; then cat debug.log; else echo "no log file"; fi
gdb:
	@if [ -f core ]; then gdb ./bam/build/debug/analyser core; else echo no core; echo; gdb ./bam/build/debug/analyser ; fi
line-counter:
	@line-counter *pp
compile:
	@tput reset
	@bam -j `nproc`
.PHONY: run printlog gdb line-counter compile start
