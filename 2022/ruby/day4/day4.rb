# Number of pairs of ranges where one is subsumed into the other.
answer1 = 0
answer2 = 0

# Input contains 2 pairs of range starts and ends.
f = File.open("input.txt", "r")
f.each_line do |line|
  first, second = line.split(',')
  fbeg = first.split('-')[0].to_i
  fend = first.split('-')[1].to_i
  sbeg = second.split('-')[0].to_i
  send = second.split('-')[1].to_i

  if ((fbeg <= sbeg && send <= fend) || (sbeg <= fbeg && fend <= send)) then
    answer1 += 1
  end
  if (fbeg <= sbeg && sbeg <= fend) || (fbeg <= send && send <= fend) || (sbeg <= fbeg && fbeg <= send) || (sbeg <= fend && fend <= send) then
    answer2 += 1
  end
end
f.close



# Write the output
File.open('output.txt', 'w') { |file| 
  file.write(answer1 , " ", answer2)
}