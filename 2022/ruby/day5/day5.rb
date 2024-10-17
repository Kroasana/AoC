# What crate is at the top of each stack after moving containers one by one.
answer1 = ""
# What crate is at the top of each stack after moving containers in groups.
answer2 = ""

# Whether the input is at the container moving stage.
isMove = false
# Containers for the first task, where movement happens container by container .
containers = [[], [], [], [], [], [], [], [], [], []]
# Containers for the second task, where movement happens in sub-stacks.
containers2 = [[], [], [], [], [], [], [], [], [], []]

# From top to bottom, the stacked up containers on each stack.
# Then, a sequence of movements of containers between stacks.
f = File.open("input.txt", "r")
f.each_line do |line|
  if line.length <= 1 then
    isMove = true
    next
  end
  if isMove then
    tmp = line.split(' ')
    cnt = tmp[1].to_i
    src = tmp[3].to_i
    trg = tmp[5].to_i

    moving = containers2[src].shift(cnt).reverse
    moving.each do |container|
      containers2[trg].unshift container
    end
    
    moving = containers[src].shift(cnt)
    moving.each do |container|
      containers[trg].unshift container 
    end
    
    

  else
    x = line.split(' ')
    line.each_char.with_index do |char, index|
      if char >= 'A' && char <='Z' then
        cont = ((index - 1) /4) + 1
        containers[cont].push char
        containers2[cont].push char
      end
    end
  end
end
f.close

containers.each do |container|
  if container.size > 0 then
    answer1 += container[0]
  end
end

containers2.each do |container|
  if container.size > 0 then
    answer2 += container[0]
  end
end

# Write the output
File.open('output.txt', 'w') { |file| 
  file.write(answer1 , " ", answer2)
}