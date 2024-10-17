$answer1 = 0
$answer2 = 0

# Read through the input and do whatever is required with it
f = File.open("input.txt", "r")
f.each_line do |line|
  puts line
end
f.close



# Write the output
File.open('output.txt', 'w') { |file| 
  file.write($answer1 , " ", $answer2)
}