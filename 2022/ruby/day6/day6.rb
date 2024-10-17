answer1 = 999999
answer2 = 999999

buffer = ""
buffer2 = ""
# Read through the input and do whatever is required with it
f = File.open("input.txt", "r")
f.each_line do |line|
  line.each_char.with_index do |char, index|
    buffer += char
    buffer2 += char
    if buffer.length == 4 then
      if buffer[0] != buffer[1] && buffer[0] != buffer[2] && buffer[0] != buffer[3]\
      && buffer[1] != buffer[2] && buffer[1] != buffer[3] && buffer[2] != buffer[3] then
        answer1 = index + 1 < answer1 ? index + 1 : answer1
      end
      buffer = buffer.slice(1..3)
    end

    if buffer2.length == 14 then
      flag = false
      buffer2.each_char.with_index do |bc, bi|
        buffer2.slice(bi+1..-1).each_char do |bc2|
          # print bc2
          flag = flag || bc == bc2
        end
      end
      unless flag then
        answer2 = index + 1 < answer2 ? index + 1 : answer2
      end
      # print buffer2 + " "
      buffer2 = buffer2.slice(1..13)
      # puts buffer2
    end
  end
end
f.close



# Write the output
File.open('output.txt', 'w') { |file| 
  file.write(answer1 , " ", answer2)
}