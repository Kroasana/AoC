# Characters a-z have priority 1-26, and A-Z have priority 27-52.
# The sum of priorities of letters that appear in both halves of a line.
answer1 = 0
# Consider splitting the input into groups of 3 consecutive lines
# The sum of priorities of letters that appear in all 3 lines of the group.
answer2 = 0
# Count the triplets and store the previous lines.
cnt = 1
bag1 = ""
bag2 = ""

def charToPriority(char)
  if char >= 'a' && char <='z' then
    char.ord - 'a'.ord + 1
  else
    char.ord - 'A'.ord + 27
  end
end

# Read through the input and do whatever is required with it
f = File.open("input.txt", "r")
f.each_line do |line|

  first, second = line.chars.each_slice(line.length / 2).map(&:join)
  first.each_char do |char|
    if second.include? char then
      answer1 += charToPriority(char)
      break
    end
    
  end

  case cnt
  when 0
    line.each_char do |char|
      if bag1.include?(char) && bag2.include?(char) then
        answer2 += charToPriority(char)
        break
      end
    end
  when 1
    bag1 = line
  when 2
    bag2 = line
  end
  cnt = (cnt + 1) % 3
end
f.close



# Write the output
File.open('output.txt', 'w') { |file| 
  file.write(answer1 , " ", answer2)
}