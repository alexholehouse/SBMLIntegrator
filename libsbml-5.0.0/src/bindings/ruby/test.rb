require 'test/unit'

test_base = "./test"

if ARGV.length() > 0
  for index in (0..ARGV.length())
    current = ARGV[index]
	hasNext = index + 1 < ARGV.length()
	if current == "-b" and hasNext
	  test_base = ARGV[index+1]
	elsif current == "-p" and hasNext
	  $LOAD_PATH << ARGV[index+1]
	end		
  end
end

Dir.chdir(test_base + "/..")

if RUBY_VERSION >= '1.9'
 testfiles = File.join(test_base + "/**", "Test*.rb")
 files = Dir::glob(testfiles)
 Test::Unit.setup_argv {files
  if files.size == 1
    $0 = File.basename(files[0])
  else
    $0 = files.to_s
  end
  files
 }
else
 Test::Unit::AutoRunner.run(RUBY_VERSION >= '1.8.3' ,test_base + '/',['--pattern=/Test.*\.rb\Z/'])
end
