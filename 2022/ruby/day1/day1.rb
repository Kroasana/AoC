# The input is lines consisting of separate calorie counts,
# divided by empty lines to separate the separate counts.
f = File.open("input.txt", "r")
# The highest sum of calories
answer1 = 0
# The sum of the three highest sums of calories.
answer2 = 0

sums = [0]
f.each_line do |line|
  if line.length <= 1 then
    sums.push(0)
  else
    sums[sums.size - 1] += line.to_i
  end
end
f.close

# Sort the sums in descending order (I know this isn't optimal time-wise)
sums = sums.sort_by{ |a| a }.reverse!
answer1 = sums[0]
answer2 = sums[0..2].sum

File.open('output.txt', 'w') { |file| 
  file.write(answer1 , " ", answer2)
}