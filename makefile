cc_version    = c++20
debug_options = -std=$(cc_version) -Wall --pedantic-errors
debug_bin_dir = bin/debug

debug: $(debug_bin_dir)/debug_word_card.o $(debug_bin_dir)/debug_operate_xml.o $(debug_bin_dir)/debug_dictionary.o
	clang++ -o $(debug_bin_dir)/$@ src/main.cc $(debug_options) $^

$(debug_bin_dir)/debug_word_card.o: src/word_card.cc src/word_card.h
	clang++ -c -o $@ src/word_card.cc $(debug_options)

$(debug_bin_dir)/debug_dictionary.o: src/dictionary.cc src/dictionary.h
	clang++ -c -o $@ src/dictionary.cc $(debug_options)

$(debug_bin_dir)/debug_operate_xml.o: src/operate_xml.cc src/operate_xml.h
	clang++ -c -o $@ src/operate_xml.cc $(debug_options)

debug_run:
	./$(debug_bin_dir)/debug

debug_clean:
	rm $(debug_bin_dir)/*
