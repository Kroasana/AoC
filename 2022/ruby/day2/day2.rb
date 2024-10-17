# Picking Rock is 1 point, Paper is 2, Shears is 3, draw is 3, win is 6.
# The points in case X means picking Rock, Y means picking Paper, Z means picking Shears
answer1 = 0
# The points in case X means lose, Y means draw, Z means win
answer2 = 0

# The input is 2 letters - A/B/C for rock/paper/shear of opponent
# and X/Y/Z which is either rock/paper/shear or lose/draw/win depending on the task.
f = File.open("input.txt", "r")
f.each_line do |line|
  their = line.split[0].ord - 'A'.ord + 1
  mine = line.split[1].ord - 'X'.ord + 1
  # Add the points from the pick.
  answer1 += mine

  win = mine - their == 1 || mine - their == -2
  tie = mine == their
  # Add the points from the match result.
  if win then answer1 += 6
  elsif tie
    answer1 += 3
  end

  #Add the points from the match result
  answer2 += (mine - 1) * 3
  # Add the points from the pick
  if mine == 3 then # win
    answer2 += their + 1 == 4 ? 1 : their + 1    
  elsif mine == 2 then #tie
    answer2 += their
  else #lose
    answer2 += their - 1 == 0 ? 3 : their -1 
  end
end
f.close



# Write the output
File.open('output.txt', 'w') { |file| 
  file.write(answer1 , " ", answer2)
}