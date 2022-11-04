build_dir = build

exe = $(build_dir)/aerokit

# tests = $(build_dir)/*.test
# t1 = Dna
# t2 = DnaEncoding
# t3 = Gene


default:
	@cd $(build_dir) && meson compile

run: default
	@./$(exe)

test: default $(tests)
	@cd $(build_dir) && meson test

profile: default $(tests) $(exe)
	@cd $(build_dir) && meson test -Db_sanitize=address
	@valgrind --tool=memcheck --leak-check=full -s $(exe)
	
plot: test data/tst.csv plot.info
	gnuplot plot.info --persist

